#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Gauge : public GameObject
{
    int hPictGauge_;    //画像番号(ゲージの中身)
    int hPictFrame_;    //画像番号(ゲージの外枠)

    int nowHp_, maxHp_, animHp_;

    bool flag = true;
    float power = 0;
   
public:
    //コンストラクタ
    Gauge(GameObject* parent);

    //デストラクタ
    ~Gauge();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetHp(int nowHp, int maxHp)
    {
        nowHp_ = nowHp;
        maxHp_ = maxHp;
        animHp_ = (animHp_ * 4 + nowHp_) / 5;
        //animHp_ = ( animHp_  + nowHp_ ) / 2;
    }
};