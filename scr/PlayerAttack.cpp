#include"PlayerAttack.h"

static const float ERASE_TIME = 18.0f;

// コンストラクタ
PlayerAttack::PlayerAttack(IWorld* world, const GSvector3& position) :
	Actor(world, "Bullet", position, BoundingSphere(1.2f)),
	timer_(0.0f){
}

// 更新
void PlayerAttack::onUpdate(float deltaTime) {
	timer_ += deltaTime;
	if (timer_ >= ERASE_TIME) dead();
}
//描画
void PlayerAttack::onDraw() const {
}

//衝突処理
void PlayerAttack::onCollide(Actor& actor) {
}