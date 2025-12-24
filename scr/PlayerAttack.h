#ifndef PLAYER_ATTACK_H_
#define PLAYER_ATTACK_H_

#include "Actor.h"

//プレイヤー攻撃クラス
class PlayerAttack : public Actor {
public:
	// コンストラクタ
	PlayerAttack(IWorld* world, const GSvector3& position);
private:
	// 更新
	virtual void onUpdate(float deltaTime) override;
	//描画
	virtual void onDraw() const override;
	//衝突処理
	virtual void onCollide(Actor& actor) override;

private:
	float timer_;
};

#endif

