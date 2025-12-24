#include"Time.h"
#include<gslib.h>
#include"NumberTexture.h"
#include"Resource.h"

//コンストラクタ
Time::Time() :
	restTime_(0),
	isTimeUp_(true){
}

//コンストラクタ
Time::Time(float restTime) :
	restTime_(restTime),
	isTimeUp_(false){
}

//更新
void Time::update(float deltaTime) {
	if (isTimeUp_) return;

	restTime_ -= deltaTime / 60.0f;

	if (restTime_ <= 0.0f) {
		restTime_ = 0.0f;
		isTimeUp_ = true;
	}
}

//描画
void Time::draw() const {
	static const GScolor black(0, 0, 0, 1);

	static const GSrect textRect(0, 0, 128, 64);
	static const GSvector2 shadowTextPos(703, 13);
	static const GSvector2 textPos(700, 10);
	gsDrawSprite2D(Texture_Text, &shadowTextPos, &textRect, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Text, &textPos, &textRect, 0, 0, 0, 0);

	static const NumberTexture number(Texture_Number, 32, 64);
	static const GSvector2 numPos(850, 10);
	static const GSvector2 shadowNumPos(853, 13);
	static const GSrect endTextRect(0, 128, 128, 192);

	if (isTimeUp_) {
		gsDrawSprite2D(Texture_Text, &shadowNumPos, &endTextRect, 0, &black, 0, 0);
		gsDrawSprite2D(Texture_Text, &numPos, &endTextRect, 0, 0, 0, 0);
		return;
	}

	static const GSvector2 pointPos(920, 10);
	static const GSvector2 shadowPointPos(923, 13);
	static const GSrect pointRect(320, 0, 340, 64);

	int fraction = (restTime_ - (int)restTime_) * 10;
	static const GSvector2 fractionPos(940, 10);
	static const GSvector2 shadowFractionPos(943, 13);

	number.draw(shadowNumPos, (int)restTime_, 2, '0', &black);
	gsDrawSprite2D(Texture_Number, &shadowPointPos, &pointRect, 0, &black, 0, 0);
	number.draw(shadowFractionPos, fraction, &black);

	number.draw(numPos, (int)restTime_, 2, '0');
	gsDrawSprite2D(Texture_Number, &pointPos, &pointRect, 0, 0, 0, 0);
	number.draw(fractionPos, fraction);

	if (restTime_ > 5.0f)return;
	const GScolor red(1.0f, 0.1f, 0.1f, ABS(gsSin((5.0f - restTime_) * 540)));
	number.draw(numPos, (int)restTime_, 2, '0', &red);
	gsDrawSprite2D(Texture_Number, &pointPos, &pointRect, 0, &red, 0, 0);
	number.draw(fractionPos, fraction, &red);
}

//時間切れか
bool Time::isTimeUp() const {
	return isTimeUp_;
}