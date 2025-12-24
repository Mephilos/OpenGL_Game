#ifndef TIME_H_
#define TIME_H_

class Time {
public:
	//コンストラクタ
	Time();
	//コンストラクタ
	Time(float restTime);
	//更新
	void update(float deltaTime);
	//描画
	void draw() const;
	//時間切れか
	bool isTimeUp() const;

private:
	float restTime_; //残り時間
	bool isTimeUp_; //時間切れか
};

#endif