#include "player_control.h"
#include"game_types.h"
#include "enemy_logic.h"
#include "num.h"
void movePlayer(char key) {
    int newX = player.x, newY = player.y;
    switch (key) {
    case 'W': case 'w': newY -= SPEED; player.dir = 0; break;
    case 'D': case 'd': newX += SPEED; player.dir = 1; break;
    case 'S': case 's': newY += SPEED; player.dir = 2; break;
    case 'A': case 'a': newX -= SPEED; player.dir = 3; break;
    }

    if (newX < 0) newX = 0;
    if (newY < 0) newY = 0;
    if (newX > WIDTH - TANK_SIZE) newX = WIDTH - TANK_SIZE;
    if (newY > HEIGHT - TANK_SIZE) newY = HEIGHT - TANK_SIZE;

    if (canMove(newX, newY)) {
        player.x = newX;
        player.y = newY;
    }
}


void processInput()
{
    bool moved = false;

    // WASD�����ƶ�  
    if (GetAsyncKeyState('W') & 0x8000) { movePlayer('W'); moved = true; }
    if (GetAsyncKeyState('A') & 0x8000) { movePlayer('A'); moved = true; }
    if (GetAsyncKeyState('S') & 0x8000) { movePlayer('S'); moved = true; }
    if (GetAsyncKeyState('D') & 0x8000) { movePlayer('D'); moved = true; }
    // �ո���� (����һ�������ȴ����ֹ��ס�������)  
    static DWORD lastFireTime = 0;
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        DWORD now = GetTickCount();
        if (now - lastFireTime >= 180 && player.alive) { // 180������ȴ  
            firePlayerBullet();
            lastFireTime = now;
        }
    }
}
    void firePlayerBullet() {
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].active) {
                bullets[i].active = true;
                bullets[i].fromPlayer = true;
                bullets[i].x = player.x + TANK_SIZE / 2;
                bullets[i].y = player.y + TANK_SIZE / 2;
                switch (player.dir) {
                case 0: bullets[i].vx = 0; bullets[i].vy = -SPEED * 2; break;
                case 1: bullets[i].vx = SPEED * 2; bullets[i].vy = 0; break;
                case 2: bullets[i].vx = 0; bullets[i].vy = SPEED * 2; break;
                case 3: bullets[i].vx = -SPEED * 2; bullets[i].vy = 0; break;
                }
                break;
            }
        }
    }
#define BUTTON_COLOR     RGB(100, 150, 250)  // ��ť��ɫ  
#define BUTTON_HOVER     RGB(80, 120, 220)   // ��ť��ͣ��ɫ  
#define TEXT_COLOR       WHITE               // ��ť������ɫ  
#define BG_BAR_COLOR     RGB(30, 30, 50)     // ��ť���򱳾���ɫ  
    void handleMouseEvent() {
        const int buttonWidth = 300;
        const int buttonHeight = 60;
        const int centerX = 1210 / 2;
        const int startY = 400;
        const int spacing = 15;
        const int buttonX = centerX - buttonWidth / 2;

        while (true) {
            MOUSEMSG msg = GetMouseMsg();

            // ��ʼ��ť����ȷ������Ƿ��ڷ�Χ�ڣ�  
            if (msg.x >= buttonX && msg.x <= buttonX + buttonWidth &&
                msg.y >= startY && msg.y <= startY + buttonHeight) {

                // �����ͣЧ��  
                setfillcolor(BUTTON_HOVER);
                fillrectangle(buttonX, startY, buttonX + buttonWidth, startY + buttonHeight);
                outtextxy(buttonX + 90, startY + 15, "��ʼ��Ϸ");

                // �������ʼ��Ϸ��  
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    cleardevice();  // ����  
                    outtextxy(centerX - 100, 300, "��Ϸ������...");
                    Sleep(2000);  // ģ�����  
                    return;
                }
            }
            // ������ť����  
            else if (msg.x >= buttonX && msg.x <= buttonX + buttonWidth &&
                msg.y >= startY + buttonHeight + spacing &&
                msg.y <= startY + buttonHeight * 2 + spacing) {

                // �����ͣЧ��  
                setfillcolor(BUTTON_HOVER);
                fillrectangle(buttonX, startY + buttonHeight + spacing,
                    buttonX + buttonWidth, startY + buttonHeight * 2 + spacing);
                outtextxy(buttonX + 90, startY + buttonHeight + spacing + 15, "������Ϸ");

                // �����������Ϸ��  
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    closegraph();  // �ر�ͼ�δ���  
                    exit(0);       // �˳�����  
                }
            }
            else {
                // ��겻�ڰ�ť����ʱ�ָ���ɫ  
                setfillcolor(BUTTON_COLOR);
                fillrectangle(buttonX, startY, buttonX + buttonWidth, startY + buttonHeight);
                fillrectangle(buttonX, startY + buttonHeight + spacing,
                    buttonX + buttonWidth, startY + buttonHeight * 2 + spacing);
                outtextxy(buttonX + 90, startY + 15, "��ʼ��Ϸ");
                outtextxy(buttonX + 90, startY + buttonHeight + spacing + 15, "������Ϸ");
            }

            FlushBatchDraw();  // ˢ�»�ͼ  
            Sleep(10);         // ����CPUռ��  
        }
    }
    void imageshow(const char localtion[200])
    {
        IMAGE img_meinv;
        loadimage(&img_meinv, localtion);
        putimage(0, 0, &img_meinv);
    }
    void ShowImageAndRestart(const char* imagePath) {
        IMAGE img;
        loadimage(&img, imagePath);
        putimage(0, 0, &img);
        Sleep(2000); // ��ʾ2��  
        BeginBatchDraw();
        imageshow("source\\background3.png");
        EndBatchDraw();
    }
    void ShowImageAndRestart1(const char* imagePath) {
        IMAGE img;
        loadimage(&img, imagePath);
        putimage(0, 0, &img);
        Sleep(2000); // ��ʾ2��  
        BeginBatchDraw();
        imageshow("source\\background4.png");
        EndBatchDraw();
    }
    void RestartGame(int* ray_x, int* ray_y, int* dx, int* dy) {
        *ray_x = START_X + 30; // ��������λ��  
        *ray_y = START_Y - 25; // ��������λ��  
        *dx = 0;
        *dy = 0;
    }
    void RestartGame1(int* ray_x, int* ray_y, int* dx, int* dy) {
        *ray_x = 66; // ��������λ��  
        *ray_y = 188; // ��������λ��  
        *dx = 0;
        *dy = 0;
    }