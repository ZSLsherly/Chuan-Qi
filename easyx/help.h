#ifndef _FUN_H
#define _FUN_H

//����ͷ�ļ������� 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <easyx.h>
#include <conio.h>
#include <iostream>

// ����������� ��Ĭ�ϣ�3 
#define LIMIT 3
// ���Կ��أ�0-�أ�1-��
#define TEST 0

// ���������λ��
#define tx 20
#define ty 290


// ��ť�ṹ��
typedef struct button {
    int x;
    int y;
    int w;
    int h;
}Button;

//��ҽṹ��
typedef struct PeopleAttribute {	// ���ֱ������
    int accumulateNum; 				// �͵Ĵ���
    int bombNum;      				// �˵���
    int houseNum;   	  			// ������
} PeopleAttribute;

/******************������*********************/
typedef struct IslandPosition { // ���ϵ���λ������
    int HP;                    // ���������ϵı���Ѫ��
    int veri;                  // �ж����λ����ʲô����С���֣��򣬷����ᣬ��
} IslandPosition;

typedef struct IslandAll {       // ��������
    IslandPosition main[10];     // 3����Ҫλ��
    int limit;                   // �жϵ������ű�����
    int num;                     // �жϵ������м���
    int owner;                   // �ж�����Ȩ
    int troop[5];                // �жϱ�������С���֣��򣬷�����
} IslandAll;

typedef struct Bridge {           // �ŵ�����
    int HP;
} Bridge;
/******************������*********************/


// ���ò�������
extern int usedBombNum;					// ��¼�ù��ĺ˵���
extern char interStatement[20];         // ������Ϣ����
extern PeopleAttribute people[2]; 		// �����˵�ֱ������
extern IslandAll island[3];             // ����������
extern Bridge islandIsland[3]; 			// ������֮�����
extern Button choice[10];               // Ԥ����ť
extern ExMessage msg;                   // ������Ϣ����


// ����������ʼ 
void printIsland();					                    // չʾս�� 
int click(Button choice);                               // �������
void clear();                                           // ��ղ�����
void placeArm(int peopleNum);                           // �ű�������
void placeBridge(int peopleNum);                        // ���š����ŵ�������
void attack(int peopleNum);                             // ����������
void houseSoldier(int peopleNum);                       // ���ӳ���
void creatButton(Button* m, int x, int y, int w, int h, const char* text);  // ���첢�����ť


#endif 