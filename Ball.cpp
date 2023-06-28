#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include<assert.h>
#include "Engine/Image.h"
#include "Engine/Audio.h"

//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1), hSound_(-1)
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
    //サウンドデータのロード

    hSound_ = Audio::Load("A4_11166.WAV");

    assert(hSound_ >= 0);
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
    std::list<Ball*>all = GetParent()->FindGameObjects<Ball>();
    for (std::list<Ball*>::iterator itr = all.begin(); itr != all.end(); itr++)
    {
        if (*itr == this) continue;
        XMFLOAT3 next = transform_.position_ + velocity; //自分の移動後の位置
        XMFLOAT3 other = (*itr)->GetNextPosition();      //相手の移動後の位置
        if (Length(next-other) < 1.0f*2.0f)  //球の半径2個分
        {
           
            XMVECTOR n = other - next;
            n = XMVector3Normalize(n);   //ｎの長さを１にする
            XMVECTOR powDot = XMVector3Dot(velocity,n);
            float pow = XMVectorGetX(powDot);
            //nは押す力の向き、powは押す力の大きさ
            XMVECTOR push = n * pow; //押すベクトル→相手に渡した力
            velocity -= push;
            (*itr)->AddForce(push);


            n = next - other;
            n = XMVector3Normalize(n);   //ｎの長さを１にする
            powDot = XMVector3Dot((*itr)->GetVelosity(),n);
            pow = XMVectorGetX(powDot); //押す力の大きさ
            //nは押す力の向き、powは押す力の大きさ
            push = n * pow; //押すベクトル→相手に渡した力
            (*itr)->AddForce(-push); //相手から引く
            AddForce(push); //自分に加える

           
        }
       
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
        Audio::Play(hSound_);
    }
    if (next.z >= 20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.z = -f.z;
        //fを加工して
        velocity = XMLoadFloat3(&f);
        Audio::Play(hSound_);
    }
    if (next.z <= -20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.z = -f.z;
        //fを加工して
        velocity = XMLoadFloat3(&f);
        Audio::Play(hSound_);
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
    std::string f = "Ball";
    f += std::to_string(no);
    f += ".fbx";
    number = no; 
   
   hModel_ = Model::Load(f);
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