#include "help.h" 

// 架桥、拆桥的主函数
void placeBridge(int peopleNum) {
    int sortBuildBridge(int peopleNum, int* bridgeVeri);		// 可架桥位置检索
    int sortBreakBridge(int peopleNum, int* bridgeVeri);		// 可拆桥位置检索

    int bridgeChoice, choiceNum = 1, veri;
    int bridgeVeri[2] = { 0 };
    IMAGE imgChoice;

    printIsland();
    outtextxy(tx, ty, "请选择操作：");
    creatButton(&choice[0], 130, 350, 150, 50, "架桥");
    creatButton(&choice[1], 450, 350, 150, 50, "拆桥");
    while (1) {			//判断点击
        if (peekmessage(&msg, EX_MOUSE)) {
            if (click(choice[0])) {					    // 架桥
                clear();
                veri = sortBuildBridge(peopleNum, bridgeVeri);
                if (veri) {
                    clear();
                    outtextxy(tx, ty, "没有可以架的桥，本次操作作废：");
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
                while (1) {
                    if (peekmessage(&msg, EX_MOUSE)) {
                        if (click(choice[0]) && bridgeVeri[0]) {
                            bridgeChoice = 1;
                            break;
                        }
                        if (click(choice[1]) && bridgeVeri[1]) {
                            bridgeChoice = 2;
                            break;
                        }
                    }
                }
                islandIsland[bridgeChoice].HP = 1;
                break;
            }
            else if (click(choice[1])) {				// 拆桥
                clear();
                veri = sortBreakBridge(peopleNum, bridgeVeri);
                if (veri) {
                    clear();
                    outtextxy(tx, ty, "没有可以拆的桥，本次操作作废：");
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
                while (1) {
                    if (peekmessage(&msg, EX_MOUSE)) {
                        if (click(choice[0]) && bridgeVeri[0]) {
                            bridgeChoice = 1;
                            break;
                        }
                        if (click(choice[1]) && bridgeVeri[1]) {
                            bridgeChoice = 2;
                            break;
                        }
                    }
                }
                islandIsland[bridgeChoice].HP = 0;
                break;
            }
        }
    }
}

// 可架桥位置检索
int sortBuildBridge(int peopleNum, int* bridgeVeri) {
    int i, veri = 1;
    int x = 130, y = 350;
    char interStation[10];

    clear();
    outtextxy(tx, ty, "请选择要架的桥");
    for (i = 1; i < 3; i++) {
        if (islandIsland[i].HP == 0 && (island[i].owner == peopleNum && island[i].num || island[i - 1].owner == peopleNum && island[i - 1].num)) {
            sprintf(interStation, "%d号桥", i);
            creatButton(&choice[i-1], x, y, 150, 50, interStation);
            bridgeVeri[i-1] = 1;
            x += 320;
            veri = 0;
        }
    }
    return veri;
}

// 可拆桥位置检索
int sortBreakBridge(int peopleNum, int* bridgeVeri) {
    int i, veri = 1;
    int x = 130, y = 350;
    char interStation[10];

    clear();
    outtextxy(tx, ty, "请选择要拆的桥");
    for (i = 1; i < 3; i++) {
        if (islandIsland[i].HP == 1 && (island[i].owner == peopleNum && island[i].num || island[i - 1].owner == peopleNum && island[i - 1].num)) {
            sprintf(interStation, "%d号桥", i);
            creatButton(&choice[i - 1], x, y, 150, 50, interStation);
            bridgeVeri[i-1] = 1;
            x += 320;
            veri = 0;
        }
    }
    return veri;
}