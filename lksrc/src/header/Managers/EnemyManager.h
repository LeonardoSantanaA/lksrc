#pragma once

#include <vector>
#include "Entities/Enemies/Enemy.h"

class EnemyManager {
public:
    static EnemyManager* GetInstance();
    static void Clean();

    void AddEnemy(Enemy* enemy);

    void RemoveEnemy(Enemy& enemy);

    const std::vector<Enemy*>& GetEnemies() const;

    void ClearEnemies();

private:
    EnemyManager() = default;

    static EnemyManager* mInstance;
    static std::vector<Enemy*> mEnemies;
};
