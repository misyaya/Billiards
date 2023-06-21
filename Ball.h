#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Ball : public GameObject
{
    
public:
    //コンストラクタ
    Ball(GameObject* parent);

    //デストラクタ
    ~Ball();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //ボール番号（1～9を指定）白玉は0
    void SetNumber(int no);

    //ボールに力を加える
    void AddForce(XMVECTOR f);



    //開放
    void Release() override;

    XMVECTOR GetVelosity() { return velocity; }
    XMFLOAT3 GetNextPosition() { return GetPosition() + velocity; }

private:
    int hModel_;    //モデル番号
    int number; //ボールの番号
    XMVECTOR velocity;//移動速度

    

  
};