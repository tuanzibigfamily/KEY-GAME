//������ ɭ����ϫ�磬2024.7.24����ɣ�С��Ϸֻ��Ϊ���������ģ����������Ҫ���Ƶĵط���
// ��ӭ��¼github���뽨�裬��Ŀ��ַΪ��https://github.com/tuanzibigfamily/KEY-GAME
#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>  
#pragma comment(lib,"winmm.lib")//���ؾ�̬��
#include <ctime>
#include <iostream> // �������������
#include<math.h>
#include <windows.h>  
#include<string>
#include <cstdlib>    // ����stdlib.h
#include"��Ϸ��ʼ����.cpp"
#undef UNICODE
#undef _UNICODE

inline void putimage_alpha(int x, int y, IMAGE* img)//���ﱳ��ɫ͸����
{
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

// ���崰�ڴ�С����Ϸ��س���
const int WindowWidth = 800;
const int WindowHeight = 600;
const int GroundHeight = 32;
int idx_current_anim = 0;
static int counter = 0;

int pause_count = 0;//��ͣ����
// ��Ϸ״̬  
enum GameState { 
    PLAYING,
    PAUSED,
    MAIN_MENU,
    GAME_OVER
};

// ����ͼƬ��Դ
IMAGE imgBackground1_1; // 1-1�ؿ�����
IMAGE imgBackground1_2; // 1-2�ؿ�����
IMAGE imgBackground1_3; // 1-3�ؿ�����
IMAGE gameover_background;
IMAGE gamewin_background;

IMAGE imgGround;        // ����ͼ

IMAGE imgNagisa;         // ����ͼ
IMAGE imgMonster_One;       // ��԰������1ͼ
IMAGE imgMonster_OneTurn;
IMAGE imgMonster_Oneshouji;
IMAGE imgMonster_Oneshouji_zhezhao;
IMAGE imgMonster_Tow;       // ��԰������2ͼ
IMAGE imgMonster_TowTurn;

IMAGE imgBullet_yuan;        // �ӵ�ͼ
IMAGE imgBullet_zhezhao;
IMAGE imgHaiXing_Animation_yuan1;//�ӵ�����ͼ���ڵװ׵�λ����ͼ
IMAGE imgHaiXing_Animation_zhezhao1;

IMAGE imgHaiXing_Animation_yuan2;//�ӵ�����ͼ
IMAGE imgHaiXing_Animation_zhezhao2;

IMAGE imgHaiXing_Animation_yuan3;//�ӵ�����ͼ
IMAGE imgHaiXing_Animation_zhezhao3;

IMAGE imgHaiXing_Animation_yuan4;//�ӵ�����ͼ
IMAGE imgHaiXing_Animation_zhezhao4;

IMAGE imgHaiXing_Animation_yuan5;//�ӵ�����ͼ
IMAGE imgHaiXing_Animation_zhezhao5;

 IMAGE imgBrick_1;         // ש��1ͼ
 IMAGE imgBrick_2;         // ש��2ͼ
 IMAGE imgBrick_3;         // ש��3ͼ
 IMAGE imgBrick_4;         // ש��4ͼ
 IMAGE imgBrick_5;         // ש��5ͼ
 IMAGE imgBrick_6;         // ש��6ͼ
 IMAGE imgBrick_7;         // ש��7ͼ
 IMAGE imgBrick_8;         // ש��8ͼ
 IMAGE imgBrick_9;         // ש��9ͼ
 

 //��������
 
 IMAGE img_ayuyi_left1;
 IMAGE img_ayuyi_left2;
 IMAGE img_ayuyi_left3;
 IMAGE img_ayuyi_left4;
 IMAGE img_ayuyi_left5;
 IMAGE img_ayuyi_left1_zhezhao;
 IMAGE img_ayuyi_left2_zhezhao;
 IMAGE img_ayuyi_left3_zhezhao;
 IMAGE img_ayuyi_left4_zhezhao;
 IMAGE img_ayuyi_left5_zhezhao;

 IMAGE img_ayuyi_right1;
 IMAGE img_ayuyi_right2;
 IMAGE img_ayuyi_right3;
 IMAGE img_ayuyi_right4;

 //IMAGE Cloudy;//�ƶ�
 struct Brick
 {
     int brick_width, brick_height; // ש���С  
     int x, y;//ש������
 };
 Brick brick;
 Brick brick_1;
 Brick brick_2;
 Brick brick_3;
 Brick brick_4;
 Brick brick_5;
 Brick brick_6;
 Brick brick_7;
 Brick brick_8;


 GameState gameState = PLAYING;

 // ��������Ľṹ��
int score = 0;      //ȫ�ֱ��������ǻ�õķ���
char scoreStr[20];  // ����ת��Ϊ�ַ����󲻻ᳬ��19���ַ�������'\0'�� 
struct Nagisa {
    int x, y;       // ���������
    int vx, vy;     // ������ٶ�
    bool isJumping; // �Ƿ�����Ծ��
    int Nagisa_width, Nagisa_height;//����ͼ��߿�
    int iframe;//���صڼ���ͼ���������������￴��ȥ��������
    int turn;//�����˶�����
    int health;
};
Nagisa nagisa;

// ���崺԰�����˵Ľṹ��
struct Monster {
    int x, y;       // ��԰�����˵�����
    int vx;         // ��԰�����˵ĺ����ٶ�
    int health;
    int turn;//�����˶�����
};

// �����ӵ��Ľṹ��
struct Bullet {
    int x, y;       // �ӵ�������
    int vx;         // �ӵ����ٶ�
    bool active;    // �ӵ��Ƿ񼤻�
    int iframe;//���صڼ���ͼ�������������ӵ�����ȥ��������
};

// ��ǰ�ؿ���ö��
enum class Level {
    Level1_1,
    Level1_2,
    Level1_3,
    GameOver
};

// ��ǰ�ؿ�
Level currentLevel = Level::Level1_1;


// ��ʼ����Ϸ
void initGame() {

    initgraph(WindowWidth, WindowHeight); // ��ʼ��ͼ�δ���
    loadimage(&imgBackground1_1, ("res\\background1_One .png")); // ����1-1�ؿ�����ͼ��
    loadimage(&imgBackground1_2, ("res\\background1_One .png")); // ����1-2�ؿ�����ͼ��
    loadimage(&imgBackground1_3, ("res\\background1_One .png")); // ����1-3�ؿ�����ͼ��
    loadimage(&gameover_background, ("res\\gameover_background.jpg"),800,600);
    loadimage(&gamewin_background, ("res\\gamewinbackground.png"), 800, 600);
    loadimage(&imgGround, _T("res\\ground.png")); // �������ͼ��

    loadimage(&imgNagisa, _T("res\\nagisa.png")); // ��������ͼ��
    loadimage(&imgMonster_One, _T("res\\Monster_One.png")); // ���봺԰������1ͼ��
    loadimage(&imgMonster_One, _T("res\\Monster_One.png"));
    loadimage(&imgMonster_OneTurn, _T("res\\Monster_OneTurn.png"));
    loadimage(&imgMonster_Oneshouji, _T("res\\Monster_Oneshouji.png"),45,60);
    loadimage(&imgMonster_Oneshouji_zhezhao, _T("res\\Monster_Oneshouji_zhezhao.png"), 45, 60);
    
    loadimage(&imgMonster_Tow, _T("res\\Monster_Tow.png"));// ���봺԰������2ͼ��
    loadimage(&imgMonster_TowTurn, _T("res\\Monster_TowTurn.png"));
    loadimage(&imgBullet_yuan, _T("res\\�ӵ��ز�1.png", 20, 20)); // �����ӵ�ͼ��
    loadimage(&imgBullet_zhezhao, _T("res\\�ӵ��ز�2.png", 20, 20));
    loadimage(&imgBrick_1, "res\\brick\\1.png");// ����ש��1ͼ��
    loadimage(&imgBrick_2, "res\\brick\\2.png");// ����ש��2ͼ��
    loadimage(&imgBrick_3, "res\\brick\\3.png");// ����ש��3ͼ��
    loadimage(&imgBrick_4, "res\\brick\\4.png");// ����ש��4ͼ��
    loadimage(&imgBrick_5, "res\\brick\\5.png");// ����ש��5ͼ��
    loadimage(&imgBrick_6, "res\\brick\\6.png");// ����ש��6ͼ��
    loadimage(&imgBrick_7, "res\\brick\\7.png");// ����ש��7ͼ��
    loadimage(&imgBrick_8, "res\\brick\\8.png");// ����ש��8ͼ��
    loadimage(&imgBrick_9, "res\\brick\\9.png");// ����ש��9ͼ��
    //ƴ��·��
    /* std::wstring path = L"res\\���ﶯ��\\left\\tuskima_ayui_left" + std::to_wstring(i) + L".png";*/
    loadimage(&img_ayuyi_left1, _T("res\\left\\tuskima_ayui_left1.png"));
    loadimage(&img_ayuyi_left2, ("res\\left\\tuskima_ayui_left2.png"));
    loadimage(&img_ayuyi_left3, ("res\\left\\tuskima_ayui_left3.png"));
    loadimage(&img_ayuyi_left4, ("res\\left\\tuskima_ayui_left4.png"));
    loadimage(&img_ayuyi_left5, ("res\\left\\tuskima_ayui_left5.png"));

    loadimage(&img_ayuyi_left1_zhezhao, ("res\\left\\tuskima_ayui_left1_zhezhao.png"));
    loadimage(&img_ayuyi_left2_zhezhao, ("res\\left\\tuskima_ayui_left2_zhezhao.png"));
    loadimage(&img_ayuyi_left3_zhezhao, ("res\\left\\tuskima_ayui_left3_zhezhao.png"));
    loadimage(&img_ayuyi_left4_zhezhao, ("res\\left\\tuskima_ayui_left4_zhezhao.png"));
    loadimage(&img_ayuyi_left5_zhezhao, ("res\\left\\tuskima_ayui_left5_zhezhao.png"));

    loadimage(&img_ayuyi_right1, ("res\\right\\tuskima_ayui_right1.png"));
    loadimage(&img_ayuyi_right2, ("res\\right\\tuskima_ayui_right2.png"));
    loadimage(&img_ayuyi_right3, ("res\\right\\tuskima_ayui_right3.png"));
    loadimage(&img_ayuyi_right4, ("res\\\right\\tuskima_ayui_right4.png"));
    //�����ӵ�����ͼƬ
    loadimage(&imgHaiXing_Animation_yuan1, _T("res\\bulletanimation\\fuko_HaiXing_Animation_yuan1.png"), 20, 20);
    loadimage(&imgHaiXing_Animation_yuan2, ("res\\bulletanimation\\fuko_HaiXing_Animation_yuan2.png"), 20, 20);
    loadimage(&imgHaiXing_Animation_yuan3, ("res\\bulletanimation\\fuko_HaiXing_Animation_yuan3.png"), 20, 20);
    loadimage(&imgHaiXing_Animation_yuan4, ("res\\bulletanimation\\fuko_HaiXing_Animation_yuan4.png"), 20, 20);
    loadimage(&imgHaiXing_Animation_yuan5, ("res\\bulletanimation\\fuko_HaiXing_Animation_yuan5.png"), 20, 20);


    loadimage(&imgHaiXing_Animation_zhezhao1, _T("res\\bulletanimation\\fuko_HaiXing_Animation_zhezhao1.png"), 20, 20);
    loadimage(&imgHaiXing_Animation_zhezhao2, ("res\\bulletanimation\\fuko_HaiXing_Animation_zhezhao2.png"), 20, 20);
    loadimage(&imgHaiXing_Animation_zhezhao3, ("res\\bulletanimation\\fuko_HaiXing_Animation_zhezhao3.png"), 20, 20);
    loadimage(&imgHaiXing_Animation_zhezhao4, ("res\\bulletanimation\\fuko_HaiXing_Animation_zhezhao4.png"), 20, 20);
    loadimage(&imgHaiXing_Animation_zhezhao5, ("res\\bulletanimation\\fuko_HaiXing_Animation_zhezhao5.png"), 20, 20);

    mciSendString("open ��ʼ����.wav alias BGM_PLAYING", NULL, 0, NULL);//**************����̫�� 7.24�޸���
    mciSendString("open ��������.wav alias BGM_GAMEOVER", NULL, 0, NULL);
    mciSendString("open �ӵ�.mp3 alias bullet", NULL, 0, NULL);
    mciSendString("open ��Ծ.mp3 alias jump", NULL, 0, NULL);
    mciSendString("open �ӵ��򵽵���.wav alias hit", NULL, 0, NULL);
    mciSendString("open ���˵���.wav alias cy", NULL, 0, NULL);
    mciSendString("open ��ɫ����.wav alias death", NULL, 0, NULL);
    /*loadimage(&Cloudy, "res\\background\\yun_1.png");*///�����ƶ�ͼ��
    HWND hwnd = GetHWnd(); //��ȡ�������������
    SetWindowText(hwnd, "�ź�������Σ��");//
}

// ���Ʊ���
void drawBackground() {
    switch (currentLevel) {
    case Level::Level1_1:
        putimage(0, 0, &imgBackground1_1);
        break;
    case Level::Level1_2:
        putimage(0, 0, &imgBackground1_2);
        break;
    case Level::Level1_3:
        putimage(0, 0, &imgBackground1_3);
        break;
    default:
        break;
    }
}

// ���Ƶ���
void drawGround() 
{
    for (int i = 0; i < WindowWidth; i += imgGround.getwidth()) {
        putimage(i, WindowHeight - GroundHeight, &imgGround);
    }
   
}

// ����ש��
void drawBricks() {
    // ���ݵ�ǰ�ؿ����Ʋ�ͬ��ש��
    switch (currentLevel) {
    case Level::Level1_1:
        // 1-1�ؿ���ש��λ�ã����Ը�����Ҫ���е���
        putimage(brick.x = 250,brick.y = WindowHeight - GroundHeight - 100, &imgBrick_6);
        putimage(brick_1.x = 200, brick_1.y = WindowHeight - GroundHeight - 50, &imgBrick_2);
        break;
    case Level::Level1_2:
        // 1-2�ؿ���ש��λ�ã����Ը�����Ҫ���е���
        putimage( 250, WindowHeight - GroundHeight - 100, &imgBrick_6);
        putimage( 200,WindowHeight - GroundHeight - 50, &imgBrick_2);
        putimage(brick_2.x = 400, brick_2.y = WindowHeight - GroundHeight - 150, &imgBrick_3);
        break;
    case Level::Level1_3:
        // 1-3�ؿ���ש��λ�ã����Ը�����Ҫ���е���
        putimage(brick_3.x = 600, brick_3.y = WindowHeight - GroundHeight - 200, &imgBrick_6);
        putimage(brick_4.x = 650, brick_4.y = WindowHeight - GroundHeight - 250, &imgBrick_7);
        putimage(250, WindowHeight - GroundHeight - 100, &imgBrick_6);
        putimage(200, WindowHeight - GroundHeight - 50, &imgBrick_2);
        putimage(400, WindowHeight - GroundHeight - 150, &imgBrick_3);
        break;
    default:
        break;
    }
}

// ��������
void drawNagisa(Nagisa& nagisa) {
    putimage(nagisa.x, nagisa.y, &imgNagisa, SRCAND); 
    //���λ�����꣺ �� SRCAND �� �������� �꣺ ��SRCPAINT�� ��������
}
//��ɫ����ʵ��
void show_animation(Nagisa& nagisa)
{

}
        
// ���ƴ�԰������
void drawMonster(Monster& monster_One, Monster& monster_Tow) {
   
}
// �����ӵ�
void drawBullet(Bullet& bullet) {
    if (bullet.active) {
        
        putimage(bullet.x, bullet.y, &imgBullet_zhezhao, SRCAND);//���λ�����꣺ �� SRCAND �� �������㣬������ɫ����
        //�꣺ ��SRCPAINT�� �������㣬�����ڱ�
          //�ȶ����ֲ��������㱣���ں������壬�ٶ�ԭͼ�������㣬����ԭͼ���������������������������ֲ�
          // �����"https://blog.csdn.net/m0_60777643/article/details/122833558"
        putimage(bullet.x, bullet.y, &imgBullet_yuan, SRCPAINT); 

    }
}

// ������Ϸ״̬
void updateGame(Nagisa& nagisa, Bullet& bullet, Monster& monster_One, Monster& monster_Tow)
{
        // ����������룬����������ƶ�����Ծ 
         if (GetAsyncKeyState('A'))
         {
             nagisa.turn = -1;

             if (nagisa.iframe == 5)
             {
                 nagisa.iframe = 1;
             }             nagisa.iframe = nagisa.iframe + 1;
            nagisa.x -= 5;
           }          
        if (GetAsyncKeyState('D') )
        {        
            nagisa.turn = 1;     
            
            if (nagisa.iframe == 5)
            {
                nagisa.iframe = 1;
            }
            nagisa.iframe = nagisa.iframe + 1;
            nagisa.x += 5;

        }/* putimage(brick_2.x = 400, brick_2.y = WindowHeight - GroundHeight - 150, &imgBrick_3);*/
        if (GetAsyncKeyState('W')&&!nagisa.isJumping )
        { // �����'w'û����ײ������û����Ծ��������������Ծ
            nagisa.iframe = +1;
            nagisa.vy = -15; // ������Ծ���ٶ�
            nagisa.isJumping = true;    
        } 
        //�ж��ϰ���ש��1 
       /*  if (nagisa.x + imgNagisa.getwidth() == brick.x)
                nagisa.vx = 0;*/
        if (nagisa.x < brick.x + imgBrick_6.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick.x
            && nagisa.y <brick.y + imgBrick_6.getheight()
            && nagisa.y + imgNagisa.getheight() > brick.y)
        {   
            // �����Ծ������û����ש������������ײ������������ש�鶥������ֹͣ��Ծ��վ��ש����  
            // ��������λ�õ�ש�鶥��  
            nagisa.isJumping = false;
            nagisa.vy = 0;
            nagisa.y = 400;//��һ���ϰ����жϣ����������ģ���������
            if (GetAsyncKeyState('A'))
            {
               nagisa.iframe = nagisa.iframe +1;
                nagisa.x -= 3;
                
                nagisa.turn = -1;
               
                if (nagisa.iframe == 5)
                {
                    nagisa.iframe = 1;
                }

            }
            if (GetAsyncKeyState('D'))
            {
                 nagisa.iframe = nagisa.iframe +1;
                nagisa.x += 3;
               
                nagisa.turn = 1;
                if (nagisa.iframe == 5)
                {
                    nagisa.iframe = 1;
                }
            }
            if (GetAsyncKeyState('W') && !nagisa.isJumping)
            { // �����'w'û����ײ������û����Ծ��������������Ծ
               
                nagisa.iframe = nagisa.iframe +1;
                nagisa.vy = -10; // ������Ծ���ٶ�
                nagisa.isJumping = true;
                if (nagisa.iframe == 5)
                {
                    nagisa.iframe = 1;
                }
            }
        }


        //�����ϰ����жϡ���������
          //�ж��ϰ���ש��2
        if (nagisa.x < brick_1.x  + imgBrick_2.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick_1.x 
            && nagisa.y <brick_1.y + imgBrick_2.getheight()
            && nagisa.y + imgNagisa.getheight() > brick_1.y)
        {
            // �����Ծ������û����ש������������ײ������������ש�鶥������ֹͣ��Ծ��վ��ש����  
            // ��������λ�õ�ש�鶥��  
            nagisa.isJumping = false;
            nagisa.vy = 0;
            nagisa.y = 450;//��һ���ϰ����жϣ����������ģ���������
            if (GetAsyncKeyState('A'))
            {
               
                nagisa.x -= 5;
                nagisa.iframe = +1;
                nagisa.turn = -1;

            }
            if (GetAsyncKeyState('D'))
            {
               
                nagisa.x += 5;
                nagisa.iframe = +1;
                nagisa.turn = 1;
            }
            if (GetAsyncKeyState('W') && !nagisa.isJumping)
            { // �����'w'û����ײ������û����Ծ��������������Ծ
                nagisa.iframe = +1;
                nagisa.vy = -15; // ������Ծ���ٶ�
                nagisa.isJumping = true;

            }
        }



        //�ж��ϰ���ש��3
        if (nagisa.x  < brick_2.x + imgBrick_3.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick_2.x 
            && nagisa.y <brick_2.y + imgBrick_3.getheight()
            && nagisa.y + imgNagisa.getheight() > brick_2.y)
        {
            // �����Ծ������û����ש������������ײ������������ש�鶥������ֹͣ��Ծ��վ��ש����  
            // ��������λ�õ�ש�鶥��  
            nagisa.isJumping = false;
            if (nagisa.y - imgNagisa.getheight() > 300 && nagisa.y - imgNagisa.getheight() < 600)
            {
                nagisa.vy = +50;//�����ﲻ�ᴥ����ͷ���ϰ���������ڵ����ϵ��ϰ�����ο� ��//�ж��ϰ���ש��2
            }
            else
            {
                nagisa.vy = 0;
                nagisa.y = 350;
            }
            if (GetAsyncKeyState('A'))
            {

               
                nagisa.x -= 3;
                nagisa.iframe = +1;
                nagisa.turn = -1;
                
                   

               


            }
            if (GetAsyncKeyState('D'))
            {
                
                nagisa.x += 3;
                nagisa.iframe = +1;
                nagisa.turn = 1;
            }
            if (GetAsyncKeyState('W') && !nagisa.isJumping)
            { // �����'w'û����ײ������û����Ծ��������������Ծ
               
                nagisa.iframe = +1;
                nagisa.vy = -10; // ������Ծ���ٶ�
                nagisa.isJumping = true;

            }
        }


        //�ж��ϰ���ש��4
        if (nagisa.x  < brick_3.x + imgBrick_6.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick_3.x
            && nagisa.y <brick_3.y + imgBrick_6.getheight()
            && nagisa.y + imgNagisa.getheight() > brick_3.y)
        {
            // �����Ծ������û����ש������������ײ������������ש�鶥������ֹͣ��Ծ��վ��ש����  
            // ��������λ�õ�ש�鶥��  
            nagisa.isJumping = false;
            if (nagisa.y - imgNagisa.getheight() > 300 && nagisa.y - imgNagisa.getheight() < 600)
            {
                nagisa.vy = +50;//�����ﲻ�ᴥ����ͷ���ϰ���������ڵ����ϵ��ϰ�����ο� ��//�ж��ϰ���ש��2
            }
            else
            {
                nagisa.vy = 0;
                nagisa.y = 300;
            }
            if (GetAsyncKeyState('A'))
            {
                nagisa.x -= 3;
                nagisa.iframe = +1;
                nagisa.turn = -1;
            }
            if (GetAsyncKeyState('D'))
            {
                nagisa.x += 3;
                nagisa.iframe = +1;
                nagisa.turn = 1;
            }
            if (GetAsyncKeyState('W') && !nagisa.isJumping)
            { // �����'w'û����ײ������û����Ծ��������������Ծ

                nagisa.iframe = +1;
                nagisa.vy = -10; // ������Ծ���ٶ�
                nagisa.isJumping = true;
            }
        }


        //�ж��ϰ���ש��5
        if (nagisa.x  < brick_4.x + imgBrick_7.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick_4.x
            && nagisa.y <brick_4.y + imgBrick_7.getheight()
            && nagisa.y + imgNagisa.getheight() > brick_4.y)
        {
            // �����Ծ������û����ש������������ײ������������ש�鶥������ֹͣ��Ծ��վ��ש����  
            // ��������λ�õ�ש�鶥��  
            nagisa.isJumping = false;
            if (nagisa.y - imgNagisa.getheight() > 300 && nagisa.y - imgNagisa.getheight() < 600)
            {
                nagisa.vy = +50;//�����ﲻ�ᴥ����ͷ���ϰ���������ڵ����ϵ��ϰ�����ο� ��//�ж��ϰ���ש��2
            }
            else
            {
                nagisa.vy = 0;
                nagisa.y = 250;
            }
            if (GetAsyncKeyState('A'))
            {
                nagisa.x -= 3;
                nagisa.iframe = +1;
                nagisa.turn = -1;
            }
            if (GetAsyncKeyState('D'))
            {
                nagisa.x += 3;
                nagisa.iframe = +1;
                nagisa.turn = 1;
            }
            if (GetAsyncKeyState('W') && !nagisa.isJumping)
            { // �����'w'û����ײ������û����Ծ��������������Ծ

                nagisa.iframe = +1;
                nagisa.vy = -10; // ������Ծ���ٶ�
                nagisa.isJumping = true;
            }
        }
            nagisa.y += nagisa.vy; // ���������λ�� 
            nagisa.vy += 1;  // ���ٶȣ�ģ������  
        if (GetAsyncKeyState('Z'))
        {// �����ӵ�      
            if (!bullet.active) {

                bullet.active = true;
               
                bullet.x = nagisa.x + imgNagisa.getwidth() / 2;
                if (nagisa.y > 545)
                {
                    nagisa.y = 550;
                }//�޸��ӵ��쳣��������*
                bullet.y = nagisa.y - 50 + imgNagisa.getheight() / 2;
                bullet.vx = 15; // �ӵ��ٶ�    
            }
        }

    // �����ӵ���λ��
    if (bullet.active)
    { 
        bullet.x += bullet.vx;
        // �ӵ������߽�����Ϊδ����״̬
        if (bullet.x > WindowWidth) {
            bullet.active = false;
        }
    } 

    // ����ӵ��Ƿ���д�԰�����˺�ש��

   // if (bullet.active) {
   //     // ��ײ��⣺�ӵ��봺԰�������Ƿ��ཻ
   //     if (bullet.x + imgBullet_yuan.getwidth() >= monster_One.x &&
   //         bullet.x <= monster_One.x + imgMonster_One.getwidth() &&
   //         bullet.y + imgBullet_yuan.getheight() >= monster_One.y &&
   //         bullet.y <= monster_One.y + imgMonster_One.getheight() &&
   //         bullet.x + imgBullet_zhezhao.getwidth() >= monster_One.x &&
   //         bullet.x <= monster_One.x + imgMonster_One.getwidth() &&
   //         bullet.y + imgBullet_zhezhao.getheight() >= monster_One.y &&
   //         bullet.y <= monster_One.y + imgMonster_One.getheight()) {
   //         // ���д�԰�����ˣ������ӵ�״̬         
   //         putimage(monster_One.x, monster_One.y, &imgMonster_Oneshouji_zhezhao, SRCAND);
   //         putimage(monster_One.x, monster_One.y, &imgMonster_Oneshouji, SRCPAINT);//�ܵ���������SRCPAINT  
   //         
   //         mciSendString("play hit", NULL, 0, NULL); 
   //         Sleep(300);
   //         monster_One.health = monster_One.health - 50;
   //         bullet.active = false;
   //     }
   //     
   //     if (bullet.x + imgBullet_yuan.getwidth() >= monster_Tow.x &&
   //         bullet.x <= monster_Tow.x + imgMonster_Tow.getwidth() &&
   //         bullet.y + imgBullet_yuan.getheight() >= monster_Tow.y &&
   //         bullet.y <= monster_Tow.y + imgMonster_One.getheight() &&
   //         bullet.x + imgBullet_zhezhao.getwidth() >= monster_Tow.x &&
   //         bullet.x <= monster_Tow.x + imgMonster_Tow.getwidth() &&
   //         bullet.y + imgBullet_zhezhao.getheight() >= monster_Tow.y &&
   //         bullet.y <= monster_Tow.y + imgMonster_One.getheight())
   //     {
   //         monster_Tow.health = monster_Tow.health - 50;
   //         bullet.active = false;
   //     }
   // }
   //// �������ɴ�԰������λ��
   // if (monster_One.health == 0)
   // {
   //     /*zmciSendString("close hit", NULL, 0, NULL);*/
   //     
   //     Sleep(100);
   //     score += 20;
   //     monster_One.turn = 1;
   //     monster_One.x = WindowWidth + 180;
   //     monster_One.health = 100;
   //    
   // }
   // if (monster_Tow.health == 0)
   // {
   //     score += 50;
   //     monster_Tow.turn = 1;
   //     monster_Tow.x = WindowWidth + 150;
   //     monster_Tow.health = 150;
   // }
 // ��԰�����˳����߽�������λ��
    if (monster_One.x < -imgMonster_One.getwidth()|| monster_One.x>890) {

        monster_One.turn = 1;
        monster_One.x = WindowWidth + 60;
        monster_One.health = 100;
    }
    if (monster_Tow.x > 890) {

        monster_Tow.turn = 1;
        monster_Tow.x = WindowWidth + 80;
        monster_Tow.health = 150;
    }


  // ��ⴺ԰�������Ƿ�����ǽ��  monster_One.x -= 2;monster_Tow.x -= 1;
    
    if (monster_One.x < brick.x + imgBrick_6.getwidth()
        && monster_One.x + imgMonster_One.getwidth() > brick.x
        && monster_One.y <brick.y + imgBrick_6.getheight()
        && monster_One.y + imgMonster_One.getheight() > brick.y)
    {
        monster_One.turn = -1;//��԰�����˺�ש����ײ��⣬����������ϰ���͸ı䷽��
    }

    if (monster_Tow.x < brick.x + imgBrick_6.getwidth()
        && monster_Tow.x + imgMonster_Tow.getwidth() > brick.x
        && monster_Tow.y <brick.y + imgBrick_6.getheight()
        && monster_Tow.y + imgMonster_Tow.getheight() > brick.y)
    {
        monster_Tow.turn = -1;//��԰�����˺�ש����ײ��⣬����������ϰ���͸ı䷽��
    }
    // ���´�԰�����˵�λ�ã�����ש���ת��
    if (monster_One.turn == 1)
    {
        putimage(monster_One.x, monster_One.y, &imgMonster_One, SRCAND);
        monster_One.x -= 2; // ��԰�����˺����ƶ��ٶ�
    }
    else
    {
        putimage(monster_One.x, monster_One.y, &imgMonster_OneTurn, SRCAND);

        monster_One.x += 2;
    }
    if (monster_Tow.turn == 1)
    {
        putimage(monster_Tow.x, monster_Tow.y, &imgMonster_Tow, SRCAND);
        monster_Tow.x -= 2;
    }
    else
    {
        putimage(monster_Tow.x, monster_Tow.y, &imgMonster_TowTurn, SRCAND);
        monster_Tow.x += 2;
    }

  
        // ����������ڵײ������õ�������
        if (nagisa.y >= WindowHeight - GroundHeight - imgNagisa.getheight()) {
            nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
            nagisa.isJumping = false;
        }      
        
    }    
    
// ��Ϸѭ�� 
    void gameLoop() {
            score = 0;
            Nagisa nagisa;
            nagisa.iframe = 0;
            nagisa.turn = 1;
            nagisa.x = 10;
            nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
            nagisa.vx = 0;
            nagisa.vy = 0;
            nagisa.isJumping = false;
            nagisa.health = 100;
            Bullet bullet;
            bullet.active = false;
            bullet.iframe = 1;
            currentLevel = Level::Level1_1;
            Monster monster_One;
            Monster monster_Tow;
            monster_One.turn = 1;
            monster_Tow.turn = 1;
            monster_One.health = 100;
            monster_Tow.health = 150;
            monster_One.x = WindowWidth + 30;
            monster_One.y = WindowHeight - GroundHeight - imgMonster_One.getheight();
            monster_One.vx = 2; // ��԰�����˺����ٶ�
            monster_Tow.x = WindowWidth + 180;
            monster_Tow.y = WindowHeight - GroundHeight - imgMonster_Tow.getheight();
            monster_Tow.vx = 2;
            gameState = PLAYING;
            int time ;//��ͣʱ�����eg:Sleep(time)
            int overtime ;
            
            while (true) {
              
                switch (gameState) {
                case PLAYING:


                    //�����֣���������  alias ȡ���� repeat �ظ�����
                   mciSendString("play BGM_PLAYING ", NULL, 0, NULL); 
                   mciSendString("play BGM_PLAYING repeat", NULL, 0, NULL);         
                    drawBackground();   // ���Ʊ���
                    drawGround();       // ���Ƶ���
                    drawBricks();       // ����ש��
                    drawNagisa(nagisa);   // ��������
                    drawMonster(monster_One, monster_Tow); // ���ƴ�԰������
                    drawBullet(bullet); // �����ӵ� 
                    settextstyle(30, 0, ("����"));
                    outtextxy(30, 30, ("��ǰ�÷֣�"));
                    itoa(score, scoreStr, 10);
                    // ʹ��itoa������ת��Ϊ�ַ���   
                    // ��һ��������Ҫת�����������ڶ���������ת������ַ����Ļ�����10��ʾʮ���ƣ�  
                    outtextxy(180, 30, scoreStr);                   

 // ������Ϸ״̬2024.7.18,,�������
                    updateGame(nagisa, bullet, monster_One, monster_Tow);
                    if (bullet.active) {
                        // ��ײ��⣺�ӵ��봺԰�������Ƿ��ཻ
                        if (bullet.x + imgBullet_yuan.getwidth() >= monster_One.x &&
                            bullet.x <= monster_One.x + imgMonster_One.getwidth() &&
                            bullet.y + imgBullet_yuan.getheight() >= monster_One.y &&
                            bullet.y <= monster_One.y + imgMonster_One.getheight() &&
                            bullet.x + imgBullet_zhezhao.getwidth() >= monster_One.x &&
                            bullet.x <= monster_One.x + imgMonster_One.getwidth() &&
                            bullet.y + imgBullet_zhezhao.getheight() >= monster_One.y &&
                            bullet.y <= monster_One.y + imgMonster_One.getheight()) {                
                            // ���д�԰�����ˣ������ӵ�״̬
                            if(monster_One.health == 100)
                            { 
                            PlaySound(_T("�ӵ��򵽵���.wav"), NULL, SND_FILENAME | SND_ASYNC);//ʹ��EasyX ͼ�ο�ʱ��PlaySound��������������ͼ�ν�������в�������
                            //���õı�־���� SND_FILENAME��pszSound ��һ���ļ�������SND_RESOURCE��pszSound ��һ����Դ������SND_ASYNC���첽�����������������������أ�
                            // SND_SYNC��ͬ���������������ȴ�����������ɺ����ŷ��أ��� SND_LOOP��ѭ��������������
                            }
                            putimage(monster_One.x, monster_One.y, &imgMonster_Oneshouji_zhezhao, SRCAND);
                            putimage(monster_One.x, monster_One.y, &imgMonster_Oneshouji, SRCPAINT);//�ܵ���������SRCPAINT  
                            Sleep(200);
                            
                            monster_One.health = monster_One.health - 50;
                            bullet.active = false;
                        }
                        
                        if (bullet.x + imgBullet_yuan.getwidth() >= monster_Tow.x &&
                            bullet.x <= monster_Tow.x + imgMonster_Tow.getwidth() &&
                            bullet.y + imgBullet_yuan.getheight() >= monster_Tow.y &&
                            bullet.y <= monster_Tow.y + imgMonster_One.getheight() &&
                            bullet.x + imgBullet_zhezhao.getwidth() >= monster_Tow.x &&
                            bullet.x <= monster_Tow.x + imgMonster_Tow.getwidth() &&
                            bullet.y + imgBullet_zhezhao.getheight() >= monster_Tow.y &&
                            bullet.y <= monster_Tow.y + imgMonster_One.getheight())
                        {    
                            monster_Tow.health = monster_Tow.health - 50;
                            bullet.active = false;
                        }                  
                    }
                    // �������ɴ�԰������λ��
                    if (monster_One.health == 0)
                    {
                        PlaySound(_T("���˵���.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        score += 20;
                        monster_One.turn = 1;
                        monster_One.x = WindowWidth + 180;
                        monster_One.health = 100;
                    }
                    if (monster_Tow.health == 0)
                    {
                        monster_Tow.x = WindowWidth + 50;
                        monster_Tow.health = 150;
                    }
                     
                    // ��ײ��⣺�����봺԰�������Ƿ��ཻ
                    if ((nagisa.x + imgNagisa.getwidth() >= monster_One.x &&
                        nagisa.x <= monster_One.x + imgMonster_One.getwidth() &&
                        nagisa.y + imgNagisa.getheight() >= monster_One.y &&
                        nagisa.y <= monster_One.y + imgMonster_One.getheight() &&
                        nagisa.x + imgNagisa.getwidth() >= monster_One.x &&
                        nagisa.x <= monster_One.x + imgMonster_One.getwidth() &&
                        nagisa.y + imgNagisa.getheight() >= monster_One.y &&
                        nagisa.y <= monster_One.y + imgMonster_One.getheight()))
                       {
                        monster_One.x = WindowWidth + 180;
                        monster_One.health = 100;
                        nagisa.health = nagisa.health - 25;                        
                    }
                    if ((nagisa.x + imgNagisa.getwidth() >= monster_Tow.x &&
                        nagisa.x <= monster_Tow.x + imgMonster_Tow.getwidth() &&
                        nagisa.y + imgNagisa.getheight() >= monster_Tow.y &&
                        nagisa.y <= monster_Tow.y + imgMonster_One.getheight() &&
                        nagisa.x + imgNagisa.getwidth() >= monster_Tow.x &&
                        nagisa.x <= monster_Tow.x + imgMonster_Tow.getwidth() &&
                        nagisa.y + imgNagisa.getheight() >= monster_Tow.y &&
                        nagisa.y <= monster_Tow.y + imgMonster_One.getheight()))
                    {
                        monster_Tow.x = WindowWidth + 50;
                        monster_Tow.health = 150;
                        nagisa.health = nagisa.health - 25;
                    }
                    if (nagisa.health == 0)
                    { 
                        
                        mciSendString("play death", NULL, 0, NULL);
                        Sleep(1000);
                        mciSendString("close death", NULL, 0, NULL);
                        mciSendString("close BGM_PLAYING", NULL, 0, NULL);
                        
                        gameState = GAME_OVER;
                   }

                    //�ӵ���������updateGame����7.19�����
                    if (bullet.active)
                    {
                        bullet.iframe = bullet.iframe + 1;


                        switch ((int)bullet.iframe)
                        {
                        case 1:
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_zhezhao1, SRCAND); 
                            //���λ�����꣺ �� SRCAND �� �������㣬������ɫ����
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_yuan1, SRCPAINT);  
                            //�꣺ ��SRCPAINT�� �������㣬�����ڱ�                   
                                                                                                  
                            //�ȶ����ֲ��������㱣���ں������壬�ٶ�ԭͼ�������㣬����ԭͼ���������������������������ֲ�
                                                                                                 
                            //�����"https://blog.csdn.net/m0_60777643/article/details/122833558"     
                            break;
                        case 2:
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_zhezhao2, SRCAND);
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_yuan2, SRCPAINT);
                            break;
                        case 3:
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_zhezhao3, SRCAND);
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_yuan3, SRCPAINT);
                           
                            break;
                        case 4:
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_zhezhao4, SRCAND);
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_yuan4, SRCPAINT);
                                break;
                        case 5:
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_zhezhao5, SRCAND);
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_yuan5, SRCPAINT);
                            break;
                        default:
                            break;
                        }
                        if (bullet.iframe == 5)
                        {
                            bullet.iframe = 1;
                        }
                    }
                    //˳��һ�ᣬ����ط�׼�����������ҵĶ����ģ����ǲ�֪��Ϊʲô������������Ժ���˵ ���ѽ���������ͼƬ����
                
            if (nagisa.turn == -1)//��������
            {
                
                switch ((int)nagisa.iframe)
                {
                case 1:

                    /* putimage(, &img_ayuyi_left1, SRCAND);*///��ɫ��תͼ���λ�����꣺ �� SRCAND �� �������� �꣺ ��SRCPAINT�� ��������
                   putimage(nagisa.x-5, nagisa.y,&img_ayuyi_left1_zhezhao, SRCAND);
                   putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left1, SRCPAINT);
                    break;
                case 2:
                    putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left2_zhezhao, SRCAND);
                    putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left2, SRCPAINT);
                    /*putimage(nagisa.x, nagisa.y, &img_ayuyi_left1, SRCAND);*/
                    break;
                case 3:
                    putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left3_zhezhao, SRCAND);
                    putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left3, SRCPAINT);
                    /*putimage(nagisa.x, nagisa.y, &img_ayuyi_left1, SRCAND);*/
                    break;
                case 4:
                    putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left4_zhezhao, SRCAND);
                    putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left4, SRCPAINT);
                    /*putimage(nagisa.x, nagisa.y, &img_ayuyi_left1, SRCAND);*/
                    break;
                case 5:
                    putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left5_zhezhao, SRCAND);
                    putimage(nagisa.x-5, nagisa.y, &img_ayuyi_left5, SRCPAINT);
                    /*putimage(nagisa.x, nagisa.y, &img_ayuyi_left1, SRCAND);*/
                    break;
                default:
                    break;
                } 
                if (nagisa.iframe == 5)
                {
                    nagisa.iframe = 1;
                }
            }
            // �����Ϸ��������
            switch (currentLevel) {
            case Level::Level1_1:
                // ��1-1�ؿ��У��������ﵽһ��λ�ã��л���1-2�ؿ�
                if (nagisa.x > 780) {
                    currentLevel = Level::Level1_2; \
                        score += 100;
                    nagisa.x = 10; // �л��ؿ���������������λ��
                    nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();

                    monster_One.x = WindowWidth + 50;
                    monster_Tow.x = WindowWidth - 30;
                }
                break;
            case Level::Level1_2:
                // ��1-2�ؿ��У��������ﵽһ��λ�ã��л���1-3�ؿ�
                if (nagisa.x > 780) {
                    currentLevel = Level::Level1_3;
                    score += 150;
                    nagisa.x = 10; // �л��ؿ���������������λ��
                    nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
                    monster_One.x = WindowWidth + 20;
                    monster_Tow.x = WindowWidth + 180;
                }
                if (nagisa.x < -50) {//��1-2�ؿ��У��������ﵽ[һ��λ����Ļ����ߣ��л���1-1�ؿ�
                    currentLevel = Level::Level1_1;
                    nagisa.x = 790; // �л��ؿ���������������λ��
                    nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
                    monster_One.x = WindowWidth + 40;
                    monster_Tow.x = WindowWidth + 180;
                }
                break;
            case Level::Level1_3:
                // ��1-3�ؿ��У��������ﵽһ��λ�ã���Ϸ����
                if (nagisa.x < -50) {//��1-2�ؿ��У��������ﵽ[һ��λ����Ļ����ߣ��л���1-1�ؿ�
                    currentLevel = Level::Level1_2;
                    nagisa.x = 790; // �л��ؿ���������������λ��
                    nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
                    monster_One.x = WindowWidth + 30;
                    monster_Tow.x = WindowWidth + 180;
                }
                if (nagisa.x > 800) {
                    currentLevel = Level::GameOver;
                    score += 200;
                    cleardevice(); // �����Ļ
                    PlaySound(_T("ʤ������.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    mciSendString("close BGM_PLAYING", NULL, 0, NULL);
                    mciSendString("play BGM_GAMEOVER", NULL, 0, NULL); 
                    mciSendString("play BGM_GAMEOVER repeat", NULL, 0, NULL);

                    putimage(0, 0, &gamewin_background);
                    settextcolor(BLACK);   
                    settextstyle(20, 0, ("����"));
                    outtextxy(500, 150, ("�ɹ������˹ź�����꣡")); // ��ʾ��Ϸ������Ϣ
                    outtextxy(500, 180, ("�ܼƵ÷֣�"));
                    itoa(score, scoreStr, 10);
                    outtextxy(600, 180, scoreStr);
                    outtextxy(500, 210, ("����������ɷ������˵�"));
                    overtime = 50000;
                    if (_getch())//��鵱ǰ�Ƿ��м�������
                    {     
                        overtime = 0;
                    }
                    Sleep(overtime);
                    mciSendString("close BGM_GAMEOVER", NULL, 0, NULL);
                    //�޲���3����Զ��������˵�
                    gameState = MAIN_MENU;
                }
                break;
            default:
                break;
            }     
            FlushBatchDraw();   // ˢ����Ļ
            Sleep(30); // ����֡��
                   //if(GetAsyncKeyState('L'))// ESC��Ϊ��ͣ  ********��ͣ�е�����**************** 2024.7 18�޸�
                    
                if (_kbhit())//��鵱ǰ�Ƿ��м�������
                {

                    int ch = _getch(); //����ȴ����룬����ͣ���������
                   
                    if (/*ch == 'q'||ch=='Q' ||*/GetAsyncKeyState(VK_ESCAPE))//q��Q��Esc����ͣ
                    {
                        pause_count = 1;
                        BeginBatchDraw();
                      
                        settextcolor(LIGHTRED);
                        setlinecolor(BLACK);
               
                        fillroundrect(x_size / 2 - 65, Y_size / 3, x_size / 2 + 55, Y_size / 3 + 30, 10, 10);//Բ�Ǿ��Σ�����������10,10�ǵ���Բ�ǳ̶�
                        settextcolor(BROWN);
                        setfont(30, 0, "����");
                        outtextxy(x_size / 2 - 65, Y_size / 3, "������Ϸ");
                        fillroundrect(x_size / 2 - 65, Y_size / 3 + 30, x_size / 2 + 55, Y_size / 3 + 60, 10, 10);
                        outtextxy(x_size / 2 - 65, Y_size / 3 + 30, " ���˵� ");
                        fillroundrect(x_size / 2 - 65, Y_size / 3 + 60, x_size / 2 + 55, Y_size / 3 + 90, 10, 10);
                        outtextxy(x_size / 2 - 65, Y_size / 3 + 60, "�˳���Ϸ");
                        EndBatchDraw();
                    }
                        ExMessage msg;
                        while (pause_count == 1  )
                        {


                            if (peekmessage(&msg, EM_MOUSE)&&msg.message == WM_LBUTTONDOWN)//�������������ϢΪ������
                            {

 
                                if (msg.x >= x_size / 2 - 65 && msg.x <= x_size / 2 + 55 && msg.y >= Y_size / 3 && msg.y <= Y_size / 3 + 30)
                                {
                                    pause_count = 0;
                                    gameState = PLAYING;

                                    break;
                                }
                                if (msg.x > x_size / 2 - 65 && msg.x<x_size / 2 + 55 && msg.y>Y_size / 3 + 30 && msg.y < Y_size / 3 + 60)
                                {
                                    pause_count = 0;
                                    gameState = MAIN_MENU;
                                    /* game g;
                                     g.start();
                                     gameLoop();*/
                                    break;
                                }
                                if (msg.x > x_size / 2 - 65 && msg.x<x_size / 2 + 55 && msg.y>Y_size / 3 + 60 && msg.y < Y_size / 3 + 90)
                                {
                                    pause_count = 0;
                                    gameState = GAME_OVER;

                                    break;

                                }
                            }
                        }
                   

                }
                     break;
                case PAUSED:

                   
                    break;
     
                case GAME_OVER:

                    mciSendString("close BGM_PLAYING", NULL, 0, NULL);          
                            //�����֣���������  alias ȡ���� repeat �ظ�����
                            mciSendString("play BGM_GAMEOVER", NULL, 0, NULL);
                            mciSendString("play BGM_GAMEOVER repeat", NULL, 0, NULL);                           
                           /*currentLevel = Level::GameOver;*/
                           cleardevice(); // �����Ļ
                           putimage(0, 0, &gameover_background);
                           settextcolor(RED);
                           settextstyle(30, 0, ("����"));
                           outtextxy(100, 50, ("��Ϸ������")); // ��ʾ��Ϸ������Ϣ
                           outtextxy(120, 80, ("����������ɷ������˵�"));
                           outtextxy(120, 110, ("�޲���60����Զ��������˵�"));
                            time = 60000;                     
                            if (_getch())//��鵱ǰ�Ƿ��м�������
                            {
                                time = 0;
                                //_getch();//��鵱ǰ�Ƿ��м������� 
                            }
                            Sleep(time);//�޲������Զ��������˵�
                           mciSendString("close BGM_GAMEOVER", NULL, 0, NULL);
                           gameState = MAIN_MENU;
                           
                    
                    break;

                case MAIN_MENU:
                    mciSendString("close BGM_PLAYING", NULL, 0, NULL);
                    cleardevice();
                    initGame();
                    game g;
                    g.start();
                    show_animation(nagisa);
                    gameLoop();
                    break;

                }
            }                     
    }
 
// ������ 
void main()
{
   
        initGame();     
        game g;
        g.start();
        show_animation(nagisa);
        gameLoop(); // ��Ϸѭ��

}


