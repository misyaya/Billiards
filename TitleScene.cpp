//#include "TitleScene.h"
//#include "Engine/Image.h"
//#include "Engine/Input.h"
//#include "Engine/SceneManager.h"
//
////�R���X�g���N�^
//TitleScene::TitleScene(GameObject* parent)
//	: GameObject(parent, "TitleScene"), hGive_(-1), hBack_(-1), pushG_(-1), pushB_(-1)
//{
//	
//	giveTransform_.position_.x = 0.0f;
//	giveTransform_.position_.y = -0.1f;
//	giveTransform_.scale_.x = 0.5f;
//	giveTransform_.scale_.y = 0.5f;
//
//	backTransform_.position_.x = 0.0f;
//	backTransform_.position_.y = -0.6f;
//	backTransform_.scale_.x = 0.5f;
//	backTransform_.scale_.y = 0.5f;
//}
//
////������
//void TitleScene::Initialize()
//{
//	//�摜�f�[�^�̃��[�h
//	hGive_= Image::Load("FoodButtonGive.png");
//	assert(hGive_ >= 0);
//
//	//�摜�f�[�^�̃��[�h
//	hBack_ = Image::Load("CommonButtonBack.png");
//	assert(hBack_ >= 0);
//
//	pushG_ = Image::Load("FoodButtonGiveDisable.png");
//	assert(pushG_ >= 0);
//
//	pushB_ = Image::Load("CommonButtonBackDisable.png");
//	assert(pushB_ >= 0);
//}
//
////�X�V
//void TitleScene::Update()
//{
//	if (Input::IsMouseButton(0))
//	{
//		flag_ = true;
//		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//		pSceneManager->ChangeScene(SCENE_ID_TEST);
//	}
//}
//
////�`��
//void TitleScene::Draw()
//{
//	Image::SetTransform(hGive_, giveTransform_);
//	Image::Draw(hGive_);
//
//	Image::SetTransform(hBack_, backTransform_);
//	Image::Draw(hBack_);
//
//	if (flag_)
//	{
//		Image::SetTransform(pushG_, giveTransform_);
//		Image::Draw(pushG_);
//	}
//
//
//	Image::SetTransform(pushB_, backTransform_);
//	Image::Draw(pushB_);
//}
//
////�J��
//void TitleScene::Release()
//{
//}

#include "TitleScene.h"
#include "Engine/Camera.h"
#include "Engine/Sprite.h"
#include "Engine/Input.h"
#include "Button.h"
#include "Engine/SceneManager.h"
//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//������
void TitleScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 50, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));

	start = Instantiate<Button>(this);
	start->SetImage("FoodButtonGive", "FoodButtonGiveDisabled");
	start->SetPosition(1920, 360 - 100);
	start->SetMovePosition(640, 360 - 100, 10.0f);
	back = Instantiate<Button>(this);
	back->SetImage("CommonButtonBack", "CommonButtonBackDisable");
	back->SetPosition(1920, 360 + 100);
	back->SetMovePosition(640, 360 + 100, 10.0f);
}

//�X�V
void TitleScene::Update()
{
	if (Input::IsMouseButtonDown(0)) {
		// �����Ă���Ȃ狭���X�g�b�v
		bool moving = false;
		if (start->IsMoving())
		{
			start->ForceMoveEnd();
			moving = true;
		}
		if (back->IsMoving())
		{
			back->ForceMoveEnd();
			moving = true;
		}
		// �����ĂȂ���Ή������s
		if (selected == START) {
			SceneManager* scene = dynamic_cast<SceneManager*>(FindObject("SceneManager"));
			scene->ChangeScene(SCENE_ID_TEST);
		}
	}
	XMFLOAT3 pos = Input::GetMousePosition();
	if (start->MouseInArea(pos)) {
		start->Push(true);
		back->Push(false);
		selected = START;
	}
	else if (back->MouseInArea(pos)) {
		back->Push(true);
		start->Push(false);
		selected = BACK;
	}
	else {
		start->Push(false);
		back->Push(false);
		selected = NONE;
	}
}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}