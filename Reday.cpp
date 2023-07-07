#include "Reday.h"
#include"Engine/Image.h"

namespace {
    float startX; //�ړ��J�nX���W
    float endX;   //�ړ��I��X���W
    float totalTime; //�ړ�����(�b)
    float currentTime; //���݂̎���

    int seq_line; //�����s���Ă���s
    float seq_time; //�V�[�P���X�����s���Ă��鎞��
    
    enum ACT { //��邱�Ƃ��R�}���h��
        A_SLIDEIN = 1,
        A_WAIT,
        A_SLIDEOUT,
        A_END
    };
    struct Sepuence {
        float time; //����
        int action; //��邱��
        float param; //�K�v�Ȓl
    };

    Sepuence tbl[] = {
        {0.0f, A_SLIDEIN, 5.0f}, //�܂��̓X���C�h�C��
        {3.0f, A_WAIT, 0.0f/*�Ӗ��Ȃ�*/}, //1�b�܂��Ă���
        {4.0f, A_SLIDEOUT, -5.0f}, //�X���C�h�A�E�g
        {5.0f, A_END, 0.0f} //�����ŏ�����
    };
    ACT currentAction; //�����s���Ă���A�N�V����
    bool canMove; //�ړ��ł���
};

//�R���X�g���N�^
Ready::Ready(GameObject* parent)
    :GameObject(parent, "Ready"),hPict_(-1)
{
    seq_line = -1;
    seq_time = 0.0f;
    canMove = false;
}

//�f�X�g���N�^
Ready::~Ready()
{
}

//������
void Ready::Initialize()
{
    //�摜�f�[�^�̃��[�h
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
//���T�C�g�ɂ������C�[�W���O�֐�
float easeInCubic(float x)
{
    return x * x * x;
}


//�X�V
void Ready::Update()
{
    seq_time += 1.0f / 60.0f;
    if (seq_time >= tbl[seq_line + 1].time) { // ���̍s�����s����
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
        //���̍s�̎��s������
    }

    currentTime += 1.0f / 60.0f; //1�t���[�����̎��Ԃ�i�܂���
    if (currentTime > totalTime)
        currentTime = totalTime;
    float t = currentTime / totalTime;//������0.0�`1.0�͈̔͂ɂ���
    float val = easeInCubic(t);//�C�[�W���O�֐����Ă�(t)  �A���Ă����l��0.0�`1.0
    //val�����Ƃ�transform_.position_��ݒ肷��
    transform_.position_.x = val * (endX - startX) + startX;

}

//�`��
void Ready::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

bool Ready::Finished()
{
    return canMove;
}

//�J��
void Ready::Release()
{
}