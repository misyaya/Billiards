#include "Gauge.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include"Player.h"

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


    transform_.position_.x = -0.90f;
  //  transform_.position_.y = 0.85f;
    transform_.position_.z = -6.0f;

    transform_.rotate_.z = 90.0f;
    transform_.scale_.x = 1.3f;

}

//更新
void Gauge::Update()
{
}

//描画
void Gauge::Draw()
{

    Transform transGauge = transform_;
    transGauge.scale_.x = (float)animHp_ / (float)maxHp_;

    Image::SetTransform(hPictGauge_, transGauge);
    Image::Draw(hPictGauge_);


    Image::SetTransform(hPictFrame_, transform_);
    Image::Draw(hPictFrame_);
}

//開放
void Gauge::Release()
{
}