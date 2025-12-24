#ifndef ACTOR_MANAGER_H_
#define ACTOR_MANAGER_H_

#include "Actor.h"
#include <unordered_map>

enum class ActorGroup;

class ActorManager {
public:
	// コンストラクタ
	ActorManager();
	// 初期化
	void initialize();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// アクターの追加
	void addActor(ActorGroup group, const ActorPtr& actor);
	// アクターの検索
	ActorPtr findActor(const std::string& name);
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	//アクターグループの取得
	const std::forward_list<ActorPtr>& getActors(ActorGroup group) const;

	// コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;
private:
	// 衝突判定
	void collide();
private:
	// ルートノード
	Actor root_;
	// アクターグループ
	std::unordered_map<ActorGroup, ActorPtr> actors_;
};

#endif

// end of file
