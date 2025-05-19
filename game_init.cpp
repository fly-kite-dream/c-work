#define _CRT_SECURE_NO_WARNINGS  
#include "game_init.h"
#include <graphics.h>
#include "enemy_logic.h"
#include <time.h>
#include"game_types.h"
#include "num.h"
#include<stdio.h>
#include <conio.h>
void initGame() {
    initgraph(WIDTH, HEIGHT);
    setbkcolor(RGB(30, 30, 30));
    cleardevice();
    BeginBatchDraw();

    loadTankImages();

    player.x = 50;
    player.y = 50;
    player.dir = 0;
    player.health = 30;
    player.alive = true;

    // 初始化敌人链表
    for (int i = 0; i < currentWave; i++) {
        EnemyNode* newEnemy = createEnemy(400 + i * (TANK_SIZE + 20), 300, 2);
        insertEnemy(&enemyList, newEnemy);
    }

    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
    }

    wallCount = MAX_WALLS;
    walls[0] = { 150, 100, 20, 200 };
    walls[1] = { 300, 50, 20, 150 };
    walls[2] = { 300, 300, 20, 150 };
    walls[3] = { 100, 350, 100, 20 };
    walls[4] = { 500, 100, 20, 200 };
    walls[5] = { 450, 250, 100, 20 };
    walls[6] = { 50, 200, 100, 20 };

    srand((unsigned)time(NULL));
}

void loadTankImages() {
    loadimage(&tankImg[3][0], "m0-0-1.gif");
    loadimage(&tankImg[3][1], "m0-0-2.gif");
    loadimage(&tankImg[0][0], "m0-1-1.gif");
    loadimage(&tankImg[0][1], "m0-1-2.gif");
    loadimage(&tankImg[1][0], "m0-2-1.gif");
    loadimage(&tankImg[1][1], "m0-2-2.gif");
    loadimage(&tankImg[2][0], "m0-3-1.gif");
    loadimage(&tankImg[2][1], "m0-3-2.gif");
}

