#pragma once
#include "game_types.h"

// 创建敌人节点
EnemyNode* createEnemy(int x, int y, int dir);

// 插入敌人节点到链表尾部
void insertEnemy(EnemyNode** head, EnemyNode* newNode);

// 释放敌人链表内存
void freeEnemyList(EnemyNode** head);

// 移动所有敌人
void moveEnemy();

// 敌人开火
void enemyFireBullet(EnemyNode* enemy);

// 检查当前波敌人状态，决定是否进入下一波
void checkWaveProgress();

// 矩形碰撞检测
bool isCollidingRect(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);

// 判断指定位置能否移动
bool canMove(int newX, int newY);

 // GAME_ENEMY_H