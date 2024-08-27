#include "Managers/GameEntity.h"
#include "Entities/Enemies/EnemyHit.h"

class DeadFire : public GameEntity {
public:
	DeadFire(const std::string& name);
	inline void SetDir(int dir) { mDir = dir; }

	virtual void Update() override;

private:
	int mDir;
	float mVelocity;
	EnemyHit mHit;
};