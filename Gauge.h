#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Gauge : public GameObject
{
    int hPictGauge_;    //�摜�ԍ�(�Q�[�W�̒��g)
    int hPictFrame_;    //�摜�ԍ�(�Q�[�W�̊O�g)

    int nowHp_, maxHp_, animHp_;

    bool flag = true;
    float power = 0;
   
public:
    //�R���X�g���N�^
    Gauge(GameObject* parent);

    //�f�X�g���N�^
    ~Gauge();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetHp(int nowHp, int maxHp)
    {
        nowHp_ = nowHp;
        maxHp_ = maxHp;
        animHp_ = (animHp_ * 4 + nowHp_) / 5;
        //animHp_ = ( animHp_  + nowHp_ ) / 2;
    }
};