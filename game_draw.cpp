#define _CRT_SECURE_NO_WARNINGS 
#include "game_draw.h"
#include <graphics.h>
#include <stdio.h>  
#include "enemy_logic.h"
#include "player_control.h"
#include "bullet_logic.h"
#include "game_init.h"
#include "game_draw.h"
#include "cutscene.h"
#include"game_types.h"
#include "num.h"
void drawWalls() {
    setfillcolor(BROWN);
    for (int i = 0; i < wallCount; i++) {
        fillrectangle(walls[i].x, walls[i].y,
            walls[i].x + walls[i].w,
            walls[i].y + walls[i].h);
    }
}
void drawTank(const Tank* t) {
    if (!t->alive) return;

    settextcolor(WHITE);
    char hp[8];
    sprintf(hp, "%d", t->health);
    outtextxy(t->x + TANK_SIZE / 2 - 5, t->y - 15, hp);

    int index = (animCount / 10) % 2;
    putimage(t->x, t->y, &tankImg[t->dir][index]);
}

void drawBullet(const Bullet* b) {
    if (!b->active) return;
    setfillcolor(b->fromPlayer ? YELLOW : CYAN);
    fillcircle((int)b->x, (int)b->y, BULLET_SIZE);
}

void drawModernBar(int progress, RECT area, COLORREF color) {
    // ���Ʊ���  
    setfillcolor(RGB(50, 50, 50));
    fillrectangle(area.left - 5, area.top - 10, area.right + 5, area.bottom + 10);

    setfillcolor(RGB(100, 100, 100));
    fillrectangle(area.left, area.top, area.right, area.bottom);

    // �������߶�  
    int fillHeight = (int)((float)progress / MAX_PROGRESS * BAR_HEIGHT);
    setfillcolor(color);
    fillrectangle(area.left, area.bottom - fillHeight, area.right, area.bottom);

    // ���ƺ��߿̶� - ���25%,50%,75%�����̶���  
    setlinecolor(RGB(255, 255, 255)); // ʹ�ð�ɫ����  
    setlinestyle(PS_SOLID, 2); // ����������ʽ�Ϳ��  

    // ����25%����  
    int lineY25 = area.bottom - (int)((float)25 / 100 * BAR_HEIGHT);
    line(area.left, lineY25, area.right, lineY25);

    // ����50%����  
    int lineY50 = area.bottom - (int)((float)50 / 100 * BAR_HEIGHT);
    line(area.left, lineY50, area.right, lineY50);

    // ����75%����  
    int lineY75 = area.bottom - (int)((float)75 / 100 * BAR_HEIGHT);
    line(area.left, lineY75, area.right, lineY75);

    // �������Ա���ʾ�ٷֱȱ��  
    settextcolor(RGB(255, 255, 255));
    settextstyle(18, 0, _T("΢���ź�"));
    setbkmode(TRANSPARENT);

    TCHAR text[10];
    _stprintf(text, _T("25%%"));
    outtextxy(area.right + 5, lineY25 - 9, text);

    _stprintf(text, _T("50%%"));
    outtextxy(area.right + 5, lineY50 - 9, text);

    _stprintf(text, _T("75%%"));
    outtextxy(area.right + 5, lineY75 - 9, text);

    // �ָ�����  
    setlinestyle(PS_SOLID, 1);
}
void drawGameUI(GameState* state) {
    // ���ƽ�����  
    drawModernBar(state->heatProgress, heatBarRect, RGB(255, 80, 80));
    drawModernBar(state->drillProgress, drillBarRect, RGB(80, 200, 80));

    // ���Ʊ�ǩ  
    settextcolor(WHITE);
    settextstyle(25, 0, _T("΢���ź�"));
    setbkmode(TRANSPARENT);

    outtextxy(heatBarRect.left - 10, heatBarRect.top - 40, _T("HEAT"));
    outtextxy(drillBarRect.left - 10, drillBarRect.top - 40, _T("DRILL"));

    // ���ƹ��Ⱦ���  
    if (state->isOverheat) {
        settextcolor(RGB(255, 0, 0));
        settextstyle(30, 0, _T("΢���ź�"));
        outtextxy(WIDTH / 2 - 100, 50, _T("OVERHEAT! COOLING..."));
    }

    // ������ڳ���ͻ���ϰ�����ʾ��ʾ  
    if (isAtObstacle(state->drillProgress) && !state->isOverheat) {
        settextcolor(RGB(255, 255, 0));
        settextstyle(30, 0, _T("΢���ź�"));

        // ����ʣ����Ҫ�ۼƵ�ʱ��  
        DWORD remainTime = (state->accumulatedTime >= 5000) ? 0 : (5000 - state->accumulatedTime);
        int remainSec = remainTime / 1000 + (remainTime % 1000 ? 1 : 0); // ����ȡ��Ϊ��  

        TCHAR breakText[50];
        _stprintf(breakText, _T("ͻ���ϰ�... �ۼ���� (%d/%d ��)"), state->accumulatedTime / 1000, 5);
        outtextxy(WIDTH / 2 - 180, 100, breakText);
    }
}
void drawProgressBar(int progress) {
    setfillcolor(WHITE);
    fillrectangle(783, 197, 783 + BAR_WIDTH, 197 + BAR_HEIGHT);

    setfillcolor(GREEN);
    int fillHeight = progress * (BAR_HEIGHT / MAX_PROGRESS);
    fillrectangle(783, 197 + BAR_HEIGHT - fillHeight,
        783 + BAR_WIDTH, 197 + BAR_HEIGHT);

    char progressText[50];
    sprintf_s(progressText, "����: %d%%", progress);
    outtextxy(803, 157, progressText);
}
#define BUTTON_COLOR     RGB(100, 150, 250)  // ��ť��ɫ  
#define BUTTON_HOVER     RGB(80, 120, 220)   // ��ť��ͣ��ɫ  
#define TEXT_COLOR       WHITE               // ��ť������ɫ  
#define BG_BAR_COLOR     RGB(30, 30, 50)     // ��ť���򱳾���ɫ  

void drawStartInterface() {
    IMAGE background;
    loadimage(&background, "source\\start.png", 1210, 615);  // ���ر���ͼƬ  

    // ���Ʊ���  
    putimage(0, 0, &background);

    // ���ð�ť����  
    const int buttonWidth = 300;   // ��ť���  
    const int buttonHeight = 60;  // ��ť�߶�  
    const int centerX = 1210 / 2; // ��������X����  
    const int startY = 400;       // ��ť������ʼλ��  
    const int spacing = 15;       // ��ť֮��ļ��  

    // ��ť���Ͻ�X����  
    const int buttonX = centerX - buttonWidth / 2;

    // ��ť���򱳾���  
    setfillcolor(BG_BAR_COLOR);
    fillrectangle(0, startY - 20, 1210, startY + buttonHeight * 2 + spacing + 20);

    // ���Ƶ�һ����ť����ʼ��Ϸ��  
    setfillcolor(BUTTON_COLOR);
    fillrectangle(buttonX, startY, buttonX + buttonWidth, startY + buttonHeight);

    // ���Ƶڶ�����ť��������Ϸ��  
    fillrectangle(buttonX, startY + buttonHeight + spacing,
        buttonX + buttonWidth, startY + buttonHeight * 2 + spacing);

    // ���ư�ť����  
    settextstyle(30, 0, "����");
    setbkmode(TRANSPARENT);
    settextcolor(TEXT_COLOR);
    outtextxy(buttonX + 90, startY + 15, "��ʼ��Ϸ");
    outtextxy(buttonX + 90, startY + buttonHeight + spacing + 15, "������Ϸ");
}