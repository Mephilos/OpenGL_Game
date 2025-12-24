#include "BoundigShphere.h"

BoundingSphere::BoundingSphere(const GSvector3& center, float radius) :
	center(center),
	radius(radius) {
}

BoundingSphere::BoundingSphere(float radius) :
  BoundingSphere({ 0.0f, 0.0f, 0.0f }, radius) {
}

BoundingSphere BoundingSphere::translate(const GSvector3& position) const {
	return { center + position, radius };
}

BoundingSphere BoundingSphere::transform(const GSmatrix4& matrix) const {
	return { matrix.transform(center), radius * matrix.getScale().y };
}

bool BoundingSphere::intersects(const BoundingSphere& other) const {
	return gsCollisionSphereAndSphere(&center, radius, &other.center, other.radius) == GS_TRUE;
}

void BoundingSphere::draw() const {
	glPushMatrix();
		glTranslatef(center.x, center.y, center.z);
		glutWireSphere(radius, 16, 16);
	glPopMatrix();
}
