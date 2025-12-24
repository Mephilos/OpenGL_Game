#include "TpsCamera.h"
#include "IWorld.h"

TpsCamera::TpsCamera(IWorld* world) :
	Actor(world, "Camera", {0.0f, 0.0f, 0.0f}, BoundingSphere(1.0)),
	velocity_(0.0f, 0.0f, 0.0f) {
}

// 更新
void TpsCamera::onUpdate(float) {
	auto player = world_->findActor("Player");
	if (player == nullptr)return;

	target_ = player->getPosition() + GSvector3(0.0f, 2.0f, 0.0f);
	target_ += player->getRotate().getAxisZ()*2.0f;
	position_ = GSvector3(0.0f, 2.0f, -6.0f) * player->getPose();
	rotate_.identity().setAxisZ(target_ - position_).nomalizeAxisZ();
}

// 描画
void TpsCamera::onDraw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		position_.x, position_.y, position_.z,
		target_.x, target_.y, target_.z,
		0.0f, 1.0f, 0.0f
	);
}

// カメラの移動
void TpsCamera::move(
	const GSvector3& restPosition,
	float stiffness,
	float friction,
	float mass
) {
	// バネの伸び具合を計算
	GSvector3 stretch = position_ - restPosition;
	// バネの力を計算
	GSvector3 force = -stiffness * stretch;
	// 加速度を計算
	GSvector3 acceleration = force / mass;
	// 移動量を計算
	velocity_ = friction * (velocity_ + acceleration);
	// 座標の更新
	position_ += velocity_;
}
