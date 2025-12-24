#include"AnimatedMesh.h"

//コンストラクタ
AnimatedMesh::AnimatedMesh(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion) :
	mesh_(mesh),
	skeleton_(skeleton),
	animation_(animation, motion) {
}

//更新
void AnimatedMesh::update(float deltaTime) {
	animation_.update(deltaTime);
}

//描画
void AnimatedMesh::draw() const {
	gsDisable(GS_CALC_SKELETON);
	gsEnable(GS_SKIN_MESH);
	gsBindSkeleton(skeleton_);
	gsSetMatrixSkeleton(matrices_.data());
	gsDrawMesh(mesh_);
}

//モーションの変更
void AnimatedMesh::changeMotion(GSuint motion) {
	animation_.changeMotion(motion);
}

//スケルトンの変換行列を計算
void AnimatedMesh::calculate(const GSmatrix4& world) {
	gsBindSkeleton(skeleton_);
	gsCalculateSkeleton(&world, animation_.getMatrices().data(), matrices_.data());
}

//変換行列を取得
const Matrices& AnimatedMesh::getMatrices() const {
	return matrices_;
}

//モーション終了時間を返す
float AnimatedMesh::getMotionEndTime() const {
	return animation_.getEndTime();
}