#include <windows.h>
#include <time.h>
#include <math.h>
#include "help.h"
#pragma comment(lib,"winmm.lib") 

int usedBombNum;			    // 记录用过的核弹数
char interStatement[20];        // 交互信息储存
PeopleAttribute people[2]; 		// 两个人的直属数据 
IslandAll island[3];            // 设置三个岛
Bridge islandIsland[3];			// 两座岛之间的桥 

// 双人对战
extern void gameTwoPeople() {
    void createBackground();            // 初始化游戏数据 
    void execute(int peopleNum);        // 执行操作
    int decideChoice();                 // 掷色子
    void openSurprise(char* fileName, char* photo); // 输出彩蛋结局

    int peopleNum, veri = 1;
    // 播放背景音乐 
    PlaySoundA("./Glorious-Morning.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    initgraph(750, 490, 1);
    HWND hnd = GetHWnd();
    SetWindowText(hnd, "和平岛");
    createBackground();                 // 初始化游戏数据 

    // 循环游戏基础过程
    while (veri) {                      
        printIsland();
        if (TEST) {                     // 开启调试模式
            printf("请输入胜利者");
            scanf("%d", &peopleNum);
        }
        else{                           // 正常胜利者判定
            peopleNum = decideChoice();
        }
        if (peopleNum == 0)             // 如果没有胜利者重新循环
            continue;
        houseSoldier(peopleNum);
        execute(peopleNum);
        if (island[0].owner == island[1].owner && island[2].owner == island[1].owner)
            veri = 0;
        if (usedBombNum == LIMIT) {           	// 凛冬岁月（彩蛋）
            char fileName[20] = "./核弹结局.txt", photo[30] = "./picture/核弹背景.jpeg";
            openSurprise(fileName, photo);
            return;
        }
    }

    // 游戏结算阶段
    printIsland();
    sprintf(interStatement, "%d号玩家胜利！！！（点击继续）", island[0].owner);
    outtextxy(tx, ty, interStatement);
    choice[0].x = 330;
    choice[0].y = 290;
    choice[0].w = 130;
    choice[0].h = 35;
    choice[1].x = 0;
    choice[1].y = 0;
    choice[1].w = 750;
    choice[1].h = 490;
    while (1) {
        if (peekmessage(&msg, EX_MOUSE)) {
            if (click(choice[0])) {         // 正常结局彩蛋
                char fileName[100] = "./彩蛋结局.txt", photo[30] = "./picture/彩蛋背景.jpeg";
                openSurprise(fileName, photo);
                return;
            }
            else if (click(choice[1]))      // 非彩蛋结束
                return;
        }
    }
}

//执行函数
void execute(int peopleNum) {
    void printIsland();                  // 展示战况1
    void cheatCode(int peopleNum);        // 作弊码

    int veri = 1;
    char interStatement[30];
    IMAGE imgChoice;

    clear();
    sprintf(interStatement, "请%d号玩家操作", peopleNum);     // 将数字转换为字符串
    outtextxy(tx, ty, interStatement);                          // 输出转换后的字符串
    creatButton(&choice[0], 30, 350, 150, 50, "攻击");
    creatButton(&choice[1], 210, 350, 150, 50, "放置兵种");
    creatButton(&choice[2], 390, 350, 150, 50, "基础操作");
    creatButton(&choice[3], 570, 350, 150, 50, "屯");

    while (1) {
        if (peekmessage(&msg, EX_MOUSE)) {
            if (click(choice[0])) {					        // 攻击
                attack(peopleNum);
                people[peopleNum - 1].accumulateNum = 1;
                break;
            }
            else if (click(choice[1])) {					// 放置兵种
                placeArm(peopleNum);
                people[peopleNum - 1].accumulateNum = 1;
                break;
            }
            else if (click(choice[2])) {					// 基础操作
                placeBridge(peopleNum);
                people[peopleNum - 1].accumulateNum = 1;
                break;
            }
            else if (click(choice[3])) {					// 屯
                people[peopleNum - 1].accumulateNum++;
                break;
            }
        }
        if (_kbhit()) {
            cheatCode(peopleNum);
            break;
        }
    }
    // 清除非胜利者的屯数
    if (peopleNum == 1)
        people[1].accumulateNum = 1;
    else if (peopleNum == 2)
        people[0].accumulateNum = 1;
}

// 游戏图像加载
void printIsland() {
    void printSoldier(int veri, int x, int y);       //输出兵种图片

    IMAGE imgIsland, imgChoice;
    IMAGE imgBridge[2], imgBomb[2];
    int i, j;
    int x, y, x0, y0, textx, texty;

    // 游戏背景输出
    setbkcolor(WHITE);
    cleardevice();
    loadimage(&imgIsland, "./picture/游戏背景.png", 750, 280);
    putimage(0, 0, &imgIsland);

    // 操作页面初始化
    clear();
    // 字体基础设置
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, "黑体");
    settextcolor(BLACK);

    //兵种输出
    y0 = 55;
    for (i = 0; i < 3; i++) {
        x0 = 75 + i * 260;
        x = x0; y = y0;
        for (j = 0; j < 2; j++) {
            printSoldier(island[i].main[j].veri, x, y);
            x += 50;
        }
        x = x0 - 25; y = y0 + 45;
        for (j = 2; j < 5; j++) {
            printSoldier(island[i].main[j].veri, x, y);
            x += 50;
        }
        x = x0 - 25; y = y0 + 90;
        for (j = 5; j < 8; j++) {
            printSoldier(island[i].main[j].veri, x, y);
            x += 50;
        }
        x = x0; y = y0 + 135;
        for (j = 8; j < 10; j++) {
            printSoldier(island[i].main[j].veri, x, y);
            x += 50;
        }
    }

    // 桥梁输出
    x = 195;
    y = 120;
    for (i = 1; i < 3; i++) {
        if (islandIsland[i].HP == 1) {
            loadimage(&imgBridge[i - 1], "./picture/bridge.jpg", 105, 35);
            putimage(x, y, &imgBridge[i - 1]);
        }
        x += 260;
    }

    // 核弹显示
    x = 15;
    y = 5;
    textx = 45;
    texty = 8;
    for (i = 0; i < 2; i++) {
        loadimage(&imgBomb[i], "./picture/bomb.png", 30, 40);
        putimage(x, y, &imgBomb[i]);
        sprintf(interStatement, "X%d", people[i].bombNum);                // 将数字转换为字符串
        outtextxy(textx, texty, interStatement);                          // 输出转换后的字符串
        x += 655;
        textx += 655;
    }

}

