#include "Gauge.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include"Player.h"

//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1)
{
    
}

//�f�X�g���N�^
Gauge::~Gauge()
{
}

//������
void Gauge::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPictGauge_ = Image::Load("LifeGauge.png");
    assert(hPictGauge_ >= 0);

    //�摜�f�[�^�̃��[�h
    hPictFrame_ = Image::Load("LifeGauge_Frame.png");
    assert(hPictFrame_ >= 0);


    transform_.position_.x = -0.90f;
  //  transform_.position_.y = 0.85f;
    transform_.position_.z = -6.0f;

    transform_.rotate_.z = 90.0f;
    transform_.scale_.x = 1.3f;

}

//�X�V
void Gauge::Update()
{
}

//�`��
void Gauge::Draw()
{

    Transform transGauge = transform_;
    transGauge.scale_.x = (float)animHp_ / (float)maxHp_;

    Image::SetTransform(hPictGauge_, transGauge);
    Image::Draw(hPictGauge_);


    Image::SetTransform(hPictFrame_, transform_);
    Image::Draw(hPictFrame_);
}

//�J��
void Gauge::Release()
{
}