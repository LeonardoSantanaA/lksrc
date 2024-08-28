#include "Managers/GameEntity.h"
#include "Entities/Enemies/EnemyHit.h"

class DeadFire : public GameEntity {
public:
	DeadFire(const std::string& name);
	inline void SetDir(int dir) {
		mDir = dir; 
		if (mDir == -1) { 
			FlipHorizontal(); 
		} 
	}

	virtual void Update() override;

private:
	int mDir;
	float mVelocity;
	EnemyHit mHit;
};