#ifndef ANIMATION_H_
#define ANIMATION_H_

#include"Matrices.h"
#include<gslib.h>

//アニメーションクラス
class Animation {
public:
	//コンストラクタ
	Animation(GSuint animation, GSuint motion);
	//更新
	void update(float deltaTime);
	//モーションの変更
	void changeMotion(GSuint motion);
	//再生中のモーション番号を返す
	GSuint getMotion() const;
	//ボーン数を返す
	GSuint getBoneCount() const;
	//終了時間を返す
	GSuint getEndTime() const;
	//変換行列を取得
	const Matrices& getMatrices() const;

private:
	//補間フレーム数
	const GSfloat LERP_TIME = 10.0f;
	//アニメーション番号
	GSuint animation_;
	//再生中のモーション番号
	GSfloat motion_;
	//再生中のアニメーションタイマー
	GSfloat motionTimer_;
	//前回再生したモーション番号
	GSuint prevMotion_;
	//前回再生した最終アニメーションタイマー
	GSfloat prevMotionTimer_;
	//補間アニメーションタイマー
	GSfloat lerpTimer_;
	//アニメーション変換行列
	Matrices matrices_;
};

#endif