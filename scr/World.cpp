#include "World.h"
#include "Field.h"

// コンストラクタ
World::World() :
	listener_([](EventMessage, void*) {}) {
}

// 更新
void World::update(float deltaTime) {
	actors_.update(deltaTime);
	camera_->update(deltaTime);
	light_->update(deltaTime);
}

// 描画
void World::draw() const {
	camera_->draw();
	light_->draw();
	field_->draw();
	actors_.draw();
}

// メッセージ処理
void World::handleMessage(EventMessage message, void* param) {
	// ワールドのメッセージ処理
	listener_(message, param);
	// アクターのメッセージ処理
	actors_.handleMessage(message, param);
	camera_->handleMessage(message, param);
	light_->handleMessage(message, param);
}
 
// フィールドの追加
void World::addField(const FieldPtr& field) {
	field_ = field;
}

// カメラの追加
void World::addCamera(const ActorPtr& camera) {
	camera_ = camera;
}

// ライトの追加
void World::addLight(const ActorPtr& light) {
	light_ = light;
}

const std::forward_list<ActorPtr>& World::getActors(ActorGroup group) const {
	return actors_.getActors(group);
}

// アクターの追加
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

// アクターの検索
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}

// フィールドの取得
FieldPtr World::getField() const {
	return field_;
}

// メッセージの送信
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

// イベントリスナーの追加
void World::addEventMessageListener(
	std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}

