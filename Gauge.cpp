#include "Gauge.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include"Player.h"
#include<assert.h>

//コンストラクタ
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1)
{
    
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
    //画像データのロード
    hPictGauge_ = Image::Load("LifeGauge.png");
    assert(hPictGauge_ >= 0);

    //画像データのロード
    hPictFrame_ = Image::Load("LifeGauge_Frame.png");
    assert(hPictFrame_ >= 0);

    ImageWidth = Image::GetWidth(hPictGauge_);
    ImageHeight = Image::GetHeight(hPictGauge_);


    /*transform_.position_.x = -0.9f;
    transform_.position_.y = -0.5f;
    transform_.position_.z = 10.0f;*/

    transform_.rotate_.z = 90.0f;
    transform_.scale_.x = scalex;

}

//更新
void Gauge::Update()
{
    
}

//描画
void Gauge::Draw()
{

    //Transform transGauge = transform_;
    //transGauge.scale_.x = (float)animHp_ * scalex / (float)maxHp_;

    int left = ImageWidth / 2 - ImageWidth / 2 * nowHp_;
    int width = ImageWidth * nowHp_;
    Image::SetRect(hPictGauge_,left,0,width,ImageHeight );
    Image::SetTransform(hPictGauge_, transform_);
    Image::Draw(hPictGauge_);


    Image::SetTransform(hPictFrame_, transform_);
    Image::Draw(hPictFrame_);
}

//開放
void Gauge::Release()
{
}

void Gauge::SetPosition(float x, float y, float z)
{
    transform_.position_.x = x;
    transform_.position_.y = y;
    transform_.position_.z = z;
}

void Gauge::AddValue(float v)
{
    nowHp_ += v;
    if (nowHp_ < 0.0f)
        nowHp_ = 0.0f;
    else if (nowHp_ > maxHp_)
        nowHp_ = maxHp_;
}

void Gauge::SetValue(float v)
{
    assert(v >= 0.0f && v <= 1.0f);

    nowHp_ = v;
    if (nowHp_ < 0.0f)
        nowHp_ = 0.0f;
    else if (nowHp_ > maxHp_)
        nowHp_ = maxHp_;
}

float Gauge::GetValue()
{
    return nowHp_;
}
