#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include<assert.h>
#include "Engine/Image.h"
#include "Engine/Audio.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1), hSound_(-1)
{
    velocity = XMVectorSet(0, 0, 0, 0);
}

//�f�X�g���N�^
Ball::~Ball()
{
    if (hModel_ > 0)
        Model::Release(hModel_);
}

//������
void Ball::Initialize()
{
    //�T�E���h�f�[�^�̃��[�h

    hSound_ = Audio::Load("A4_11166.WAV");

    assert(hSound_ >= 0);
}

//�X�V
void Ball::Update()
{
    // 0.001������
    // velocity�̒���len�����߂�
    // len����0.001���炷(0�ȉ��ɂȂ�����0�ɂ���)
    // velocity�̒�����len�ɂ���
    float len = Length(velocity);
    len -= 0.001f;
    if (len < 0.0f)
        len = 0.0f;
    velocity = XMVector3Normalize(velocity) * len;
    
    //�{�[���ǂ����Ŕ��˂���
    std::list<Ball*>all = GetParent()->FindGameObjects<Ball>();
    for (std::list<Ball*>::iterator itr = all.begin(); itr != all.end(); itr++)
    {
        if (*itr == this) continue;
        XMFLOAT3 next = transform_.position_ + velocity; //�����̈ړ���̈ʒu
        XMFLOAT3 other = (*itr)->GetNextPosition();      //����̈ړ���̈ʒu
        if (Length(next-other) < 1.0f*2.0f)  //���̔��a2��
        {
           
            XMVECTOR n = other - next;
            n = XMVector3Normalize(n);   //���̒������P�ɂ���
            XMVECTOR powDot = XMVector3Dot(velocity,n);
            float pow = XMVectorGetX(powDot);
            //n�͉����͂̌����Apow�͉����͂̑傫��
            XMVECTOR push = n * pow; //�����x�N�g��������ɓn������
            velocity -= push;
            (*itr)->AddForce(push);


            n = next - other;
            n = XMVector3Normalize(n);   //���̒������P�ɂ���
            powDot = XMVector3Dot((*itr)->GetVelosity(),n);
            pow = XMVectorGetX(powDot); //�����͂̑傫��
            //n�͉����͂̌����Apow�͉����͂̑傫��
            push = n * pow; //�����x�N�g��������ɓn������
            (*itr)->AddForce(-push); //���肩�����
            AddForce(push); //�����ɉ�����

           
        }
       
    }

    //�ǂɔ��˂���
    XMFLOAT3 next = transform_.position_ + velocity;
    if (next.x >= 30.0f)
    {
        XMVECTOR n = XMVectorSet(-1, 0, 0, 0); //�E�̕ǂ̖@��(������1)
        n = n * -1; //�t�����ɂ���=�ǂɌ������x�N�g��
        XMVECTOR ipvec = XMVector3Dot(velocity, n);
        float ip = XMVectorGetX(ipvec); //�ǂ������͂̑傫��
        XMVECTOR push = n * ip; //�ǂ������x�N�g��
        XMVECTOR th = velocity - push; //�ǂɉ����Ă�x�N�g��
        push *= -1; //�����Ԃ��ꂽ�x�N�g��
        velocity = push + th;

      /*
        XMFLOAT3 f;
        XMStoreFloat3(&f,velocity);
        f.x = -f.x;
        //f.x = 0; �ǂ���͂���
        //f�����H����
        velocity = XMLoadFloat3(&f);
       */
    }
    if (next.x <= -30.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.x = -f.x;
        //f�����H����
        velocity = XMLoadFloat3(&f);
        Audio::Play(hSound_);
    }
    if (next.z >= 20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.z = -f.z;
        //f�����H����
        velocity = XMLoadFloat3(&f);
        Audio::Play(hSound_);
    }
    if (next.z <= -20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.z = -f.z;
        //f�����H����
        velocity = XMLoadFloat3(&f);
        Audio::Play(hSound_);
    }

    transform_.position_ += velocity;
}

//�`��
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

//�J��
void Ball::Release()
{
}