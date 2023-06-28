#include "Player.h"
#include "Ball.h"
#include"Engine/Input.h"
#include "Engine/Model.h"
#include "Gauge.h"
#include "Engine/VFX.h"
/*
* �L�[�{�[�h��
* �ʂ̌����𓮂����ā@���˂���
* �Q�[�W�������肳���肷��
* �Q�[�W�������ق�player�p���[�A�b�v
* 
* �Q�[�W�傫������
* �{�[�����Ԃ���Ƃ��ɉ�������
* �Q�[�W�}�b�N�X�܂ł������Ƃ��Ƀo�[�ɃG�t�F�N�g������
* 
* �ǂɂԂ���ƂȂ�܂�
* �{�[�����m���Ԃ������Ƃ����炵�������ǃ_���ł���
* 
*/

Player::Player(GameObject* parent)
	:maxHp_(180), nowHp_(0)
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
			if (nowHp_ > maxHp_ + 15)
			{
				flag = false;
				EmitterData  data;
				data.textureFileName = "circle_Y.png";

				data.position.x =-33.0f;
				data.position.z =10.0f;
				data.positionRnd = XMFLOAT3(0.0f, 0.1, 0.0f);
				data.delay = 5;
				data.lifeTime = 150;
				data.accel = 0.98;

				//data.direction = XMFLOAT3(0, 10, 0);
				data.size = XMFLOAT2(2, 2);
				data.sizeRnd = XMFLOAT2(0.4, 0.4);
				data.scale = XMFLOAT2(1.01f, 1.01f);
				data.color.w = 0.2f; //�s�����x
				data.deltaColor.w = -0.002;
				data.position.y = -2.0f;
				data.rotateRnd.z = 180; //-180�`180 
				//data.spin.z = 0.2f;

				
				hEmit = VFX::Start(data);	//�G�~�b�^�[��ݒu
				
			}

		}

		

		if (!flag)
		{
			nowHp_ -= 10;
			power -= 0.2f;
			if (nowHp_ + 15 < -1)
			{
				flag = true;
				VFX::End(hEmit);
			}
				
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

}

void Player::Release()
{
	
}
