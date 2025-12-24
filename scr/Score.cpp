#include "Score.h"
#include "NumberTexture.h"
#include <algorithm>
#include <gslib.h>
#include"Resource.h"

// コンストラクタ
Score::Score(int score) : score_(score) {
}

// スコアの加算
void Score::add(int score)
{
	score_ = std::min(score_ + score, 999);
}

// スコアの描画
void Score::draw() const {
	static const GScolor color(0.0f, 0.0f, 0.0f, 1.0f);

	static const GSrect textRect(0, 64, 128, 128);
	static const GSvector2 shadowTextPos(363, 13);
	static const GSvector2 textPos(360, 10);
	gsDrawSprite2D(Texture_Text, &shadowTextPos, &textRect, 0, &color, 0, 0);
	gsDrawSprite2D(Texture_Text, &textPos, &textRect, 0, 0, 0, 0);

	static const NumberTexture number(Texture_Number, 32, 64);
	number.draw(GSvector2(516, 14), score_, 3, '0', &color);
	number.draw(GSvector2(512, 10), score_, 3);
}

// スコアの取得
int Score::get() const {
	return score_;
}
