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
	
	//�v���C���[�����삷���
	void SetMyBall(Ball* ball){ myBall = ball; }
	void Release();
private:
	Ball* myBall;
	float direction; //����(Y��]�̊p�x�F���W�A��)
	float power; //�͂̑傫��
	int hModel_;    //���f���ԍ�
	
	int nowHp_, maxHp_;
	bool flag;
	int hSound_;    //�T�E���h�ԍ�
	int hEmit;
};

