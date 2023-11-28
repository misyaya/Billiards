//#pragma once
//#include "Engine/GameObject.h"
//
////�e�X�g�V�[�����Ǘ�����N���X
//class TitleScene : public GameObject
//{
//	int hGive_;    //�摜�ԍ�
//	int hBack_;    //�摜�ԍ�
//	int pushG_;    //�摜�ԍ�
//	int pushB_;    //�摜�ԍ�
//
//	bool flag_;
//
//	Transform giveTransform_;
//	Transform backTransform_;
//public:
//	//�R���X�g���N�^
//	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
//	TitleScene(GameObject* parent);
//
//	//������
//	void Initialize() override;
//
//	//�X�V
//	void Update() override;
//
//	//�`��
//	void Draw() override;
//
//	//�J��
//	void Release() override;
//};

#pragma once
#include "Engine/GameObject.h"

class Button;

//�^�C�g���V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
private:
	Button* start;
	Button* back;
	enum SELECT {
		NONE = -1,
		START = 0,
		BACK,
	};
	SELECT selected;
};