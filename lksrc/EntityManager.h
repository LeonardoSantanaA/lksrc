#pragma once

#include <string>
#include <SDL.h>
#include <memory>
#include <unordered_map>
#include "GameEntity.h"
#include <unordered_map>

enum EntityType {
	PLAYER = 0,

};

class EntityManager {
public:
	//entity manager is the object factory of lksrc, use CreateEntity() passing or not a specific name.
	static EntityManager* GetInstance();

	//create a new entity without a name, it will be created with a name like "entity_INDEX"
	bool CreateEntity();

	//create a new entity with a specific name.
	bool CreateEntity(const std::string& name);

	//add a new specific type for your entity manager, like a player, enemy etc.
	//parse in the param the enum value of type of entity which you want to instantiate
	//add in the enum "EntityType" in the EntityManager.h the name of a entity that you create
	//and add in this function the return of this specific type
	bool CreateEntity(const EntityType& type);

	//get a shared_ptr of a specific entity.
	std::shared_ptr<GameEntity> GetEntityRef(const std::string& name);

	//remove a specific entity
	void RemoveEntity(const std::string& name);

	void UpdateAllEntities();

	void RenderAllEntities();

	void DeleteAllEntities();

	//return the count of existing entities
	long long GetEntityCount() const;

private:
	EntityManager(): mEntityCount(0) {};
	static EntityManager* mInstance;

	std::unordered_map<std::string, std::shared_ptr<GameEntity>> mEntities;
	long long mEntityCount;
	
};