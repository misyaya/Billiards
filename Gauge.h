#pragma once
#include "Engine/GameObject.h"


//◆◆◆を管理するクラス
class Gauge : public GameObject
{
private:
    int hPictGauge_;    //画像番号(ゲージの中身)
    int hPictFrame_;    //画像番号(ゲージの外枠)

    float nowHp_;       //今の値
    const float maxHp_ = 1.0f; //最大値
    float animHp_; //表示用の値
    int ImageWidth;   //ゲージ画像の幅
    int ImageHeight;  //ゲージ画像の高さ


    bool flag = true;
    float power = 0;
    float scalex = 1.3f;
   
public:
    static constexpr float MIN = 0.0f;
    static constexpr float MAX = 1.0f;

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

    void SetHp(float nowHp, float maxHp)
    {
       /* nowHp_ = nowHp;
        maxHp_ = maxHp;
        animHp_ = (animHp_ * 4 + nowHp_ )/5;*/
        //animHp_ = ( animHp_  + nowHp_ ) / 2;
    }

    void SetPosition(float x, float y, float z);

    /// <summary>
    /// 値を加減算する
    /// </summary>
    /// <param name="v"></param>
    void AddValue(float v);

    void SetValue(float v);

    float GetValue();
};