#include "SceneManager.h"
#include "SceneNull.h"

// コンストラクタ
SceneManager::SceneManager() :
	currentScene_(std::make_shared<SceneNull>()) {
}

// 初期化
void SceneManager::initialize() {
	end();
	scenes_.clear();
}

// 更新
void SceneManager::update(float deltaTime) {
	currentScene_->update(deltaTime);
	if (currentScene_->isEnd()) {
		change(currentScene_->next());
	}
}

// 描画
void SceneManager::draw() const {
	currentScene_->draw();
}

// 終了
void SceneManager::end() {
	currentScene_->end();
	currentScene_ = std::make_shared<SceneNull>();
}

// シーンの追加
void SceneManager::add(Scene name, const IScenePtr& scene) {
	scenes_[name] = scene;
}

// シーンの更新
void SceneManager::change(Scene name) {
	end();
	currentScene_ = scenes_[name];
	currentScene_->start();
}
