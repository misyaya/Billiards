#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Ready : public GameObject
{
private:
    int hPict_;    //画像番号
public:
    //コンストラクタ
    Ready(GameObject* parent);

    //デストラクタ
    ~Ready();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    bool Finished(); //Readyが終わったらture

    //開放
    void Release() override;
};
