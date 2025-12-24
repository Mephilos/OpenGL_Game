#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "IScenePtr.h"
#include <unordered_map>

enum class Scene;

// シーン管理クラス
class SceneManager {
public:
	// コンストラクタ
	SceneManager();
	// 初期化
	void initialize();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// 終了
	void end();
	// シーンの追加
	void add(Scene name, const IScenePtr& scene);
	// シーンの更新
	void change(Scene name);
	// コピー禁止
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;
private:
	// シーン
	std::unordered_map<Scene, IScenePtr>	scenes_;
	// 現在のシーン
	IScenePtr currentScene_;
};

#endif
