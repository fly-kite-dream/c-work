#pragma once
#include "game_types.h"
#include <graphics.h>

#define MAX_WALLS 20
#define MAX_BULLETS 50

extern int currentWave;
extern Tank player;
extern EnemyNode* enemyList;
extern Wall walls[MAX_WALLS];
extern int wallCount;
extern Bullet bullets[MAX_BULLETS];
extern IMAGE tankImg[4][2]; // 假设支持4方向2帧
extern int enemiesDefeated;
extern int animCount;
extern int enemiesDefeated;
//extern  int progress;         // 静态变量保持状态  
//extern  int isAtMaxProgress;  // 状态标记  
//extern const char* imageLocks;