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
		//ここで玉を打つ
		XMVECTOR base = XMVectorSet(0, 0, power, 0);  //回転してない時に移動するベクトル
		XMMATRIX yrot = XMMatrixRotationY(direction); //回転行列を作って
		XMVECTOR v = XMVector3Transform(base, yrot);  //その回転でベクトルの向きを変える
		myBall->AddForce(v); //これが回転後の移動ベクトル
	}
}

void Player::Draw()
{
	//transform_.position_ を設定
	//白い球が原点にあるとして、白い球のどこに表示するかを求める
	XMVECTOR base = XMVectorSet(0, 0, 1.2f, 0);
	XMMATRIX yrot = XMMatrixRotationY(direction);
	XMVECTOR v = XMVector3Transform(base, yrot);
	//そこに、白い球の座標を足せば
	//表示座標が求まるので、transform_.position_に代入する
	transform_.position_ = myBall->GetPosition() + v;




	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
