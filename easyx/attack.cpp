#include "help.h"

// 攻击的主函数
void attack(int peopleNum) {
    int sortAttacker(int peopleNum, int* islandChoice, char* attackerVeri);                      // 检索攻击者
    int sortVictim(int peopleNum, int taunt, int* positionVeri);			 // 检索受攻击者, taunt:是否嘲讽
    void nuclearStrike(int peopleNum);                                       // 战术核打击
    void attackExcute(int islandChoice, int positionNum, int hurt);          // 攻击兵种执行

    char attackerChoice, attackerVeri[7];
    int islandVeri[6] = { 0 }, positionVeri[10] = { 0 };
    int i, islandChoice = 5, attackerNum, positionNum = 11;
    int x, y;

    printIsland();
    attackerNum = sortAttacker(peopleNum, &islandChoice, attackerVeri);
    if (!attackerNum) {              // 检索攻击者
        outtextxy(tx, ty, "没有可用于攻击的单位，本次操作作废：");
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
    outtextxy(tx, ty, "您选择用什么攻击：");
    while (1) {                              // 选择攻击者
        if (peekmessage(&msg, EX_MOUSE)) {
            for (i = 0; i < attackerNum; i++) {
                if (click(choice[i])) {
                    attackerChoice = attackerVeri[i];
                    break;
                }
            }
            if (i != attackerNum)
                break;
        }
    }
    clear();
    // 远程攻击无嘲讽
    if (attackerChoice == 'q') {                  // 轻炮攻击
        outtextxy(tx, ty, "您可以攻击：");
        x =40, y = 330;
        for (i = 0; i < 3; i++) {										// 可攻击岛屿检索 
            if (island[i].owner != peopleNum && island[i].num) {
                sprintf(interStatement, "%d号岛屿", i + 1);
                creatButton(&choice[i], x, y, 115, 50, interStatement);
                x += 130;
                islandVeri[i] = 1;
                islandVeri[5] = 1;
            }
        }
        for (i = 3; i < 5; i++) {					    				// 可攻击桥梁检索 
            if (islandIsland[i-2].HP) {
                sprintf(interStatement, "%d号桥", i - 2);
                creatButton(&choice[i], x, y, 115, 50, interStatement);
                x += 130;
                islandVeri[i] = 1;
                islandVeri[5] = 1;
            }
        }
        if (!islandVeri[5]) {                                           // 没有可攻击目标
            clear();
            outtextxy(tx, ty, "没有可以攻击的岛或桥，本次操作作废：");
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
        while (1) {                                              // 选择攻击桥或岛
            if (peekmessage(&msg, EX_MOUSE)) {
                for (i = 0; i < 5; i++) {
                    if (click(choice[i])&&islandVeri[i]) {
                        islandChoice = i;
                        break;
                    }
                }
                if (i != 5)
                    break;
            }
        }
        if (islandChoice > 2) {                                 // 攻击桥梁
            islandChoice -= 2;
            islandIsland[islandChoice].HP = 0;
            return;
        }
        else {                                                 // 攻击岛
            sortVictim(islandChoice, 0, positionVeri);
            outtextxy(tx, ty, "您选择攻击（名字/位置）：");
            while (1) {                                        // 选择具体攻击对象
                if (peekmessage(&msg, EX_MOUSE)) {
                    for (i = 0; i < 10; i++) {
                        if (click(choice[i])&&positionVeri[i]) {
                            positionNum = i;
                            break;
                        }
                    }
                    if (positionNum != 11)
                        break;
                }
            }
            attackExcute(islandChoice, positionNum, 1);
        }
    }
    else if (attackerChoice == 'h') {            // 核打击
        nuclearStrike(peopleNum);
        return;
    }
    // 近战被嘲讽
    else {
        if (!sortVictim(islandChoice, 1, positionVeri)) { 			// 无可攻击目标
            clear();
            outtextxy(tx, ty, "没有可被攻击单位，本次操作作废：");
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
        outtextxy(tx, ty, "您选择攻击（名字/位置）：");
        while (1) {                                                 // 具体攻击对象
            if (peekmessage(&msg, EX_MOUSE)) {
                for (i = 0; i < 10; i++) {
                    if (click(choice[i]) && positionVeri[i]) {
                        positionNum = i;
                        break;
                    }
                }
                if (positionNum != 11)
                    break;
            }
        }
        if (attackerChoice == 'x') {               // 小兵、胖子、法师具体攻击
            attackExcute(islandChoice, positionNum, 1);
        }
        else if (attackerChoice == 'p') {
            attackExcute(islandChoice, positionNum, 2);
        }
        else if (attackerChoice == 'f') {
            attackExcute(islandChoice, positionNum, 3);
        }
    }
}

// 战术核打击
void nuclearStrike(int peopleNum) {
    void attackExcute(int islandChoice, int positionNum, int hurt);

    int i, islandChoice, islandVeri[3] = { 0 };
    int x = 75, y = 350;

    clear();
    outtextxy(tx, ty, "您可以打击：");
    for (i = 0; i < 3; i++) {
        if (island[i].owner != peopleNum) {
            sprintf(interStatement, "%d号岛屿", i + 1);
            creatButton(&choice[i], x, y, 150, 50, interStatement);
            islandVeri[i] = 1;
            x += 220;
        }
    }
    while (1) {                                     // 攻击岛屿选择
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
    for (i = 0; i < 10; i++) {					  // 秒杀所有位置 
        attackExcute(islandChoice, i, 3);
    }
    island[islandChoice].limit--;                 // 核污染，上限减一
    usedBombNum++;                                // 使用过核弹数加一
    people[peopleNum - 1].bombNum--;              // 核弹数量减一
    island[islandChoice].num = 0;                 // 人物数量清零
}

// 攻击兵种执行
void attackExcute(int islandChoice, int positionNum, int hurt) {
    if (island[islandChoice].main[positionNum].veri == 0) {			// 核弹提速 
        return;
    }
    island[islandChoice].main[positionNum].HP -= hurt;                  // 伤害结算
    if (island[islandChoice].main[positionNum].HP <= 0) {               // 兵种死亡结算
        island[islandChoice].troop[island[islandChoice].main[positionNum].veri - 1]--;
        island[islandChoice].num--;
        if (island[islandChoice].main[positionNum].veri == 6) {         // 房子特殊结算
            people[(island[islandChoice].owner) - 1].houseNum--;
            island[islandChoice].limit--;
        }
        island[islandChoice].main[positionNum].veri = 0;
    }
}

// 检索受攻击者，taunt:是否嘲讽
int sortVictim(int islandChoice, int taunt, int* positionVeri) {
    int i, veri = 0;
    int x = 40, y = 330;

    clear();
    if (taunt && island[islandChoice].troop[2]) {           // 受到嘲讽
        for (i = 0; i < 10; i++) {
            if (island[islandChoice].main[i].veri == 3) {
                positionVeri[i] = 1;
                veri = 1;
                sprintf(interStatement, "球哥/%d", i+1); 
                creatButton(&choice[i], x, y, 150, 45, interStatement);
                x += 180;
            }
            if (x >= 600) {
                x = 40;
                y += 55;
            }
        }
    }
    else {                                               // 未受到嘲讽
        for (i = 0; i < 10; i++) {
            switch (island[islandChoice].main[i].veri) {
                case 1: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "小兵/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 2: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "胖子/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 3: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "球哥/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 4: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "法师/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 5: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "轻炮/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 6: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "房子/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
            }
            if (x >= 600) {
                x = 40;
                y += 55;
            }
        }
    }
    return veri;
}

// 检索攻击者
int sortAttacker(int peopleNum, int* islandChoice, char* attackerVeri) {
    int veriCannon = 1, i = 0;
    int x = 80, y = 330;
    
    clear();
    // 远程轻炮检索 
    if (peopleNum == 1) {
        if (island[0].troop[4]) {
            creatButton(&choice[i], x, y, 120, 50, "轻炮");
            attackerVeri[i++] = 'q';
            x += 170;
            veriCannon = 0;
        }
    }
    else {
        if (island[2].troop[4]) {
            creatButton(&choice[i], x, y, 120, 50, "轻炮");
            attackerVeri[i++] = 'q';
            x += 170;
            veriCannon = 0;
        }
    }
    // 非远程攻击检索 
    if (island[1].owner == peopleNum) { // 中间岛归操作者
        if (island[1].troop[4] && veriCannon) {
            creatButton(&choice[i], x, y, 120, 50, "轻炮");
            attackerVeri[i++] = 'q';
            x += 170;
        }
        if ((peopleNum == 1 && islandIsland[2].HP) || (peopleNum == 2 && islandIsland[1].HP)) { // 有桥，近战有效
            if (island[1].troop[3]) {
                creatButton(&choice[i], x, y, 120, 50, "法师");
                attackerVeri[i++] = 'f';
                x += 170;
            }
            if (island[1].troop[1]) {
                creatButton(&choice[i], x, y, 120, 50, "胖子");
                attackerVeri[i++] = 'p';
                x += 170;
            }
            else if (island[1].troop[0]) {
                creatButton(&choice[i], x, y, 120, 50, "小兵");
                attackerVeri[i++] = 'x';
                x += 170;
            }
        }
        // 攻击目标岛反馈 
        if (peopleNum == 1) {
            *islandChoice = 2;
        }
        else {
            *islandChoice = 0;
        }
    }
    else if (island[1].owner == 0) { // 中间岛未被占领
        // 无需操作
    }
    else { // 中间岛归受攻击者
        if (islandIsland[peopleNum].HP) { // 有桥，近战有效
            if (peopleNum == 1) {
                if (island[0].troop[3]) {
                    creatButton(&choice[i], x, y, 120, 50, "法师");
                    attackerVeri[i++] = 'f';
                    x += 170;
                }
                if (island[0].troop[1]) {
                    creatButton(&choice[i], x, y, 120, 50, "胖子");
                    attackerVeri[i++] = 'p';
                    x += 170;
                }
                else if (island[0].troop[0]) {
                    creatButton(&choice[i], x, y, 120, 50, "小兵");
                    attackerVeri[i++] = 'x';
                    x += 170;
                }
            }
            else {
                if (island[2].troop[3]) {
                    creatButton(&choice[i], x, y, 120, 50, "法师");
                    attackerVeri[i++] = 'f';
                    x += 170;
                }
                if (island[2].troop[1]) {
                    creatButton(&choice[i], x, y, 120, 50, "胖子");
                    attackerVeri[i++] = 'p';
                    x += 170;
                }
                else if (island[2].troop[0]) {
                    creatButton(&choice[i], x, y, 120, 50, "小兵");
                    attackerVeri[i++] = 'x';
                    x += 170;
                }
            }
        }
        // 攻击目标岛反馈
        *islandChoice = 1;
    }
    if (people[peopleNum - 1].bombNum) {
        if (i < 4) {
            creatButton(&choice[i], x, y, 120, 50, "核弹");
            attackerVeri[i++] = 'h';
        }
        else {
            creatButton(&choice[i], 345, 420, 120, 50, "核弹");
            attackerVeri[i++] = 'h';
        }
    }
    return i;
}