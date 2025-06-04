#include "help.h" 

// ���š����ŵ�������
void placeBridge(int peopleNum) {
    int sortBuildBridge(int peopleNum, int* bridgeVeri);		// �ɼ���λ�ü���
    int sortBreakBridge(int peopleNum, int* bridgeVeri);		// �ɲ���λ�ü���

    int bridgeChoice, choiceNum = 1, veri;
    int bridgeVeri[2] = { 0 };
    IMAGE imgChoice;

    printIsland();
    outtextxy(tx, ty, "��ѡ�������");
    creatButton(&choice[0], 130, 350, 150, 50, "����");
    creatButton(&choice[1], 450, 350, 150, 50, "����");
    while (1) {			//�жϵ��
        if (peekmessage(&msg, EX_MOUSE)) {
            if (click(choice[0])) {					    // ����
                clear();
                veri = sortBuildBridge(peopleNum, bridgeVeri);
                if (veri) {
                    clear();
                    outtextxy(tx, ty, "û�п��Լܵ��ţ����β������ϣ�");
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
            else if (click(choice[1])) {				// ����
                clear();
                veri = sortBreakBridge(peopleNum, bridgeVeri);
                if (veri) {
                    clear();
                    outtextxy(tx, ty, "û�п��Բ���ţ����β������ϣ�");
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

// �ɼ���λ�ü���
int sortBuildBridge(int peopleNum, int* bridgeVeri) {
    int i, veri = 1;
    int x = 130, y = 350;
    char interStation[10];

    clear();
    outtextxy(tx, ty, "��ѡ��Ҫ�ܵ���");
    for (i = 1; i < 3; i++) {
        if (islandIsland[i].HP == 0 && (island[i].owner == peopleNum && island[i].num || island[i - 1].owner == peopleNum && island[i - 1].num)) {
            sprintf(interStation, "%d����", i);
            creatButton(&choice[i-1], x, y, 150, 50, interStation);
            bridgeVeri[i-1] = 1;
            x += 320;
            veri = 0;
        }
    }
    return veri;
}

// �ɲ���λ�ü���
int sortBreakBridge(int peopleNum, int* bridgeVeri) {
    int i, veri = 1;
    int x = 130, y = 350;
    char interStation[10];

    clear();
    outtextxy(tx, ty, "��ѡ��Ҫ�����");
    for (i = 1; i < 3; i++) {
        if (islandIsland[i].HP == 1 && (island[i].owner == peopleNum && island[i].num || island[i - 1].owner == peopleNum && island[i - 1].num)) {
            sprintf(interStation, "%d����", i);
            creatButton(&choice[i - 1], x, y, 150, 50, interStation);
            bridgeVeri[i-1] = 1;
            x += 320;
            veri = 0;
        }
    }
    return veri;
}