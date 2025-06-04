#include "help.h"

// ������������
void attack(int peopleNum) {
    int sortAttacker(int peopleNum, int* islandChoice, char* attackerVeri);                      // ����������
    int sortVictim(int peopleNum, int taunt, int* positionVeri);			 // �����ܹ�����, taunt:�Ƿ񳰷�
    void nuclearStrike(int peopleNum);                                       // ս���˴��
    void attackExcute(int islandChoice, int positionNum, int hurt);          // ��������ִ��

    char attackerChoice, attackerVeri[7];
    int islandVeri[6] = { 0 }, positionVeri[10] = { 0 };
    int i, islandChoice = 5, attackerNum, positionNum = 11;
    int x, y;

    printIsland();
    attackerNum = sortAttacker(peopleNum, &islandChoice, attackerVeri);
    if (!attackerNum) {              // ����������
        outtextxy(tx, ty, "û�п����ڹ����ĵ�λ�����β������ϣ�");
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
    outtextxy(tx, ty, "��ѡ����ʲô������");
    while (1) {                              // ѡ�񹥻���
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
    // Զ�̹����޳���
    if (attackerChoice == 'q') {                  // ���ڹ���
        outtextxy(tx, ty, "�����Թ�����");
        x =40, y = 330;
        for (i = 0; i < 3; i++) {										// �ɹ���������� 
            if (island[i].owner != peopleNum && island[i].num) {
                sprintf(interStatement, "%d�ŵ���", i + 1);
                creatButton(&choice[i], x, y, 115, 50, interStatement);
                x += 130;
                islandVeri[i] = 1;
                islandVeri[5] = 1;
            }
        }
        for (i = 3; i < 5; i++) {					    				// �ɹ����������� 
            if (islandIsland[i-2].HP) {
                sprintf(interStatement, "%d����", i - 2);
                creatButton(&choice[i], x, y, 115, 50, interStatement);
                x += 130;
                islandVeri[i] = 1;
                islandVeri[5] = 1;
            }
        }
        if (!islandVeri[5]) {                                           // û�пɹ���Ŀ��
            clear();
            outtextxy(tx, ty, "û�п��Թ����ĵ����ţ����β������ϣ�");
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
        while (1) {                                              // ѡ�񹥻��Ż�
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
        if (islandChoice > 2) {                                 // ��������
            islandChoice -= 2;
            islandIsland[islandChoice].HP = 0;
            return;
        }
        else {                                                 // ������
            sortVictim(islandChoice, 0, positionVeri);
            outtextxy(tx, ty, "��ѡ�񹥻�������/λ�ã���");
            while (1) {                                        // ѡ����幥������
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
    else if (attackerChoice == 'h') {            // �˴��
        nuclearStrike(peopleNum);
        return;
    }
    // ��ս������
    else {
        if (!sortVictim(islandChoice, 1, positionVeri)) { 			// �޿ɹ���Ŀ��
            clear();
            outtextxy(tx, ty, "û�пɱ�������λ�����β������ϣ�");
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
        outtextxy(tx, ty, "��ѡ�񹥻�������/λ�ã���");
        while (1) {                                                 // ���幥������
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
        if (attackerChoice == 'x') {               // С�������ӡ���ʦ���幥��
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

// ս���˴��
void nuclearStrike(int peopleNum) {
    void attackExcute(int islandChoice, int positionNum, int hurt);

    int i, islandChoice, islandVeri[3] = { 0 };
    int x = 75, y = 350;

    clear();
    outtextxy(tx, ty, "�����Դ����");
    for (i = 0; i < 3; i++) {
        if (island[i].owner != peopleNum) {
            sprintf(interStatement, "%d�ŵ���", i + 1);
            creatButton(&choice[i], x, y, 150, 50, interStatement);
            islandVeri[i] = 1;
            x += 220;
        }
    }
    while (1) {                                     // ��������ѡ��
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
    for (i = 0; i < 10; i++) {					  // ��ɱ����λ�� 
        attackExcute(islandChoice, i, 3);
    }
    island[islandChoice].limit--;                 // ����Ⱦ�����޼�һ
    usedBombNum++;                                // ʹ�ù��˵�����һ
    people[peopleNum - 1].bombNum--;              // �˵�������һ
    island[islandChoice].num = 0;                 // ������������
}

// ��������ִ��
void attackExcute(int islandChoice, int positionNum, int hurt) {
    if (island[islandChoice].main[positionNum].veri == 0) {			// �˵����� 
        return;
    }
    island[islandChoice].main[positionNum].HP -= hurt;                  // �˺�����
    if (island[islandChoice].main[positionNum].HP <= 0) {               // ������������
        island[islandChoice].troop[island[islandChoice].main[positionNum].veri - 1]--;
        island[islandChoice].num--;
        if (island[islandChoice].main[positionNum].veri == 6) {         // �����������
            people[(island[islandChoice].owner) - 1].houseNum--;
            island[islandChoice].limit--;
        }
        island[islandChoice].main[positionNum].veri = 0;
    }
}

// �����ܹ����ߣ�taunt:�Ƿ񳰷�
int sortVictim(int islandChoice, int taunt, int* positionVeri) {
    int i, veri = 0;
    int x = 40, y = 330;

    clear();
    if (taunt && island[islandChoice].troop[2]) {           // �ܵ�����
        for (i = 0; i < 10; i++) {
            if (island[islandChoice].main[i].veri == 3) {
                positionVeri[i] = 1;
                veri = 1;
                sprintf(interStatement, "���/%d", i+1); 
                creatButton(&choice[i], x, y, 150, 45, interStatement);
                x += 180;
            }
            if (x >= 600) {
                x = 40;
                y += 55;
            }
        }
    }
    else {                                               // δ�ܵ�����
        for (i = 0; i < 10; i++) {
            switch (island[islandChoice].main[i].veri) {
                case 1: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "С��/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 2: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "����/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 3: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "���/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 4: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "��ʦ/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 5: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "����/%d", i + 1);
                    creatButton(&choice[i], x, y, 150, 45, interStatement);
                    x += 180;
                    veri = 1;
                    break;
                }
                case 6: {
                    positionVeri[i] = 1;
                    sprintf(interStatement, "����/%d", i + 1);
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

// ����������
int sortAttacker(int peopleNum, int* islandChoice, char* attackerVeri) {
    int veriCannon = 1, i = 0;
    int x = 80, y = 330;
    
    clear();
    // Զ�����ڼ��� 
    if (peopleNum == 1) {
        if (island[0].troop[4]) {
            creatButton(&choice[i], x, y, 120, 50, "����");
            attackerVeri[i++] = 'q';
            x += 170;
            veriCannon = 0;
        }
    }
    else {
        if (island[2].troop[4]) {
            creatButton(&choice[i], x, y, 120, 50, "����");
            attackerVeri[i++] = 'q';
            x += 170;
            veriCannon = 0;
        }
    }
    // ��Զ�̹������� 
    if (island[1].owner == peopleNum) { // �м䵺�������
        if (island[1].troop[4] && veriCannon) {
            creatButton(&choice[i], x, y, 120, 50, "����");
            attackerVeri[i++] = 'q';
            x += 170;
        }
        if ((peopleNum == 1 && islandIsland[2].HP) || (peopleNum == 2 && islandIsland[1].HP)) { // ���ţ���ս��Ч
            if (island[1].troop[3]) {
                creatButton(&choice[i], x, y, 120, 50, "��ʦ");
                attackerVeri[i++] = 'f';
                x += 170;
            }
            if (island[1].troop[1]) {
                creatButton(&choice[i], x, y, 120, 50, "����");
                attackerVeri[i++] = 'p';
                x += 170;
            }
            else if (island[1].troop[0]) {
                creatButton(&choice[i], x, y, 120, 50, "С��");
                attackerVeri[i++] = 'x';
                x += 170;
            }
        }
        // ����Ŀ�굺���� 
        if (peopleNum == 1) {
            *islandChoice = 2;
        }
        else {
            *islandChoice = 0;
        }
    }
    else if (island[1].owner == 0) { // �м䵺δ��ռ��
        // �������
    }
    else { // �м䵺���ܹ�����
        if (islandIsland[peopleNum].HP) { // ���ţ���ս��Ч
            if (peopleNum == 1) {
                if (island[0].troop[3]) {
                    creatButton(&choice[i], x, y, 120, 50, "��ʦ");
                    attackerVeri[i++] = 'f';
                    x += 170;
                }
                if (island[0].troop[1]) {
                    creatButton(&choice[i], x, y, 120, 50, "����");
                    attackerVeri[i++] = 'p';
                    x += 170;
                }
                else if (island[0].troop[0]) {
                    creatButton(&choice[i], x, y, 120, 50, "С��");
                    attackerVeri[i++] = 'x';
                    x += 170;
                }
            }
            else {
                if (island[2].troop[3]) {
                    creatButton(&choice[i], x, y, 120, 50, "��ʦ");
                    attackerVeri[i++] = 'f';
                    x += 170;
                }
                if (island[2].troop[1]) {
                    creatButton(&choice[i], x, y, 120, 50, "����");
                    attackerVeri[i++] = 'p';
                    x += 170;
                }
                else if (island[2].troop[0]) {
                    creatButton(&choice[i], x, y, 120, 50, "С��");
                    attackerVeri[i++] = 'x';
                    x += 170;
                }
            }
        }
        // ����Ŀ�굺����
        *islandChoice = 1;
    }
    if (people[peopleNum - 1].bombNum) {
        if (i < 4) {
            creatButton(&choice[i], x, y, 120, 50, "�˵�");
            attackerVeri[i++] = 'h';
        }
        else {
            creatButton(&choice[i], 345, 420, 120, 50, "�˵�");
            attackerVeri[i++] = 'h';
        }
    }
    return i;
}