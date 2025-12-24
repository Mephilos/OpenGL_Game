#ifndef RAY_H_
#define RAY_H_

#include <gslib.h>

class Ray {
public:
	// コンストラクタ
	Ray(const GSvector3& position, const GSvector3& direction);
	// デフォルトコンストラクタ
	Ray();
public:
	// 座標
	GSvector3 position;
	// 方向
	GSvector3 direction;
};

#endif

