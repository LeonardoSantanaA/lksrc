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
                std::cout << "Enemy removed: " << enemy.GetName() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Exception during enemy removal: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Attempted to remove an enemy that is not in the list. Enemy name: " << enemy.GetName() << std::endl;
        }
    }


    const std::vector<Enemy*>& EnemyManager::GetEnemies() const {
        return mEnemies;
    }

    void EnemyManager::ClearEnemies() {
        mEnemies.clear();
    }

