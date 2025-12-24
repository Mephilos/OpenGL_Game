#ifndef SCENE_NULL_H_
#define SCENE_NULL_H_

#include "IScene.h"

class SceneNull : public IScene {
public:
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
};



#endif
