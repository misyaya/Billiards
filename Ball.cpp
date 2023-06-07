#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include<assert.h>
//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1)
{
    velocity = XMVectorSet(0, 0, 0, 0);
}

//デストラクタ
Ball::~Ball()
{
    if (hModel_ > 0)
        Model::Release(hModel_);
}

//初期化
void Ball::Initialize()
{
}

//更新
void Ball::Update()
{
    // 0.001ずつ減る
    // velocityの長さlenを求める
    // lenから0.001減らす(0以下になったら0にする)
    // velocityの長さをlenにする
    float len = Length(velocity);
    len -= 0.001f;
    if (len < 0.0f)
        len = 0.0f;
    velocity = XMVector3Normalize(velocity) * len;
    
    //ボールどうしで反射する
    std::list<Ball*>all = FindGameObjects<Ball>();
    for (std::list<Ball*>::iterator itr = all.begin(); itr != all.end(); itr++)
    {
        if (*itr == this) continue;
        XMFLOAT3 next = transform_.position_ + velocity; //自分の移動後の位置
        XMFLOAT3 other = (*itr)->GetNextPosition();      //相手の移動後の位置
        //if(nextとotherが重なったら)
    }

    //壁に反射する
    XMFLOAT3 next = transform_.position_ + velocity;
    if (next.x >= 30.0f)
    {
        XMVECTOR n = XMVectorSet(-1, 0, 0, 0); //右の壁の法線(長さが1)
        n = n * -1; //逆向きにする=壁に向かうベクトル
        XMVECTOR ipvec = XMVector3Dot(velocity, n);
        float ip = XMVectorGetX(ipvec); //壁を押す力の大きさ
        XMVECTOR push = n * ip; //壁を押すベクトル
        XMVECTOR th = velocity - push; //壁に沿ってるベクトル
        push *= -1; //押し返されたベクトル
        velocity = push + th;

      /*
        XMFLOAT3 f;
        XMStoreFloat3(&f,velocity);
        f.x = -f.x;
        //f.x = 0; 壁すりはこれ
        //fを加工して
        velocity = XMLoadFloat3(&f);
       */
    }
    if (next.x <= -30.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.x = -f.x;
        //fを加工して
        velocity = XMLoadFloat3(&f);
    }
    if (next.z >= 20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.z = -f.z;
        //fを加工して
        velocity = XMLoadFloat3(&f);
    }
    if (next.z <= -20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.z = -f.z;
        //fを加工して
        velocity = XMLoadFloat3(&f);
    }

    transform_.position_ += velocity;
}

//描画
void Ball::Draw()
{
    if (hModel_ < 0)
        return;

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

void Ball::SetNumber(int no)
{
    number = no;
    hModel_ = Model::Load("DebugCollision/SphereCollider.fbx");
    assert(hModel_ >= 0);   
}

void Ball::AddForce(XMVECTOR f)
{
    velocity += f;
}

//開放
void Ball::Release()
{
}