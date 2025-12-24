#include "Line.h"

// コンストラクタ
Line::Line(const GSvector3& start, const GSvector3& end) :
  start(start), end(end) {
}

// デフォルトコンストラクタ
Line::Line() :
	Line({ 0.0f, 0.0f ,0.0f }, { 0.0f, 0.0f, 0.0f }) {
}
