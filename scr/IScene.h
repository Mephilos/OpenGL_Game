#ifndef ISCENE_H_
#define ISCENE_H_

enum class Scene;

class IScene {
public:
	// 仮想デストラクタ
	virtual ~IScene() {}
	// 開始
	virtual void start() = 0;
	// 更新
	virtual void update(float deltaTime) = 0;
	// 描画
	virtual void draw() const = 0;
	// 終了しているか？
	virtual bool isEnd() const = 0;
	// 次のシーンを返す
	virtual Scene next() const = 0;
	// 終了
	virtual void end() = 0;
};

#endif

