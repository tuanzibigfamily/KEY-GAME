#include<stdio.h>
#include <graphics.h>
#include <conio.h>
  #include <windows.h>
#include <mmsystem.h>  
#pragma comment(lib,"winmm.lib")//加载静态库
int main() {
    // 初始化 MCI 设备  
    //mciSendString("open 开始音乐.mp3 alias BGM", NULL, 0, NULL);

    //// 播放音乐  
    //mciSendString("play BGM", NULL, 0, NULL);
    mciSendString("open 开始音乐.wav alias BGM", NULL, 0, NULL);
    mciSendString("play BGM", NULL, 0, NULL);
    _getch();
   //********************************************************
    //使用EasyX 图形库时，PlaySound函数可以用来在图形界面程序中播放声音
    //常用的标志包括 SND_FILENAME（pszSound 是一个文件名）、SND_RESOURCE（pszSound 是一个资源名）、SND_ASYNC（异步播放声音，即函数立即返回）
    // SND_SYNC（同步播放声音，即等待声音播放完成后函数才返回）和 SND_LOOP（循环播放声音）
    //// 停止播放  
    //mciSendString("stop BGM",0, 0, 0);

    //// 关闭 MCI 设备  
    //mciSendString("close BGMG",0, 0,0);
    return 0;
}