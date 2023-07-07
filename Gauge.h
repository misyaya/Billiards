#pragma once
#include "Engine/GameObject.h"


//���������Ǘ�����N���X
class Gauge : public GameObject
{
private:
    int hPictGauge_;    //�摜�ԍ�(�Q�[�W�̒��g)
    int hPictFrame_;    //�摜�ԍ�(�Q�[�W�̊O�g)

    float nowHp_;       //���̒l
    const float maxHp_ = 1.0f; //�ő�l
    float animHp_; //�\���p�̒l
    int ImageWidth;   //�Q�[�W�摜�̕�
    int ImageHeight;  //�Q�[�W�摜�̍���


    bool flag = true;
    float power = 0;
    float scalex = 1.3f;
   
public:
    static constexpr float MIN = 0.0f;
    static constexpr float MAX = 1.0f;

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

    void SetHp(float nowHp, float maxHp)
    {
       /* nowHp_ = nowHp;
        maxHp_ = maxHp;
        animHp_ = (animHp_ * 4 + nowHp_ )/5;*/
        //animHp_ = ( animHp_  + nowHp_ ) / 2;
    }

    void SetPosition(float x, float y, float z);

    /// <summary>
    /// �l�������Z����
    /// </summary>
    /// <param name="v"></param>
    void AddValue(float v);

    void SetValue(float v);

    float GetValue();
};