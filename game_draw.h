
#pragma once
#include "game_types.h"

// 绘制障碍物
void drawWalls();

// 绘制坦克
void drawTank(const Tank* t);

// 绘制子弹
void drawBullet(const Bullet* b);

// 绘制进度条（现代样式）
void drawModernBar(int progress, RECT area, COLORREF color);
void drawStartInterface();


// 绘制游戏界面UI
void drawGameUI(GameState* state);
void drawProgressBar(int progress);
// GAME_DRAW_H