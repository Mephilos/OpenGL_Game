#ifndef RESULT_H_
#define RESULT_H_

#include<gslib.h>
#include<vector>

class Score;
class NumberTexture;

//リザルト管理クラス
class Result {
public:
	//コンストラクタ
	Result(const float* frameTime = 0, const Score* score = 0);
	//更新
	void update();
	//描画
	void draw() const;

private:
	//スコアの更新
	void updateScore(int rank);
	//ランキングの保存
	void save();
	//矩形の設定
	void setRect(GSrect* result1, GSrect* result2) const;
	//評価の表示
	void drawEvaluation(const GScolor& red, const GScolor& black) const;
	//順位の表示
	void drawRank(const GScolor& red, const GScolor& black) const;
	//1位の表示
	void draw1st(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const;
	//2位の表示
	void draw2nd(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const;
	//3位の表示
	void draw3rd(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const;
	//4位の表示
	void draw4th(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const;
	//5位の表示
	void draw5th(const NumberTexture& number, const GScolor& red, const GScolor& black, bool* drawCurrentScore) const;

private:
	const Score* score_;
	const float* frameTime_;
	std::vector<int> scores_;
};

#endif