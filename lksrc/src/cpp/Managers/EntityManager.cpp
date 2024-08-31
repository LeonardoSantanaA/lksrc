#include "Managers/EntityManager.h"
#include "Core/Engine.h"
#include "Entities/Player.h"
#include "../../thirdpart/TinyXML/includes/tinyxml.h"
#include "Camera/Camera.h"
#include "Map/MapParser.h"

EntityManager* EntityManager::mInstance = nullptr;

EntityManager* EntityManager::GetInstance() {
	if (!mInstance) {
		mInstance = new EntityManager;
	}

	return mInstance;
}

bool EntityManager::CreateEntity() {
	std::string name = "entity_" + std::to_string(GetEntityCount());
	std::shared_ptr<GameEntity> newEntity = std::make_shared<GameEntity>(name);
	SDL_Log("new entity. entities: %d", static_cast<int>(GetEntityCount()));
	mEntities.insert(std::make_pair(name, newEntity));
	mEntityCount++;
	return (mEntities[name] != nullptr);
}

bool EntityManager::CreateEntity(const std::string& name) {
	std::shared_ptr<GameEntity> newEntity = std::make_shared<GameEntity>(name);
	SDL_Log("new entity. entities: %d", static_cast<int>(GetEntityCount()));
	mEntities.insert(std::make_pair(name, newEntity));
	mEntityCount++;
	return (mEntities[name] != nullptr);
}


void EntityManager::RegisterType(const std::string& className, std::function < bool() > creator) {
	mTypeRegistry[className] = creator;
}

bool EntityManager::CreateEntityType(const std::string& className) {
	auto type = mTypeRegistry.find(className);
	if (type != mTypeRegistry.end()) {
		return type->second();
	}
	
	SDL_Log("trying get unknown type. entitymanager::createEntityType(). className: %s", className.c_str());
	return false;
	
}

void EntityManager::ParseEntities(const std::string& path) {
	TiXmlDocument xml;

	xml.LoadFile(path + ".lkobj");
	if (xml.Error()) {
		SDL_Log("failed to load entitymanager::parseentities in %s.lkobj - error: %s", path.c_str(), xml.ErrorDesc());
		return;
	}
	else {
		SDL_Log("reading entities from %s.lkobj", path.c_str());
	}

	TiXmlElement* root = xml.RootElement();
	int tileSize = 1;

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("config")) {
			e->Attribute("tilesize", &tileSize);
		}

		if (e->Value() == std::string("entity")) {
			int x = 0, y = 0, w = 0, h = 0, layer=0, flip = 0, animated=0;
			double scale = 0;
			const char* entityType = nullptr;
			const char* resource = nullptr;

			entityType = e->Attribute("type");
			resource = e->Attribute("resource");
			e->Attribute("animated", &animated);
			e->Attribute("layer", &layer);
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			e->Attribute("w", &w);
			e->Attribute("h", &h);
			e->Attribute("scale", &scale);
			e->Attribute("flip", &flip);

			CreateEntityType(entityType);
			std::string newEntityName = "entity_" + std::to_string(GetEntityCount() - 1);
			SDL_Log("configuring entity: %s", newEntityName.c_str());
			std::shared_ptr<GameEntity> newEntity = GetEntityRef<GameEntity>(newEntityName);

			newEntity->SetPosition(x * tileSize, y * tileSize);
			
			if(w > 0 && h > 0 && scale > 0) newEntity->SetDimensions(w, h, static_cast<float>(scale));

			if (flip == 1) {
				newEntity->FlipHorizontal();
			}
			else if (flip == 2) {
				newEntity->FlipVertical();
			}

			switch (layer) {
				case 0:
					newEntity->SetRenderLayer(RenderEntityLayer::BACKGROUND);
					break;

				case 1:
					newEntity->SetRenderLayer(RenderEntityLayer::MIDDLEGROUND);
					break;

				case 2:
					newEntity->SetRenderLayer(RenderEntityLayer::FOREGROUND);
					break;

				case 3:
					newEntity->SetRenderLayer(RenderEntityLayer::END);
					break;

				default:
					newEntity->SetRenderLayer(RenderEntityLayer::BACKGROUND);
					break;
			}

			newEntity->Init();
			SDL_Log("new entity parsed, id: %s", newEntityName.c_str());
		}
	}
}



void EntityManager::RemoveEntity(const std::string& name) {
	auto entity = mEntities.find(name);
	if (entity != mEntities.end()) {
		if (entity->second) {
			try {
				mEntities.erase(entity);
				mEntityCount--;

				SDL_Log("Entity removed -> %s.Entities: %d", name.c_str(), static_cast<int>(mEntityCount));
			}
			catch (const std::exception& e) {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Exception during entity removal: %s", e.what());
			}
		}
		else {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Warning: Entity exists but is null. Key: %s", name.c_str());
		}
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Trying to remove entity that doesn't exist. EntityManager::RemoveEntity(). Key: %s", name.c_str());
	}
}



void EntityManager::UpdateAllEntities() {
	std::vector<std::shared_ptr<GameEntity>> entitiesToUpdate;
	entitiesToUpdate.reserve(mEntities.size()); 

	auto camera = Camera::GetInstance();

	for (const auto& [key, entity] : mEntities) {
		if (entity) {
			if (camera) { //if camera exists, update only entities colliding with camera
				if (camera->IsInCamera(*entity, 100, 100)) {
					entitiesToUpdate.push_back(entity);
				}
			}
			else {
				entitiesToUpdate.push_back(entity);
			}
			
		}
		else {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unknown entity in EntityManager::UpdateAllEntities(). Key: %s", key.c_str());
		}
	}

	for (const auto& entity : entitiesToUpdate) {
		if (entity) {
			entity->Update();
		}
	}
}

void EntityManager::RenderLayerEntity(const RenderEntityLayer& layer) {
	size_t index = 0;
	auto camera = Camera::GetInstance();
	for (auto it = mEntities.begin(); it != mEntities.end(); it++) {
		if (mEntities[it->first] && layer == mEntities[it->first]->GetRenderLayer()) {
			if (camera) {
				if (camera->IsInCamera(*mEntities[it->first], 50, 50)) {
					mEntities[it->first]->Render();
				}
			}
			else {
				mEntities[it->first]->Render();
			}
		}
		else if (!mEntities[it->first]) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "unknown entity render entitymanager::renderlayerentity(): %d", static_cast<int>(index));
		}

		index++;

	}
}

void EntityManager::RenderAllEntities() {
	RenderLayerEntity(RenderEntityLayer::BACKGROUND);
	RenderLayerEntity(RenderEntityLayer::MIDDLEGROUND);
	RenderLayerEntity(RenderEntityLayer::FOREGROUND);
	RenderLayerEntity(RenderEntityLayer::END);
}

void EntityManager::DeleteAllEntities() {
	mEntities.clear();
	mEntityCount = 0;
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}

long long EntityManager::GetEntityCount() const{
	return mEntityCount;
}

