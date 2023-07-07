#include "Reday.h"
#include"Engine/Image.h"

namespace {
    float startX; //移動開始X座標
    float endX;   //移動終了X座標
    float totalTime; //移動時間(秒)
    float currentTime; //現在の時間

    int seq_line; //今実行している行
    float seq_time; //シーケンスを実行している時間
    
    enum ACT { //やることをコマンドに
        A_SLIDEIN = 1,
        A_WAIT,
        A_SLIDEOUT,
        A_END
    };
    struct Sepuence {
        float time; //時間
        int action; //やること
        float param; //必要な値
    };

    Sepuence tbl[] = {
        {0.0f, A_SLIDEIN, 5.0f}, //まずはスライドイン
        {3.0f, A_WAIT, 0.0f/*意味なし*/}, //1秒まってから
        {4.0f, A_SLIDEOUT, -5.0f}, //スライドアウト
        {5.0f, A_END, 0.0f} //ここで消える
    };
    ACT currentAction; //今実行しているアクション
    bool canMove; //移動できる
};

//コンストラクタ
Ready::Ready(GameObject* parent)
    :GameObject(parent, "Ready"),hPict_(-1)
{
    seq_line = -1;
    seq_time = 0.0f;
    canMove = false;
}

//デストラクタ
Ready::~Ready()
{
}

//初期化
void Ready::Initialize()
{
    //画像データのロード
    hPict_ = Image::Load("READY.png");
    assert(hPict_ >= 0);

    startX = 3.0f;
    endX = 0.0f;
    totalTime = 3.0f;
    currentTime = 0.0f;
}


//function easeInCubic(x: number) : number
//{
//        return x * x * x;
//}
//↑サイトにあったイージング関数
float easeInCubic(float x)
{
    return x * x * x;
}


//更新
void Ready::Update()
{
    seq_time += 1.0f / 60.0f;
    if (seq_time >= tbl[seq_line + 1].time) { // 次の行を実行する
        seq_line++;
        switch (tbl[seq_line].action){
        case A_END:
            KillMe();
            break;
        case A_SLIDEIN:
            startX = tbl[seq_line].param;
            endX = 0;
            totalTime = tbl[seq_line +1 ].time - seq_time;
            currentTime = 0.0f;
            break;
        case A_WAIT:
            startX = transform_.position_.x;
            endX = transform_.position_.x;
            totalTime = tbl[seq_line + 1].time - seq_time;
            currentTime = 0.0f;
            break;
        case A_SLIDEOUT:
            canMove = true;
            startX = transform_.position_.x;
            endX = tbl[seq_line].param;
            totalTime = tbl[seq_line + 1].time - seq_time;
            currentTime = 0.0f;
            break;
        }
        //その行の実行をする
    }

    currentTime += 1.0f / 60.0f; //1フレーム分の時間を進ませる
    if (currentTime > totalTime)
        currentTime = totalTime;
    float t = currentTime / totalTime;//ここを0.0～1.0の範囲にする
    float val = easeInCubic(t);//イージング関数を呼ぶ(t)  帰ってきた値は0.0～1.0
    //valをもとにtransform_.position_を設定する
    transform_.position_.x = val * (endX - startX) + startX;

}

//描画
void Ready::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

bool Ready::Finished()
{
    return canMove;
}

//開放
void Ready::Release()
{
}