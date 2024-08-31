#include "Managers/EnemyManager.h"
#include "Managers/EntityManager.h"

EnemyManager* EnemyManager::mInstance;
std::vector<Enemy*> EnemyManager::mEnemies;

 EnemyManager* EnemyManager::GetInstance() {
     if (!mInstance) {
        mInstance = new EnemyManager();
     }
        return mInstance;
    }

    void EnemyManager::Clean() {
        delete mInstance;
        mInstance = nullptr;
    }

    void EnemyManager::AddEnemy(Enemy* enemy) {
        mEnemies.push_back(enemy);
    }

    void EnemyManager::RemoveEnemy(Enemy& enemy) {
        auto it = std::find(mEnemies.begin(), mEnemies.end(), &enemy);

        if (it != mEnemies.end()) {
            try {
                mEnemies.erase(it);   
                SDL_Log("Enemy removed: '%s'", enemy.GetName().c_str());
            }
            catch (const std::exception& e) {
                SDL_Log("Exception during enemy removal: '%s'", e.what());
            }
        }
        else {
            SDL_Log("Attempted to remove an enemy that is not in the list. Enemy name: '%s'", enemy.GetName().c_str());;
        }
    }


    const std::vector<Enemy*>& EnemyManager::GetEnemies() const {
        return mEnemies;
    }

    void EnemyManager::ClearEnemies() {
        mEnemies.clear();
    }

