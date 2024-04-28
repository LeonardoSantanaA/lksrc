#include "EntityManager.h"

EntityManager* EntityManager::mInstance = nullptr;

EntityManager* EntityManager::GetInstance() {
	if (!mInstance) {
		mInstance = new EntityManager;
	}

	return mInstance;
}


bool EntityManager::CreateEntity(const std::string& name, SDL_Renderer* renderer) {
	std::shared_ptr<GameEntity> newEntity = std::make_shared<GameEntity>(name, renderer);
	std::cout << "new entity. entities: " << EntityManager::GetInstance()->GetEntityCount() << std::endl;
	mEntities.insert(std::make_pair(name, newEntity));
	mEntityCount++;
	return (mEntities[name] != nullptr);
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

void EntityManager::RenderAllEntities() {
	size_t index = 0;
	for (auto it = mEntities.begin(); it != mEntities.end(); it++) {
		if (mEntities[it->first]) {
			mEntities[it->first]->Render();
		}
		else if (!mEntities[it->first]) {
			std::cout << "unknown entity render entitymanager::renderallentities(): " << index << std::endl;
		}
		index++;
	}
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