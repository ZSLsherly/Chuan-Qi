#include "help.h" 

// 放兵的主函数
void placeArm(int peopleNum) {
    void printIsland(); // 展示当前战况
    int sortPosition(int islandNum); 				// 放兵种可用具体位置检索
    void sortSoldierIsland(int peopleNum, int* p); 	// 放兵可用岛检索
    void sortHouseIsland(int peopleNum, int* p);	// 放房子可用岛检索
    extern void nuclearStrike(int peopleNum); 		// 战术核打击

    int soldier, positionNum, islandChoice, islandVeri[4] = { 0 };
    int y = 350, x=75, i, veri = 0;

    printIsland();
    outtextxy(tx, ty, "您选择放置：");
    // 放置兵种
    switch (people[peopleNum - 1].accumulateNum) {
        case 1: {
            creatButton(&choice[0], 40, 350, 80, 50, "小兵");
            while (1) {
                if (peekmessage(&msg, EX_MOUSE)) {
                    if (click(choice[0])) {
                        soldier = 1;
                        break;
                    }
                }
            }
            break;
        }
        case 2: {
            creatButton(&choice[0], 40, 350, 80, 50, "小兵");
            creatButton(&choice[1], 140, 350, 80, 50, "胖子");
            creatButton(&choice[2], 240, 350, 80, 50, "球哥");
            creatButton(&choice[3], 340, 350, 80, 50, "法师");
            creatButton(&choice[4], 440, 350, 80, 50, "轻炮");
            while (1) {
                if (peekmessage(&msg, EX_MOUSE)) {
                    for (i = 0; i < 5; i++) {
                        if (click(choice[i])) {
                            soldier = i + 1;
                            break;
                        }
                    }
                    if (i != 5)
                        break;
                }
            }
            break;
        }
        case 3: {
            creatButton(&choice[0], 40, 350, 80, 50, "小兵");
            creatButton(&choice[1], 140, 350, 80, 50, "胖子");
            creatButton(&choice[2], 240, 350, 80, 50, "球哥");
            creatButton(&choice[3], 340, 350, 80, 50, "法师");
            creatButton(&choice[4], 440, 350, 80, 50, "轻炮");
            creatButton(&choice[5], 540, 350, 80, 50, "房子");
            while (1) {
                if (peekmessage(&msg, EX_MOUSE)) {
                    for (i = 0; i < 6; i++) {
                        if (click(choice[i])) {
                            soldier = i + 1;
                            break;
                        }
                    }
                    if (i != 6)
                        break;
                }
            }
            break;
        }
        default: {
            creatButton(&choice[0], 40, 350, 80, 50, "小兵");
            creatButton(&choice[1], 140, 350, 80, 50, "胖子");
            creatButton(&choice[2], 240, 350, 80, 50, "球哥");
            creatButton(&choice[3], 340, 350, 80, 50, "法师");
            creatButton(&choice[4], 440, 350, 80, 50, "轻炮");
            creatButton(&choice[5], 540, 350, 80, 50, "房子");
            creatButton(&choice[6], 640, 350, 80, 50, "核弹");
            while (1) {
                if (peekmessage(&msg, EX_MOUSE)) {
                    for (i = 0; i < 7; i++) {
                        if (click(choice[i])) {
                            soldier = i + 1;
                            break;
                        }
                    }
                    if (i != 7)
                        break;
                }
            }
            break;
        }
    }
    // 核弹处理
    if (soldier == 7) { 					// 核弹
        clear();
        outtextxy(tx, ty, "是否使用核弹：");
        creatButton(&choice[0], 140, 350, 80, 50, "是");
        creatButton(&choice[1], 500, 350, 80, 50, "否");
        while (1) {
            if (peekmessage(&msg, EX_MOUSE)) {
                if (click(choice[0])) {
                    veri = 1;
                    break;
                }
                if (click(choice[1])) {
                    break;
                }
            }
        }
        people[peopleNum - 1].bombNum++;
        if (veri == 1) {
            nuclearStrike(peopleNum);	// 发起核打击
        }
        return;
    }
    else if (soldier == 6)				// 判断是否为房子
        sortHouseIsland(peopleNum, islandVeri);
    else
        sortSoldierIsland(peopleNum, islandVeri);
    if (!islandVeri[3]) {               // 错误操作检验
        clear();
        outtextxy(tx, ty, "没有可以放兵的岛屿，本次操作作废：");
        creatButton(&choice[0], 250, 350, 150, 50, "下一回合");
        while (1) {
            if (peekmessage(&msg, EX_MOUSE)) {
                if (click(choice[0])) {
                    break;
                }
            }
        }
        return;
    }
    clear();
    outtextxy(tx, ty, "您选择放在哪个岛:");         // 选择放兵岛屿
    for (i = 0; i < 3; i++) {
        if (islandVeri[i]) {
            sprintf(interStatement, "%d号岛屿", i + 1);
            creatButton(&choice[i], x, y, 150, 50, interStatement);
            x += 220;
        }
    }
    while (1) {
        if (peekmessage(&msg, EX_MOUSE)) {
            if (click(choice[0]) && islandVeri[0]) {
                islandChoice = 0;
                break;
            }
            if (click(choice[1]) && islandVeri[1]) {
                islandChoice = 1;
                break;
            }
            if (click(choice[2]) && islandVeri[2]) {
                islandChoice = 2;
                break;
            }
        }
    }
    positionNum = sortPosition(islandChoice);       // 检索可放兵位置并自动放兵
    switch (soldier) {// 小，胖，球，法，轻，房
        case 1: {
            island[islandChoice].main[positionNum].HP = 1;
            island[islandChoice].main[positionNum].veri = 1;
            island[islandChoice].troop[0]++;
            break;
        }
        case 2: {
            island[islandChoice].main[positionNum].HP = 2;
            island[islandChoice].main[positionNum].veri = 2;
            island[islandChoice].troop[1]++;
            break;
        }
        case 3: {
            island[islandChoice].main[positionNum].HP = 3;
            island[islandChoice].main[positionNum].veri = 3;
            island[islandChoice].troop[2]++;
            break;
        }
        case 4: {
            island[islandChoice].main[positionNum].HP = 1;
            island[islandChoice].main[positionNum].veri = 4;
            island[islandChoice].troop[3]++;
            break;
        }
        case 5: {
            island[islandChoice].main[positionNum].HP = 1;
            island[islandChoice].main[positionNum].veri = 5;
            island[islandChoice].troop[4]++;
            break;
        }
        case 6: {
            island[islandChoice].main[positionNum].HP = 3;
            island[islandChoice].main[positionNum].veri = 6;
            island[islandChoice].limit += 2;
            people[peopleNum - 1].houseNum++;
            break;
        }
        default:
            printf("放兵位置检索出现错误，程序已终止");
    }
    island[islandChoice].num++;
    island[islandChoice].owner = peopleNum;
}

