#include "SceneNull.h"
#include "Scene.h"

// 開始
void SceneNull::start() {}

// 更新
void SceneNull::update(float) {}

// 描画
void SceneNull::draw() const {}

// 終了しているか？
bool SceneNull::isEnd() const {
	return false;
}

// 次のシーンを返す
Scene SceneNull::next() const {
	return Scene::None;
}

// 終了
void SceneNull::end() {}