// 兵种图像加载
void printSoldier(int veri, int x, int y) {
    IMAGE imgSoldier;

    switch (veri) {
    case 0:   break;                //位置无兵
    case 1: {
        loadimage(&imgSoldier, "./picture/minion.png", 35, 35);
        putimage(x, y, &imgSoldier);
        break;
    }
    case 2: {
        loadimage(&imgSoldier, "./picture/stronger.png", 35, 35);
        putimage(x, y, &imgSoldier);
        break;
    }
    case 3: {
        loadimage(&imgSoldier, "./picture/fatty.png", 35, 35);
        putimage(x, y, &imgSoldier);
        break;
    }
    case 4: {
        loadimage(&imgSoldier, "./picture/caster.png", 35, 35);
        putimage(x, y, &imgSoldier);
        break;
    }
    case 5: {
        loadimage(&imgSoldier, "./picture/cannon.png", 35, 35);
        putimage(x, y, &imgSoldier);
        break;
    }
    case 6: {
        loadimage(&imgSoldier, "./picture/house.png", 35, 35);
        putimage(x, y, &imgSoldier);
        break;
    }
    }
}

// 掷色子
int decideChoice() {
    void printDice(int peopleNum, int num);     // 输出色子

    int num1, num2, i, end;
    char interStatement[30];
    IMAGE imgChoice;

    creatButton(&choice[0], 280, 350, 200, 50, "开始掷色子");
    while (1) {			//判断点击
        if (peekmessage(&msg, EX_MOUSE)) {
            if (click(choice[0])) {					//进入游戏
                clear();
                break;
            }
        }
    }

    srand((unsigned)time(NULL));            //初始化随机数
    for (i = 0; i < 17; i++) {
        num1 = rand() % 6 + 1;
        printDice(1, num1);
        num2 = rand() % 6 + 1;
        printDice(2, num2);
        // 动画性输出，最久724ms
        Sleep(ceil(sqrt(pow(2, i) + 400)));
    }
    num1 = rand() % 6 + 1;
    printDice(1, num1);
    num2 = rand() % 6 + 1;
    printDice(2, num2);
    if (num1 > num2) {
        end = 1;
    }
    else if (num2 > num1) {
        end = 2;
    }
    else {
        outtextxy(tx, ty, "点数相等，平局！");          // 直接输出平局
        Sleep(1500);
        return 0;
    }
    sprintf(interStatement, "恭喜%d号玩家胜利", end);   // 将数字转换为字符串
    outtextxy(tx, ty, interStatement);                  // 输出转换后的字符串
    Sleep(1000);
    return end;
}

