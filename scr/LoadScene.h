#ifndef LOAD_SCENE_H_
#define LOAD_SCENE_H_

#include "IScene.h"

//ロードシーン
class LoadScene : public IScene {
public:
	// コンストラクタ
	LoadScene();
	// デストラクタ
	virtual ~LoadScene();
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
	//リソース読み込み
	void load();
private:
	bool isEnd_;	// 終了フラグ
	int frameTime_;
};

#endif