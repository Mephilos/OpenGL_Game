#ifndef ACTOR_H_
#define ACTOR_H_

#include "ActorPtr.h"
#include "BoundigShphere.h"
#include <gslib.h>
#include <string>
#include <memory>
#include <functional>
#include <forward_list>

class IWorld;

enum class EventMessage;

class Actor {
public:
	// コンストラクタ
	Actor(IWorld* world, const std::string& name, const GSvector3& position, const BoundingSphere& body);
	// コンストラクタ
	explicit Actor(const std::string& name = "none");
	// 仮想デストラクタ
	virtual ~Actor() {}
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// 衝突処理
	void collide(Actor& other);
	// 死亡しているか？
	bool isDead() const;
	// 死亡する
	void dead();
	// 名前を返す
	const std::string& getName() const;
	// 座標を返す
	GSvector3 getPosition() const;
	// 回転行列を返す
	GSmatrix4 getRotate() const;
	// 変換行列を返す
	GSmatrix4 getPose() const;
	// 子の検索
	ActorPtr findCildren(const std::string& name);
	// 子の検索
	ActorPtr findCildren(std::function<bool (const Actor&)> fn);
	// 子同士の衝突
	void collideChildren(Actor& other);
	// 兄弟同士の衝突判定
	void collideSibling();
	// 子の追加
	void addChild(const ActorPtr& child);
	// 子を巡回
	void eachChildren(std::function<void(Actor&)> fn);
	// 子を巡回(const版)
	void eachChildren(std::function<void(const Actor&)> fn) const;
	// 子を削除する
	void removeChildren(std::function <bool(Actor&)> fn);
	// 子を削除する
	void removeChildren();
	// 子を消去
	void clearChildren();
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	//子の取得
	const std::forward_list<ActorPtr>& getChildren() const;
	// コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);
	// 衝突判定
	bool isCollide(const Actor& other) const;

protected:
	// ワールド
	IWorld*				world_;
	// 名前
	std::string			name_;
	// 座標
	GSvector3			position_;
	// 回転
	GSmatrix4			rotate_;
	// 衝突判定
	BoundingSphere		body_;
	// 死亡フラグ
	bool				dead_;

private:
	// 子アクター
	std::forward_list<ActorPtr> children_;
};

#endif
