#include "help.h"
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// 全局变量定义
Button choice[10];  // 按钮数组
ExMessage msg;      // 消息结构

// 检查按钮是否被点击
int click(Button choice) {
	return msg.message == WM_LBUTTONDOWN &&
		msg.x >= choice.x && msg.x <= choice.x + choice.w &&
		msg.y >= choice.y && msg.y <= choice.y + choice.h;
}


// 创建按钮
void creatButton(Button* m, int x, int y, int w, int h, const char* text) {
	m->x = x;
	m->y = y;
	m->w = w;
	m->h = h;

	// 设置填充颜色为白色
	setfillcolor(YELLOW);
	// 设置边框颜色（如果需要边框）
	solidrectangle(x, y, x + w, y + h);

	// 设置文字颜色和字体
	setbkmode(TRANSPARENT);  // 设置文字背景为透明

	settextcolor(BLACK);
	settextstyle(24, 0, "宋体");

	// 计算文字绘制位置，使其居中
	int tx_ = x + (w - textwidth(text)) / 2;
	int ty_ = y + (h - textheight(text)) / 2;

	// 绘制文字
	outtextxy(tx_, ty_, text);
}
void openInstructions(const char* fileName, int x, int y) {
	FILE* fin = fopen(fileName, "r");
	if (!fin) {
		MessageBox(GetHWnd(), "无法打开说明文件！", "错误", MB_OK | MB_ICONERROR);
		return;
	}

	// 背景图与文字设置
	IMAGE img;
	loadimage(&img, "./picture/游戏说明背景.jpg", 750, 490);
	setbkcolor(WHITE);
	settextcolor(WHITE);
	settextstyle(18, 0, "宋体");

	// 读取所有行
	char* lines[1000];
	int lineCount = 0;
	char buffer[10000];
	while (fgets(buffer, sizeof(buffer), fin) && lineCount < 1000) {
		size_t len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';  // 去换行符
		lines[lineCount] = (char*)malloc(strlen(buffer) + 1);
		strcpy(lines[lineCount], buffer);
		lineCount++;
	}
	fclose(fin);

	// 计算每页行数
	int lineHeight = textheight("测试");
	int maxLines = getheight()/ (lineHeight + 4);  // 保留底部空间给按钮
	int totalPages = (lineCount + maxLines - 1) / maxLines;
	int currentPage = 0;

	Button nextBtn, prevBtn;

	while (1) {
		// 绘制背景和按钮
		putimage(0, 0, &img);

		// 设置按钮
		if (currentPage > 0)
			creatButton(&prevBtn, 450, 420, 120, 40, "上一页");
		creatButton(&nextBtn, 580, 420, 120, 40, (currentPage < totalPages - 1) ? "下一页" : "返回");
		settextcolor(WHITE);
		settextstyle(18, 0, "宋体");

		// 显示文本内容
		int start = currentPage * maxLines;
		int end = (start + maxLines < lineCount) ? (start + maxLines) : lineCount;

		int curY = y;
		for (int i = start; i < end; ++i) {
			outtextxy(x, curY, lines[i]);
			curY += lineHeight + 4;
		}

		// 等待鼠标点击
		while (1) {
			if (peekmessage(&msg, EX_MOUSE)) {
				if (currentPage > 0 && click(prevBtn)) {
					currentPage--;
					break;
				}
				if (click(nextBtn)) {
					if (currentPage < totalPages - 1) {
						currentPage++;
						break;
					}
					else {
						// 清理资源并返回
						for (int i = 0; i < lineCount; ++i)
							free(lines[i]);
						return;
					}
				}
				
			}
		}
	}
}

int main() {
	void gameTwoPeople();// 双人对战
	void peopleAi();	// 人机对战
	void openInstructions(const char* fileName, int x, int y);// 输出文档

	Button startGame, close;
	int veri;
	IMAGE img;
	initgraph(750, 490, 1);
	while (1) {//菜单选择
		loadimage(&img, "./picture/菜单背景.jpg", 750, 490);
		putimage(0, 0, &img);
		HWND hnd = GetHWnd();
		SetWindowText(hnd, "菜单");
		creatButton(&startGame, 110, 80, 150, 50, "和平岛");
		creatButton(&close, 480, 80, 150, 50, "关闭游戏");
		//system("pause");
		// 判断点击
		while (1) {
			veri = 0;
			if (peekmessage(&msg, EX_MOUSE)) {
				// 进入和平岛
				if (click(startGame)) {
					while (1) {
						PlaySoundA(NULL, NULL, 0);
						// 关闭音乐
						initgraph(750, 490, 1);
						HWND hnd = GetHWnd();
						SetWindowText(hnd, "和平岛");
						loadimage(&img, "./picture/和平岛背景.jpg", 750, 490);
						putimage(0, 0, &img);

						creatButton(&choice[0], 110, 80, 150, 50, "进入游戏");
						creatButton(&choice[1], 480, 80, 150, 50, "游戏说明");
						creatButton(&choice[2], 110, 300, 150, 50, "返回菜单");
						creatButton(&choice[3], 480, 300, 150, 50, "关闭游戏");
						while (1) {			// 判断点击
							if (peekmessage(&msg, EX_MOUSE)) {
								if (click(choice[0])) {
									//进入游戏
									gameTwoPeople();
									break;
								}
								else if (click(choice[1])) {
									//游戏说明
									openInstructions("./游戏玩法介绍.txt", 0, 0);
									break;
								}
								else if (click(choice[2])) {
									veri = 1;
									//应回菜单
									break;
								}
								else if (click(choice[3])) {//关闭游戏
									exit(0);
								}
							}
						}
						if (veri)
							break;
					}
					if (veri)
						break;
				}
				// 关闭游戏
				else if (click(close)) {
					exit(0);
				}
			}
		}
	}
	closegraph();
	return 0;
}

void peopleAi() {
	// 保留
}