#include"EnemyGenerator.h"
#include"IWorld.h"
#include"Enemy.h"
#include"ActorGroup.h"

//コンストラクタ
EnemyGenerator::EnemyGenerator(IWorld* world, const GSvector3& position) :
	Actor(world, "EnemyGenerator", position, BoundingSphere(0.0f)){
	GSvector3 vec = GSvector3(0, 0, 0) - position;
	(ABS(vec.x) >= ABS(vec.z)) ?
		rotate_.setAxisZ(GSvector3(SGN(vec.x), 0, 0)) :
		rotate_.setAxisZ(GSvector3(0, 0, SGN(vec.z)));
	rotate_.nomalizeAxisZ();
}

//更新
void EnemyGenerator::onUpdate(float deltaTime) {
	if (gsRand(0, 2000) == 0) {
		world_->addActor(ActorGroup::Enemy, std::make_shared<Enemy>(world_, position_, rotate_.getAxisZ()));
	}
}

//描画
void EnemyGenerator::onDraw() const{
}

//衝突処理
void EnemyGenerator::onCollide(Actor& actor) {
}