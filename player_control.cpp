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

    // WASD控制移动  
    if (GetAsyncKeyState('W') & 0x8000) { movePlayer('W'); moved = true; }
    if (GetAsyncKeyState('A') & 0x8000) { movePlayer('A'); moved = true; }
    if (GetAsyncKeyState('S') & 0x8000) { movePlayer('S'); moved = true; }
    if (GetAsyncKeyState('D') & 0x8000) { movePlayer('D'); moved = true; }
    // 空格射击 (增加一个射击冷却，防止按住后发射过快)  
    static DWORD lastFireTime = 0;
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        DWORD now = GetTickCount();
        if (now - lastFireTime >= 180 && player.alive) { // 180毫秒冷却  
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
#define BUTTON_COLOR     RGB(100, 150, 250)  // 按钮颜色  
#define BUTTON_HOVER     RGB(80, 120, 220)   // 按钮悬停颜色  
#define TEXT_COLOR       WHITE               // 按钮文字颜色  
#define BG_BAR_COLOR     RGB(30, 30, 50)     // 按钮区域背景颜色  
    void handleMouseEvent() {
        const int buttonWidth = 300;
        const int buttonHeight = 60;
        const int centerX = 1210 / 2;
        const int startY = 400;
        const int spacing = 15;
        const int buttonX = centerX - buttonWidth / 2;

        while (true) {
            MOUSEMSG msg = GetMouseMsg();

            // 开始按钮区域（确认鼠标是否在范围内）  
            if (msg.x >= buttonX && msg.x <= buttonX + buttonWidth &&
                msg.y >= startY && msg.y <= startY + buttonHeight) {

                // 鼠标悬停效果  
                setfillcolor(BUTTON_HOVER);
                fillrectangle(buttonX, startY, buttonX + buttonWidth, startY + buttonHeight);
                outtextxy(buttonX + 90, startY + 15, "开始游戏");

                // 点击“开始游戏”  
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    cleardevice();  // 清屏  
                    outtextxy(centerX - 100, 300, "游戏加载中...");
                    Sleep(2000);  // 模拟加载  
                    return;
                }
            }
            // 结束按钮区域  
            else if (msg.x >= buttonX && msg.x <= buttonX + buttonWidth &&
                msg.y >= startY + buttonHeight + spacing &&
                msg.y <= startY + buttonHeight * 2 + spacing) {

                // 鼠标悬停效果  
                setfillcolor(BUTTON_HOVER);
                fillrectangle(buttonX, startY + buttonHeight + spacing,
                    buttonX + buttonWidth, startY + buttonHeight * 2 + spacing);
                outtextxy(buttonX + 90, startY + buttonHeight + spacing + 15, "结束游戏");

                // 点击“结束游戏”  
                if (msg.uMsg == WM_LBUTTONDOWN) {
                    closegraph();  // 关闭图形窗口  
                    exit(0);       // 退出程序  
                }
            }
            else {
                // 鼠标不在按钮区域时恢复颜色  
                setfillcolor(BUTTON_COLOR);
                fillrectangle(buttonX, startY, buttonX + buttonWidth, startY + buttonHeight);
                fillrectangle(buttonX, startY + buttonHeight + spacing,
                    buttonX + buttonWidth, startY + buttonHeight * 2 + spacing);
                outtextxy(buttonX + 90, startY + 15, "开始游戏");
                outtextxy(buttonX + 90, startY + buttonHeight + spacing + 15, "结束游戏");
            }

            FlushBatchDraw();  // 刷新绘图  
            Sleep(10);         // 减少CPU占用  
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
        Sleep(2000); // 显示2秒  
        BeginBatchDraw();
        imageshow("source\\background3.png");
        EndBatchDraw();
    }
    void ShowImageAndRestart1(const char* imagePath) {
        IMAGE img;
        loadimage(&img, imagePath);
        putimage(0, 0, &img);
        Sleep(2000); // 显示2秒  
        BeginBatchDraw();
        imageshow("source\\background4.png");
        EndBatchDraw();
    }
    void RestartGame(int* ray_x, int* ray_y, int* dx, int* dy) {
        *ray_x = START_X + 30; // 重置射线位置  
        *ray_y = START_Y - 25; // 重置射线位置  
        *dx = 0;
        *dy = 0;
    }
    void RestartGame1(int* ray_x, int* ray_y, int* dx, int* dy) {
        *ray_x = 66; // 重置射线位置  
        *ray_y = 188; // 重置射线位置  
        *dx = 0;
        *dy = 0;
    }