
#pragma once
#include "game_types.h"

// �����ϰ���
void drawWalls();

// ����̹��
void drawTank(const Tank* t);

// �����ӵ�
void drawBullet(const Bullet* b);

// ���ƽ��������ִ���ʽ��
void drawModernBar(int progress, RECT area, COLORREF color);
void drawStartInterface();


// ������Ϸ����UI
void drawGameUI(GameState* state);
void drawProgressBar(int progress);
// GAME_DRAW_H