#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject {
public:
	Button(GameObject* parent);
	~Button();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	bool Finished(); // Button���I�������true
	void SetImage(std::string normal, std::string pushed); //�{�^��
	void SetPosition(int x, int y); //�{�^���\���ʒu
	void Push(bool pushed); //�{�^�������������A�����ĂȂ���
	bool MouseInArea(XMFLOAT3 mousePos); //�}�E�X�{�^�����ɓ����Ă��邩
	/// <summary>
	/// �{�^�����ړ�������
	/// </summary>
	/// <param name="toX">�ړ���̍��WX</param>
	/// <param name="toY">�ړ���̍��WY</param>
	/// <param name="seconds">�ړ�����(�b)</param>
	void SetMovePosition(int toX, int toY, float seconds);

	/// <summary>
	/// �����Ă�Ȃ�ture
	/// </summary>
	/// <returns></returns>
	bool IsMoving();

	/// <summary>
	/// �����I�Ɉړ����I��������
	/// </summary>
	void ForceMoveEnd();

private:
	int hImage; // �ʏ�摜
	int hPush; // �����ꂽ�摜
	bool pushed; // ������Ă��邩

	XMFLOAT3 center; // �{�^���̒��S���W(��ʍ��W)
	XMFLOAT3 size; // �{�^���̉摜�T�C�Y

	// ���������
	XMFLOAT3 startPos;
	XMFLOAT3 endPos;
	float totalTime;
	float currnetTime;
};