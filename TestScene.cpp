#include "TestScene.h"
#include"Ball.h"
#include"Engine/Camera.h"
#include"Player.h"
#include "Gauge.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 50, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));

	for (int i = 0; i < 9; i++)
	{
		Ball* b = Instantiate<Ball>(this);
		b->SetNumber(i + 1);
		b->SetPosition((i - 4) * 1.4, 0, (i - 4) * 1.4);
	}

	Player* p = Instantiate<Player>(this);
	Ball* b = Instantiate<Ball>(this);
	Instantiate<Gauge>(this);
	b->SetPosition(-10, 0, 10);
	b->SetNumber(0);//白玉
	p->SetMyBall(b);
}

//更新
void TestScene::Update()
{
	// ここでめり込んでる玉を探して引きはがす
	std::list<Ball*> balls = FindGameObjects<Ball>(); //すべてのボールのリスト
	for (auto itr1 = balls.begin(); itr1 != balls.end(); itr1++)
	{
		for (auto itr2 = itr1; itr2 != balls.end(); itr2++)
		{
			if (itr1 == itr2)
				continue;
			// *itr1と*itr2の座標を見て、むりやりはがす
			XMVECTOR distance = (*itr1)->GetPosition() - (*itr2)->GetPosition();
			if (Length(distance) < 1.0f * 2.0f) // 重なっている
			{
				float depth = 1.0f * 2.0f - Length(distance); // めり込み量
				//めり込み量の半分ずつ移動すればいい
				distance = XMVector3Normalize(distance) * depth / 2.0f; // 押す量
				(*itr1)->SetPosition((*itr1)->GetPosition() + distance);
				(*itr2)->SetPosition((*itr2)->GetPosition() + distance * (-1.0f));
			}
		}
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
