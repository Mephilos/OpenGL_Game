#ifndef GAME_PLAY_SCENE_H_
#define GAME_PLAY_SCENE_H_

#include "IScene.h"
#include <memory>
#include "Score.h"
#include"Time.h"
#include"Result.h"
#include"Radar.h"

class World;
enum class EventMessage;

class GamePlayScene : public IScene {
public:
	// コンストラクタ
	GamePlayScene();
	// デストラクタ
	virtual ~GamePlayScene();
	// 開始
	virtual void start() override;
	// 更新
	virtual void update(float deltaTime) override;
	// 描画
	virtual void draw() const override;
	// 終了しているか？
	virtual bool isEnd() const override;
	// 次のシーンを返す
	virtual Scene next() const override;
	// 終了
	virtual void end() override;

	// メッセージ処理
	void handleMessage(EventMessage message, void* param);

private:
	using WorldPtr = std::shared_ptr<World>;
	// ワールド
	WorldPtr	world_;
	// スコア
	Score		score_;
	// 終了フラグ
	bool		isEnd_;
	//残り時間
	Time restTime_;
	//終了後フレーム時間
	float frameTime_;
	//リザルト管理
	Result result_;
	//レーダー
	Radar radar_;
};

#endif

