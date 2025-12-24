#include"Animation.h"

//コンストラクタ
Animation::Animation(GSuint animation, GSuint motion) :
	animation_(animation),
	motion_(motion),
	motionTimer_(0.0f),
	prevMotion_(motion),
	prevMotionTimer_(0.0f),
	lerpTimer_(0.0f) {
	update(0.0f);
}

//更新
void Animation::update(float deltaTime) {
	motionTimer_ += deltaTime;
	lerpTimer_ = std::min(lerpTimer_ + deltaTime, LERP_TIME);
	gsCalculateAnimationLerp(
		animation_, prevMotion_, prevMotionTimer_,
		animation_, motion_, motionTimer_,
		lerpTimer_ / LERP_TIME,
		matrices_.data());
}

//モーションの変更
void Animation::changeMotion(GSuint motion) {
	if (motion_ == motion)return;
	prevMotion_ = motion_;
	prevMotionTimer_ = motionTimer_;
	motion_ = motion;
	motionTimer_ = 0.0f;
	lerpTimer_ = 0.0f;
}

//再生中のモーション番号を返す
GSuint Animation::getMotion() const {
	return motion_;
}

//ボーン数を返す
GSuint Animation::getBoneCount() const {
	return gsGetAnimationNumBones(animation_, motion_);
}

//終了時間を返す
GSuint Animation::getEndTime() const {
	return gsGetEndAnimationTime(animation_, motion_);
}

//変換行列を取得
const Matrices& Animation::getMatrices() const {
	return matrices_;
}