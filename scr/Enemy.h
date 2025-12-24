#ifndef ENEMY_H_
#define ENEMY_H_

#include "Actor.h"
#include"AnimatedMesh.h"

// 敵
class Enemy : public Actor {
public:
	enum class State {
		Spawn,
		Move,
		Damage,
		Dead
	};

public:
	Enemy(IWorld* world, const GSvector3&  position, const GSvector3& vector = { 0.0f,0.0f,0.0f });
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	Enemy::State getState() const;

private:
	//状態の更新
	void updateState(float deltaTime);
	//状態の変更
	void changeState(State state, GSuint motion);
	//出現
	void spawn(float deltaTime);
	//移動
	void move(float deltaTime);
	//ダメージ中
	void damage(float deltaTime);
	//死亡
	void dead(float deltaTime);
	//ステージ外に出たか
	bool outStage() const;

private:
	GSvector3 velocity_;
	AnimatedMesh mesh_;
	GSuint motion_;
	State state_;
	float stateTimer_;
};

#endif
