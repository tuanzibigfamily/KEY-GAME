//������ ɭ����ϫ�磬2024.7.24����ɣ�С��Ϸֻ��Ϊ���������ģ����������Ҫ���Ƶĵط���
// ��ӭ��¼github���뽨�裬��Ŀ��ַΪ��https://github.com/tuanzibigfamily/KEY-GAME
#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <iostream> // �������������
#include<math.h>
#include"�����ʽ�Ż�.h"
IMAGE imgBackground1_One;
IMAGE imgBackground1_Tow;
#define x_size 800                 //��Ļ��С
#define Y_size 600
class game {     
public:
int pause;  
    void start();          //������Ϸ��ʼ�Ľ��棬�Ͱ���ͣ����Ľ���
};

void game::start()
{
    loadimage(&imgBackground1_One, _T("res\\background_1.png"), 800, 600, true);
    loadimage(&imgBackground1_Tow, _T("res\\back.jpg"), 800, 600, true);
    cleardevice();
    putimage(0, 0, &imgBackground1_One);
    setlinecolor(BLACK);
    setbkcolor(WHITE);
    fillroundrect(x_size / 2 - 150, Y_size / 6, x_size / 2 + 170, Y_size / 6 + 40, 10, 10);//Բ�Ǿ��Σ�����������10,10�ǵ���Բ�ǳ̶�
    settextcolor(BROWN); // ����������ɫΪ��ɫ  
    settextstyle(20, 0, "����"); // �������ִ�СΪ20���Ӵ֣�����  
    setfont(40, 0, "����");
    /*outtextxy(x_size-400, 200, "��Ϸ��ʼ");*/
    RECT r1 = { 0, 0, x_size, Y_size / 3 };
    outtextxy(x_size / 2 - 150 , Y_size / 6,"�ź�������Σ��");
    settextcolor(BROWN);
    setfont(20, 0, "����");
    RECT r2 = { x_size / 2 - 45,Y_size / 3,x_size / 2 + 45,Y_size / 3 + 30 }; rectangle(x_size / 2 - 45, Y_size / 3, x_size / 2 + 45, Y_size / 3 + 30);
    drawtext("��ʼ��Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r3 = { x_size / 2 - 45,Y_size / 3 + 30,x_size / 2 + 45,Y_size / 3 + 60 }; rectangle(x_size / 2 - 45, Y_size / 3 + 30, x_size / 2 + 45, Y_size / 3 + 60);
    drawtext("��Ϸ����", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r4 = { x_size / 2 - 45,Y_size / 3 + 60,x_size / 2 + 45,Y_size / 3 + 90 }; rectangle(x_size / 2 - 45, Y_size / 3 + 60, x_size / 2 + 45, Y_size / 3 + 90);
    drawtext("����˵��", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r5 = { x_size / 2 - 45,Y_size / 3 + 90,x_size / 2 + 45,Y_size / 3 + 120 }; rectangle(x_size / 2 - 45, Y_size / 3 + 90, x_size / 2 + 45, Y_size / 3 + 120);
    drawtext("�˳���Ϸ", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
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
                setfont(20, 0, "����");
                settextcolor(MAGENTA);
                setlinecolor(LIGHTCYAN);
                rectangle(x_size / 10 - 5, Y_size / 8, x_size / 2  , Y_size / 2 + 70);
                //������Ӵ�����******************************************************************************2024.7.18ע��
                outtextxy(x_size / 10, Y_size / 8 + 2,  "��Ϸ���ܣ�");
                outtextxy(x_size / 10, Y_size / 8 + 27, "ĳ�죬��͵Ĺź�������⵽��");
                outtextxy(x_size / 10, Y_size / 8 + 52, "ͻȻ����Ĵ�԰��ƽ�͹������ˣ�");
                outtextxy(x_size / 10, Y_size / 8 + 77, "Ϊ�˱�������꣬Nagisa������");
                outtextxy(x_size / 10, Y_size / 8 + 102,"���������w��վ�˳���,������");
                outtextxy(x_size / 10, Y_size / 8 + 127,"�������ּһ�ź����������");
                outtextxy(x_size / 10, Y_size / 8 + 152,"�ָ��˺�ƽ��");
                outtextxy(x_size / 10, Y_size / 8 + 177,"С��Ϸֻ��Ϊ���������ģ�����");
                outtextxy(x_size / 10, Y_size / 8 + 202,"�����Ҫ���Ƶĵط�����ӭ��¼");
                outtextxy(x_size / 10, Y_size / 8 + 227,"github���뽨�裬��Ŀ��ַΪ��");
                outtextxy(x_size / 10, Y_size / 8 + 252,"https://github.com/tuanzibig");//��Ŀ��ַ https://github.com/tuanzibigfamily/KEY-GAME
                outtextxy(x_size / 10, Y_size / 8 + 272,"family/KEY-GAME");
                RECT R1 = { x_size - 46,Y_size - 26,x_size - 2,Y_size - 2 }; rectangle(x_size - 46, Y_size - 26, x_size - 2, Y_size - 2);
                drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
                outtextxy(x_size / 2 - 110, Y_size / 3 + 2, "����˵����");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 32, "���ƣ�A��");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 62, "���ƣ�D��");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 92, "���䣺Z��");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 122, "��Ծ��W��");
                outtextxy(x_size / 2 - 110, Y_size / 3 + 152, "��ͣ��Esc��");
                RECT R2 = { x_size - 46,Y_size - 26,x_size - 2,Y_size - 2 }; rectangle(x_size - 46, Y_size - 26, x_size - 2, Y_size - 2);
                drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
                    drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
                        drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
                            drawtext("��ʼ��Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                            break;
                        case 1:
                            drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                            break;
                        case 2:
                            drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                            break;
                        case 3:
                            drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
                                drawtext("��ʼ��Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                                break;
                            case 1:
                                drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                                break;
                            case 2:
                                drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                                break;
                            case 3:
                                drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                                break;
                            }
                        }
                    }
                }
            }
            FlushBatchDraw();//��ʼ������ͼ
            break;
        default:
            break;
        }
    }
}