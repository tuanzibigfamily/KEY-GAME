//创作者 森匠，汐风，2024.7.24日完成，小游戏只是为爱发电做的，还有许多需要完善的地方，
// 欢迎登录github参与建设，项目地址为：https://github.com/tuanzibigfamily/KEY-GAME
#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>  
#pragma comment(lib,"winmm.lib")//加载静态库
#include <ctime>
#include <iostream> // 包含输入输出流
#include<math.h>
#include <windows.h>  
#include<string>
#include <cstdlib>    // 引入stdlib.h
#include"游戏开始界面.cpp"
#undef UNICODE
#undef _UNICODE

inline void putimage_alpha(int x, int y, IMAGE* img)//人物背景色透明化
{
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

// 定义窗口大小和游戏相关常量
const int WindowWidth = 800;
const int WindowHeight = 600;
const int GroundHeight = 32;
int idx_current_anim = 0;
static int counter = 0;

int pause_count = 0;//暂停变量
// 游戏状态  
enum GameState { 
    PLAYING,
    PAUSED,
    MAIN_MENU,
    GAME_OVER
};

// 加载图片资源
IMAGE imgBackground1_1; // 1-1关卡背景
IMAGE imgBackground1_2; // 1-2关卡背景
IMAGE imgBackground1_3; // 1-3关卡背景
IMAGE gameover_background;
IMAGE gamewin_background;

IMAGE imgGround;        // 地面图

IMAGE imgNagisa;         // 人物图
IMAGE imgMonster_One;       // 春园和往人1图
IMAGE imgMonster_OneTurn;
IMAGE imgMonster_Oneshouji;
IMAGE imgMonster_Oneshouji_zhezhao;
IMAGE imgMonster_Tow;       // 春园和往人2图
IMAGE imgMonster_TowTurn;

IMAGE imgBullet_yuan;        // 子弹图
IMAGE imgBullet_zhezhao;
IMAGE imgHaiXing_Animation_yuan1;//子弹动画图，黑底白底位运算图
IMAGE imgHaiXing_Animation_zhezhao1;

IMAGE imgHaiXing_Animation_yuan2;//子弹动画图
IMAGE imgHaiXing_Animation_zhezhao2;

IMAGE imgHaiXing_Animation_yuan3;//子弹动画图
IMAGE imgHaiXing_Animation_zhezhao3;

IMAGE imgHaiXing_Animation_yuan4;//子弹动画图
IMAGE imgHaiXing_Animation_zhezhao4;

IMAGE imgHaiXing_Animation_yuan5;//子弹动画图
IMAGE imgHaiXing_Animation_zhezhao5;

 IMAGE imgBrick_1;         // 砖块1图
 IMAGE imgBrick_2;         // 砖块2图
 IMAGE imgBrick_3;         // 砖块3图
 IMAGE imgBrick_4;         // 砖块4图
 IMAGE imgBrick_5;         // 砖块5图
 IMAGE imgBrick_6;         // 砖块6图
 IMAGE imgBrick_7;         // 砖块7图
 IMAGE imgBrick_8;         // 砖块8图
 IMAGE imgBrick_9;         // 砖块9图
 

 //动画数组
 
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

 //IMAGE Cloudy;//云朵
 struct Brick
 {
     int brick_width, brick_height; // 砖块大小  
     int x, y;//砖块坐标
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

 // 定义人物的结构体
int score = 0;      //全局变量，主角获得的分数
char scoreStr[20];  // 分数转换为字符串后不会超过19个字符（包括'\0'） 
struct Nagisa {
    int x, y;       // 人物的坐标
    int vx, vy;     // 人物的速度
    bool isJumping; // 是否在跳跃中
    int Nagisa_width, Nagisa_height;//人物图像高宽
    int iframe;//加载第几副图，这样就能让人物看上去动起来了
    int turn;//人物运动方向
    int health;
};
Nagisa nagisa;

// 定义春园和往人的结构体
struct Monster {
    int x, y;       // 春园和往人的坐标
    int vx;         // 春园和往人的横向速度
    int health;
    int turn;//人物运动方向
};

// 定义子弹的结构体
struct Bullet {
    int x, y;       // 子弹的坐标
    int vx;         // 子弹的速度
    bool active;    // 子弹是否激活
    int iframe;//加载第几副图，这样就能让子弹看上去动起来了
};

// 当前关卡的枚举
enum class Level {
    Level1_1,
    Level1_2,
    Level1_3,
    GameOver
};

// 当前关卡
Level currentLevel = Level::Level1_1;


// 初始化游戏
void initGame() {

    initgraph(WindowWidth, WindowHeight); // 初始化图形窗口
    loadimage(&imgBackground1_1, ("res\\background1_One .png")); // 载入1-1关卡背景图像
    loadimage(&imgBackground1_2, ("res\\background1_One .png")); // 载入1-2关卡背景图像
    loadimage(&imgBackground1_3, ("res\\background1_One .png")); // 载入1-3关卡背景图像
    loadimage(&gameover_background, ("res\\gameover_background.jpg"),800,600);
    loadimage(&gamewin_background, ("res\\gamewinbackground.png"), 800, 600);
    loadimage(&imgGround, _T("res\\ground.png")); // 载入地面图像

    loadimage(&imgNagisa, _T("res\\nagisa.png")); // 载入人物图像
    loadimage(&imgMonster_One, _T("res\\Monster_One.png")); // 载入春园和往人1图像
    loadimage(&imgMonster_One, _T("res\\Monster_One.png"));
    loadimage(&imgMonster_OneTurn, _T("res\\Monster_OneTurn.png"));
    loadimage(&imgMonster_Oneshouji, _T("res\\Monster_Oneshouji.png"),45,60);
    loadimage(&imgMonster_Oneshouji_zhezhao, _T("res\\Monster_Oneshouji_zhezhao.png"), 45, 60);
    
    loadimage(&imgMonster_Tow, _T("res\\Monster_Tow.png"));// 载入春园和往人2图像
    loadimage(&imgMonster_TowTurn, _T("res\\Monster_TowTurn.png"));
    loadimage(&imgBullet_yuan, _T("res\\子弹素材1.png", 20, 20)); // 载入子弹图像
    loadimage(&imgBullet_zhezhao, _T("res\\子弹素材2.png", 20, 20));
    loadimage(&imgBrick_1, "res\\brick\\1.png");// 载入砖块1图像
    loadimage(&imgBrick_2, "res\\brick\\2.png");// 载入砖块2图像
    loadimage(&imgBrick_3, "res\\brick\\3.png");// 载入砖块3图像
    loadimage(&imgBrick_4, "res\\brick\\4.png");// 载入砖块4图像
    loadimage(&imgBrick_5, "res\\brick\\5.png");// 载入砖块5图像
    loadimage(&imgBrick_6, "res\\brick\\6.png");// 载入砖块6图像
    loadimage(&imgBrick_7, "res\\brick\\7.png");// 载入砖块7图像
    loadimage(&imgBrick_8, "res\\brick\\8.png");// 载入砖块8图像
    loadimage(&imgBrick_9, "res\\brick\\9.png");// 载入砖块9图像
    //拼凑路径
    /* std::wstring path = L"res\\人物动画\\left\\tuskima_ayui_left" + std::to_wstring(i) + L".png";*/
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
    //加载子弹动画图片
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

    mciSendString("open 开始音乐.wav alias BGM_PLAYING", NULL, 0, NULL);//**************音量太大 7.24修改完
    mciSendString("open 结束音乐.wav alias BGM_GAMEOVER", NULL, 0, NULL);
    mciSendString("open 子弹.mp3 alias bullet", NULL, 0, NULL);
    mciSendString("open 跳跃.mp3 alias jump", NULL, 0, NULL);
    mciSendString("open 子弹打到敌人.wav alias hit", NULL, 0, NULL);
    mciSendString("open 敌人倒下.wav alias cy", NULL, 0, NULL);
    mciSendString("open 角色倒下.wav alias death", NULL, 0, NULL);
    /*loadimage(&Cloudy, "res\\background\\yun_1.png");*///载入云朵图像
    HWND hwnd = GetHWnd(); //获取窗口名句柄函数
    SetWindowText(hwnd, "古河面包店大危机");//
}

// 绘制背景
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

// 绘制地面
void drawGround() 
{
    for (int i = 0; i < WindowWidth; i += imgGround.getwidth()) {
        putimage(i, WindowHeight - GroundHeight, &imgGround);
    }
   
}

// 绘制砖块
void drawBricks() {
    // 根据当前关卡绘制不同的砖块
    switch (currentLevel) {
    case Level::Level1_1:
        // 1-1关卡的砖块位置，可以根据需要进行调整
        putimage(brick.x = 250,brick.y = WindowHeight - GroundHeight - 100, &imgBrick_6);
        putimage(brick_1.x = 200, brick_1.y = WindowHeight - GroundHeight - 50, &imgBrick_2);
        break;
    case Level::Level1_2:
        // 1-2关卡的砖块位置，可以根据需要进行调整
        putimage( 250, WindowHeight - GroundHeight - 100, &imgBrick_6);
        putimage( 200,WindowHeight - GroundHeight - 50, &imgBrick_2);
        putimage(brick_2.x = 400, brick_2.y = WindowHeight - GroundHeight - 150, &imgBrick_3);
        break;
    case Level::Level1_3:
        // 1-3关卡的砖块位置，可以根据需要进行调整
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

// 绘制人物
void drawNagisa(Nagisa& nagisa) {
    putimage(nagisa.x, nagisa.y, &imgNagisa, SRCAND); 
    //添加位运算宏宏： “ SRCAND ” 做与运算 宏： “SRCPAINT” 做或运算
}
//角色动画实现
void show_animation(Nagisa& nagisa)
{

}
        
// 绘制春园和往人
void drawMonster(Monster& monster_One, Monster& monster_Tow) {
   
}
// 绘制子弹
void drawBullet(Bullet& bullet) {
    if (bullet.active) {
        
        putimage(bullet.x, bullet.y, &imgBullet_zhezhao, SRCAND);//添加位运算宏宏： “ SRCAND ” 做与运算，消除白色部分
        //宏： “SRCPAINT” 做或运算，消除黑边
          //先对遮罩层做与运算保留黑海星主体，再对原图做或运算，保留原图海星主体叠加上做了与运算的遮罩层
          // 详情见"https://blog.csdn.net/m0_60777643/article/details/122833558"
        putimage(bullet.x, bullet.y, &imgBullet_yuan, SRCPAINT); 

    }
}

// 更新游戏状态
void updateGame(Nagisa& nagisa, Bullet& bullet, Monster& monster_One, Monster& monster_Tow)
{
        // 处理键盘输入，控制人物的移动和跳跃 
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
        { // 如果按'w'没有碰撞且人物没有跳跃，则人物向上跳跃
            nagisa.iframe = +1;
            nagisa.vy = -15; // 设置跳跃初速度
            nagisa.isJumping = true;    
        } 
        //判断障碍物砖块1 
       /*  if (nagisa.x + imgNagisa.getwidth() == brick.x)
                nagisa.vx = 0;*/
        if (nagisa.x < brick.x + imgBrick_6.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick.x
            && nagisa.y <brick.y + imgBrick_6.getheight()
            && nagisa.y + imgNagisa.getheight() > brick.y)
        {   
            // 如果跳跃过程中没有与砖块其他部分碰撞，并且碰到了砖块顶部，则停止跳跃并站在砖块上  
            // 调整人物位置到砖块顶部  
            nagisa.isJumping = false;
            nagisa.vy = 0;
            nagisa.y = 400;//第一个障碍物判断，还有其他的，，，待做
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
            { // 如果按'w'没有碰撞且人物没有跳跃，则人物向上跳跃
               
                nagisa.iframe = nagisa.iframe +1;
                nagisa.vy = -10; // 设置跳跃初速度
                nagisa.isJumping = true;
                if (nagisa.iframe == 5)
                {
                    nagisa.iframe = 1;
                }
            }
        }


        //其他障碍物判断。。。。。
          //判断障碍物砖块2
        if (nagisa.x < brick_1.x  + imgBrick_2.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick_1.x 
            && nagisa.y <brick_1.y + imgBrick_2.getheight()
            && nagisa.y + imgNagisa.getheight() > brick_1.y)
        {
            // 如果跳跃过程中没有与砖块其他部分碰撞，并且碰到了砖块顶部，则停止跳跃并站在砖块上  
            // 调整人物位置到砖块顶部  
            nagisa.isJumping = false;
            nagisa.vy = 0;
            nagisa.y = 450;//第一个障碍物判断，还有其他的，，，待做
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
            { // 如果按'w'没有碰撞且人物没有跳跃，则人物向上跳跃
                nagisa.iframe = +1;
                nagisa.vy = -15; // 设置跳跃初速度
                nagisa.isJumping = true;

            }
        }



        //判断障碍物砖块3
        if (nagisa.x  < brick_2.x + imgBrick_3.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick_2.x 
            && nagisa.y <brick_2.y + imgBrick_3.getheight()
            && nagisa.y + imgNagisa.getheight() > brick_2.y)
        {
            // 如果跳跃过程中没有与砖块其他部分碰撞，并且碰到了砖块顶部，则停止跳跃并站在砖块上  
            // 调整人物位置到砖块顶部  
            nagisa.isJumping = false;
            if (nagisa.y - imgNagisa.getheight() > 300 && nagisa.y - imgNagisa.getheight() < 600)
            {
                nagisa.vy = +50;//让人物不会触碰到头顶障碍物，正常铺在地面上的障碍物请参考 ：//判断障碍物砖块2
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
            { // 如果按'w'没有碰撞且人物没有跳跃，则人物向上跳跃
               
                nagisa.iframe = +1;
                nagisa.vy = -10; // 设置跳跃初速度
                nagisa.isJumping = true;

            }
        }


        //判断障碍物砖块4
        if (nagisa.x  < brick_3.x + imgBrick_6.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick_3.x
            && nagisa.y <brick_3.y + imgBrick_6.getheight()
            && nagisa.y + imgNagisa.getheight() > brick_3.y)
        {
            // 如果跳跃过程中没有与砖块其他部分碰撞，并且碰到了砖块顶部，则停止跳跃并站在砖块上  
            // 调整人物位置到砖块顶部  
            nagisa.isJumping = false;
            if (nagisa.y - imgNagisa.getheight() > 300 && nagisa.y - imgNagisa.getheight() < 600)
            {
                nagisa.vy = +50;//让人物不会触碰到头顶障碍物，正常铺在地面上的障碍物请参考 ：//判断障碍物砖块2
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
            { // 如果按'w'没有碰撞且人物没有跳跃，则人物向上跳跃

                nagisa.iframe = +1;
                nagisa.vy = -10; // 设置跳跃初速度
                nagisa.isJumping = true;
            }
        }


        //判断障碍物砖块5
        if (nagisa.x  < brick_4.x + imgBrick_7.getwidth()
            && nagisa.x + imgNagisa.getwidth() > brick_4.x
            && nagisa.y <brick_4.y + imgBrick_7.getheight()
            && nagisa.y + imgNagisa.getheight() > brick_4.y)
        {
            // 如果跳跃过程中没有与砖块其他部分碰撞，并且碰到了砖块顶部，则停止跳跃并站在砖块上  
            // 调整人物位置到砖块顶部  
            nagisa.isJumping = false;
            if (nagisa.y - imgNagisa.getheight() > 300 && nagisa.y - imgNagisa.getheight() < 600)
            {
                nagisa.vy = +50;//让人物不会触碰到头顶障碍物，正常铺在地面上的障碍物请参考 ：//判断障碍物砖块2
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
            { // 如果按'w'没有碰撞且人物没有跳跃，则人物向上跳跃

                nagisa.iframe = +1;
                nagisa.vy = -10; // 设置跳跃初速度
                nagisa.isJumping = true;
            }
        }
            nagisa.y += nagisa.vy; // 更新人物的位置 
            nagisa.vy += 1;  // 加速度，模拟重力  
        if (GetAsyncKeyState('Z'))
        {// 发射子弹      
            if (!bullet.active) {

                bullet.active = true;
               
                bullet.x = nagisa.x + imgNagisa.getwidth() / 2;
                if (nagisa.y > 545)
                {
                    nagisa.y = 550;
                }//修复子弹异常下落问题*
                bullet.y = nagisa.y - 50 + imgNagisa.getheight() / 2;
                bullet.vx = 15; // 子弹速度    
            }
        }

    // 更新子弹的位置
    if (bullet.active)
    { 
        bullet.x += bullet.vx;
        // 子弹超出边界则标记为未激活状态
        if (bullet.x > WindowWidth) {
            bullet.active = false;
        }
    } 

    // 检测子弹是否击中春园和往人和砖块

   // if (bullet.active) {
   //     // 碰撞检测：子弹与春园和往人是否相交
   //     if (bullet.x + imgBullet_yuan.getwidth() >= monster_One.x &&
   //         bullet.x <= monster_One.x + imgMonster_One.getwidth() &&
   //         bullet.y + imgBullet_yuan.getheight() >= monster_One.y &&
   //         bullet.y <= monster_One.y + imgMonster_One.getheight() &&
   //         bullet.x + imgBullet_zhezhao.getwidth() >= monster_One.x &&
   //         bullet.x <= monster_One.x + imgMonster_One.getwidth() &&
   //         bullet.y + imgBullet_zhezhao.getheight() >= monster_One.y &&
   //         bullet.y <= monster_One.y + imgMonster_One.getheight()) {
   //         // 击中春园和往人，重置子弹状态         
   //         putimage(monster_One.x, monster_One.y, &imgMonster_Oneshouji_zhezhao, SRCAND);
   //         putimage(monster_One.x, monster_One.y, &imgMonster_Oneshouji, SRCPAINT);//受到攻击动画SRCPAINT  
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
   //// 重新生成春园和往人位置
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
 // 春园和往人超出边界则重置位置
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


  // 检测春园和往人是否碰到墙壁  monster_One.x -= 2;monster_Tow.x -= 1;
    
    if (monster_One.x < brick.x + imgBrick_6.getwidth()
        && monster_One.x + imgMonster_One.getwidth() > brick.x
        && monster_One.y <brick.y + imgBrick_6.getheight()
        && monster_One.y + imgMonster_One.getheight() > brick.y)
    {
        monster_One.turn = -1;//春园和往人和砖块碰撞检测，如果碰到了障碍物就改变方向
    }

    if (monster_Tow.x < brick.x + imgBrick_6.getwidth()
        && monster_Tow.x + imgMonster_Tow.getwidth() > brick.x
        && monster_Tow.y <brick.y + imgBrick_6.getheight()
        && monster_Tow.y + imgMonster_Tow.getheight() > brick.y)
    {
        monster_Tow.turn = -1;//春园和往人和砖块碰撞检测，如果碰到了障碍物就改变方向
    }
    // 更新春园和往人的位置，碰到砖块后转向
    if (monster_One.turn == 1)
    {
        putimage(monster_One.x, monster_One.y, &imgMonster_One, SRCAND);
        monster_One.x -= 2; // 春园和往人横向移动速度
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

  
        // 如果超出窗口底部，重置到地面上
        if (nagisa.y >= WindowHeight - GroundHeight - imgNagisa.getheight()) {
            nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
            nagisa.isJumping = false;
        }      
        
    }    
    
// 游戏循环 
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
            monster_One.vx = 2; // 春园和往人横向速度
            monster_Tow.x = WindowWidth + 180;
            monster_Tow.y = WindowHeight - GroundHeight - imgMonster_Tow.getheight();
            monster_Tow.vx = 2;
            gameState = PLAYING;
            int time ;//暂停时间变量eg:Sleep(time)
            int overtime ;
            
            while (true) {
              
                switch (gameState) {
                case PLAYING:


                    //打开音乐，播放音乐  alias 取别名 repeat 重复播放
                   mciSendString("play BGM_PLAYING ", NULL, 0, NULL); 
                   mciSendString("play BGM_PLAYING repeat", NULL, 0, NULL);         
                    drawBackground();   // 绘制背景
                    drawGround();       // 绘制地面
                    drawBricks();       // 绘制砖块
                    drawNagisa(nagisa);   // 绘制人物
                    drawMonster(monster_One, monster_Tow); // 绘制春园和往人
                    drawBullet(bullet); // 绘制子弹 
                    settextstyle(30, 0, ("宋体"));
                    outtextxy(30, 30, ("当前得分："));
                    itoa(score, scoreStr, 10);
                    // 使用itoa将整数转换为字符串   
                    // 第一个参数是要转换的整数，第二个参数是转换后的字符串的基数（10表示十进制）  
                    outtextxy(180, 30, scoreStr);                   

 // 更新游戏状态2024.7.18,,明天继续
                    updateGame(nagisa, bullet, monster_One, monster_Tow);
                    if (bullet.active) {
                        // 碰撞检测：子弹与春园和往人是否相交
                        if (bullet.x + imgBullet_yuan.getwidth() >= monster_One.x &&
                            bullet.x <= monster_One.x + imgMonster_One.getwidth() &&
                            bullet.y + imgBullet_yuan.getheight() >= monster_One.y &&
                            bullet.y <= monster_One.y + imgMonster_One.getheight() &&
                            bullet.x + imgBullet_zhezhao.getwidth() >= monster_One.x &&
                            bullet.x <= monster_One.x + imgMonster_One.getwidth() &&
                            bullet.y + imgBullet_zhezhao.getheight() >= monster_One.y &&
                            bullet.y <= monster_One.y + imgMonster_One.getheight()) {                
                            // 击中春园和往人，重置子弹状态
                            if(monster_One.health == 100)
                            { 
                            PlaySound(_T("子弹打到敌人.wav"), NULL, SND_FILENAME | SND_ASYNC);//使用EasyX 图形库时，PlaySound函数可以用来在图形界面程序中播放声音
                            //常用的标志包括 SND_FILENAME（pszSound 是一个文件名）、SND_RESOURCE（pszSound 是一个资源名）、SND_ASYNC（异步播放声音，即函数立即返回）
                            // SND_SYNC（同步播放声音，即等待声音播放完成后函数才返回）和 SND_LOOP（循环播放声音）。
                            }
                            putimage(monster_One.x, monster_One.y, &imgMonster_Oneshouji_zhezhao, SRCAND);
                            putimage(monster_One.x, monster_One.y, &imgMonster_Oneshouji, SRCPAINT);//受到攻击动画SRCPAINT  
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
                    // 重新生成春园和往人位置
                    if (monster_One.health == 0)
                    {
                        PlaySound(_T("敌人倒下.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
                     
                    // 碰撞检测：人物与春园和往人是否相交
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

                    //子弹动画放在updateGame后面7.19日完成
                    if (bullet.active)
                    {
                        bullet.iframe = bullet.iframe + 1;


                        switch ((int)bullet.iframe)
                        {
                        case 1:
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_zhezhao1, SRCAND); 
                            //添加位运算宏宏： “ SRCAND ” 做与运算，消除白色部分
                            putimage(bullet.x, bullet.y, &imgHaiXing_Animation_yuan1, SRCPAINT);  
                            //宏： “SRCPAINT” 做或运算，消除黑边                   
                                                                                                  
                            //先对遮罩层做与运算保留黑海星主体，再对原图做或运算，保留原图海星主体叠加上做了与运算的遮罩层
                                                                                                 
                            //详情见"https://blog.csdn.net/m0_60777643/article/details/122833558"     
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
                    //顺带一提，这个地方准备做人物向右的动作的，但是不知道为什么会出现闪屏，以后再说 ，已解决，多放张图片即可
                
            if (nagisa.turn == -1)//人物向左
            {
                
                switch ((int)nagisa.iframe)
                {
                case 1:

                    /* putimage(, &img_ayuyi_left1, SRCAND);*///黑色反转图添加位运算宏宏： “ SRCAND ” 做与运算 宏： “SRCPAINT” 做或运算
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
            // 检查游戏结束条件
            switch (currentLevel) {
            case Level::Level1_1:
                // 在1-1关卡中，如果人物达到一定位置，切换到1-2关卡
                if (nagisa.x > 780) {
                    currentLevel = Level::Level1_2; \
                        score += 100;
                    nagisa.x = 10; // 切换关卡后，重新设置人物位置
                    nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();

                    monster_One.x = WindowWidth + 50;
                    monster_Tow.x = WindowWidth - 30;
                }
                break;
            case Level::Level1_2:
                // 在1-2关卡中，如果人物达到一定位置，切换到1-3关卡
                if (nagisa.x > 780) {
                    currentLevel = Level::Level1_3;
                    score += 150;
                    nagisa.x = 10; // 切换关卡后，重新设置人物位置
                    nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
                    monster_One.x = WindowWidth + 20;
                    monster_Tow.x = WindowWidth + 180;
                }
                if (nagisa.x < -50) {//在1-2关卡中，如果人物达到[一定位置屏幕最左边，切换到1-1关卡
                    currentLevel = Level::Level1_1;
                    nagisa.x = 790; // 切换关卡后，重新设置人物位置
                    nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
                    monster_One.x = WindowWidth + 40;
                    monster_Tow.x = WindowWidth + 180;
                }
                break;
            case Level::Level1_3:
                // 在1-3关卡中，如果人物达到一定位置，游戏结束
                if (nagisa.x < -50) {//在1-2关卡中，如果人物达到[一定位置屏幕最左边，切换到1-1关卡
                    currentLevel = Level::Level1_2;
                    nagisa.x = 790; // 切换关卡后，重新设置人物位置
                    nagisa.y = WindowHeight - GroundHeight - imgNagisa.getheight();
                    monster_One.x = WindowWidth + 30;
                    monster_Tow.x = WindowWidth + 180;
                }
                if (nagisa.x > 800) {
                    currentLevel = Level::GameOver;
                    score += 200;
                    cleardevice(); // 清空屏幕
                    PlaySound(_T("胜利音乐.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    mciSendString("close BGM_PLAYING", NULL, 0, NULL);
                    mciSendString("play BGM_GAMEOVER", NULL, 0, NULL); 
                    mciSendString("play BGM_GAMEOVER repeat", NULL, 0, NULL);

                    putimage(0, 0, &gamewin_background);
                    settextcolor(BLACK);   
                    settextstyle(20, 0, ("宋体"));
                    outtextxy(500, 150, ("成功保卫了古河面包店！")); // 显示游戏结束信息
                    outtextxy(500, 180, ("总计得分："));
                    itoa(score, scoreStr, 10);
                    outtextxy(600, 180, scoreStr);
                    outtextxy(500, 210, ("按任意键即可返回主菜单"));
                    overtime = 50000;
                    if (_getch())//检查当前是否有键盘输入
                    {     
                        overtime = 0;
                    }
                    Sleep(overtime);
                    mciSendString("close BGM_GAMEOVER", NULL, 0, NULL);
                    //无操作3秒后自动返回主菜单
                    gameState = MAIN_MENU;
                }
                break;
            default:
                break;
            }     
            FlushBatchDraw();   // 刷新屏幕
            Sleep(30); // 控制帧率
                   //if(GetAsyncKeyState('L'))// ESC键为暂停  ********暂停有点问题**************** 2024.7 18修复
                    
                if (_kbhit())//检查当前是否有键盘输入
                {

                    int ch = _getch(); //这里等待输入，起到暂停程序的作用
                   
                    if (/*ch == 'q'||ch=='Q' ||*/GetAsyncKeyState(VK_ESCAPE))//q、Q、Esc键暂停
                    {
                        pause_count = 1;
                        BeginBatchDraw();
                      
                        settextcolor(LIGHTRED);
                        setlinecolor(BLACK);
               
                        fillroundrect(x_size / 2 - 65, Y_size / 3, x_size / 2 + 55, Y_size / 3 + 30, 10, 10);//圆角矩形，后面两参数10,10是调节圆角程度
                        settextcolor(BROWN);
                        setfont(30, 0, "宋体");
                        outtextxy(x_size / 2 - 65, Y_size / 3, "继续游戏");
                        fillroundrect(x_size / 2 - 65, Y_size / 3 + 30, x_size / 2 + 55, Y_size / 3 + 60, 10, 10);
                        outtextxy(x_size / 2 - 65, Y_size / 3 + 30, " 主菜单 ");
                        fillroundrect(x_size / 2 - 65, Y_size / 3 + 60, x_size / 2 + 55, Y_size / 3 + 90, 10, 10);
                        outtextxy(x_size / 2 - 65, Y_size / 3 + 60, "退出游戏");
                        EndBatchDraw();
                    }
                        ExMessage msg;
                        while (pause_count == 1  )
                        {


                            if (peekmessage(&msg, EM_MOUSE)&&msg.message == WM_LBUTTONDOWN)//如果点击的鼠标消息为鼠标左键
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
                            //打开音乐，播放音乐  alias 取别名 repeat 重复播放
                            mciSendString("play BGM_GAMEOVER", NULL, 0, NULL);
                            mciSendString("play BGM_GAMEOVER repeat", NULL, 0, NULL);                           
                           /*currentLevel = Level::GameOver;*/
                           cleardevice(); // 清空屏幕
                           putimage(0, 0, &gameover_background);
                           settextcolor(RED);
                           settextstyle(30, 0, ("宋体"));
                           outtextxy(100, 50, ("游戏结束！")); // 显示游戏结束信息
                           outtextxy(120, 80, ("按任意键即可返回主菜单"));
                           outtextxy(120, 110, ("无操作60秒后自动返回主菜单"));
                            time = 60000;                     
                            if (_getch())//检查当前是否有键盘输入
                            {
                                time = 0;
                                //_getch();//检查当前是否有键盘输入 
                            }
                            Sleep(time);//无操作后自动返回主菜单
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
 
// 主函数 
void main()
{
   
        initGame();     
        game g;
        g.start();
        show_animation(nagisa);
        gameLoop(); // 游戏循环

}


