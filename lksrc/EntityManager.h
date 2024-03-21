#pragma once

#include <string>
#include <SDL.h>
#include <memory>
#include <unordered_map>
#include "GameEntity.h"

class EntityManager {
public:
	static EntityManager* GetInstance();

	bool CreateEntity(const std::string& name, SDL_Renderer* renderer);

	std::shared_ptr<GameEntity> GetEntityRef(const std::string& name);

	void RemoveEntity(const std::string& name);

	void UpdateAllEntities();
	void RenderAllEntities();

	void DeleteAllEntities();

	long long GetEntityCount() const;

private:
	EntityManager(): mEntityCount(0) {};
	static EntityManager* mInstance;


	std::unordered_map<std::string, std::shared_ptr<GameEntity>> mEntities;
	long long mEntityCount;
	
};