#include<stdio.h>
#include <graphics.h>
#include <conio.h>
  #include <windows.h>
#include <mmsystem.h>  
#pragma comment(lib,"winmm.lib")//���ؾ�̬��
int main() {
    // ��ʼ�� MCI �豸  
    //mciSendString("open ��ʼ����.mp3 alias BGM", NULL, 0, NULL);

    //// ��������  
    //mciSendString("play BGM", NULL, 0, NULL);
    mciSendString("open ��ʼ����.wav alias BGM", NULL, 0, NULL);
    mciSendString("play BGM", NULL, 0, NULL);
    _getch();
   //********************************************************
    //ʹ��EasyX ͼ�ο�ʱ��PlaySound��������������ͼ�ν�������в�������
    //���õı�־���� SND_FILENAME��pszSound ��һ���ļ�������SND_RESOURCE��pszSound ��һ����Դ������SND_ASYNC���첽�����������������������أ�
    // SND_SYNC��ͬ���������������ȴ�����������ɺ����ŷ��أ��� SND_LOOP��ѭ������������
    //// ֹͣ����  
    //mciSendString("stop BGM",0, 0, 0);

    //// �ر� MCI �豸  
    //mciSendString("close BGMG",0, 0,0);
    return 0;
}