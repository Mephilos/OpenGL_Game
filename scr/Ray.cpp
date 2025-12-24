#include "Ray.h"

Ray::Ray(const GSvector3& position, const GSvector3& direction) :
	position(position), direction(direction) {
}

Ray::Ray() :
	Ray({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }) {
}
