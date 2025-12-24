#include "Camera.h"
#include "IWorld.h"

// コンストラクタ
Camera::Camera(IWorld* world) :
	Actor(world, "Camera", { 0.0f, 0.0f, 0.0f }, BoundingSphere(1.0f)) {
}

// 更新
void Camera::onUpdate(float deltaTime) {
	(void)deltaTime;
	// プレーヤを検索
	auto player = world_->findActor("Player");
	// プレーヤがいない
	if (player == nullptr) return;

	// プレーヤの座標を取得
	position_ = player->getPosition() + GSvector3(0.0f, 2.0f, 0.0f);
	// プレーヤの回転（向き）を取得
	rotate_ = player->getRotate();
}

// 描画
void Camera::onDraw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(getPose().convertViewRH());
}
