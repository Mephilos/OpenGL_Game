#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "IScene.h"

// タイトルシーン
class TitleScene : public IScene {
public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	virtual ~TitleScene();
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

private:
	bool isEnd_;	// 終了フラグ
	float timer_;	//タイマー
};

#endif


