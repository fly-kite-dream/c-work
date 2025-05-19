#define _CRT_SECURE_NO_WARNINGS  
#include "cutscene.h"
#include <graphics.h>
#include <stdio.h>  
#include <windows.h>  
#include <conio.h>
#include<Windows.h>
#include "num.h"
void playstory(const char* frames[], int frameCount, int x, int y)
{
    IMAGE img; // 用于加载帧图像  

    for (int i = 0; i < frameCount; i++)
    {
        BeginBatchDraw(); // 开启双缓冲  
        cleardevice();    // 清屏（在缓冲区进行，不直接影响显示）  
        loadimage(&img, frames[i]); // 加载当前帧图片  
        putimage(x, y, &img);       // 显示当前帧  
        FlushBatchDraw();           // 刷新缓冲区内容到屏幕  

        // 判断是否有键按下  
        if (_kbhit()) {
            int ch = _getch();
            if (ch == ' ') {  // 空格跳过剧情  
                break;
            }
        }

        Sleep(16);                  // 设置帧间隔时间，目标帧率接近 60FPS  
    }

    img = IMAGE(); // 释放图像资源  
}