// 色子图像加载
void printDice(int peopleNum, int num) {
    IMAGE imgDice;
    int x, y = 330;

    if (peopleNum == 1)
        x = 140;
    else
        x = 500;
    switch (num) {
    case 1: {
        loadimage(&imgDice, "./picture/1.png", 110, 110);
        putimage(x, y, &imgDice);
        break;
    }
    case 2: {
        loadimage(&imgDice, "./picture/2.png", 110, 110);
        putimage(x, y, &imgDice);
        break;
    }
    case 3: {
        loadimage(&imgDice, "./picture/3.png", 110, 110);
        putimage(x, y, &imgDice);
        break;
    }
    case 4: {
        loadimage(&imgDice, "./picture/4.png", 110, 110);
        putimage(x, y, &imgDice);
        break;
    }
    case 5: {
        loadimage(&imgDice, "./picture/5.png", 110, 110);
        putimage(x, y, &imgDice);
        break;
    }
    case 6: {
        loadimage(&imgDice, "./picture/6.png", 110, 110);
        putimage(x, y, &imgDice);
        break;
    }
    }
}

// 作弊码 
void cheatCode(int peopleNum) {

    char cheat[30];
    int choiceNum, num;

    scanf("%s", cheat);
    scanf("%d%d", &choiceNum, &num);
    if (strcmp(cheat, "bomb") == 0) {				// choice_num视为玩家编号
        people[choiceNum - 1].bombNum += num;
    }
    else if (strcmp(cheat, "house") == 0) {			// choice_num视为岛屿选择
        extern int sortPosition(int islandChoice);			// 放兵位置检索 

        int positionNum;

        choiceNum--;
        do {
            positionNum = sortPosition(choiceNum);
            island[choiceNum].main[positionNum].HP = 3;
            island[choiceNum].main[positionNum].veri = 6;
            island[choiceNum].limit += 2;
            people[peopleNum - 1].houseNum++;
            island[choiceNum].num++;
        } while (--num);
        island[choiceNum].owner = peopleNum;
    }
    else {
        // 清空缓存区
        char temp;
        while ((temp = getchar()) != '\n' && temp != EOF) {}
        printf("作弊码未响应\n");
        return;
    }
    // 清空缓存区
    char temp;
    while ((temp = getchar()) != '\n' && temp != EOF) {}
    printf("作弊码已执行\n");
    printIsland();
}

// 游戏数据初始化
void createBackground() {
    int i, j;

    // 初始化岛
    for (i = 0; i < 3; i++) {
        island[i].limit = LIMIT;
        island[i].num = 0;
        for (j = 0; j < 10; j++) {
            island[i].main[j].veri = 0;
        }
        for (j = 0; j < 5; j++) {
            island[i].troop[j] = 0;
        }
    }
    island[0].owner = 1;
    island[1].owner = 0;
    island[2].owner = 2;

    // 初始化玩家 
    for (i = 0; i < 2; i++) {
        people[i].accumulateNum = 1;
        people[i].bombNum = 0;
        people[i].houseNum = 0;
    }

    // 初始化桥梁 
    for (i = 1; i < 3; i++) {
        islandIsland[i].HP = 0;
    }
    // 初始化使用核弹数
    usedBombNum = 0;
}

// 清空操作区
void clear() {
    IMAGE imgChoice;

    loadimage(&imgChoice, "./picture/游戏说明背景.jpg", 750, 210);
    putimage(0, 280, &imgChoice);
}

// 输出彩蛋结局
void openSurprise(char* fileName, char* photo) {
    IMAGE img;
    int x = 50, y = 20;

    PlaySoundA("./Schindler’s List.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    loadimage(&img, photo, 750, 490);
    putimage(0, 0, &img);
    setbkmode(TRANSPARENT);
    settextstyle(27, 0, "黑体");      // 设置字体样式
    settextcolor((COLORREF(RGB(219, 40, 40))));
    char str[1000] = { 0 }, print[3] = { 0 };
    char* p, * end = str;

    // 输出文档内容
    while (fgets(str, sizeof(str), file)) {
        for (p = str; *end || *p; p += 2) {
            end = p + 4;
            // 检查坐标是否超出屏幕范围
            if (x >= 700) {
                x = 50;
                y += 50;
            }
            // 逐个汉字输出
            print[0] = *p;
            print[1] = *(p + 1);
            outtextxy(x, y, print);
            x += 30;  // 字间隔
            Sleep(60);
        }
        break;
    }
    // 点击继续
    choice[0].x = 0;
    choice[0].y = 0;
    choice[0].w = 750;
    choice[0].h = 490;
    while (1) {
        if (peekmessage(&msg, EX_MOUSE))
            if (click(choice[0]))
                break;
    }
    fclose(file);
}