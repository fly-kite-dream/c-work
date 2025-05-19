#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_types.h"

// ���ݰ����ƶ����̹��
void movePlayer(char key);

// ����������루������⣩
void processInput();

// ���̹�˿���
void firePlayerBullet();
void handleMouseEvent();
void RestartGame1(int* ray_x, int* ray_y, int* dx, int* dy);
void RestartGame(int* ray_x, int* ray_y, int* dx, int* dy);
void ShowImageAndRestart1(const char* imagePath);
void ShowImageAndRestart(const char* imagePath);
void imageshow(const char localtion[200]);

#endif // GAME_PLAYER_H