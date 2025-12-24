#include "Light.h"

// コンストラクタ
Light::Light(IWorld* world, const GSvector3& position) :
	Actor(world, "Light", position, BoundingSphere()) {
}

// 描画
void Light::onDraw() const {
	static const float ambient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const float diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float position[] = { position_.x, position_.y, position_.z, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}