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
    IMAGE img; // ���ڼ���֡ͼ��  

    for (int i = 0; i < frameCount; i++)
    {
        BeginBatchDraw(); // ����˫����  
        cleardevice();    // �������ڻ��������У���ֱ��Ӱ����ʾ��  
        loadimage(&img, frames[i]); // ���ص�ǰ֡ͼƬ  
        putimage(x, y, &img);       // ��ʾ��ǰ֡  
        FlushBatchDraw();           // ˢ�»��������ݵ���Ļ  

        // �ж��Ƿ��м�����  
        if (_kbhit()) {
            int ch = _getch();
            if (ch == ' ') {  // �ո���������  
                break;
            }
        }

        Sleep(16);                  // ����֡���ʱ�䣬Ŀ��֡�ʽӽ� 60FPS  
    }

    img = IMAGE(); // �ͷ�ͼ����Դ  
}