void initGameState(GameState* state) {
    state->heatProgress = 0;
    state->drillProgress = 0;
    state->isOverheat = false;
    state->lineHitTime = 0;
    state->currentLine = 0;
    state->accumulatedTime = 0;
    state->animFrame = 0;
    state->isAnimPlaying = false;
}
//void initGameState(GameState* state) {
//    state->heatProgress = 0;
//    state->drillProgress = 0;
//    state->isOverheat = FALSE;
//    state->lineHitTime = 0;
//    state->currentLine = 0;
//    state->accumulatedTime = 0;
//    state->animFrame = 0;
//    state->isAnimPlaying = FALSE;
//}
char* WideCharToMultiByteStr(const wchar_t* wstr) {
    int len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = (char*)malloc(len * sizeof(char));
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    return str;
}
void gameLoop() {
    while (1) {
        cleardevice();
        settextcolor(WHITE);
        settextstyle(35, 0, _T("微软雅黑"));
        setbkmode(TRANSPARENT);
        char* gameStr = WideCharToMultiByteStr(L"游戏正在进行中...");
        outtextxy(200, 200, gameStr);
        free(gameStr);
        Sleep(1000);
    }
}
bool loginInterface() {
    // 初始化窗口
    initgraph(1210, 615);

    // 加载背景图
    IMAGE background;
    try {
        loadimage(&background, "source\\start.png", 1210, 615);
        putimage(0, 0, &background);
    }
    catch (...) {
        setbkcolor(RGB(70, 130, 180));
        cleardevice();
    }

    setbkmode(TRANSPARENT);
    settextstyle(28, 0, "微软雅黑");
    settextcolor(WHITE);

    outtextxy(1210 / 2 - textwidth("用户登录系统") / 2, 100, "用户登录系统");

    int labelX = 1210 / 2 - 200;
    outtextxy(labelX, 250, "用户名:");
    outtextxy(labelX, 350, "密  码:");

    int inputX = 1210 / 2 - 100;
    int inputWidth = 300;
    setfillcolor(WHITE);
    fillrectangle(inputX, 245, inputX + inputWidth, 275);
    fillrectangle(inputX, 345, inputX + inputWidth, 375);

    char username[30] = { 0 };
    char password[30] = { 0 };
    int usernamePos = 0, passwordPos = 0;
    bool isTypingUsername = true;

    while (true) {
        setfillcolor(WHITE);
        fillrectangle(inputX, 245, inputX + inputWidth, 275);
        fillrectangle(inputX, 345, inputX + inputWidth, 375);

        settextcolor(BLACK);
        outtextxy(inputX + 5, 250, username);

        char hiddenPass[30] = { 0 };
        for (int i = 0; i < passwordPos; i++) hiddenPass[i] = '*';
        outtextxy(inputX + 5, 350, hiddenPass);

        setfillcolor(RGB(100, 200, 100));
        if (isTypingUsername)
            fillrectangle(inputX - 5, 240, inputX + inputWidth + 5, 245);
        else
            fillrectangle(inputX - 5, 340, inputX + inputWidth + 5, 345);

        FlushBatchDraw();

        char ch = _getch();
        if (ch == '\r') {
            FILE* fp = fopen("user.txt", "r");

            bool fileExists = false;
            bool fileEmpty = true;
            bool found = false;
            char fileUser[30], filePass[30];

            if (fp) {
                fileExists = true;
                while (fscanf(fp, "%s %s", fileUser, filePass) != EOF) {
                    fileEmpty = false;
                    if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
                        found = true;
                        break;
                    }
                }
                fclose(fp);
            }

            if (!fileExists || fileEmpty) {
                // 第一次使用，写入用户信息
                FILE* wf = fopen("user.txt", "a");
                if (wf) {
                    fprintf(wf, "%s %s\n", username, password);
                    fclose(wf);
                    MessageBox(GetHWnd(), "首次用户已注册成功", "提示", MB_OK);
                    return true;
                }
                else {
                    MessageBox(GetHWnd(), "无法写入用户信息文件", "错误", MB_OK);
                }
            }
            else if (found) {
                return true;
            }
            else {
                MessageBox(GetHWnd(), "用户名或密码错误", "登录失败", MB_OK);
                usernamePos = passwordPos = 0;
                memset(username, 0, sizeof(username));
                memset(password, 0, sizeof(password));
            }
        }
        else if (ch == '\b') {
            if (isTypingUsername && usernamePos > 0)
                username[--usernamePos] = '\0';
            else if (!isTypingUsername && passwordPos > 0)
                password[--passwordPos] = '\0';
        }
        else if (ch == '\t') {
            isTypingUsername = !isTypingUsername;
        }
        else if (ch == 27) {
            closegraph();
            return false;
        }
        else if (isprint(ch)) {
            if (isTypingUsername && usernamePos < 29) {
                username[usernamePos++] = ch;
                username[usernamePos] = '\0';
            }
            else if (!isTypingUsername && passwordPos < 29) {
                password[passwordPos++] = ch;
                password[passwordPos] = '\0';
            }
        }
    }
}
void playAnimation(GameState* state, const char* frames[], int frameCount) {
    static IMAGE lastFrame; // 静态变量保存上一帧图像  

    if (state->isAnimPlaying) {
        // 加载当前帧图像到新图像对象  
        IMAGE currentFrame;
        loadimage(&currentFrame, frames[state->animFrame]);

        // 使用透明度混合效果减少闪烁（模拟帧间平滑过渡）  
        putimage(0, 0, &currentFrame);

        // 保存当前帧以备下次使用  
        lastFrame = currentFrame;

        // 不需要在这里更新帧序号，已在主循环中处理  
    }
    else if (lastFrame.getwidth() > 0) {
        // 如果不在播放但有上一帧图像，则继续显示上一帧  
        putimage(0, 0, &lastFrame);
    }
    else {
        // 首次运行时没有上一帧，加载第一帧  
        loadimage(&lastFrame, frames[0]);
        putimage(0, 0, &lastFrame);
    }
}