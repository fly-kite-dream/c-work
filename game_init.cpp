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

    // ��ʼ����������
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
        settextstyle(35, 0, _T("΢���ź�"));
        setbkmode(TRANSPARENT);
        char* gameStr = WideCharToMultiByteStr(L"��Ϸ���ڽ�����...");
        outtextxy(200, 200, gameStr);
        free(gameStr);
        Sleep(1000);
    }
}
bool loginInterface() {
    // ��ʼ������
    initgraph(1210, 615);

    // ���ر���ͼ
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
    settextstyle(28, 0, "΢���ź�");
    settextcolor(WHITE);

    outtextxy(1210 / 2 - textwidth("�û���¼ϵͳ") / 2, 100, "�û���¼ϵͳ");

    int labelX = 1210 / 2 - 200;
    outtextxy(labelX, 250, "�û���:");
    outtextxy(labelX, 350, "��  ��:");

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
                // ��һ��ʹ�ã�д���û���Ϣ
                FILE* wf = fopen("user.txt", "a");
                if (wf) {
                    fprintf(wf, "%s %s\n", username, password);
                    fclose(wf);
                    MessageBox(GetHWnd(), "�״��û���ע��ɹ�", "��ʾ", MB_OK);
                    return true;
                }
                else {
                    MessageBox(GetHWnd(), "�޷�д���û���Ϣ�ļ�", "����", MB_OK);
                }
            }
            else if (found) {
                return true;
            }
            else {
                MessageBox(GetHWnd(), "�û������������", "��¼ʧ��", MB_OK);
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
    static IMAGE lastFrame; // ��̬����������һ֡ͼ��  

    if (state->isAnimPlaying) {
        // ���ص�ǰ֡ͼ����ͼ�����  
        IMAGE currentFrame;
        loadimage(&currentFrame, frames[state->animFrame]);

        // ʹ��͸���Ȼ��Ч��������˸��ģ��֡��ƽ�����ɣ�  
        putimage(0, 0, &currentFrame);

        // ���浱ǰ֡�Ա��´�ʹ��  
        lastFrame = currentFrame;

        // ����Ҫ���������֡��ţ�������ѭ���д���  
    }
    else if (lastFrame.getwidth() > 0) {
        // ������ڲ��ŵ�����һ֡ͼ���������ʾ��һ֡  
        putimage(0, 0, &lastFrame);
    }
    else {
        // �״�����ʱû����һ֡�����ص�һ֡  
        loadimage(&lastFrame, frames[0]);
        putimage(0, 0, &lastFrame);
    }
}