// 放兵可用岛检索
void sortSoldierIsland(int peopleNum, int* islandVeri) {
    int i;

    for (i = 0; i < 3; i++) {
        if (island[i].owner == peopleNum) { 							// 自己岛上 
            if (island[i].num < island[i].limit && island[i].num < 10) {	// 没放满
                islandVeri[i] = 1;
                islandVeri[3] = 1;
            }
        }
        else if (island[i].owner == 0) { 								// 中立岛上 
            if (islandIsland[peopleNum].HP == 1 && peopleNum == 1) {		// 有桥 
                if (island[0].num) {										// 己方有兵
                    islandVeri[i] = 1;
                    islandVeri[3] = 1;
                }
            }
            else if (islandIsland[peopleNum].HP == 1 && peopleNum == 2) {   // 有桥
                if (island[2].num) {										// 己方有兵 
                    islandVeri[i] = 1;
                    islandVeri[3] = 1;
                }
            }
        }
        else { 											                // 敌方岛上
            if (island[i].num == 0) {						                // 敌方无兵 
                if (peopleNum == 1) {
                    if (islandIsland[i].HP && island[i - 1].owner == 1 && island[i - 1].num) {
                        islandVeri[i] = 1;
                        islandVeri[3] = 1;
                    }
                }
                else {
                    if (islandIsland[i + 1].HP && island[i + 1].owner == 2 && island[i + 1].num) {
                        islandVeri[i] = 1;
                        islandVeri[3] = 1;
                    }
                }
            }
        }
    }
    return;
}

// 放房子可用岛检索
void sortHouseIsland(int peopleNum, int* islandVeri) {
    int i;
    for (i = 0; i < 3; i++) {
        if (island[i].owner == peopleNum && island[i].num < 10) {   // 己方岛屿
            islandVeri[i] = 1;
            islandVeri[3] = 1;
        }
        if (island[i].owner == 0 && islandIsland[peopleNum].HP) {   // 中立岛屿
            islandVeri[i] = 1;
            islandVeri[3] = 1;
        }
    }
    return;
}

// 放兵种可用具体位置检索
int sortPosition(int islandChoice) {
    int i, cnt = 0;

    for (i = 0; i < 10; i++) {
        if (!island[islandChoice].main[i].veri)
            return cnt;
        cnt++;
    }
    return -1;
}

// 房屋自动出兵
void houseSoldier(int peopleNum) {
    void sortSoldierIsland(int peopleNum, int* islandVeri); // 放兵可用岛检索
    int sortPosition(int islandChoice);				// 放兵种可用具体位置检索

    int i = people[peopleNum - 1].houseNum, j, islandChoice, positionNum;

    clear();
    while (i--) {
        int y = 350, x = 75;
        int islandVeri[4] = { 0 };

        outtextxy(tx, ty, "您选择房子出兵哪个岛：");
        sortSoldierIsland(peopleNum, islandVeri);
        if (!islandVeri[3]) {       // 无位置可出兵，直接跳过
            clear();
            outtextxy(tx, ty, "无法放兵，跳过房屋放兵（点击继续）");
            choice[0].x = 0;
            choice[0].y = 0;
            choice[0].w = 750;
            choice[0].h = 490;
            while (1) {
                if (peekmessage(&msg, EX_MOUSE)) {
                    if (click(choice[0])) {
                        return;
                    }
                }
            }
        }
        for (j = 0; j < 3; j++) {       // 出兵岛屿选择
            if (islandVeri[j]) {
                sprintf(interStatement, "%d号岛屿", j + 1);
                creatButton(&choice[j], x, y, 150, 50, interStatement);
                x += 220;
            }
        }
        creatButton(&choice[3], 340, 290, 150, 35, "放弃出兵");
        while (1) {
            if (peekmessage(&msg, EX_MOUSE)) {
                if (click(choice[0]) && islandVeri[0]) {
                    islandChoice = 0;
                    break;
                }
                if (click(choice[1]) && islandVeri[1]) {
                    islandChoice = 1;
                    break;
                }
                if (click(choice[2]) && islandVeri[2]) {
                    islandChoice = 2;
                    break;
                }
                if (click(choice[3])) {     // 结束出兵
                    return;
                }
            }
        }
        positionNum = sortPosition(islandChoice);
        island[islandChoice].main[positionNum].HP = 1;
        island[islandChoice].main[positionNum].veri = 1;
        island[islandChoice].troop[0]++;
        island[islandChoice].num++;
        island[islandChoice].owner = peopleNum;
        printIsland();
    }
    return;
}