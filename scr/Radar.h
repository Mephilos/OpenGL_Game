#ifndef RADAR_H_
#define RADAR_H_

class Actor;
enum class ActorGroup;
class World;

//レーダークラス
class Radar {
public:
	//コンストラクタ
	Radar();
	Radar(World* world);
	//描画
	void draw() const;

private:
	//敵描画
	void drawEnemy() const;

private:
	World* world_;
};

#endif