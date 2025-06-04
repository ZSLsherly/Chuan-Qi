#ifndef _FUN_H
#define _FUN_H

//公用头文件的声明 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <easyx.h>
#include <conio.h>
#include <iostream>

// 岛屿兵种上限 ，默认：3 
#define LIMIT 3
// 调试开关：0-关，1-开
#define TEST 0

// 交互语输出位置
#define tx 20
#define ty 290


// 按钮结构体
typedef struct button {
    int x;
    int y;
    int w;
    int h;
}Button;

//玩家结构体
typedef struct PeopleAttribute {	// 玩家直属数据
    int accumulateNum; 				// 屯的次数
    int bombNum;      				// 核弹数
    int houseNum;   	  			// 房子数
} PeopleAttribute;

/******************岛和桥*********************/
typedef struct IslandPosition { // 岛上单个位置属性
    int HP;                    // 存放这个岛上的兵的血量
    int veri;                  // 判断这个位置是什么兵：小，胖，球，法，轻，房
} IslandPosition;

typedef struct IslandAll {       // 岛的属性
    IslandPosition main[10];     // 3个主要位置
    int limit;                   // 判断岛上最多放兵数量
    int num;                     // 判断岛上已有几人
    int owner;                   // 判断所属权
    int troop[5];                // 判断兵种数：小，胖，球，法，轻
} IslandAll;

typedef struct Bridge {           // 桥的属性
    int HP;
} Bridge;
/******************岛和桥*********************/


// 公用参数声明
extern int usedBombNum;					// 记录用过的核弹数
extern char interStatement[20];         // 交互信息储存
extern PeopleAttribute people[2]; 		// 两个人的直属数据
extern IslandAll island[3];             // 设置三个岛
extern Bridge islandIsland[3]; 			// 两座岛之间的桥
extern Button choice[10];               // 预备按钮
extern ExMessage msg;                   // 操作信息检索


// 函数声明开始 
void printIsland();					                    // 展示战况 
int click(Button choice);                               // 检索点击
void clear();                                           // 清空操作区
void placeArm(int peopleNum);                           // 放兵主函数
void placeBridge(int peopleNum);                        // 架桥、拆桥的主函数
void attack(int peopleNum);                             // 攻击主函数
void houseSoldier(int peopleNum);                       // 房子出兵
void creatButton(Button* m, int x, int y, int w, int h, const char* text);  // 制造并输出按钮


#endif 