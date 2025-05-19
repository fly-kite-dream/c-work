#define _CRT_SECURE_NO_WARNINGS  
#include <graphics.h>  
#include <conio.h>  
#include <stdio.h>  
#include <windows.h>  
#include<Windows.h>
#include <time.h>
#include <math.h>
#include "enemy_logic.h"
#include "player_control.h"
#include "bullet_logic.h"
#include "game_init.h"
#include "game_draw.h"
#include "cutscene.h"
#include"game_types.h"
#include "num.h"

#pragma comment(lib, "winmm.lib")  
#define START_X 50  
#define START_Y 550  
#define END_X 750  
#define END_Y 50  
#define RAY_SIZE 10  
#define BAR_HEIGHT 400  
#define BAR_WIDTH 30  
#define MOVE_UP_RATE 2 
#define MOVE_DOWN_RATE 1.5 
#define MAX_PROGRESS 100  
#define WIDTH 980  
#define HEIGHT 615 

void movePlayer(char key);
void firePlayerBullet();

#define TANK_SIZE 40
#define BULLET_SIZE 6
#define SPEED 5
#define MAX_BULLETS 20
#define MAX_WALLS 7
#define MAX_WAVES 3
#define USERNAME "1"
#define PASSWORD "1"
bool iscollidingrect(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
    return (ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by);
}



const char* imageLocks[60] = {
    "source\\lock\\dock00.jpg",
    "source\\lock\\dock01.jpg",
    "source\\lock\\dock02.jpg",
    "source\\lock\\dock03.jpg",
    "source\\lock\\dock04.jpg",
    "source\\lock\\dock05.jpg",
    "source\\lock\\dock06.jpg",
    "source\\lock\\dock07.jpg",
    "source\\lock\\dock08.jpg",
    "source\\lock\\dock09.jpg",
    "source\\lock\\dock10.jpg",
    "source\\lock\\dock11.jpg",
    "source\\lock\\dock12.jpg",
    "source\\lock\\dock13.jpg",
    "source\\lock\\dock14.jpg",
    "source\\lock\\dock15.jpg",
    "source\\lock\\dock16.jpg",
    "source\\lock\\dock17.jpg",
    "source\\lock\\dock18.jpg",
    "source\\lock\\dock19.jpg",
    "source\\lock\\dock20.jpg",
    "source\\lock\\dock21.jpg",
    "source\\lock\\dock22.jpg",
    "source\\lock\\dock23.jpg",
    "source\\lock\\dock24.jpg",
    "source\\lock\\dock25.jpg",
    "source\\lock\\dock26.jpg",
    "source\\lock\\dock27.jpg",
    "source\\lock\\dock28.jpg",
    "source\\lock\\dock29.jpg",
    "source\\lock\\dock30.jpg",
    "source\\lock\\dock31.jpg",
    "source\\lock\\dock32.jpg",
    "source\\lock\\dock33.jpg",
    "source\\lock\\dock34.jpg",
    "source\\lock\\dock35.jpg",
    "source\\lock\\dock36.jpg",
    "source\\lock\\dock37.jpg",
    "source\\lock\\dock38.jpg",
    "source\\lock\\dock39.jpg",
    "source\\lock\\dock40.jpg",
    "source\\lock\\dock41.jpg",
    "source\\lock\\dock42.jpg",
    "source\\lock\\dock43.jpg",
    "source\\lock\\dock44.jpg",
    "source\\lock\\dock45.jpg",
    "source\\lock\\dock46.jpg",
    "source\\lock\\dock47.jpg",
    "source\\lock\\dock48.jpg",
    "source\\lock\\dock49.jpg",
    "source\\lock\\dock50.jpg",
    "source\\lock\\dock51.jpg",
    "source\\lock\\dock52.jpg",
    "source\\lock\\dock53.jpg",
    "source\\lock\\dock54.jpg",
    "source\\lock\\dock55.jpg",
    "source\\lock\\dock56.jpg",
    "source\\lock\\dock57.jpg",
    "source\\lock\\dock58.jpg",
    "source\\lock\\dock59.jpg"
};




