#ifndef ANIMATION_MESH_H_
#define ANIMATION_MESH_H_

#include"Animation.h"

//アニメーション付きメッシュクラス
class AnimatedMesh {
public:
	//コンストラクタ
	AnimatedMesh(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion = 0);
	//更新
	void update(float deltaTime);
	//描画
	void draw() const;
	//モーションの変更
	void changeMotion(GSuint motion);
	//スケルトンの変換行列を計算
	void calculate(const GSmatrix4& world);
	//変換行列を取得
	const Matrices& getMatrices() const;
	//モーション終了時間を返す
	float getMotionEndTime() const;

private:
	//メッシュ
	GSuint mesh_;
	//スケルトン
	GSuint skeleton_;
	//アニメーション
	Animation animation_;
	//スケルトン変換行列
	Matrices matrices_;
};


#endif