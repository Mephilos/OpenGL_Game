#include"Enemy.h"
#include"IWorld.h"
#include"Field.h"
#include"Ray.h"
#include"EventMessage.h"
#include"Resource.h"
#include"Player.h"
#include<GSmusic.h>

const float FLASH_TIME = 20.0f;

//敵のモーション制御
enum {
	Enemy_Motion_Idle = 0,
	Enemy_Motion_Walk = 1,
	Enemy_Motion_Damage = 14,
	Enemy_Motion_Dead = 15
};

Enemy::Enemy(IWorld* world, const GSvector3&  position, const GSvector3& vector) :
	Actor(world, "Enemy", position, BoundingSphere(0.5f)),
	velocity_(0, 0, 0),
	mesh_(Mesh_Enemy, Skl_Enemy, Anm_Enemy, Enemy_Motion_Idle),
	motion_(Enemy_Motion_Idle),
	state_(State::Spawn),
	stateTimer_(0.0f){
	if (vector.length() == 0.0f)return;
	rotate_.setAxisZ(vector).nomalizeAxisZ();
	mesh_.calculate(getPose());
}

void Enemy::onUpdate(float deltaTime) {
	updateState(deltaTime);
	mesh_.changeMotion(motion_);
	mesh_.update(deltaTime);
	mesh_.calculate(getPose());

	Ray ray(position_, { 0.0f, 1.0f, 0.0f });
	GSvector3 intersect;
	if (world_->getField()->collision(ray, &intersect)) {
		position_.y = intersect.y;
	}
}

void Enemy::onDraw() const{
	if (state_ == State::Move || state_ == State::Damage) {
		mesh_.draw();
		return;
	}
	
	if ((int)stateTimer_ % 3 == 0) mesh_.draw();
}

void Enemy::onCollide(Actor& actor){
	if (state_ == State::Dead || state_ == State::Damage) return;

	if (actor.getName() == "Player") {
		if (static_cast<Player&>(actor).getState() == Player::State::Damage) return;
		gsPlaySE(SE_EnemyDead);
		changeState(State::Damage, Enemy_Motion_Damage);
		return;
	}

	gsPlaySE(SE_EnemyDead);
	changeState(State::Damage, Enemy_Motion_Damage);
	static const int score = 1;
	world_->sendMessage(EventMessage::AddScore, (void*)&score);
}

void Enemy::onMessage(EventMessage event, void* param) {
	switch (event)
	{
	case EventMessage::EnemyDamage:
		if (this == param) changeState(State::Damage, Enemy_Motion_Damage);
		gsPlaySE(SE_EnemyDead);
		break;
	default:
		break;
	}
}

//状態の更新
void Enemy::updateState(float deltaTime) {
	switch (state_)
	{
	case Enemy::State::Spawn:
		spawn(deltaTime);
		break;
	case Enemy::State::Move:
		move(deltaTime);
		break;
	case Enemy::State::Damage:
		damage(deltaTime);
		break;
	case Enemy::State::Dead:
		dead(deltaTime);
		break;
	default:
		break;
	}
	stateTimer_ += deltaTime;
}

//状態の変更
void Enemy::changeState(State state, GSuint motion) {
	if (motion_ != motion) motion_ = motion;
	if(state_ != state) state_ = state;
	stateTimer_ = 0.0f;
}
//出現
void Enemy::spawn(float deltaTime) {
	if (stateTimer_ >= FLASH_TIME) {
		velocity_ = (world_->findActor("Player")->getPosition() - position_).getNormalized()*0.10f;
		rotate_.setAxisZ(velocity_).nomalizeAxisZ();
		changeState(State::Move, Enemy_Motion_Walk);
		return;
	}
}
//移動
void Enemy::move(float deltaTime) {
	position_ += velocity_;
	if (outStage()) changeState(State::Dead, Enemy_Motion_Idle);
}
//ダメージ中
void Enemy::damage(float deltaTime) {
	if (stateTimer_ >= mesh_.getMotionEndTime()-1) {
		changeState(State::Dead, Enemy_Motion_Dead);
	}
}
//死亡
void Enemy::dead(float deltaTime) {
	if (stateTimer_ >= FLASH_TIME) {
		dead_ = true;
	}
}

Enemy::State Enemy::getState() const {
	return state_;
}

//ステージ外に出たか
bool Enemy::outStage() const {
	return (position_ != position_.clamp(GSvector3(-21, -21, -21), GSvector3(21, 21, 21)));
}