#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "game_types.h"

// ��ʼ����Ϸ���ڼ������Դ
void initGame();

// ����̹��ͼƬ��Դ
void loadTankImages();

// ��ʼ����Ϸ״̬
void initGameState(GameState* state);
void gameLoop();
bool loginInterface();
char* WideCharToMultiByteStr(const wchar_t* wstr);
#endif // GAME_INIT_H