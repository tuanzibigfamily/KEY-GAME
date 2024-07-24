//创作者 森匠，汐风，2024.7.24日完成，小游戏只是为爱发电做的，还有许多需要完善的地方，
// 欢迎登录github参与建设，项目地址为：https://github.com/tuanzibigfamily/KEY-GAME
#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <iostream> // 包含输入输出流
#include<math.h>
#include"字体格式优化.h"
IMAGE imgBackground1_One;
IMAGE imgBackground1_Tow;
#define x_size 800                 //屏幕大小
#define Y_size 600
class game {     
public:
int pause;  
    void start();          //处理游戏开始的界面，和按暂停键后的界面
};

void game::start()
{
    loadimage(&imgBackground1_One, _T("res\\background_1.png"), 800, 600, true);
    loadimage(&imgBackground1_Tow, _T("res\\back.jpg"), 800, 600, true);
    cleardevice();
    putimage(0, 0, &imgBackground1_One);
    setlinecolor(BLACK);
    setbkcolor(WHITE);
    fillroundrect(x_size / 2 - 150, Y_size / 6, x_size / 2 + 170, Y_size / 6 + 40, 10, 10);//圆角矩形，后面两参数10,10是调节圆角程度
    settextcolor(BROWN); // 设置文字颜色为黑色  
    settextstyle(20, 0, "宋体"); // 设置文字大小为20，加粗，字体  
    setfont(40, 0, "楷体");
    /*outtextxy(x_size-400, 200, "游戏开始");*/
    RECT r1 = { 0, 0, x_size, Y_size / 3 };
    outtextxy(x_size / 2 - 150 , Y_size / 6,"古河面包店大危机");
    settextcolor(BROWN);
    setfont(20, 0, "宋体");
    RECT r2 = { x_size / 2 - 45,Y_size / 3,x_size / 2 + 45,Y_size / 3 + 30 }; rectangle(x_size / 2 - 45, Y_size / 3, x_size / 2 + 45, Y_size / 3 + 30);
    drawtext("开始游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r3 = { x_size / 2 - 45,Y_size / 3 + 30,x_size / 2 + 45,Y_size / 3 + 60 }; rectangle(x_size / 2 - 45, Y_size / 3 + 30, x_size / 2 + 45, Y_size / 3 + 60);
    drawtext("游戏介绍", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r4 = { x_size / 2 - 45,Y_size / 3 + 60,x_size / 2 + 45,Y_size / 3 + 90 }; rectangle(x_size / 2 - 45, Y_size / 3 + 60, x_size / 2 + 45, Y_size / 3 + 90);
    drawtext("操作说明", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r5 = { x_size / 2 - 45,Y_size / 3 + 90,x_size / 2 + 45,Y_size / 3 + 120 }; rectangle(x_size / 2 - 45, Y_size / 3 + 90, x_size / 2 + 45, Y_size / 3 + 120);
    drawtext("退出游戏", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    int flag1 = 1, flag2 = 0, flag3 = 0;
    MOUSEMSG m;
    while (flag1 == 1)
    {
        BeginBatchDraw();
        m = GetMouseMsg();
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            EndBatchDraw();
            if (m.x > x_size / 2 - 45 && m.x<x_size / 2 + 45 && m.y>Y_size / 3 && m.y < Y_size / 3 + 30 && flag1 == 1 && flag2 == 0 && flag3 == 0)
            {
               
                flag1 = 0;
                break;
            }
            else if (m.x > x_size / 2 - 45 && m.x<x_size / 2 + 45 && m.y>Y_size / 3 + 30 && m.y < Y_size / 3 + 60 && flag1 == 1 && flag3 == 0)
            {
                flag2 = 1;
                cleardevice();
                putimage(0, 0, &imgBackground1_Tow);
                setfont(20, 0, "楷体");
                settextcolor(MAGENTA);
                setlinecolor(LIGHTCYAN);
                rectangle(x_size / 10 - 5, Y_size / 8, x_size / 2  , Y_size / 2 + 70);
                //后续添加创作者******************************************************************************2024.7.18注释
                outtextxy(x_size / 10, Y_size / 8 + 2,  "游戏介绍：");
                outtextxy(x_size / 10, Y_size / 8 + 27, "某天，祥和的古河面包店遭到了");
                outtextxy(x_size / 10, Y_size / 8 + 52, "突然闯入的春园阳平和国崎往人，");
                outtextxy(x_size / 10, Y_size / 8 + 77, "为了保护面包店，Nagisa和亚由");
                outtextxy(x_size / 10, Y_size / 8 + 102,"（友情出演w）站了出来,赶走了");
                outtextxy(x_size / 10, Y_size / 8 + 127,"这两个怪家伙，古河面包店最终");
                outtextxy(x_size / 10, Y_size / 8 + 152,"恢复了和平。");
                outtextxy(x_size / 10, Y_size / 8 + 177,"小游戏只是为爱发电做的，还有");
                outtextxy(x_size / 10, Y_size / 8 + 202,"许多需要完善的地方，欢迎登录");
                outtextxy(x_size / 10, Y_size / 8 + 227,"github参与建设，项目地址为：");
                outtextxy(x_size / 10, Y_size / 8 + 252,"https://github.com/tuanzibig");//项目地址 https://github.com/tuanzibigfamily/KEY-GAME
                outtextxy(x_size / 10, Y_size / 8 + 272,"family/KEY-GAME");
                RECT R1 = { x_size - 46,Y_size - 26,x_size - 2,Y_size - 2 }; rectangle(x_size - 46, Y_size - 26, x_size - 2, Y_size - 2);
                drawtext("返回", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                break;
            }
            else if (m.x > x_size / 2 - 45 && m.x<x_size / 2 + 45 && m.y>Y_size / 3 + 60 && m.y < Y_size / 3 + 90 && flag1 == 1 && flag2 == 0)
            {
                flag3 = 1;
                cleardevice();
                putimage(0, 0, &imgBackground1_One);
                settextcolor(LIGHTRED);
                setlinecolor(BLACK);
                rectangle(x_size / 2 - 115, Y_size / 3, x_size / 2 + 115, Y_size / 2 + 100);
                outtextxy(x_size / 2 - 110, Y_size / 3 + 2, "操作说明：");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 32, "左移：A键");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 62, "右移：D键");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 92, "发射：Z键");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 122, "跳跃：W键");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 152, "暂停：Esc键");
                RECT R2 = { x_size - 46,Y_size - 26,x_size - 2,Y_size - 2 }; rectangle(x_size - 46, Y_size - 26, x_size - 2, Y_size - 2);
                drawtext("返回", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                break;
            }
            else if (m.x > x_size / 2 - 45 && m.x<x_size / 2 + 45 && m.y>Y_size / 3 + 90 && m.y < Y_size / 3 + 120 && flag1 == 1 && flag2 == 0 && flag3 == 0)
                exit(0);
            else if (m.x > x_size - 46 && m.x<x_size - 3 && m.y>Y_size - 26 && m.y < Y_size - 3 && (flag2 == 1 || flag3 == 1))
            {
                cleardevice();
                flag1 = 0, flag2 = 0, flag3 = 0;
                start();
            }
            else
                break;
        case WM_MOUSEMOVE:
            RECT r;
            if (flag2 == 1 || flag3 == 1)
            {
                if (m.x > x_size - 46 && m.x<x_size - 3 && m.y>Y_size - 26 && m.y < Y_size - 3)
                {
                    r.left = x_size - 46;
                    r.top = Y_size - 26;
                    r.right = x_size - 2;
                    r.bottom = Y_size - 2;
                    int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
                    setfillstyle(RED);
                    fillpoly(4, points);
                    setbkmode(TRANSPARENT);
                    drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                }
                else
                {
                    if (getpixel(x_size - 46 + 1, Y_size - 26 + 1) == RED)
                    {
                        r.left = x_size - 46;
                        r.top = Y_size - 26;
                        r.right = x_size - 2;
                        r.bottom = Y_size - 2;
                        int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
                        setfillstyle(BLACK);
                        fillpoly(4, points);
                        setbkmode(TRANSPARENT);
                        drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    }
                }
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    if (m.x > x_size / 2 - 45 && m.x<x_size / 2 + 45 && m.y>Y_size / 3 + i * 30 && m.y < Y_size / 3 + 30 + i * 30)
                    {
                        r.left = x_size / 2 - 45;
                        r.top = Y_size / 3 + i * 30;
                        r.right = x_size / 2 + 45;
                        r.bottom = Y_size / 3 + 30 + i * 30;
                        int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
                        setfillstyle(RED);
                        fillpoly(4, points);
                        setbkmode(TRANSPARENT);
                        switch (i)
                        {
                        case 0:
                            drawtext("开始游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                            break;
                        case 1:
                            drawtext("游戏介绍", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                            break;
                        case 2:
                            drawtext("操作说明", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                            break;
                        case 3:
                            drawtext("退出游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                            break;
                        }
                    }
                    else
                    {
                        if (getpixel(x_size / 2 - 45 + 1, Y_size / 3 + i * 30 + 1) == RED)
                        {
                            r.left = x_size / 2 - 45;
                            r.top = Y_size / 3 + i * 30;
                            r.right = x_size / 2 + 45;
                            r.bottom = Y_size / 3 + 30 + i * 30;
                            int points[8] = { r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom };
                            setfillstyle(BLACK);
                            fillpoly(4, points);
                            setbkmode(TRANSPARENT);
                            switch (i)
                            {
                            case 0:
                                drawtext("开始游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                                break;
                            case 1:
                                drawtext("游戏介绍", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                                break;
                            case 2:
                                drawtext("操作说明", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                                break;
                            case 3:
                                drawtext("退出游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                                break;
                            }
                        }
                    }
                }
            }
            FlushBatchDraw();//开始批量绘图
            break;
        default:
            break;
        }
    }
}