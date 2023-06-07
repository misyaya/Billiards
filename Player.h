#pragma once
#include"Engine/GameObject.h"

class Ball;

class Player :public GameObject
{

public:
	Player(GameObject* parent);
	~Player();
	void Update();
	void Draw();

	//�v���C���[�����삷���
	void SetMyBall(Ball* ball){ myBall = ball; }

private:
	Ball* myBall;
	float direction; //����(Y��]�̊p�x�F���W�A��)
	float power; //�͂̑傫��
	int hModel_;    //���f���ԍ�
};

