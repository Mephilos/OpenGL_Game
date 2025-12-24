#ifndef GAME_H_
#define GAME_H_

#include <GSgame.h>
#include "SceneManager.h"

class Game : public gslib::Game {
public:
	// コンストラクタ
	Game();
	//デストラクタ
	~Game();
private:
	// 開始
	virtual void start() override;
	// 更新
	virtual void update(float deltaTime)  override;
	// 描画
	virtual void draw() override;
	// 描画
	virtual void end() override;
	//リソース読み込み
	void load();
private:
	// シーンマネージャ
	SceneManager	sceneManager_;
};

#endif
