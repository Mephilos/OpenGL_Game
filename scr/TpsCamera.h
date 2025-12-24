#ifndef TPS_CAMERA_H_
#define TPS_CAMERA_H_

#include "Actor.h"

class TpsCamera : public Actor {
public:
	// コンストラクタ
	explicit TpsCamera(IWorld* world);
private:
	// 更新
	virtual void onUpdate(float deltaTime) override;
	// 描画
	virtual void onDraw() const override;
	// カメラの移動
	void move(
		const GSvector3& restPosition,
		float stiffness,
		float friction,
		float mass
	);

private:
	// 移動量
	GSvector3 velocity_;
	// 目標位置
	GSvector3 target_;
};

#endif
