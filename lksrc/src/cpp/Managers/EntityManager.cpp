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
	std::cout << "new entity. entities: " << GetEntityCount() << std::endl;
	mEntities.insert(std::make_pair(name, newEntity));
	mEntityCount++;
	return (mEntities[name] != nullptr);
}

bool EntityManager::CreateEntity(const std::string& name) {
	std::shared_ptr<GameEntity> newEntity = std::make_shared<GameEntity>(name);
	std::cout << "new entity. entities: " << GetEntityCount() << std::endl;
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
	
	std::cout << "trying get unknown type. entitymanager::createEntityType(). className: " << className << std::endl;
	return false;
	
}

void EntityManager::ParseEntities(const std::string& path) {
	TiXmlDocument xml;

	xml.LoadFile(path + ".lkobj");
	if (xml.Error()) {
		std::cout << "failed to load entitymanager::parseentities in " << path + ".lkobj" << " - " << xml.ErrorDesc() << std::endl;
		return;
	}
	else {
		std::cout << "reading entities from " << path + ".lkobj" << std::endl;
	}

	TiXmlElement* root = xml.RootElement();
	int tileSize = 1;

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("config")) {
			e->Attribute("tilesize", &tileSize);
			std::cout << "tileSize of entities:" << tileSize << std::endl;
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
			std::cout << "configuring entity: " << newEntityName << std::endl;
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
			std::cout << "new entity parsed, id: " << newEntityName << std::endl;
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

				std::cout << "Entity removed (" << name << "). Entities: " << mEntityCount << std::endl;
			}
			catch (const std::exception& e) {
				std::cerr << "Exception during entity removal: " << e.what() << std::endl;
			}
		}
		else {
			std::cerr << "Warning: Entity exists but is null. Key: " << name << std::endl;
		}
	}
	else {
		std::cerr << "Trying to remove entity that doesn't exist. EntityManager::RemoveEntity(). Key: " << name << std::endl;
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
			std::cerr << "Unknown entity in EntityManager::UpdateAllEntities(). Key: " << key << std::endl;
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
			std::cout << "unknown entity render entitymanager::renderlayerentity(): " << index << std::endl;
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
	mEntities.erase(mEntities.begin(), mEntities.end());
	mEntityCount = 0;
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}

long long EntityManager::GetEntityCount() const{
	return mEntityCount;
}

