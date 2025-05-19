#ifndef bullet_logic_h
#define bullet_logic_h

#include "game_types.h"

void updateBullets();
bool isCollidingRect(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);
void updateGameState(GameState* state);
BOOL isAtObstacle(int progress);
BOOL canBreakObstacle(GameState* state);
int updateProgressBar(int* isAtMaxFlag);
#endif // GAME_UPDATE_H