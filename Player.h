#pragma once
#include"Engine/GameObject.h"
#include "Engine/Text.h"

class Ball;

class Player :public GameObject
{
	
public:
	Player(GameObject* parent);
	~Player();
	void Initilaize();
	void Update();
	void Draw();
	
	//プレイヤーが操作する玉
	void SetMyBall(Ball* ball){ myBall = ball; }
	void Release();
private:
	Ball* myBall;
	float direction; //向き(Y回転の角度：ラジアン)
	float power; //力の大きさ
	int hModel_;    //モデル番号
	
	int nowHp_, maxHp_;
	bool flag;
	int hSound_;    //サウンド番号
	int hEmit;
};

