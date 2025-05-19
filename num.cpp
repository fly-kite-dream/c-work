#include "num.h"

// 定义变量，且初始化
//int currentWave = 1;
//Tank player = { 0 };
//EnemyNode* enemyList = nullptr;
//int wallCount = 0;
//Bullet* bullets = nullptr;
//IMAGE(*tankImg)[2] = nullptr;  // 根据实际如何初始化调整



int currentWave = 1;
Tank player = { 0 };
EnemyNode* enemyList = nullptr;
Wall walls[MAX_WALLS] = { 0 };
int wallCount = 0;
Bullet bullets[MAX_BULLETS] = { 0 };
IMAGE tankImg[4][2];
//int enemiesDefeated = 0;
int animCount = 0;
int enemiesDefeated = 0;
//static int progress = 0;         // 静态变量保持状态  
//static int isAtMaxProgress = 0;  // 状态标记  
//const char* imageLocks[60] = {
//    "source\\lock\\dock00.jpg",
//    "source\\lock\\dock01.jpg",
//    "source\\lock\\dock02.jpg",
//    "source\\lock\\dock03.jpg",
//    "source\\lock\\dock04.jpg",
//    "source\\lock\\dock05.jpg",
//    "source\\lock\\dock06.jpg",
//    "source\\lock\\dock07.jpg",
//    "source\\lock\\dock08.jpg",
//    "source\\lock\\dock09.jpg",
//    "source\\lock\\dock10.jpg",
//    "source\\lock\\dock11.jpg",
//    "source\\lock\\dock12.jpg",
//    "source\\lock\\dock13.jpg",
//    "source\\lock\\dock14.jpg",
//    "source\\lock\\dock15.jpg",
//    "source\\lock\\dock16.jpg",
//    "source\\lock\\dock17.jpg",
//    "source\\lock\\dock18.jpg",
//    "source\\lock\\dock19.jpg",
//    "source\\lock\\dock20.jpg",
//    "source\\lock\\dock21.jpg",
//    "source\\lock\\dock22.jpg",
//    "source\\lock\\dock23.jpg",
//    "source\\lock\\dock24.jpg",
//    "source\\lock\\dock25.jpg",
//    "source\\lock\\dock26.jpg",
//    "source\\lock\\dock27.jpg",
//    "source\\lock\\dock28.jpg",
//    "source\\lock\\dock29.jpg",
//    "source\\lock\\dock30.jpg",
//    "source\\lock\\dock31.jpg",
//    "source\\lock\\dock32.jpg",
//    "source\\lock\\dock33.jpg",
//    "source\\lock\\dock34.jpg",
//    "source\\lock\\dock35.jpg",
//    "source\\lock\\dock36.jpg",
//    "source\\lock\\dock37.jpg",
//    "source\\lock\\dock38.jpg",
//    "source\\lock\\dock39.jpg",
//    "source\\lock\\dock40.jpg",
//    "source\\lock\\dock41.jpg",
//    "source\\lock\\dock42.jpg",
//    "source\\lock\\dock43.jpg",
//    "source\\lock\\dock44.jpg",
//    "source\\lock\\dock45.jpg",
//    "source\\lock\\dock46.jpg",
//    "source\\lock\\dock47.jpg",
//    "source\\lock\\dock48.jpg",
//    "source\\lock\\dock49.jpg",
//    "source\\lock\\dock50.jpg",
//    "source\\lock\\dock51.jpg",
//    "source\\lock\\dock52.jpg",
//    "source\\lock\\dock53.jpg",
//    "source\\lock\\dock54.jpg",
//    "source\\lock\\dock55.jpg",
//    "source\\lock\\dock56.jpg",
//    "source\\lock\\dock57.jpg",
//    "source\\lock\\dock58.jpg",
//    "source\\lock\\dock59.jpg"
//};