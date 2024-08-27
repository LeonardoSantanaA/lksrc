#pragma once

#include <string>
#include <SDL.h>
#include <memory>
#include <unordered_map>
#include "Managers/GameEntity.h"
#include "Graphics/RenderEntityLayer.h"
#include <mutex>

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
	// static Register<Player> registerPlayer("PLAYER", true);
	//-> OBS: this boolean param can be set to true (default = false) if the name is static
	//if the boolean param is false, the type name will be automatic generate
	// This allows you to call:
	// EntityManager::GetInstance()->CreateEntityType("PLAYER");
	bool CreateEntityType(const std::string& className);

	//load entities from .tml file
	//example of .tml file:
	// //
	//<?xml version="1.0" encoding="UTF-8"?>
	//<Objects>
	//	< object type = "PLAYER" layer = "0" x = "450" y = "10" w = "32 h="32" scale="1" flip="0"/>
	//	< / Objects
	//
	//You can override Init() function in your entity, will call this function after constructor
	void ParseEntities(const std::string& path);

	//get a shared_ptr of a specific entity, using template
	//Ex: std::shared_ptr<GameEntity> enemy = EntityManager::GetInstance()->GetEntityRef<GameEntity>("zombie");
	//or: std::shared_ptr<Player> player = EntityManager::GetInstance()->GetEntityRef<Player>("PLAYER");
	template <typename T>
	std::shared_ptr<T> GetEntityRef(const std::string& name) const {
		auto it = mEntities.find(name);
		if (it != mEntities.end()) {
			std::shared_ptr<T> entity = std::dynamic_pointer_cast<T>(it->second);
			if (entity) {
				return entity;
			}
			else {
				std::cout << "Entity found but wrong type. Key: " << name << std::endl;
				return nullptr;
			}
		}
		else {
			std::cout << "Entity not found. Key: " << name << std::endl;
			return nullptr;
		}
	}

	//remove a specific entity
	void RemoveEntity(const std::string& name);

	//update all entities in game
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

	inline std::shared_ptr<const std::unordered_map<std::string, std::shared_ptr<GameEntity>>> GetEntities() const {
		return std::make_shared<const std::unordered_map<std::string, std::shared_ptr<GameEntity>>>(mEntities);
	}

private:
	EntityManager(): mEntityCount(0) {};
	static EntityManager* mInstance;
	std::unordered_map<std::string, std::shared_ptr<GameEntity>> mEntities;
	std::unordered_map<std::string, std::function<bool()>> mTypeRegistry;
	long long mEntityCount;

	//add template entity when register
	template <typename T>
	void AddEntity(const std::string& name, std::shared_ptr<T> entity) {
		mEntities[name] = std::static_pointer_cast<GameEntity>(entity);
	}

	template<class Type>
	friend class Register;
};

template<class Type>
class Register {
public:
	Register(const std::string& className, bool staticName = false) {
		EntityManager::GetInstance()->RegisterType(className, [staticName, className]() {
			auto entityManager = EntityManager::GetInstance();
			std::string name = "entity_" + std::to_string(entityManager->GetEntityCount());;
			if (staticName) {
				name = className;
			}
		
			std::shared_ptr<Type> newEntity = std::make_shared<Type>(name);
			entityManager->AddEntity(name, newEntity);
			entityManager->mEntities.insert(std::make_pair(name, newEntity));
			entityManager->mEntityCount++;
		
			std::cout << "new type instantiate. name: " << name << std::endl;
			return (entityManager->mEntities[name] != nullptr);
			});
	}
};