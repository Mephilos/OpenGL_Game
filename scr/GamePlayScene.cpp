#include "GamePlayScene.h"
#include "Scene.h"
#include "World.h"
#include "Light.h"
#include "Camera.h"
#include "TpsCamera.h"
#include "Field.h"
#include "ActorGroup.h"
#include "Player.h"
#include "EventMessage.h"
#include <GSmusic.h>
#include"Resource.h"
#include"EnemyGenerator.h"

// コンストラクタ
GamePlayScene::GamePlayScene() :
	isEnd_(false){
}

// デストラクタ
GamePlayScene::~GamePlayScene() {
}

// 開始
void GamePlayScene::start() {
	isEnd_ = false;
	frameTime_ = 0.0f;

	gsPlaySE(SE_Select);

	world_ = std::make_shared<World>();
	world_->addEventMessageListener([=](EventMessage msg, void* param) {handleMessage(msg, param);});

	world_->addField(std::make_shared<Field>(0, 2));
	world_->addCamera(std::make_shared<TpsCamera>(world_.get()));
	world_->addLight(std::make_shared<Light>(world_.get(), GSvector3(0.0f, 10.0f, 0.0f)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), GSvector3(0.0f, 0.0f, 0.0f)));
	for (int i = 0; i <= 15; i++) {
		world_->addActor(ActorGroup::Enemy, std::make_shared<EnemyGenerator>(world_.get(), GSvector3(-21, 0, -20 + i * 2 * 20.0f / 15.0f)));
		world_->addActor(ActorGroup::Enemy, std::make_shared<EnemyGenerator>(world_.get(), GSvector3(21, 0, 20 - i * 2 * 20.0f / 15.0f)));
		world_->addActor(ActorGroup::Enemy, std::make_shared<EnemyGenerator>(world_.get(), GSvector3(20 - i * 2 * 20.0f / 15.0f, 0, 21)));
		world_->addActor(ActorGroup::Enemy, std::make_shared<EnemyGenerator>(world_.get(), GSvector3(-20 + i * 2 * 20.0f / 15.0f, 0, -21)));
	}
	score_ = Score();
	restTime_ = Time(60.0f);
	result_ = Result(&frameTime_, &score_);
	radar_ = Radar(world_.get());

	gsBindMusic(Music_GamePlay);
	gsPlayMusic();
}

// 更新
void GamePlayScene::update(float deltaTime) {
	if (!restTime_.isTimeUp()) {
		world_->update(deltaTime);
		restTime_.update(deltaTime);
		if (restTime_.isTimeUp()) {
			gsPlaySE(SE_TimeUp);
			gsStopMusic();
			gsBindMusic(Music_Ending);
			gsPlayMusic();
			result_.update();
		}
		return;
	}
	
	frameTime_ >= 1200 ? isEnd_ = true : frameTime_ += deltaTime;
	if (gsGetKeyTrigger(GKEY_SPACE)) {
		isEnd_ = true;
	}
}

// 描画
void GamePlayScene::draw() const {
	world_->draw();
	score_.draw();
	restTime_.draw();
	radar_.draw();

	if (!restTime_.isTimeUp())return;

	result_.draw();
}

// 終了しているか？
bool GamePlayScene::isEnd() const {
	return isEnd_;
}

// 次のシーンを返す
Scene GamePlayScene::next() const {
	return Scene::Title;
}

// 終了
void GamePlayScene::end() {
	world_ = nullptr;
	gsStopMusic();
}

// メッセージ処理
void GamePlayScene::handleMessage(EventMessage message, void* param) {
	switch (message) {
	case EventMessage::AddScore:
		int* score = (int*)param;
		score_.add(*score);
		break;
	}
}