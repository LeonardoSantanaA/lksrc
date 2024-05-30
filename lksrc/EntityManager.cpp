#include "EntityManager.h"
#include "Engine.h"
#include "Player.h"
#include "thirdpart/TinyXML/tinyxml.h"

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
	std::cout << "new entity. entities: " << EntityManager::GetInstance()->GetEntityCount() << std::endl;
	mEntities.insert(std::make_pair(name, newEntity));
	mEntityCount++;
	return (mEntities[name] != nullptr);
}

bool EntityManager::CreateEntity(const std::string& name) {
	std::shared_ptr<GameEntity> newEntity = std::make_shared<GameEntity>(name);
	std::cout << "new entity. entities: " << EntityManager::GetInstance()->GetEntityCount() << std::endl;
	mEntities.insert(std::make_pair(name, newEntity));
	mEntityCount++;
	return (mEntities[name] != nullptr);
}

/*
bool EntityManager::CreateEntity(const EntityType& type) {
	switch (type) {
	case PLAYER:
	{
		std::string name = "player";
		std::shared_ptr<Player> newPlayer = std::make_shared<Player>(name);
		mEntities.insert(std::make_pair(name, newPlayer));
		mEntityCount++;
		std::cout << "new player instantiate. type: " << name << std::endl;
		return (mEntities[name] != nullptr);
	}

	default:
		std::cout << "type not found. entitymanager::createentity()." << std::endl;
		return false;
	}
}
*/

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

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
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
			std::shared_ptr<GameEntity> newEntity = GetEntityRef(newEntityName);
			newEntity->SetPosition(x, y);
			
			if(w > 0 && h > 0 && scale > 0) newEntity->SetDimensions(w, h, scale);

			if (flip == 1) {
				newEntity->FlipHorizontal();
			}
			else if (flip == 2) {
				newEntity->FlipVertical();
			}

			if (layer == 0) {
				newEntity->SetRenderLayer(RenderEntityLayer::BACKGROUND);
			}
			else if (layer == 1) {
				newEntity->SetRenderLayer(RenderEntityLayer::MIDDLEGROUND);
			}
			else if (layer == 2) {
				newEntity->SetRenderLayer(RenderEntityLayer::FOREGROUND);
			}
			else if (layer == 3) {
				newEntity->SetRenderLayer(RenderEntityLayer::END);
			}

			newEntity->Init();
			

			std::cout << "new entity parsed, id: " << newEntityName << std::endl;
		}
	}
}

std::shared_ptr<GameEntity> EntityManager::GetEntityRef(const std::string& name) {
	auto entity = mEntities.find(name);
	if (entity != mEntities.end()) {
		return (mEntities[name]);
	}
	else {
		std::cout << "trying get unknown entity. entitymanager::getentityref(). key: " << name << std::endl;
		return nullptr;
	}

}

void EntityManager::RemoveEntity(const std::string& name) {
	auto entity = mEntities.find(name);
	if (entity != mEntities.end()) {
		std::cout << "entity removed. entities: " << EntityManager::GetInstance()->GetEntityCount() << std::endl;
		mEntities.erase(entity);
		mEntityCount--;
	}
	else {
		std::cout << "trying remove entity that doesnt exist. entitymanager::removeentity(). key: " << name << std::endl;
	}
	
	
}

void EntityManager::UpdateAllEntities() {
	size_t index = 0;
	for (auto it = mEntities.begin(); it != mEntities.end(); it++) {
		if (mEntities[it->first]) {
			mEntities[it->first]->Update();
		}
		else {
			std::cout << "unknown entity update entitymanager::updateallentities(): " << index << std::endl;
		}
		index++;
	}
}


void EntityManager::RenderLayerEntity(const RenderEntityLayer& layer) {
	size_t index = 0;
	for (auto it = mEntities.begin(); it != mEntities.end(); it++) {
		if (mEntities[it->first] && layer == mEntities[it->first]->GetRenderLayer()) {
			mEntities[it->first]->Render();
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

