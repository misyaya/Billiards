#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject {
public:
	Button(GameObject* parent);
	~Button();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	bool Finished(); // Buttonが終わったらtrue
	void SetImage(std::string normal, std::string pushed); //ボタン
	void SetPosition(int x, int y); //ボタン表示位置
	void Push(bool pushed); //ボタンを押したか、押してないか
	bool MouseInArea(XMFLOAT3 mousePos); //マウスボタン内に入っているか
	/// <summary>
	/// ボタンを移動させる
	/// </summary>
	/// <param name="toX">移動後の座標X</param>
	/// <param name="toY">移動後の座標Y</param>
	/// <param name="seconds">移動時間(秒)</param>
	void SetMovePosition(int toX, int toY, float seconds);

	/// <summary>
	/// 動いてるならture
	/// </summary>
	/// <returns></returns>
	bool IsMoving();

	/// <summary>
	/// 強制的に移動を終了させる
	/// </summary>
	void ForceMoveEnd();

private:
	int hImage; // 通常画像
	int hPush; // 押された画像
	bool pushed; // 押されているか

	XMFLOAT3 center; // ボタンの中心座標(画面座標)
	XMFLOAT3 size; // ボタンの画像サイズ

	// 動きを作る
	XMFLOAT3 startPos;
	XMFLOAT3 endPos;
	float totalTime;
	float currnetTime;
};