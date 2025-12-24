#ifndef LINE_H_
#define LINE_H_

#include <gslib.h>

// 線分クラス
class Line {
public:
	// コンストラクタ
	Line(const GSvector3& start, const GSvector3& end);
	// デフォルトコンストラクタ
	Line();
public:
	// 始点
	GSvector3	start;
	// 終点
	GSvector3	end;
};

#endif
