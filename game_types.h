#pragma once
#include <graphics.h>

#define TANK_SIZE 40
#define BULLET_SIZE 6
#define SPEED 5
#define MAX_BULLETS 20
#define MAX_WALLS 7
#define MAX_WAVES 3
#define WIDTH 980
#define HEIGHT 615
#define BAR_HEIGHT 400
#define BAR_WIDTH 30
#define MAX_PROGRESS 100
#define START_X 50  
#define START_Y 550  
#define END_X 750  
#define END_Y 50  
#define RAY_SIZE 10  
#define BAR_HEIGHT 400  
#define BAR_WIDTH 30  
#define MOVE_UP_RATE 2 
#define MOVE_DOWN_RATE 1.5 
#define MAX_PROGRESS 100  
#define WIDTH 980  
#define HEIGHT 615 
const RECT heatBarRect = { 50,  150, 50 + BAR_WIDTH,  150 + BAR_HEIGHT };
const RECT drillBarRect = { WIDTH - 85, 150, WIDTH - 85 + BAR_WIDTH, 150 + BAR_HEIGHT };
const POINT animCenter = { WIDTH / 2 - 100, HEIGHT / 2 - 80 };

typedef struct {
    int x, y;
    int dir;
    int health;
    bool alive;
} Tank;

typedef struct {
    double x, y;
    double vx, vy;
    bool active;
    bool fromPlayer;
} Bullet;

typedef struct {
    int x, y;
    int w, h;
} Wall;

typedef struct EnemyNode {
    Tank tank;
    struct EnemyNode* next;
} EnemyNode;


//Tank player;
//EnemyNode* enemyList = NULL;  // 使用链表管理敌人
//int currentWave = 1;

//Bullet bullets[MAX_BULLETS];

//Wall walls[MAX_WALLS];
//int wallCount = 0;

//IMAGE tankImg[4][2];
//static int animCount = 0;
struct GameState {
    int heatProgress;          // 热度进度  
    int drillProgress;         // 钻孔进度  
    BOOL isOverheat;           // 是否过热  
    DWORD lineHitTime;         // 碰到障碍线的时间  
    int currentLine;           // 当前所在的障碍线位置  
    DWORD accumulatedTime;     // 在当前障碍点的累计钻孔时间  
    int animFrame;             // 动画当前帧  
    BOOL isAnimPlaying;        // 动画播放状态  
};
