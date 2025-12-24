#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "GamePlayScene.h"
#include"Resource.h"
#include<GSmusic.h>
#include"LoadScene.h"

// コンストラクタ
Game::Game() :
	gslib::Game(1024, 768){
}

//デストラクタ
Game::~Game() {
	unsigned int i;

	for (i = 0; i < MeshEnd_; i++) gsDeleteMesh(i);
	for (i = 0; i < SklEnd_; i++) gsDeleteSkeleton(i);
	for (i = 0; i < AnmEnd_; i++) gsDeleteAnimation(i);
	for (i = 0; i < OctEnd_; i++) gsDeleteOctree(i);
	for (i = 0; i < TextureEnd_; i++) gsDeleteTexture(i);
	for (i = 0; i < MusicEnd_; i++) gsDeleteMusic(i);
	for (i = 0; i < SEEnd_; i++) gsDeleteSE(i);
}

// 開始
void Game::start() {
	sceneManager_.add(Scene::Load, std::make_shared<LoadScene>());
	sceneManager_.add(Scene::Title, std::make_shared<TitleScene>());
	sceneManager_.add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	sceneManager_.change(Scene::Load);
}

// 更新
void Game::update(float deltaTime) {
	sceneManager_.update(deltaTime);
}

// 描画
void Game::draw() {
	sceneManager_.draw();
}

// 描画
void Game::end() {
	sceneManager_.end();
}