#include "help.h" 

// �ű���������
void placeArm(int peopleNum) {
    void printIsland(); // չʾ��ǰս��
    int sortPosition(int islandNum); 				// �ű��ֿ��þ���λ�ü���
    void sortSoldierIsland(int peopleNum, int* p); 	// �ű����õ�����
    void sortHouseIsland(int peopleNum, int* p);	// �ŷ��ӿ��õ�����
    extern void nuclearStrike(int peopleNum); 		// ս���˴��

    int soldier, positionNum, islandChoice, islandVeri[4] = { 0 };
    int y = 350, x=75, i, veri = 0;

    printIsland();
    outtextxy(tx, ty, "��ѡ����ã�");
    // ���ñ���
    switch (people[peopleNum - 1].accumulateNum) {
        case 1: {
            creatButton(&choice[0], 40, 350, 80, 50, "С��");
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
            creatButton(&choice[0], 40, 350, 80, 50, "С��");
            creatButton(&choice[1], 140, 350, 80, 50, "����");
            creatButton(&choice[2], 240, 350, 80, 50, "���");
            creatButton(&choice[3], 340, 350, 80, 50, "��ʦ");
            creatButton(&choice[4], 440, 350, 80, 50, "����");
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
            creatButton(&choice[0], 40, 350, 80, 50, "С��");
            creatButton(&choice[1], 140, 350, 80, 50, "����");
            creatButton(&choice[2], 240, 350, 80, 50, "���");
            creatButton(&choice[3], 340, 350, 80, 50, "��ʦ");
            creatButton(&choice[4], 440, 350, 80, 50, "����");
            creatButton(&choice[5], 540, 350, 80, 50, "����");
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
            creatButton(&choice[0], 40, 350, 80, 50, "С��");
            creatButton(&choice[1], 140, 350, 80, 50, "����");
            creatButton(&choice[2], 240, 350, 80, 50, "���");
            creatButton(&choice[3], 340, 350, 80, 50, "��ʦ");
            creatButton(&choice[4], 440, 350, 80, 50, "����");
            creatButton(&choice[5], 540, 350, 80, 50, "����");
            creatButton(&choice[6], 640, 350, 80, 50, "�˵�");
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
    // �˵�����
    if (soldier == 7) { 					// �˵�
        clear();
        outtextxy(tx, ty, "�Ƿ�ʹ�ú˵���");
        creatButton(&choice[0], 140, 350, 80, 50, "��");
        creatButton(&choice[1], 500, 350, 80, 50, "��");
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
            nuclearStrike(peopleNum);	// ����˴��
        }
        return;
    }
    else if (soldier == 6)				// �ж��Ƿ�Ϊ����
        sortHouseIsland(peopleNum, islandVeri);
    else
        sortSoldierIsland(peopleNum, islandVeri);
    if (!islandVeri[3]) {               // �����������
        clear();
        outtextxy(tx, ty, "û�п��Էű��ĵ��죬���β������ϣ�");
        creatButton(&choice[0], 250, 350, 150, 50, "��һ�غ�");
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
    outtextxy(tx, ty, "��ѡ������ĸ���:");         // ѡ��ű�����
    for (i = 0; i < 3; i++) {
        if (islandVeri[i]) {
            sprintf(interStatement, "%d�ŵ���", i + 1);
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
    positionNum = sortPosition(islandChoice);       // �����ɷű�λ�ò��Զ��ű�
    switch (soldier) {// С���֣��򣬷����ᣬ��
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
            printf("�ű�λ�ü������ִ��󣬳�������ֹ");
    }
    island[islandChoice].num++;
    island[islandChoice].owner = peopleNum;
}

// �ű����õ�����
void sortSoldierIsland(int peopleNum, int* islandVeri) {
    int i;

    for (i = 0; i < 3; i++) {
        if (island[i].owner == peopleNum) { 							// �Լ����� 
            if (island[i].num < island[i].limit && island[i].num < 10) {	// û����
                islandVeri[i] = 1;
                islandVeri[3] = 1;
            }
        }
        else if (island[i].owner == 0) { 								// �������� 
            if (islandIsland[peopleNum].HP == 1 && peopleNum == 1) {		// ���� 
                if (island[0].num) {										// �����б�
                    islandVeri[i] = 1;
                    islandVeri[3] = 1;
                }
            }
            else if (islandIsland[peopleNum].HP == 1 && peopleNum == 2) {   // ����
                if (island[2].num) {										// �����б� 
                    islandVeri[i] = 1;
                    islandVeri[3] = 1;
                }
            }
        }
        else { 											                // �з�����
            if (island[i].num == 0) {						                // �з��ޱ� 
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

// �ŷ��ӿ��õ�����
void sortHouseIsland(int peopleNum, int* islandVeri) {
    int i;
    for (i = 0; i < 3; i++) {
        if (island[i].owner == peopleNum && island[i].num < 10) {   // ��������
            islandVeri[i] = 1;
            islandVeri[3] = 1;
        }
        if (island[i].owner == 0 && islandIsland[peopleNum].HP) {   // ��������
            islandVeri[i] = 1;
            islandVeri[3] = 1;
        }
    }
    return;
}

// �ű��ֿ��þ���λ�ü���
int sortPosition(int islandChoice) {
    int i, cnt = 0;

    for (i = 0; i < 10; i++) {
        if (!island[islandChoice].main[i].veri)
            return cnt;
        cnt++;
    }
    return -1;
}

// �����Զ�����
void houseSoldier(int peopleNum) {
    void sortSoldierIsland(int peopleNum, int* islandVeri); // �ű����õ�����
    int sortPosition(int islandChoice);				// �ű��ֿ��þ���λ�ü���

    int i = people[peopleNum - 1].houseNum, j, islandChoice, positionNum;

    clear();
    while (i--) {
        int y = 350, x = 75;
        int islandVeri[4] = { 0 };

        outtextxy(tx, ty, "��ѡ���ӳ����ĸ�����");
        sortSoldierIsland(peopleNum, islandVeri);
        if (!islandVeri[3]) {       // ��λ�ÿɳ�����ֱ������
            clear();
            outtextxy(tx, ty, "�޷��ű����������ݷű������������");
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
        for (j = 0; j < 3; j++) {       // ��������ѡ��
            if (islandVeri[j]) {
                sprintf(interStatement, "%d�ŵ���", j + 1);
                creatButton(&choice[j], x, y, 150, 50, interStatement);
                x += 220;
            }
        }
        creatButton(&choice[3], 340, 290, 150, 35, "��������");
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
                if (click(choice[3])) {     // ��������
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