#ifndef SCORE_H_
#define SCORE_H_

// スコアクラス
class Score {
public:
	// コンストラクタ
	explicit Score(int score = 0);
	// スコアの加算
	void add(int score);
	// スコアの描画
	void draw() const;
	// スコアの取得
	int get() const;
private:
	// スコア
	int score_;
};

#endif

