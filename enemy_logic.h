#pragma once
#include "game_types.h"

// �������˽ڵ�
EnemyNode* createEnemy(int x, int y, int dir);

// ������˽ڵ㵽����β��
void insertEnemy(EnemyNode** head, EnemyNode* newNode);

// �ͷŵ��������ڴ�
void freeEnemyList(EnemyNode** head);

// �ƶ����е���
void moveEnemy();

// ���˿���
void enemyFireBullet(EnemyNode* enemy);

// ��鵱ǰ������״̬�������Ƿ������һ��
void checkWaveProgress();

// ������ײ���
bool isCollidingRect(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);

// �ж�ָ��λ���ܷ��ƶ�
bool canMove(int newX, int newY);

 // GAME_ENEMY_H