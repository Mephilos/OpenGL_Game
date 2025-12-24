#include"TitleScene.h"
#include"Scene.h"
#include<gslib.h>
#include"Resource.h"
#include<GSmusic.h>

static const float MOVE_ENDTIME = 30.0f;

// コンストラクタ
TitleScene::TitleScene() :
	isEnd_(false),
	timer_(0.0f) {
}

// デストラクタ
TitleScene::~TitleScene() {
}

// 開始
void TitleScene::start() {
	isEnd_ = false;
	timer_ = 0.0f;

	gsBindMusic(Music_Title);
	gsPlayMusic();
}

// 更新
void TitleScene::update(float deltaTime) {
	if (gsGetKeyTrigger(GKEY_SPACE) == GS_TRUE) {
		isEnd_ = true;
	}
	
	timer_ += deltaTime;;
}

// 描画
void TitleScene::draw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0f, 0.0f, 50.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	);
	gsDrawSprite2D(Texture_Title, 0, 0, 0, 0, 0, 0);

	const GSvector2 karatePos = GSvector2(700, 150).lerp(GSvector2(-400, 150), CLAMP(timer_ / MOVE_ENDTIME, 0.0f, 1.0f));
	gsDrawSprite2D(Texture_Karate, &karatePos, 0, 0, 0, 0, 0);

	const GSvector2 kendoPos = GSvector2(-460, 150).lerp(GSvector2(360, 150), CLAMP(timer_ / MOVE_ENDTIME, 0.0f, 1.0f));
	gsDrawSprite2D(Texture_Kendo, &kendoPos, 0, 0, 0, 0, 0);

	const GScolor color(1.0f, 1.0f, 1.0f, ABS(gsCos(timer_*4.0f)));
	const GScolor black(0.0f, 0.0f, 0.0f, ABS(gsCos(timer_*4.0f)));
	static const GSvector2 textPos(250, 720);
	static const GSvector2 shadowTextPos(254, 724);
	gsDrawSprite2D(Texture_Osu, &shadowTextPos, 0, 0, &black, 0, 0);
	gsDrawSprite2D(Texture_Osu, &textPos, 0, 0, &color, 0, 0);
}

// 終了しているか？
bool TitleScene::isEnd() const {
	return isEnd_;
}

// 次のシーンを返す
Scene TitleScene::next() const {
	return Scene::GamePlay;
}

// 終了
void TitleScene::end() {
	gsStopMusic();
}
