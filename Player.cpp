#include "Player.h"
#include "Ball.h"
#include"Engine/Input.h"
#include "Engine/Model.h"
#include "Gauge.h"

/*
* �L�[�{�[�h��
* �ʂ̌����𓮂����ā@���˂���
* �Q�[�W�������肳���肷��
* �Q�[�W�������ق�player�p���[�A�b�v
* 
* 
* 
* 
*/

Player::Player(GameObject* parent)
	:maxHp_(180), nowHp_(0), pText(nullptr)
{
	direction = 0.0f;
	power = 0.0f;
	hModel_ = Model::Load("DebugCollision/SphereCollider.fbx");
	transform_.scale_ = XMFLOAT3(0.2, 0.2, 0.2);
}

Player::~Player()
{

}

void Player::Initilaize()
{
	pText = new Text;

	pText->Initialize();
	
}

void Player::Update()
{
	

	if (Input::IsKey(DIK_W))
		direction = 0.0f;
	if (Input::IsKey(DIK_A))
		direction -= 0.05;
	if (Input::IsKey(DIK_D))
		direction += 0.05;


	if (Input::IsKey(DIK_SPACE))
	{
		if (flag) {
			nowHp_ += 5;
			power += 0.1;
			if (nowHp_ > maxHp_ + 10)
				flag = false;
		}

		

		if (!flag)
		{
			nowHp_ -= 10;
			power -= 0.2f;
			if (nowHp_+15 < -1)
				flag = true;
		}
	}



	Gauge* pGauge = (Gauge*)FindObject("Gauge");
	pGauge->SetHp(nowHp_, maxHp_);



	if (Input::IsKeyUp(DIK_SPACE))
	{
	
		//�����ŋʂ�ł�
		XMVECTOR base = XMVectorSet(0, 0, power, 0);  //��]���ĂȂ����Ɉړ�����x�N�g��
		XMMATRIX yrot = XMMatrixRotationY(direction); //��]�s��������
		XMVECTOR v = XMVector3Transform(base, yrot);  //���̉�]�Ńx�N�g���̌�����ς���
		myBall->AddForce(v); //���ꂪ��]��̈ړ��x�N�g��
	}
	
}

void Player::Draw()
{
	//transform_.position_ ��ݒ�
	//�����������_�ɂ���Ƃ��āA�������̂ǂ��ɕ\�����邩�����߂�
	XMVECTOR base = XMVectorSet(0, 0, 1.2f, 0);
	XMMATRIX yrot = XMMatrixRotationY(direction);
	XMVECTOR v = XMVector3Transform(base, yrot);
	//�����ɁA�������̍��W�𑫂���
	//�\�����W�����܂�̂ŁAtransform_.position_�ɑ������
	transform_.position_ = myBall->GetPosition() + v;




	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

//	pText->Draw(10, 30, power);
}

void Player::Release()
{
	
}
