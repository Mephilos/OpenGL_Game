#ifndef PLAYER_H_
#define PLAYER_H_

#include"Actor.h"
#include"AnimatedMesh.h"

// プレーヤ
class Player : public Actor {
public:
	enum class State {
		Move,
		Attack,
		Damage,
		GetUp,
	};

public:
	Player(IWorld* world, const GSvector3& position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor&) override;
	Player::State getState() const;

private:
	void updateState(float deltaTime);
	void changeState(State state, GSuint motion);
	void move(float deltaTime);
	void attack(float deltaTime);
	void damage(float deltaTime);
	void getUp(float deltaTime);

private:
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//モーション番号
	GSuint motion_;
	State state_;
	float stateTimer_;
	const float WALK_SPEED = 0.2f;
};

#endif
