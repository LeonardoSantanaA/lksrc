#pragma once

#include <string>
#include <SDL.h>
#include <memory>
#include <unordered_map>
#include "GameEntity.h"
#include "RenderEntityLayer.h"

/*
enum EntityType {
	PLAYER = 0,

};
*/

class EntityManager {
public:
	//entity manager is the object factory of lksrc, use CreateEntity() passing or not a specific name.
	static EntityManager* GetInstance();

	//create a new entity without a name, it will be created with a name like "entity_[index]"
	bool CreateEntity();

	//create a new entity with a specific name.
	bool CreateEntity(const std::string& name);

	//bool CreateEntity(const EntityType& type);

	// Add a new specific type to your entity manager, such as a player, enemy, etc.
	// Pass the string name of the entity type you want to instantiate as a parameter.
	// Add the following code to the cpp file of the entity that inherits from the GameEntity class:
	// For example:
	// static Register<Player> registerPlayer("PLAYER");
	// This allows you to call:
	// EntityManager::GetInstance()->CreateEntityType("PLAYER");
	bool CreateEntityType(const std::string& className);

	//get a shared_ptr of a specific entity.
	std::shared_ptr<GameEntity> GetEntityRef(const std::string& name);

	//remove a specific entity
	void RemoveEntity(const std::string& name);

	void UpdateAllEntities();

	//render a specific RenderEntityLayer
	void RenderLayerEntity(const RenderEntityLayer& layer);
	//render all layers in order of RenderEntityLayer
	void RenderAllEntities();

	void DeleteAllEntities();

	//return the count of existing entities
	long long GetEntityCount() const;

	//this function register the class of a unherited class to allows instatiate
	void RegisterType(const std::string& className, std::function < bool() > creator);

private:
	EntityManager(): mEntityCount(0) {};
	static EntityManager* mInstance;
	std::unordered_map<std::string, std::shared_ptr<GameEntity>> mEntities;
	std::unordered_map<std::string, std::function<bool()>> mTypeRegistry;
	long long mEntityCount;

	template<class Type>
	friend class Register;
};

template<class Type>
class Register {
public:
	Register(const std::string& className) {
		EntityManager::GetInstance()->RegisterType(className, []() {
			auto entityManager = EntityManager::GetInstance();
			std::string name = "entity_" + std::to_string(entityManager->GetEntityCount());
			std::shared_ptr<Type> newEntity = std::make_shared<Type>(name);
			entityManager->mEntities.insert(std::make_pair(name, newEntity));
			entityManager->mEntityCount++;
			std::cout << "new type instantiate. name: " << name << std::endl;
			return (entityManager->mEntities[name] != nullptr);
			});
	}
};