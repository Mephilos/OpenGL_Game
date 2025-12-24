#include"LoadScene.h"
#include"Scene.h"
#include<gslib.h>
#include"Resource.h"
#include<GSmusic.h>

// コンストラクタ
LoadScene::LoadScene() :
	isEnd_(false),
	frameTime_(0){
}

// デストラクタ
LoadScene::~LoadScene() {
}

// 開始
void LoadScene::start() {
	isEnd_ = false;
	gsLoadTexture(TextureEnd_, "res/texture/load.png");
}

// 更新
void LoadScene::update(float deltaTime) {
	if (frameTime_ > 1) {
		load();
		gsDeleteTexture(TextureEnd_);
		isEnd_ = true;
	}
	frameTime_++;
}

// 描画
void LoadScene::draw() const {
	gsDrawSprite2D(TextureEnd_, 0, 0, 0, 0, 0, 0);
}

// 終了しているか？
bool LoadScene::isEnd() const {
	return isEnd_;
}

// 次のシーンを返す
Scene LoadScene::next() const {
	return Scene::Title;
}

// 終了
void LoadScene::end() {
}

//リソース読み込み
void LoadScene::load() {
	gsLoadMesh(Mesh_Player, "res/model/Kendo/kendo.msh");
	gsLoadMesh(Mesh_Enemy, "res/model/Karate/karate.msh");
	gsLoadMesh(Mesh_SkyBox, "res/model/sky/skydome.msh");

	gsLoadSkeleton(Skl_Player, "res/model/Kendo/kendo.skl");
	gsLoadSkeleton(Skl_Enemy, "res/model/Karate/karate.skl");

	gsLoadAnimation(Anm_Player, "res/model/Kendo/kendo.anm");
	gsLoadAnimation(Anm_Enemy, "res/model/Karate/karate.anm");

	gsLoadOctree(Oct_Field, "res/model/koutei/koutei.oct");

	gsLoadTexture(Texture_Number, "res/texture/num.png");
	gsLoadTexture(Texture_Text, "res/texture/text.png");
	gsLoadTexture(Texture_Title, "res/texture/title.bmp");
	gsLoadTexture(Texture_Osu, "res/texture/osu.png");
	gsLoadTexture(Texture_Karate, "res/texture/mini_karate.png");
	gsLoadTexture(Texture_Kendo, "res/texture/mini_kendo.png");
	gsLoadTexture(Texture_Blue, "res/texture/blue.png");
	gsLoadTexture(Texture_Radar, "res/texture/radar.png");
	gsLoadTexture(Texture_Point, "res/texture/pt.png");
	gsLoadTexture(Texture_Result1, "res/texture/result1.png");
	gsLoadTexture(Texture_Result2, "res/texture/result2.png");

	gsLoadMusic(Music_Title, "res/sound/title.wav", GS_TRUE);
	gsLoadMusic(Music_GamePlay, "res/sound/kendo.wav", GS_TRUE);
	gsLoadMusic(Music_Ending, "res/sound/ed.wav", GS_TRUE);

	gsLoadSE(SE_PlayerAttack, "res/sound/Attack1.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SE_PlayerDamage, "res/sound/Damage2.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SE_EnemyDead, "res/sound/Attack2.wav", 5, GWAVE_DEFAULT);
	gsLoadSE(SE_Select, "res/sound/Select.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SE_TimeUp, "res/sound/timeend.wav", 1, GWAVE_DEFAULT);
}