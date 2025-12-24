#include"Result.h"
#include"Resource.h"
#include"Score.h"
#include"NumberTexture.h"
#include<fstream>

static const float MOVE_ENDTIME = 30.0f;

//コンストラクタ
Result::Result(const float* frameTime, const Score* score) :
	frameTime_(frameTime),
	score_(score),
	scores_(5){
	std::ifstream loadFile("res/ranking.txt");
	for (std::vector<int>::size_type i = 0; i < scores_.size(); i++) {
		loadFile >> scores_[i];
	}
	loadFile.close();
}

//更新
void Result::update() {
	for (std::vector<int>::size_type i = 0; i < scores_.size(); i++) {
		if (scores_[i] <= score_->get()) {
			updateScore(i);
			save();
			break;
		}
	}
}

//スコアの更新
void Result::updateScore(int rank) {
	for (int i = scores_.size() - 1; i > rank; i--) {
		scores_[i] = scores_[i - 1];
	}
	scores_[rank] = score_->get();
}

//ランキングの保存
void Result::save() {
	std::ofstream saveFile("res/ranking.txt");
	for (int i = 0; i < 5; i++) {
		saveFile << scores_[i] << std::endl;
	}
	saveFile.close();
}

//描画
void Result::draw() const {
	if (score_ == 0) return;

	static const GSvector2 bluePos(25, 100);
	static const GSrect blueRect(0, 0, 984, 575);
	static const GScolor blueAlpha(1.0f, 1.0f, 1.0f, 0.5f);
	gsDrawSprite2D(Texture_Blue, &bluePos, &blueRect, 0, &blueAlpha, 0, 0);

	const GSvector2 kendoPos = GSvector2(-460, 100).lerp(GSvector2(360, 100), CLAMP(*frameTime_ / MOVE_ENDTIME, 0.0f, 1.0f));
	gsDrawSprite2D(Texture_Kendo, &kendoPos, 0, 0, 0, 0, 0);

	static const GScolor black(0.0f, 0.0f, 0.0f, 1.0f);
	static const GScolor red(1.0f, 0, 0, 1.0f);

	drawEvaluation(red, black);

	drawRank(red, black);

	const GScolor blackAlpha(0.0f, 0.0f, 0.0f, ABS(gsCos(*frameTime_*4.0f)));
	const GScolor alpha(1.0f, 1.0f, 1.0f, ABS(gsCos(*frameTime_*4.0f)));
	static const GSvector2 textPos(250, 700);
	static const GSvector2 shadowTextPos(254, 704);
	gsDrawSprite2D(Texture_Osu, &shadowTextPos, 0, 0, &blackAlpha, 0, 0);
	gsDrawSprite2D(Texture_Osu, &textPos, 0, 0, &alpha, 0, 0);
}

//矩形の設定
void Result::setRect(GSrect* result1, GSrect* result2) const{
	if (score_->get() < 30) {
		*result1 = GSrect(0, 64 * 4, 984, 64 * 5);
		*result2 = GSrect(0, 200 * 4, 984, 200 * 5 - 1);
	}
	else if (score_->get() < 45) {
		*result1 = GSrect(0, 64 * 3, 984, 64 * 4);
		*result2 = GSrect(0, 200 * 3, 984, 200 * 4 - 1);
	}
	else if (score_->get() < 60) {
		*result1 = GSrect(0, 64 * 2, 984, 64 * 3);
		*result2 = GSrect(0, 200 * 2, 984, 200 * 3 - 1);
	}
	else if (score_->get() < 80) {
		*result1 = GSrect(0, 64 * 1, 984, 64 * 2);
		*result2 = GSrect(0, 200 * 1, 984, 200 * 2 - 1);
	}
}

//評価の表示
void  Result::drawEvaluation(const GScolor& red, const GScolor& black) const {
	static const GSvector2 res1Pos(25, 105);
	static const GSvector2 shadowRes1Pos(29, 109);
	static const GSvector2 res2Pos(25, 170);
	static const GSvector2 shadowRes2Pos(29, 174);
	GSrect res1Rect(0, 0, 984, 64);
	GSrect res2Rect(0, 0, 984, 200 - 1);
	setRect(&res1Rect, &res2Rect);

	gsDrawSprite2D(Texture_Result1, &shadowRes1Pos, &res1Rect, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Result1, &res1Pos, &res1Rect, 0, &red, 0, 0);
	gsDrawSprite2D(Texture_Result2, &shadowRes2Pos, &res2Rect, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Result2, &res2Pos, &res2Rect, 0, 0, 0, 0);
}

//順位の表示
void Result::drawRank(const GScolor& red, const GScolor& black) const{
	static const GSvector2 textPos(30, 350);
	static const GSvector2 shadowTextPos(34, 354);
	static const GSrect textRect(0, 192, 128, 256);
	gsDrawSprite2D(Texture_Text, &shadowTextPos, &textRect, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Text, &textPos, &textRect, 0, &red, 0, 0);

	static const NumberTexture number(Texture_Number, 32, 64);
	bool drawCurrentScore = false; //現在のスコアを描画した
	draw1st(number, red, black, &drawCurrentScore);
	draw2nd(number, red, black, &drawCurrentScore);
	draw3rd(number, red, black, &drawCurrentScore);
	draw4th(number, red, black, &drawCurrentScore);
	draw5th(number, red, black, &drawCurrentScore);
}

