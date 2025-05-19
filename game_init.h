#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "game_types.h"

// 初始化游戏窗口及相关资源
void initGame();

// 加载坦克图片资源
void loadTankImages();

// 初始化游戏状态
void initGameState(GameState* state);
void gameLoop();
bool loginInterface();
char* WideCharToMultiByteStr(const wchar_t* wstr);
#endif // GAME_INIT_H