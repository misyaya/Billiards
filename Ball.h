#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Ball : public GameObject
{
    
public:
    //�R���X�g���N�^
    Ball(GameObject* parent);

    //�f�X�g���N�^
    ~Ball();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�{�[���ԍ��i1�`9���w��j���ʂ�0
    void SetNumber(int no);

    //�{�[���ɗ͂�������
    void AddForce(XMVECTOR f);



    //�J��
    void Release() override;

    XMVECTOR GetVelosity() { return velocity; }
    XMFLOAT3 GetNextPosition() { return GetPosition() + velocity; }

private:
    int hModel_;    //���f���ԍ�
    int number; //�{�[���̔ԍ�
    XMVECTOR velocity;//�ړ����x

    

  
};