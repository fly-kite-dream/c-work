#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_types.h"

// 根据按键移动玩家坦克
void movePlayer(char key);

// 处理玩家输入（按键监测）
void processInput();

// 玩家坦克开火
void firePlayerBullet();
void handleMouseEvent();
void RestartGame1(int* ray_x, int* ray_y, int* dx, int* dy);
void RestartGame(int* ray_x, int* ray_y, int* dx, int* dy);
void ShowImageAndRestart1(const char* imagePath);
void ShowImageAndRestart(const char* imagePath);
void imageshow(const char localtion[200]);

#endif // GAME_PLAYER_H