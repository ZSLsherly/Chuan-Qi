#include <windows.h>
#include <time.h>
#include <math.h>
#include "help.h"
#pragma comment(lib,"winmm.lib") 

int usedBombNum;			    // ��¼�ù��ĺ˵���
char interStatement[20];        // ������Ϣ����
PeopleAttribute people[2]; 		// �����˵�ֱ������ 
IslandAll island[3];            // ����������
Bridge islandIsland[3];			// ������֮����� 

// ˫�˶�ս
extern void gameTwoPeople() {
    void createBackground();            // ��ʼ����Ϸ���� 
    void execute(int peopleNum);        // ִ�в���
    int decideChoice();                 // ��ɫ��
    void openSurprise(char* fileName, char* photo); // ����ʵ����

    int peopleNum, veri = 1;
    // ���ű������� 
    PlaySoundA("./Glorious-Morning.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    initgraph(750, 490, 1);
    HWND hnd = GetHWnd();
    SetWindowText(hnd, "��ƽ��");
    createBackground();                 // ��ʼ����Ϸ���� 

    // ѭ����Ϸ��������
    while (veri) {                      
        printIsland();
        if (TEST) {                     // ��������ģʽ
            printf("������ʤ����");
            scanf("%d", &peopleNum);
        }
        else{                           // ����ʤ�����ж�
            peopleNum = decideChoice();
        }
        if (peopleNum == 0)             // ���û��ʤ��������ѭ��
            continue;
        houseSoldier(peopleNum);
        execute(peopleNum);
        if (island[0].owner == island[1].owner && island[2].owner == island[1].owner)
            veri = 0;
        if (usedBombNum == LIMIT) {           	// �ݶ����£��ʵ���
            char fileName[20] = "./�˵����.txt", photo[30] = "./picture/�˵�����.jpeg";
            openSurprise(fileName, photo);
            return;
        }
    }

    // ��Ϸ����׶�
    printIsland();
    sprintf(interStatement, "%d�����ʤ�������������������", island[0].owner);
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
            if (click(choice[0])) {         // ������ֲʵ�
                char fileName[100] = "./�ʵ����.txt", photo[30] = "./picture/�ʵ�����.jpeg";
                openSurprise(fileName, photo);
                return;
            }
            else if (click(choice[1]))      // �ǲʵ�����
                return;
        }
    }
}

//ִ�к���
void execute(int peopleNum) {
    void printIsland();                  // չʾս��1
    void cheatCode(int peopleNum);        // ������

    int veri = 1;
    char interStatement[30];
    IMAGE imgChoice;

    clear();
    sprintf(interStatement, "��%d����Ҳ���", peopleNum);     // ������ת��Ϊ�ַ���
    outtextxy(tx, ty, interStatement);                          // ���ת������ַ���
    creatButton(&choice[0], 30, 350, 150, 50, "����");
    creatButton(&choice[1], 210, 350, 150, 50, "���ñ���");
    creatButton(&choice[2], 390, 350, 150, 50, "��������");
    creatButton(&choice[3], 570, 350, 150, 50, "��");

    while (1) {
        if (peekmessage(&msg, EX_MOUSE)) {
            if (click(choice[0])) {					        // ����
                attack(peopleNum);
                people[peopleNum - 1].accumulateNum = 1;
                break;
            }
            else if (click(choice[1])) {					// ���ñ���
                placeArm(peopleNum);
                people[peopleNum - 1].accumulateNum = 1;
                break;
            }
            else if (click(choice[2])) {					// ��������
                placeBridge(peopleNum);
                people[peopleNum - 1].accumulateNum = 1;
                break;
            }
            else if (click(choice[3])) {					// ��
                people[peopleNum - 1].accumulateNum++;
                break;
            }
        }
        if (_kbhit()) {
            cheatCode(peopleNum);
            break;
        }
    }
    // �����ʤ���ߵ�����
    if (peopleNum == 1)
        people[1].accumulateNum = 1;
    else if (peopleNum == 2)
        people[0].accumulateNum = 1;
}

