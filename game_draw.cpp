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
    // 绘制背景  
    setfillcolor(RGB(50, 50, 50));
    fillrectangle(area.left - 5, area.top - 10, area.right + 5, area.bottom + 10);

    setfillcolor(RGB(100, 100, 100));
    fillrectangle(area.left, area.top, area.right, area.bottom);

    // 计算填充高度  
    int fillHeight = (int)((float)progress / MAX_PROGRESS * BAR_HEIGHT);
    setfillcolor(color);
    fillrectangle(area.left, area.bottom - fillHeight, area.right, area.bottom);

    // 绘制横线刻度 - 添加25%,50%,75%三条刻度线  
    setlinecolor(RGB(255, 255, 255)); // 使用白色线条  
    setlinestyle(PS_SOLID, 2); // 设置线条样式和宽度  

    // 绘制25%横线  
    int lineY25 = area.bottom - (int)((float)25 / 100 * BAR_HEIGHT);
    line(area.left, lineY25, area.right, lineY25);

    // 绘制50%横线  
    int lineY50 = area.bottom - (int)((float)50 / 100 * BAR_HEIGHT);
    line(area.left, lineY50, area.right, lineY50);

    // 绘制75%横线  
    int lineY75 = area.bottom - (int)((float)75 / 100 * BAR_HEIGHT);
    line(area.left, lineY75, area.right, lineY75);

    // 在线条旁边显示百分比标记  
    settextcolor(RGB(255, 255, 255));
    settextstyle(18, 0, _T("微软雅黑"));
    setbkmode(TRANSPARENT);

    TCHAR text[10];
    _stprintf(text, _T("25%%"));
    outtextxy(area.right + 5, lineY25 - 9, text);

    _stprintf(text, _T("50%%"));
    outtextxy(area.right + 5, lineY50 - 9, text);

    _stprintf(text, _T("75%%"));
    outtextxy(area.right + 5, lineY75 - 9, text);

    // 恢复线型  
    setlinestyle(PS_SOLID, 1);
}
void drawGameUI(GameState* state) {
    // 绘制进度条  
    drawModernBar(state->heatProgress, heatBarRect, RGB(255, 80, 80));
    drawModernBar(state->drillProgress, drillBarRect, RGB(80, 200, 80));

    // 绘制标签  
    settextcolor(WHITE);
    settextstyle(25, 0, _T("微软雅黑"));
    setbkmode(TRANSPARENT);

    outtextxy(heatBarRect.left - 10, heatBarRect.top - 40, _T("HEAT"));
    outtextxy(drillBarRect.left - 10, drillBarRect.top - 40, _T("DRILL"));

    // 绘制过热警告  
    if (state->isOverheat) {
        settextcolor(RGB(255, 0, 0));
        settextstyle(30, 0, _T("微软雅黑"));
        outtextxy(WIDTH / 2 - 100, 50, _T("OVERHEAT! COOLING..."));
    }

    // 如果正在尝试突破障碍，显示提示  
    if (isAtObstacle(state->drillProgress) && !state->isOverheat) {
        settextcolor(RGB(255, 255, 0));
        settextstyle(30, 0, _T("微软雅黑"));

        // 计算剩余需要累计的时间  
        DWORD remainTime = (state->accumulatedTime >= 5000) ? 0 : (5000 - state->accumulatedTime);
        int remainSec = remainTime / 1000 + (remainTime % 1000 ? 1 : 0); // 向上取整为秒  

        TCHAR breakText[50];
        _stprintf(breakText, _T("突破障碍... 累计钻孔 (%d/%d 秒)"), state->accumulatedTime / 1000, 5);
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
    sprintf_s(progressText, "进度: %d%%", progress);
    outtextxy(803, 157, progressText);
}
#define BUTTON_COLOR     RGB(100, 150, 250)  // 按钮颜色  
#define BUTTON_HOVER     RGB(80, 120, 220)   // 按钮悬停颜色  
#define TEXT_COLOR       WHITE               // 按钮文字颜色  
#define BG_BAR_COLOR     RGB(30, 30, 50)     // 按钮区域背景颜色  

void drawStartInterface() {
    IMAGE background;
    loadimage(&background, "source\\start.png", 1210, 615);  // 加载背景图片  

    // 绘制背景  
    putimage(0, 0, &background);

    // 设置按钮参数  
    const int buttonWidth = 300;   // 按钮宽度  
    const int buttonHeight = 60;  // 按钮高度  
    const int centerX = 1210 / 2; // 画布中心X坐标  
    const int startY = 400;       // 按钮顶部起始位置  
    const int spacing = 15;       // 按钮之间的间距  

    // 按钮左上角X坐标  
    const int buttonX = centerX - buttonWidth / 2;

    // 按钮区域背景条  
    setfillcolor(BG_BAR_COLOR);
    fillrectangle(0, startY - 20, 1210, startY + buttonHeight * 2 + spacing + 20);

    // 绘制第一个按钮（开始游戏）  
    setfillcolor(BUTTON_COLOR);
    fillrectangle(buttonX, startY, buttonX + buttonWidth, startY + buttonHeight);

    // 绘制第二个按钮（结束游戏）  
    fillrectangle(buttonX, startY + buttonHeight + spacing,
        buttonX + buttonWidth, startY + buttonHeight * 2 + spacing);

    // 绘制按钮文字  
    settextstyle(30, 0, "楷体");
    setbkmode(TRANSPARENT);
    settextcolor(TEXT_COLOR);
    outtextxy(buttonX + 90, startY + 15, "开始游戏");
    outtextxy(buttonX + 90, startY + buttonHeight + spacing + 15, "结束游戏");
}