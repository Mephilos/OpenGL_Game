#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include <gslib.h>

class BoundingSphere {
public:
	BoundingSphere(const GSvector3& center, float radius);

	explicit BoundingSphere(float radius = 0.0f);

	BoundingSphere translate(const GSvector3& position) const;

	BoundingSphere transform(const GSmatrix4& matrix) const;

	bool intersects(const BoundingSphere& other) const;

	void draw() const;

public:
	// íÜêSç¿ïW
	GSvector3	center;
	// îºåa
	float			radius;
};

#endif
