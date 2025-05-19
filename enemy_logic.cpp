#include "enemy_logic.h"
//#include "game_globals.h"   // 引入全局变量声明
#include <stdlib.h>
#include <math.h>
#include "num.h"
EnemyNode* createEnemy(int x, int y, int dir) {
    EnemyNode* newNode = (EnemyNode*)malloc(sizeof(EnemyNode));
    newNode->tank.x = x;
    newNode->tank.y = y;
    newNode->tank.dir = dir;
    newNode->tank.health = 3;
    newNode->tank.alive = true;
    newNode->next = NULL;
    return newNode;
}

bool canMove(int newX, int newY) {
    for (int i = 0; i < wallCount; i++) {
        if (isCollidingRect(newX, newY, TANK_SIZE, TANK_SIZE,
            walls[i].x, walls[i].y, walls[i].w, walls[i].h))
            return false;
    }
    return true;
}

void insertEnemy(EnemyNode** head, EnemyNode* newNode) {
    newNode->next = *head;
    *head = newNode;
}

void freeEnemyList(EnemyNode** head) {
    while (*head) {
        EnemyNode* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void moveEnemy() {
    EnemyNode* current = enemyList;
    while (current != NULL) {
        if (!current->tank.alive) {
            current = current->next;
            continue;
        }

        if (rand() % 50 == 0)
            current->tank.dir = rand() % 4;

        int newX = current->tank.x;
        int newY = current->tank.y;
        int enemySpeed = SPEED / 2 + (currentWave - 1);
        switch (current->tank.dir) {
        case 0: newY -= enemySpeed; break;
        case 1: newX += enemySpeed; break;
        case 2: newY += enemySpeed; break;
        case 3: newX -= enemySpeed; break;
        }

        if (newX < 0) newX = 0;
        if (newY < 0) newY = 0;
        if (newX > WIDTH - TANK_SIZE) newX = WIDTH - TANK_SIZE;
        if (newY > HEIGHT - TANK_SIZE) newY = HEIGHT - TANK_SIZE;

        if (canMove(newX, newY)) {
            current->tank.x = newX;
            current->tank.y = newY;
        }

        enemyFireBullet(current);
        current = current->next;
    }
}

void enemyFireBullet(EnemyNode* enemy) {
    if (rand() % 100 < 5) {
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].active) {
                bullets[i].active = true;
                bullets[i].fromPlayer = false;
                bullets[i].x = enemy->tank.x + TANK_SIZE / 2;
                bullets[i].y = enemy->tank.y + TANK_SIZE / 2;
                double dx = player.x + TANK_SIZE / 2 - bullets[i].x;
                double dy = player.y + TANK_SIZE / 2 - bullets[i].y;
                double len = sqrt(dx * dx + dy * dy);
                if (len == 0) len = 1;
                bullets[i].vx = (dx / len) * SPEED * 2;
                bullets[i].vy = (dy / len) * SPEED * 2;
                break;
            }
        }
    }
}

void checkWaveProgress() {
    bool allDefeated = true;
    EnemyNode* current = enemyList;
    while (current != NULL) {
        if (current->tank.alive) {
            allDefeated = false;
            break;
        }
        current = current->next;
    }

    if (allDefeated) {
        freeEnemyList(&enemyList);
        currentWave++;
        if (currentWave > MAX_WAVES) {
            currentWave = 1;
            player.health = 3;
            player.alive = true;
        }
        for (int i = 0; i < currentWave; i++) {
            EnemyNode* newEnemy = createEnemy(400 + i * (TANK_SIZE + 20), 300, 2);
            insertEnemy(&enemyList, newEnemy);
        }
    }
}