// ��Ϸͼ�����
void printIsland() {
    void printSoldier(int veri, int x, int y);       //�������ͼƬ

    IMAGE imgIsland, imgChoice;
    IMAGE imgBridge[2], imgBomb[2];
    int i, j;
    int x, y, x0, y0, textx, texty;

    // ��Ϸ�������
    setbkcolor(WHITE);
    cleardevice();
    loadimage(&imgIsland, "./picture/��Ϸ����.png", 750, 280);
    putimage(0, 0, &imgIsland);

    // ����ҳ���ʼ��
    clear();
    // �����������
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, "����");
    settextcolor(BLACK);

    //�������
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

    // �������
    x = 195;
    y = 120;
    for (i = 1; i < 3; i++) {
        if (islandIsland[i].HP == 1) {
            loadimage(&imgBridge[i - 1], "./picture/bridge.jpg", 105, 35);
            putimage(x, y, &imgBridge[i - 1]);
        }
        x += 260;
    }

    // �˵���ʾ
    x = 15;
    y = 5;
    textx = 45;
    texty = 8;
    for (i = 0; i < 2; i++) {
        loadimage(&imgBomb[i], "./picture/bomb.png", 30, 40);
        putimage(x, y, &imgBomb[i]);
        sprintf(interStatement, "X%d", people[i].bombNum);                // ������ת��Ϊ�ַ���
        outtextxy(textx, texty, interStatement);                          // ���ת������ַ���
        x += 655;
        textx += 655;
    }

}

// ����ͼ�����
void printSoldier(int veri, int x, int y) {
    IMAGE imgSoldier;

    switch (veri) {
    case 0:   break;                //λ���ޱ�
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

// ��ɫ��
int decideChoice() {
    void printDice(int peopleNum, int num);     // ���ɫ��

    int num1, num2, i, end;
    char interStatement[30];
    IMAGE imgChoice;

    creatButton(&choice[0], 280, 350, 200, 50, "��ʼ��ɫ��");
    while (1) {			//�жϵ��
        if (peekmessage(&msg, EX_MOUSE)) {
            if (click(choice[0])) {					//������Ϸ
                clear();
                break;
            }
        }
    }

    srand((unsigned)time(NULL));            //��ʼ�������
    for (i = 0; i < 17; i++) {
        num1 = rand() % 6 + 1;
        printDice(1, num1);
        num2 = rand() % 6 + 1;
        printDice(2, num2);
        // ��������������724ms
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
        outtextxy(tx, ty, "������ȣ�ƽ�֣�");          // ֱ�����ƽ��
        Sleep(1500);
        return 0;
    }
    sprintf(interStatement, "��ϲ%d�����ʤ��", end);   // ������ת��Ϊ�ַ���
    outtextxy(tx, ty, interStatement);                  // ���ת������ַ���
    Sleep(1000);
    return end;
}

// ɫ��ͼ�����
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

// ������ 
void cheatCode(int peopleNum) {

    char cheat[30];
    int choiceNum, num;

    scanf("%s", cheat);
    scanf("%d%d", &choiceNum, &num);
    if (strcmp(cheat, "bomb") == 0) {				// choice_num��Ϊ��ұ��
        people[choiceNum - 1].bombNum += num;
    }
    else if (strcmp(cheat, "house") == 0) {			// choice_num��Ϊ����ѡ��
        extern int sortPosition(int islandChoice);			// �ű�λ�ü��� 

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
        // ��ջ�����
        char temp;
        while ((temp = getchar()) != '\n' && temp != EOF) {}
        printf("������δ��Ӧ\n");
        return;
    }
    // ��ջ�����
    char temp;
    while ((temp = getchar()) != '\n' && temp != EOF) {}
    printf("��������ִ��\n");
    printIsland();
}

// ��Ϸ���ݳ�ʼ��
void createBackground() {
    int i, j;

    // ��ʼ����
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

    // ��ʼ����� 
    for (i = 0; i < 2; i++) {
        people[i].accumulateNum = 1;
        people[i].bombNum = 0;
        people[i].houseNum = 0;
    }

    // ��ʼ������ 
    for (i = 1; i < 3; i++) {
        islandIsland[i].HP = 0;
    }
    // ��ʼ��ʹ�ú˵���
    usedBombNum = 0;
}

// ��ղ�����
void clear() {
    IMAGE imgChoice;

    loadimage(&imgChoice, "./picture/��Ϸ˵������.jpg", 750, 210);
    putimage(0, 280, &imgChoice);
}

// ����ʵ����
void openSurprise(char* fileName, char* photo) {
    IMAGE img;
    int x = 50, y = 20;

    PlaySoundA("./Schindler��s List.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    loadimage(&img, photo, 750, 490);
    putimage(0, 0, &img);
    setbkmode(TRANSPARENT);
    settextstyle(27, 0, "����");      // ����������ʽ
    settextcolor((COLORREF(RGB(219, 40, 40))));
    char str[1000] = { 0 }, print[3] = { 0 };
    char* p, * end = str;

    // ����ĵ�����
    while (fgets(str, sizeof(str), file)) {
        for (p = str; *end || *p; p += 2) {
            end = p + 4;
            // ��������Ƿ񳬳���Ļ��Χ
            if (x >= 700) {
                x = 50;
                y += 50;
            }
            // ����������
            print[0] = *p;
            print[1] = *(p + 1);
            outtextxy(x, y, print);
            x += 30;  // �ּ��
            Sleep(60);
        }
        break;
    }
    // �������
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