#define _CRT_SECURE_NO_WARNINGS  
#include "bullet_logic.h"
#include "game_types.h"
//#include "game_globals.h"     // 引入全局变量声明

#include <windows.h>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "num.h"
BOOL isAtObstacle(int progress) {
    return (progress == 25) || (progress == 50) || (progress == 75);
}

BOOL canBreakObstacle(GameState* state) {
    return (state->accumulatedTime >= 5000);
}

//int enemiesDefeated = 0;

void updateBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;

        bullets[i].x += bullets[i].vx;
        bullets[i].y += bullets[i].vy;

        if (bullets[i].x < 0 || bullets[i].x > WIDTH ||
            bullets[i].y < 0 || bullets[i].y > HEIGHT) {
            bullets[i].active = false;
            continue;
        }

        for (int j = 0; j < wallCount; j++) {
            if (isCollidingRect((int)bullets[i].x - BULLET_SIZE,
                (int)bullets[i].y - BULLET_SIZE,
                BULLET_SIZE * 2, BULLET_SIZE * 2,
                walls[j].x, walls[j].y, walls[j].w, walls[j].h))
            {
                bullets[i].active = false;
                break;
            }
        }

        if (bullets[i].active && bullets[i].fromPlayer) {
            EnemyNode* current = enemyList;
            while (current != NULL) {
                if (current->tank.alive &&
                    isCollidingRect((int)bullets[i].x - BULLET_SIZE,
                        (int)bullets[i].y - BULLET_SIZE,
                        BULLET_SIZE * 2, BULLET_SIZE * 2,
                        current->tank.x, current->tank.y,
                        TANK_SIZE, TANK_SIZE))
                {
                    current->tank.health--;
                    if (current->tank.health <= 0) {
                        enemiesDefeated++;
                        current->tank.alive = false;
                    }
                    bullets[i].active = false;
                    break;
                }
                current = current->next;
            }
        }
        else if (bullets[i].active && !bullets[i].fromPlayer) {
            if (player.alive &&
                isCollidingRect((int)bullets[i].x - BULLET_SIZE,
                    (int)bullets[i].y - BULLET_SIZE,
                    BULLET_SIZE * 2, BULLET_SIZE * 2,
                    player.x, player.y,
                    TANK_SIZE, TANK_SIZE))
            {
                player.health--;
                if (player.health <= 0) {
                    player.alive = false;
                }
                bullets[i].active = false;
            }
        }
    }
}

bool isCollidingRect(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
    return (ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by);
}

void updateGameState(GameState* state) {
    BOOL isKeyDown = (GetAsyncKeyState('W') & 0x8000) != 0;
    DWORD currentTime = GetTickCount();
    static DWORD lastUpdateTime = currentTime;
    DWORD deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    if (state->isOverheat) {
        state->heatProgress = max(state->heatProgress - MOVE_DOWN_RATE * 2, 0);
        if (state->heatProgress == 0) {
            state->isOverheat = FALSE;
        }
        state->isAnimPlaying = FALSE;
        return;
    }

    if (isKeyDown) {
        state->heatProgress = min(state->heatProgress + MOVE_UP_RATE, MAX_PROGRESS);
        if (state->heatProgress >= MAX_PROGRESS) {
            state->isOverheat = TRUE;
            return;
        }

        if (!state->isAnimPlaying) {
            state->isAnimPlaying = TRUE;
            state->animFrame = 0;
        }

        if (isAtObstacle(state->drillProgress)) {
            if (state->currentLine != state->drillProgress) {
                state->currentLine = state->drillProgress;
                state->accumulatedTime = 0;
            }
            state->accumulatedTime += deltaTime;

            if (canBreakObstacle(state)) {
                state->drillProgress++;
                state->accumulatedTime = 0;
            }
        }
        else {
            state->drillProgress = min(state->drillProgress + 1, MAX_PROGRESS);
            if (isAtObstacle(state->drillProgress)) {
                state->currentLine = state->drillProgress;
                state->accumulatedTime = 0;
            }
        }
    }
    else {
        state->heatProgress = max(state->heatProgress - MOVE_DOWN_RATE, 0);
        state->isAnimPlaying = FALSE;
    }
}

int updateProgressBar(int* isAtMaxFlag) {
    static int progress = 0;         // 静态变量保持状态  
    static int isAtMaxProgress = 0;  // 状态标记  

    // 处理上升逻辑  
    if (GetAsyncKeyState('W') & 0x8000) {
        if (!isAtMaxProgress && progress < MAX_PROGRESS) {
            progress += MOVE_UP_RATE;
            if (progress >= MAX_PROGRESS) {
                progress = MAX_PROGRESS;
                isAtMaxProgress = 1; // 进入强制回落阶段  
            }
        }
    }

    // 处理回落逻辑  
    if (isAtMaxProgress) {
        progress -= MOVE_DOWN_RATE;
        if (progress <= 0) {
            progress = 0;
            isAtMaxProgress = 0; // 重置状态  
        }
    }
    else if (progress > 0) {
        progress -= MOVE_DOWN_RATE;
        if (progress < 0) progress = 0;
    }
    *isAtMaxFlag = isAtMaxProgress;
    return progress;
}