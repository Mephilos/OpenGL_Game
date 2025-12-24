#ifndef LIGHT_H_
#define LIGHT_H_

#include "Actor.h"

class Light : public Actor {
public:
	// コンストラクタ
	Light(IWorld* world, const GSvector3& position);
private:
	// 描画
	virtual void onDraw() const override;
};

#endif

