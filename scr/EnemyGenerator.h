#ifndef ENEMY_GENERATOR_H_
#define ENEMY_GENERATOR_H_

#include"Actor.h"

class EnemyGenerator : public Actor {
public:
	//コンストラクタ
	EnemyGenerator(IWorld* world, const GSvector3& position);
	//更新
	virtual void onUpdate(float deltaTime) override;
	//描画
	virtual void onDraw() const override;
	//衝突処理
	virtual void onCollide(Actor& actor) override;
};

#endif