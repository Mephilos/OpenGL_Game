#ifndef CAMERA_H_
#define CAMERA_H_

#include "Actor.h"

class Camera : public Actor {
public:
	// コンストラクタ
	explicit Camera(IWorld* world);
private:
	// 更新
	virtual void onUpdate(float deltaTime) override;
	// 描画
	virtual void onDraw() const override;
};


#endif
