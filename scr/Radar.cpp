#include"Radar.h"
#include"Resource.h"
#include"Actor.h"
#include"ActorGroup.h"
#include"World.h"
#include"Enemy.h"

Radar::Radar() :
	world_(0){
}

//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
Radar::Radar(World* world):
	world_(world){
}

//•`‰æ
void Radar::draw() const {
	static const GScolor radarAlpha(1.0f, 1.0f, 1.0f, 0.4f);
	static const GSvector2 radarPos(10, 10);

	gsDrawSprite2D(Texture_Radar, &radarPos, 0, 0, &radarAlpha, 0, 0);

	static const GSvector2 playerPos(134, 134);
	static const GScolor playerColor(0.0f, 1.0f, 0.4f, 1.0f);

	gsDrawSprite2D(Texture_Point, &playerPos, 0, 0, &playerColor, 0, 0);

	drawEnemy();
}

//“G•`‰æ
void Radar::drawEnemy() const {
	static const GScolor red(1.0f, 0.0f, 0.0f, 1.0f);
	static const GScolor gray(0.6f, 0.6f, 0.6f, 1.0f);
	static const GScolor skyBlue(0.7f, 0.8f, 1.0f, 1.0f);

	const std::forward_list<ActorPtr>& enemies = world_->getActors(ActorGroup::Enemy);

	ActorPtr player = world_->findActor("Player");
	if (player == nullptr) return;
	const GSvector2 playerPos = GSvector2(player->getPosition().x, player->getPosition().z)*(-6.5f);

	static const GSvector2 min(8, 8);
	static const GSvector2 max(262, 262);
	static const GSvector2 center(136, 136);
	const GSmatrix4 playerRotate = player->getRotate();
	const GSmatrix3 rotate(
		playerRotate._11, playerRotate._13, 0.0f,
		playerRotate._31, playerRotate._33, 0.0f,
		0.0f, 0.0f, 1.0f);

	GSvector2 enemyPos;

	for (std::forward_list<ActorPtr>::const_iterator i = enemies.begin(); i != enemies.end(); i++) {
		enemyPos = GSvector2((*i)->getPosition().x, (*i)->getPosition().z)*(-6.5f)  - playerPos;
		enemyPos = enemyPos * rotate;
		enemyPos += center;

		if (enemyPos != enemyPos.clamp(min, max)) continue;
		if ((*i)->getName() == "EnemyGenerator") {
			gsDrawSprite2D(Texture_Point, &enemyPos, 0, 0, &skyBlue, 0, 0);
			continue;
		}
		if (static_cast<Enemy*>(i->get())->getState() == Enemy::State::Damage || static_cast<Enemy*>(i->get())->getState() == Enemy::State::Dead) {
			gsDrawSprite2D(Texture_Point, &enemyPos, 0, 0, &gray, 0, 0);
			continue;
		}
		gsDrawSprite2D(Texture_Point, &enemyPos, 0, 0, &red, 0, 0);
	}
}