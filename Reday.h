#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Ready : public GameObject
{
private:
    int hPict_;    //�摜�ԍ�
public:
    //�R���X�g���N�^
    Ready(GameObject* parent);

    //�f�X�g���N�^
    ~Ready();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    bool Finished(); //Ready���I�������ture

    //�J��
    void Release() override;
};