//1位の表示
void Result::draw1st(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const {
	static const GSvector2 rankPos1st(165, 350);
	static const GSvector2 shadowRankPos1st(169, 354);
	static const GSrect rankRect1st(128, 0, 256, 60);
	static const GSvector2 scorePos(300, 350);
	static const GSvector2 shadowScorePos(304, 354);

	gsDrawSprite2D(Texture_Text, &shadowRankPos1st, &rankRect1st, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Text, &rankPos1st, &rankRect1st, 0, 0, 0, 0);

	number.draw(shadowScorePos, scores_[0], 3, '0', &black);
	number.draw(scorePos, scores_[0], 3);
	
	if (*drawCurrentScore) return;

	if (scores_[0] == score_->get()) {
		gsDrawSprite2D(Texture_Text, &rankPos1st, &rankRect1st, 0, &red, 0, 0);
		number.draw(scorePos, scores_[0], 3, '0', &red);
		*drawCurrentScore = true;
	}
}

//2位の表示
void Result::draw2nd(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const {
	static const GSvector2 rankPos2nd(165, 350 + 64);
	static const GSvector2 shadowRankPos2nd(169, 354 + 64);
	static const GSrect rankRect2nd(128, 60, 256, 120);
	static const GSvector2 scorePos(300, 350 + 64);
	static const GSvector2 shadowScorePos(304, 354 + 64);

	gsDrawSprite2D(Texture_Text, &shadowRankPos2nd, &rankRect2nd, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Text, &rankPos2nd, &rankRect2nd, 0, 0, 0, 0);

	number.draw(shadowScorePos, scores_[1], 3, '0', &black);
	number.draw(scorePos, scores_[1], 3);

	if (*drawCurrentScore) return;

	if (scores_[1] == score_->get()) {
		gsDrawSprite2D(Texture_Text, &rankPos2nd, &rankRect2nd, 0, &red, 0, 0);
		number.draw(scorePos, scores_[1], 3, '0', &red);
		*drawCurrentScore = true;
	}
}

//3位の表示
void Result::draw3rd(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const {
	static const GSvector2 rankPos3rd(165, 350 + 64 * 2);
	static const GSvector2 shadowRankPos3rd(169, 354 + 64 * 2);
	static const GSrect rankRect3rd(128, 120, 256, 180);
	static const GSvector2 scorePos(300, 350 + 64 * 2);
	static const GSvector2 shadowScorePos(304, 354 + 64 * 2);

	gsDrawSprite2D(Texture_Text, &shadowRankPos3rd, &rankRect3rd, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Text, &rankPos3rd, &rankRect3rd, 0, 0, 0, 0);

	number.draw(shadowScorePos, scores_[2], 3, '0', &black);
	number.draw(scorePos, scores_[2], 3);

	if (*drawCurrentScore) return;

	if (scores_[2] == score_->get()) {
		gsDrawSprite2D(Texture_Text, &rankPos3rd, &rankRect3rd, 0, &red, 0, 0);
		number.draw(scorePos, scores_[2], 3, '0', &red);
		*drawCurrentScore = true;
	}
}

//4位の表示
void Result::draw4th(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const {
	static const GSvector2 rankPos4th(165, 350 + 64 * 3);
	static const GSvector2 shadowRankPos4th(169, 354 + 64 * 3);
	static const GSrect rankRect4th(128, 180, 256, 240);
	static const GSvector2 scorePos(300, 350 + 64 * 3);
	static const GSvector2 shadowScorePos(304, 354 + 64 * 3);

	gsDrawSprite2D(Texture_Text, &shadowRankPos4th, &rankRect4th, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Text, &rankPos4th, &rankRect4th, 0, 0, 0, 0);

	number.draw(shadowScorePos, scores_[3], 3, '0', &black);
	number.draw(scorePos, scores_[3], 3);

	if (*drawCurrentScore) return;

	if (scores_[3] == score_->get()) {
		gsDrawSprite2D(Texture_Text, &rankPos4th, &rankRect4th, 0, &red, 0, 0);
		number.draw(scorePos, scores_[3], 3, '0', &red);
		*drawCurrentScore = true;
	}
}

//5位の表示
void Result::draw5th(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const {
	static const GSvector2 rankPos5th(165, 350 + 64 * 4);
	static const GSvector2 shadowRankPos5th(169, 354 + 64 * 4);
	static const GSrect rankRect5th(128, 240, 256, 300);
	static const GSvector2 scorePos(300, 350 + 64 * 4);
	static const GSvector2 shadowScorePos(304, 354 + 64 * 4);

	gsDrawSprite2D(Texture_Text, &shadowRankPos5th, &rankRect5th, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Text, &rankPos5th, &rankRect5th, 0, 0, 0, 0);

	number.draw(shadowScorePos, scores_[4], 3, '0', &black);
	number.draw(scorePos, scores_[4], 3);

	if (*drawCurrentScore) return;

	if (scores_[4] == score_->get()) {
		gsDrawSprite2D(Texture_Text, &rankPos5th, &rankRect5th, 0, &red, 0, 0);
		number.draw(scorePos, scores_[4], 3, '0', &red);
		*drawCurrentScore = true;
	}
}