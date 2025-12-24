#include"Player.h"
#include"IWorld.h"
#include"Field.h"
#include"Ray.h"
#include"PlayerAttack.h"
#include"EventMessage.h"
#include<GSmusic.h>
#include"Resource.h"
#include"Enemy.h"
#include"ActorGroup.h"

enum {
	Motion_Idle = 0,
	Motion_FowardWalk = 1,
	Motion_Attack = 17,
	Motion_Damage = 14,
	Motion_GetUp = 16
};

Player::Player(IWorld* world, const GSvector3& position) :
	Actor(world, "Player", position, BoundingSphere(0.5f)),
	mesh_(Mesh_Player, Skl_Player, Anm_Player, Motion_Idle),
	motion_(Motion_Idle),
	state_(State::Move),
	stateTimer_(0) {
	mesh_.calculate(getPose());
}

void Player::onUpdate(float deltaTime) {
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

void Player::onDraw() const {
	mesh_.draw();
}

void Player::onCollide(Actor& actor) {
	if (state_ == State::Damage || state_ == State::GetUp) return;
	if (static_cast<Enemy&>(actor).getState() != Enemy::State::Move) return;
	world_->sendMessage(EventMessage::EnemyDamage, &actor);
	gsPlaySE(SE_PlayerDamage);
	changeState(State::Damage, Motion_Damage);
}

void Player::updateState(float deltaTime) {
	switch (state_)
	{
	case Player::State::Move:
		move(deltaTime);
		break;
	case Player::State::Attack:
		attack(deltaTime);
		break;
	case Player::State::Damage:
		damage(deltaTime);
		break;
	case Player::State::GetUp:
		getUp(deltaTime);
		break;
	default:
		break;
	}
	stateTimer_ += deltaTime;
}

void Player::changeState(State state, GSuint motion) {
	if (motion_ != motion)motion_ = motion;
	if (state_ != state) state_ = state;
	stateTimer_ = 0.0f;
}

void Player::move(float deltaTime) {
	if (gsGetKeyTrigger(GKEY_SPACE)) {
		changeState(State::Attack, Motion_Attack);
		gsPlaySE(SE_PlayerAttack);
		world_->addActor(ActorGroup::PlayerBullet, std::make_shared<PlayerAttack>(world_, position_ + rotate_.getAxisZ()*0.75f));
		return;
	}

	GSuint motion = Motion_Idle;

	float foward_speed = 0.0f;
	if (gsGetKeyState(GKEY_UP)) {
		foward_speed = WALK_SPEED;
		motion = Motion_FowardWalk;
	}

	float angle = 0.0f;
	if (gsGetKeyState(GKEY_LEFT) == GS_TRUE)  angle += 3.0f;
	if (gsGetKeyState(GKEY_RIGHT) == GS_TRUE) angle -= 3.0f;
	rotate_.rotateY(angle);

	changeState(State::Move, motion);

	GSvector3 velocity(0, 0, 0);
	velocity += rotate_.getAxisZ()*foward_speed;
	position_ += velocity*deltaTime;
	position_ = position_.clamp(GSvector3(-20, -20, -20), GSvector3(20, 20, 20));
}

void Player::attack(float deltaTime) {
	if (stateTimer_ >= 24) {
		move(deltaTime);
	}
}

void Player::damage(float deltaTime) {
	if (stateTimer_ >= mesh_.getMotionEndTime() - 1) {
		changeState(State::GetUp, Motion_GetUp);
	}
}

void Player::getUp(float deltaTime) {
	if (stateTimer_ >= mesh_.getMotionEndTime() - 1) {
		move(deltaTime);
	}
}

Player::State Player::getState() const {
	return state_;
}