struct a//����һ���ṹ��
{
    IMAGE kk;//ͼƬ���� ������
    struct a* next;//ָ����
};


bool CheckFailArea(int rayX, int rayY, int startX, int endX, int startY, int endY)
{
    // ����������Ͻ������Ƿ����ض�����  
    return (rayX >= startX) && (rayX <= endX) &&
        (rayY >= startY) && (rayY <= endY);
}




#define BUTTON_COLOR     RGB(100, 150, 250)  // ��ť��ɫ  
#define BUTTON_HOVER     RGB(80, 120, 220)   // ��ť��ͣ��ɫ  
#define TEXT_COLOR       WHITE               // ��ť������ɫ  
#define BG_BAR_COLOR     RGB(30, 30, 50)     // ��ť���򱳾���ɫ  




// ��Ļ���  
#define WIDTH 980  
#define HEIGHT 615   
IMAGE Background; // ��������ͼ�����  
int num = 0;//�����жϸý���������,1Ϊ��һ��û����2����ڶ��ع��ˣ�3�������ڶ���
int main() {
    initgraph(1210, 615);
    BeginBatchDraw();
    if (loginInterface()) {
        drawStartInterface();
        handleMouseEvent();
    }

    EndBatchDraw();
    closegraph();
    char tempPaths[1010][50];
    initgraph(WIDTH, HEIGHT);
    char paths1[1010][50];
    for (int i = 0; i < 500; i++) {
        sprintf((char*)paths1[i], "source\\1\\story%05d.png", 10000 + i); // ����·��  
    }

    // ����ָ�����鲢��ʼ����ÿ��ָ��ָ���ά�����һ�У�  
    const char* frames1[1010];
    for (int i = 0; i < 500; i++) {
        frames1[i] = paths1[i];
    }
    
    if (!PlaySound(TEXT("source\\01.wav"), NULL, SND_FILENAME | SND_ASYNC)) {
        printf("Failed to play sound.\n");
        return -1; // �����Ƶ�ļ������ڣ���ֹ����  
    }
    

    playstory(frames1,500,0,0);
    initgraph(WIDTH, HEIGHT);
 

    BeginBatchDraw();
    imageshow("source\\background3.png");
    EndBatchDraw();

    // ��ʼ������λ��  
    int ray_x = START_X + 30;
    int ray_y = START_Y -25;

     //��ҿ��Ʒ��򣬳�ʼ���ϣ�dx, dy �ֱ��ʾ�ƶ��ķ���������  
    int dx = 0, dy = 0;
   ;
    while (1) {
        // �������֮ǰ�Ļ���  
        if (
            CheckFailArea(ray_x, ray_y, 0, 271, 0, 409) ||
            CheckFailArea(ray_x, ray_y, 215, 251, 502, 591) ||
            CheckFailArea(ray_x, ray_y, 245, 274, 329, 450) ||
            CheckFailArea(ray_x, ray_y, 275, 555, 330, 380) ||
            CheckFailArea(ray_x, ray_y, 275, 745, 381, 450) ||
            CheckFailArea(ray_x, ray_y, 310, 400, 193, 205) ||
            CheckFailArea(ray_x, ray_y, 331, 658, 205, 273) ||
            CheckFailArea(ray_x, ray_y, 332, 400, 237, 294) ||
            CheckFailArea(ray_x, ray_y, 447, 626, 90, 169) ||
            CheckFailArea(ray_x, ray_y, 596, 657, 273, 324) ||
            CheckFailArea(ray_x, ray_y, 657, 682, 244, 325) ||
            CheckFailArea(ray_x, ray_y, 683, 740, 145, 326) ||
            CheckFailArea(ray_x, ray_y, 738, 935, 243, 328) ||
            CheckFailArea(ray_x, ray_y, 787, 857, 90, 170) ||
            CheckFailArea(ray_x, ray_y, 603, 803, 493, 594) ||
            CheckFailArea(ray_x, ray_y, 801, 923, 330, 494)|| 
          //  CheckFailArea(ray_x, ray_y, 0, 69, 0,615)||
            CheckFailArea(ray_x, ray_y, 934, 980, 0, 615)||
            CheckFailArea(ray_x, ray_y, 0, 980, 0, 91.2)||
            CheckFailArea(ray_x, ray_y, 0, 980, 590, 615)


            ) {
            num = 1;//fail
        }
        if (CheckFailArea(ray_x, ray_y, 904, 923, 160, 215)|| CheckFailArea(ray_x, ray_y, 0, 69, 0, 615)) { num = 2; }//success

        if (num == 1)
        {
            ShowImageAndRestart("source\\Screenshot 2025-03-03 110408.png");
            RestartGame(&ray_x, &ray_y,&dx,&dy);
            num = 0;
        }
        if (num == 2)
        {
            ShowImageAndRestart("source\\laoda2.png");
            num = 3;
        }
        if (num == 3)
        {
            num = 0;
            break;
        }


        setfillcolor(WHITE); // ʹ�ð�ɫ����������ߵľ�λ��  
        solidrectangle(ray_x, ray_y, ray_x + RAY_SIZE, ray_y + RAY_SIZE); // ���������  

        // �������Ʒ���  
        if (_kbhit()) {
            char key = _getch(); // ��ȡ���µļ�  
            if (GetAsyncKeyState('W') & 0x8000) { dx = 0; dy = -3; }  // ����  
            if (GetAsyncKeyState('S') & 0x8000) { dx = 0; dy = 3; }   // ����  
            if (GetAsyncKeyState('A') & 0x8000) { dx = -3; dy = 0; }  // ����  
            if (GetAsyncKeyState('D') & 0x8000) { dx = 3; dy = 0; }   // ����  
        }

        // �������ߵ�λ��  
        ray_x += dx;
        ray_y += dy;

        // ȷ�����߲��������ڱ߽�  
        if (ray_x < 0) ray_x = 0;
        if (ray_x > WIDTH - RAY_SIZE) ray_x = WIDTH - RAY_SIZE;
        if (ray_y < 0) ray_y = 0;
        if (ray_y > HEIGHT - RAY_SIZE) ray_y = HEIGHT - RAY_SIZE;

        // �������ߵ���λ��  
        setfillcolor(GREEN);
        solidrectangle(ray_x, ray_y, ray_x + RAY_SIZE, ray_y + RAY_SIZE); // ��������  

        // �ӳ�   
        Sleep(30);
    }
    cleardevice();
    RestartGame1(&ray_x, &ray_y, &dx, &dy);
    BeginBatchDraw();
    imageshow("source\\background4.png");
    EndBatchDraw();

    while (1) {
        // �������֮ǰ�Ļ���  
        if (
            CheckFailArea(ray_x, ray_y, 51, 128, 398, 439) ||
            CheckFailArea(ray_x, ray_y, 141, 234, 525, 590) ||
            CheckFailArea(ray_x, ray_y, 91, 171, 293, 352) ||
            CheckFailArea(ray_x, ray_y, 172, 267, 90, 485) ||
            CheckFailArea(ray_x, ray_y, 280, 320, 364, 551) ||
            CheckFailArea(ray_x, ray_y, 266, 624, 80, 150) ||
            CheckFailArea(ray_x, ray_y, 369, 414, 161, 234) ||
            CheckFailArea(ray_x, ray_y, 530, 589, 160, 194) ||
            CheckFailArea(ray_x, ray_y, 447, 626, 90, 169) ||
            CheckFailArea(ray_x, ray_y, 339, 438, 274, 334) ||
            CheckFailArea(ray_x, ray_y, 363, 451, 364, 463) ||
            CheckFailArea(ray_x, ray_y, 466, 500, 195, 290) ||
            CheckFailArea(ray_x, ray_y, 500, 567, 240, 289) ||
            CheckFailArea(ray_x, ray_y, 452, 482, 355, 438) ||
            CheckFailArea(ray_x, ray_y, 564, 624, 325, 435) ||
            CheckFailArea(ray_x, ray_y, 622, 676, 327, 474) ||
            CheckFailArea(ray_x, ray_y, 381, 687, 517, 592) ||
            CheckFailArea(ray_x, ray_y, 483, 555, 486, 512) ||
            CheckFailArea(ray_x, ray_y, 590, 756, 240, 289) ||
            CheckFailArea(ray_x, ray_y, 691, 757, 120, 241) ||
            CheckFailArea(ray_x, ray_y, 742, 802, 244, 590) ||
            CheckFailArea(ray_x, ray_y, 804, 827, 244, 443) ||
            CheckFailArea(ray_x, ray_y, 832, 884, 289, 374) ||
            CheckFailArea(ray_x, ray_y, 831, 858, 239, 373)
            ) {
            num = 1; // fail  
        }

        if (CheckFailArea(ray_x, ray_y, 835, 893, 560, 599) || CheckFailArea(ray_x, ray_y, 0, 44, 151, 209)) {
            num = 2; // success  
        }

        if (num == 1) {
            ShowImageAndRestart1("source\\Screenshot 2025-03-03 110408.png");
            RestartGame1(&ray_x, &ray_y, &dx, &dy);
            num = 0;
        }
        if (num == 2) {
            ShowImageAndRestart1("source\\laoda2.png");
            num = 3;
        }
        if (num == 3) break;

        setfillcolor(WHITE); // ʹ�ð�ɫ����������ߵľ�λ��  
        solidrectangle(66, 188, 66 + RAY_SIZE, 188 + RAY_SIZE); // ���������  

        // �������Ʒ���  
        if (_kbhit()) {
            char key = _getch(); // ��ȡ���µļ�  
            if (GetAsyncKeyState('W') & 0x8000) { dx = 0; dy = -3; }  // ����  
            if (GetAsyncKeyState('S') & 0x8000) { dx = 0; dy = 3; }   // ����  
            if (GetAsyncKeyState('A') & 0x8000) { dx = -3; dy = 0; }  // ����  
            if (GetAsyncKeyState('D') & 0x8000) { dx = 3; dy = 0; }   // ����  
        }

        // �������ߵ�λ��  
        ray_x += dx;
        ray_y += dy;

        // ȷ�����߲��������ڱ߽�  
        if (ray_x < 0) ray_x = 0;
        if (ray_x > WIDTH - RAY_SIZE) ray_x = WIDTH - RAY_SIZE;
        if (ray_y < 0) ray_y = 0;
        if (ray_y > HEIGHT - RAY_SIZE) ray_y = HEIGHT - RAY_SIZE;

        // �������ߵ���λ��  
        setfillcolor(GREEN);
        solidrectangle(ray_x, ray_y, ray_x + RAY_SIZE, ray_y + RAY_SIZE); // ��������  

        // �ӳ�   
        Sleep(30);
    };
    bool keyW = false;
    char paths2[729][50]; // ����·���Ķ�ά����  

    // ���ݱ������·������ʼ��� 2000��������� 2728  
    for (int i = 0; i < 729; i++) {
        sprintf(paths2[i], "source\\2\\story%04d.png", 2000 + i); // ����·����ʽ  
    }

    // ����ָ�����飬����ÿ��ָ��ָ���ά�����е�һ��  
    const char* frames2[729];
    for (int i = 0; i < 729; i++) {
        frames2[i] = paths2[i];
    }

    if (!PlaySound(TEXT("source\\02.wav"), NULL, SND_FILENAME | SND_ASYNC)) {
        printf("Failed to play sound.\n");
        return -1; // �����Ƶ�ļ������ڣ���ֹ����  
    }


    playstory(frames2, 729, 0, 0);
        // ... ����ԭ�д��� ...  

        // ���뿪����Ϸ����  
        cleardevice();

        // ���ؿ���������һ֡��Ϊ��ʼ����  
        IMAGE initialLockImage;
        loadimage(&initialLockImage, imageLocks[0]);
        putimage(0, 0, &initialLockImage);

        // ��ʼ����Ϸ״̬  
        GameState state;
        initGameState(&state);

        const int frameCount = sizeof(imageLocks) / sizeof(imageLocks[0]);

        // ʹ��˫�����ֹ����  
        BeginBatchDraw();
       
 
        while (true) {
            BeginBatchDraw();

            // ���ز���ʾ�����򶯻�֡  
            if (state.isAnimPlaying) {
                IMAGE animFrame;
                loadimage(&animFrame, imageLocks[state.animFrame]);
                putimage(0, 0, &animFrame);

                // ���¶���֡  
                state.animFrame = (state.animFrame + 1) % frameCount;
            }
            else {
                // δ���Ŷ���ʱ��ʾ��һ֡  
                putimage(0, 0, &initialLockImage);
            }

            // ������Ϸ״̬  
            updateGameState(&state);

            // ����UI  
            drawGameUI(&state);

            // ˢ�µ���Ļ  
            FlushBatchDraw();

            // ����֡��  
            Sleep(33); // Լ30FPS  

            // �˳����  
            if (GetAsyncKeyState('Q') & 0x8000) break;

            // �����Ϸ�Ƿ����  
            if (state.drillProgress >= MAX_PROGRESS) {
                // ��Ϸʤ���߼�  
                break;
            }
        }
        char paths4[1070][50];
        for (int i = 0; i < 500; i++) {
            sprintf((char*)paths4[i], "source\\4\\story%05d.png", 40000 + i); // ����·��  
        }

        // ����ָ�����鲢��ʼ����ÿ��ָ��ָ���ά�����һ�У�  
        const char* frames4[1070];
        for (int i = 0; i < 500; i++) {
            frames4[i] = paths4[i];
        }
        if (!PlaySound(TEXT("source\\03.wav"), NULL, SND_FILENAME | SND_ASYNC)) {
            printf("Failed to play sound.\n");
            return -1; // �����Ƶ�ļ������ڣ���ֹ����  
        }

        playstory(frames4, 500, 0, 0);
        initGame();

        // ���ʵ�λ��ȫ���������ʼ��  

        while (1) {
            cleardevice();
            animCount++;

            processInput();  // ��������  

            moveEnemy();
            updateBullets();

            // ����ʾ��������Ҫȷ��ÿ����һ������ʱ���� enemiesDefeated  
            // ��������ײ�����������ʱִ�У� enemiesDefeated++;  

            checkWaveProgress();

            drawWalls();
            if (player.alive) drawTank(&player);
            EnemyNode* current = enemyList;
            while (current != NULL) {
                drawTank(&current->tank);
                current = current->next;
            }
            for (int i = 0; i < MAX_BULLETS; i++) {
                drawBullet(&bullets[i]);
            }

            // ʤ���жϣ�����6������  
            if (enemiesDefeated >= 6) {
                settextcolor(GREEN);
                settextstyle(50, 0, "Arial");
                outtextxy(WIDTH / 2 - 150, HEIGHT / 2 - 25, "YOU WIN!");
                FlushBatchDraw();
                // �ȴ���Ұ������˳�  
                while (!_kbhit()) Sleep(100);
                break;
            }

            // ��Ϸʧ���ж�  
            if (!player.alive) {
                settextcolor(RED);
                settextstyle(50, 0, "Arial");
                outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 25, "GAME OVER");
                FlushBatchDraw();
                while (!_kbhit()) Sleep(100);
                break;
            }

            FlushBatchDraw();
            Sleep(30);
        }

        freeEnemyList(&enemyList);
        
        EndBatchDraw();
        closegraph();
        return 0;
    }