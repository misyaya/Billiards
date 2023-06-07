#include "Player.h"
#include "Ball.h"
#include"Engine/Input.h"
#include "Engine/Model.h"

Player::Player(GameObject* parent)
{
	direction = 0.0f;
	power = 0.3f;
	hModel_ = Model::Load("DebugCollision/SphereCollider.fbx");
	transform_.scale_ = XMFLOAT3(0.2, 0.2, 0.2);
}

Player::~Player()
{

}

void Player::Update()
{
	if (Input::IsKey(DIK_A))
		direction -= 0.01;
	if (Input::IsKey(DIK_D))
		direction += 0.01;
	if (Input::IsKeyDown(DIK_SPACE))
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
}
