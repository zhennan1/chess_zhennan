/*国际象棋（C语言） 2022年5月
作者：万振南 2021030014
编译环境：Visual Studio 2022
EasyX版本：EasyX_20220116
程序使用说明书*/;

#undef UNICODE
#undef _UNICODE

#include <easyx.h>  
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

/*函数声明*/;

void initial();    //开始
void info();       //信息
void chessboard(); //棋盘
void click();      //鼠标点击
void round();      //一个回合

int wKing(int a[2]);    //白方国王行棋规则
int wQueen(int a[2]);   //白方王后行棋规则
int wBishop(int a[2]);  //白方两象行棋规则
int wKnight(int a[2]);  //白方两马行棋规则
int wRook(int a[2]);    //白方两车行棋规则
int wPawn(int a[2]);    //白方士兵行棋规则

int bKing(int a[2]);    //黑方国王行棋规则
int bQueen(int a[2]);   //黑方王后行棋规则
int bBishop(int a[2]);  //黑方两象行棋规则
int bKnight(int a[2]);  //黑方两马行棋规则
int bRook(int a[2]);    //黑方两车行棋规则
int bPawn(int a[2]);    //黑方士兵行棋规则

int wEat(int a[2]);     //判断白棋能否吃黑棋，若能则执行
int bEat(int a[2]);     //判断黑棋能否吃白棋，若能则执行
int wBlock(int a[2]);   //判断该位置有无白棋，从而判断能否落子
int bBlock(int a[2]);   //判断该位置有无黑棋，从而判断能否落子

void judge();           //判断比赛是否决出胜负，以及谁胜谁负
void putw();            //依据坐标绘制黑棋图像
void putb();            //摆放黑棋
void display();         //更新棋盘

/*全局变量*/;

//定义图像变量：p01~p06,p11~p16
IMAGE p01, p02, p03, p04, p05, p06;  //白棋王、后、象、马、车、兵
IMAGE p11, p12, p13, p14, p15, p16;  //黑棋王、后、象、马、车、兵

int a = 360, b = 600, c = 40;        //a：开始界面长度；b：开始界面宽度；c：图标边长
int le = 100, wi = 100;              //le：棋子、格子长度；wi：棋子、格子长度

//i，j：计数；k：同种棋子序号；n：可行格子序号；p：暂时性同种棋子序号，用于put，block，eat等
int i = 0, j = 0, k = 0, n = 0, p = 0, bn = 0, wn = 0;

//yn1, yn2, yn3:用于记录对话框选择的结果
int yn1 = 0, yn2 = 0, yn3 = 0;
int sign = 0;  //sign：用于判断单次操作是否完成
int mark = 0;  //mark: 用于判断棋子是否能落在某处
int wb = 0;    //判断是白方还是黑方正在下棋

//用于判断王车易位是否可行，1表示可以，0表示不可以
int wCastling = 1, wCastling1 = 1, wCastling2 = 1;
int bCastling = 1, bCastling1 = 1, bCastling2 = 1;

//用于判断吃过路兵是否可行，1表示可以，0表示不可以
int wEn_passant = 0, wEn_passantx = 0, wEn_passanty = 0;
int bEn_passant = 0, bEn_passantx = 0, bEn_passanty = 0;

int wCheck = 0;
int bCheck = 0;
int final = 0;  //final：用于判断游戏是否结束

time_t start, now, wt, bt;       //start：游戏开始时刻；now：现在时刻；wt：白方回合开始时刻；bt：黑方回合开始时刻
char s1[100], ws[100], bs[100];  //s1：游戏时间字符串；ws：白方倒计时；bs：黑方倒计时

int wK[2] = { 5,8 };             //wK：白棋国王坐标
int wQ[2] = { 4,8 };             //wQ：白棋皇后坐标
int wB[2][2] = { {3,8},{6,8} };  //wB：白棋两象坐标
int wN[2][2] = { {2,8},{7,8} };  //wN：白棋两马坐标
int wR[2][2] = { {1,8},{8,8} };  //wR：白棋两车坐标
int wP[8][2] = { {1,7},{2,7},{3,7},{4,7},{5,7},{6,7},{7,7},{8,7} };  //wP：白棋士兵坐标

int wQp[8][2];  //wQp：白棋兵升变后坐标
int wBp[8][2];  //wBp：白棋兵升变象坐标
int wNp[8][2];  //wNp：白棋兵升变马坐标
int wRp[8][2];  //wRp：白棋兵升变车坐标

int bK[2] = { 5,1 };             //bK：黑棋国王坐标
int bQ[2] = { 4,1 };             //bQ：黑棋王后坐标
int bB[2][2] = { {3,1},{6,1} };  //bB：黑棋两象坐标
int bN[2][2] = { {2,1},{7,1} };  //bN：黑棋两马坐标
int bR[2][2] = { {1,1},{8,1} };  //bR：黑棋两车坐标
int bP[8][2] = { {1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2} };  //bP：黑棋士兵坐标

int bQp[8][2];  //bQp：黑棋兵升变后坐标
int bBp[8][2];  //bBp：黑棋兵升变象坐标
int bNp[8][2];  //bNp：黑棋兵升变马坐标
int bRp[8][2];  //bRp：黑棋兵升变车坐标

int D[65][2] = { '\0' }; //可行域
int mx = -1, my = -1;    //鼠标位置
int xm = -1, ym = -1;    //鼠标坐标
int x[2] = { -1,-1 }, y[2] = { -1,-1 };	//坐标
int temp[2] = { -1,-1 }; //暂时性坐标

//开始
void initial()  //开始
{
	initgraph(a, b);
	setbkcolor(WHITE);
	IMAGE i1;
	loadimage(&i1, ("initial.png"), a, b, TRUE);//读取开始界面背景图片
	putimage(0, 0, &i1);
	IMAGE i2;
	loadimage(&i2, ("info.jpg"), c, c, TRUE);//读取设置图片
	putimage(a - c, b - c, &i2);
	fillcircle(a / 2, 0, 300);
	settextstyle(50, 25, "楷体");
	settextcolor(BLACK);
	outtextxy(a / 2 - 100, 50, "国际象棋");
	settextstyle(60, 30, "Consolas");
	outtextxy(a / 2 - 100, 150, " CHESS ");     //打印CHESS
	settextstyle(40, 20, 0);
	settextcolor(DARKGRAY);
	outtextxy(a / 2 - 60, b - 200, " PLAY ");   //打印PLAY
	settextcolor(DARKGRAY);
	outtextxy(a / 2 - 60, b - 120, " EXIT ");   //打印EXIT
	while (1)
	{
		int flag = 0;
		ExMessage m;  //定义消息变量
		m = getmessage(EM_MOUSE | EM_KEY);  //从鼠标处获得消息
		switch (m.message)
		{
		case (WM_LBUTTONDOWN):  //鼠标左键点击后
			if (abs(m.x - a / 2) < 60 && abs(m.y - b + 180) < 20)
			{
				chessboard();
				flag = 1;
			}
			if (abs(m.x - a / 2) < 60 && abs(m.y - b + 100) < 20)
			{
				return;
			}
			else if (m.x > a - c && m.x < a && m.y > b - c && m.y < b)
			{
				info();
			}
		}
		if (flag)
			break;
		rewind(stdin);
	}
}

//信息
void info()  //设置
{
	cleardevice();
	settextstyle(40, 15, "Times New Roman");
	settextcolor(DARKGRAY);
	outtextxy(a / 2 - 50, 50, " INFO ");
	settextstyle(30, 10, "Times New Roman");
	outtextxy(20, 120, "");
	outtextxy(20, 160, "国际象棋（C语言）");
	outtextxy(20, 200, "Visual Studio 2022");
	outtextxy(20, b - 40, "按ENTER键返回……");
	rewind(stdin);
	getchar();
	initial();
}

//棋盘
void chessboard()  //棋盘初始化
{
	initgraph(le * 8 + 400, wi * 8 + 100);  //创建自定义大小窗口（默认1200 * 900）
	cleardevice();  //刷新
	IMAGE i21;
	loadimage(&i21, ("initial.png"), le * 8 + 400, wi * 8 + 100, TRUE);	//读取棋盘界面背景图片
	putimage(0, 0, &i21);
	//绘制黑白相间的格子
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (k == 0)
				setfillcolor(WHITE);
			else if (k == 1)
				setfillcolor(DARKGRAY);
			solidrectangle(200 + le * i, 50 + wi * j, 200 + le * (i + 1), 50 + wi * (j + 1));
			k = 1 - k;
		}
		k = 1 - k;
	}
	display();
	IMAGE pp, pg, ph, pe;
	loadimage(&pp, ("peace.jpg"), 40, 40, TRUE);
	putimage(20, 50, &pp);
	loadimage(&pg, ("flag.jpg"), 40, 40, TRUE);
	putimage(20, 120, &pg);
	loadimage(&ph, ("history.jpg"), 40, 40, TRUE);
	//putimage(20, 140, &ph);
	loadimage(&pe, ("exit.jpg"), 72, 72, TRUE);
	putimage(280 + le * 8, 50, &pe);
	setbkcolor(WHITE);
	settextstyle(40, 18, "隶书");
	settextcolor(BLACK);
	outtextxy(60, 50, "求和");
	outtextxy(60, 120, "认输");
	//outtextxy(60, 140, "历史");
	outtextxy(280 + le * 8, 122, "退出");
	setfillcolor(WHITE);
	fillcircle(200 + le * 4, -300, 340);
	setfillcolor(BLACK);
	fillcircle(60, 4 * wi + 20, 40);
	start = clock();
	while (1)
	{
		round();
		judge();
		if (final == 1)
		{
			MessageBox(NULL, "WINNER: WHITE", "FINAL_RESULT", MB_OK | MB_SYSTEMMODAL);
			printf("WINNER: WHITE");
			break;
		}
		if (final == 2)
		{
			MessageBox(NULL, "WINNER: BLACK", "FINAL_RESULT", MB_OK | MB_SYSTEMMODAL);
			printf("WINNER: BLACK");
			break;
		}
		if (final == 3)
		{
			MessageBox(NULL, "DRAW", "FINAL_RESULT", MB_OK | MB_SYSTEMMODAL);
			printf("DRAW");
			break;
		}
	}
}

//鼠标点击
void click()
{
	FlushBatchDraw();
	i = 0, j = 0;
	int duration = 0, minute = 0, second = 0;
	int wduration = 0, bduration = 0;
	ExMessage m; //鼠标
	while (1)
	{
		now = clock();
		duration = int(now - start) / 1000;  //游戏总时长，化为秒
		minute = duration / 60;  //化为分
		second = duration % 60;  //化为秒
		wduration = 60 - int(now - wt) / 1000;  //白方倒计时
		bduration = 60 - int(now - bt) / 1000;  //黑方倒计时
		sprintf_s(s1, "Time: %d min %d s", minute, second); //时间：xx分xx秒
		sprintf_s(ws, "%d s", wduration);  //白方倒计时字符串
		sprintf_s(bs, "%d s", bduration);  //黑方倒计时字符串
		setbkcolor(WHITE);
		settextcolor(BLACK);
		settextstyle(30, 10, "Times New Roman");
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(200 + le * 4, -300, 340);
		outtextxy(120 + le * 4, 0, s1);
		if (wb == 1 && wduration >= 0)  //若是白方回合
		{
			setfillcolor(WHITE);
			fillcircle(60, 4 * wi + 80, 40);
			setlinecolor(GREEN);
			outtextxy(40, 80 + le * 4, ws);    //打印白方倒计时字符串
			setbkcolor(BLACK);
			settextcolor(WHITE);
			outtextxy(40, le * 4, "60 s");     //打印60s
		}
		if (wb == -1 && bduration >= 0)  //若是黑方回合
		{
			setfillcolor(BLACK);
			fillcircle(60, 4 * wi + 20, 40);
			setlinecolor(GREEN);
			outtextxy(40, 80 + le * 4, "60 s");//打印60s
			setbkcolor(BLACK);
			settextcolor(WHITE);
			outtextxy(40, le * 4, bs);   //打印黑方倒计时字符串
		}
		FlushBatchDraw();
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			if (m.message == WM_LBUTTONDOWN)
			{
				mx = m.x;
				my = m.y;
				//获取离鼠标最近的点的坐标信息
				for (i = 1; i <= 8; i++)
				{
					for (j = 1; j <= 8; j++)
					{
						if (abs(m.x + le / 2 - i * le - 200) < 50 && abs(m.y + wi / 2 - j * wi - 50) < 50)
						{
							xm = i;
							ym = j;
						}
					}
				}
				break;
			}
		}
		setlinecolor(GREEN);
		FlushBatchDraw();
	}
	i = 0, j = 0;
}

//一个回合
void round()
{
	BeginBatchDraw();
	setlinecolor(GREEN);
	wt = clock();
	while (1)
	{
		wb = 1;
		sign = 0;
		mark = 0;
		for (n = 0; n <= 63; n++)
		{
			D[n][0] = 0;
			D[n][1] = 0;
		}
		n = 0;
		click();
		x[0] = xm;
		y[0] = ym;
		//和棋
		if (mx >= 20 && mx <= 140 && my >= 50 && my <= 90)
		{
			yn1 = MessageBox(NULL, "你想要请求和棋吗？\nDo you want to ask for a draw?", "DRAW", MB_YESNO | MB_SYSTEMMODAL);
			if (yn1 == 6)
			{
				yn1 = MessageBox(NULL, "你接受和棋吗？\nDo you accept draw?", "DRAW", MB_YESNO | MB_SYSTEMMODAL);
				if (yn1 == 6)
				{
					final = 3;
					break;
				}
			}
		}
		//认输
		if (mx >= 20 && mx <= 140 && my >= 120 && my <= 160)
		{
			yn2 = MessageBox(NULL, "你想要认输吗？\nDo you want to admit defeat?", "ADMIT_DEFEAT", MB_YESNO | MB_SYSTEMMODAL);
			if (yn2 == 6)
			{
				final = 2;
				break;
			}
		}
		//退出
		if (mx >= 280 + le * 8 && mx <= 360 + le * 8 && my >= 50 && my <= 170)
		{
			yn2 = MessageBox(NULL, "你确定要退出吗？\nAre you sure you want to quit?", "EXIT", MB_YESNO | MB_SYSTEMMODAL);
			if (yn2 == 6)
			{
				final = 2;
				break;
			}
		}

		wKing(wK);

		wQueen(wQ);

		for (k = 0; k < 2; k++)
			wBishop(wB[k]);

		for (k = 0; k < 2; k++)
			wKnight(wN[k]);

		for (k = 0; k < 2; k++)
			wRook(wR[k]);

		bEn_passant = 0;

		for (k = 0; k < 8; k++)
			wPawn(wP[k]);

		for (k = 0; k < 8; k++)
			wQueen(wQp[k]);

		for (k = 0; k < 8; k++)
			wBishop(wBp[k]);

		for (k = 0; k < 8; k++)
			wKnight(wNp[k]);

		for (k = 0; k < 8; k++)
			wRook(wRp[k]);

		display();

		if (sign)
			break;
	}

	judge();

	bt = clock();

	while (1)
	{
		wb = -1;
		if (final != 0)
			break;
		sign = 0;
		mark = 0;
		for (n = 0; n <= 63; n++)
		{
			D[n][0] = 0;
			D[n][1] = 0;
		}
		n = 0;
		click();
		x[0] = xm;
		y[0] = ym;
		if (mx >= 20 && mx <= 140 && my >= 50 && my <= 90)
		{
			yn1 = MessageBox(NULL, "你想要请求和棋吗？\nDo you want to ask for a draw?", "DRAW", MB_YESNO | MB_SYSTEMMODAL);
			if (yn1 == 6)
			{
				yn1 = MessageBox(NULL, "你接受和棋吗？\nDo you accept draw?", "DRAW", MB_YESNO | MB_SYSTEMMODAL);
				if (yn1 == 6)
				{
					final = 3;
					break;
				}
			}
		}
		if (mx >= 20 && mx <= 140 && my >= 120 && my <= 160)
		{
			yn2 = MessageBox(NULL, "你想要认输吗？\nDo you want to admit defeat?", "ADMIT_DEFEAT", MB_YESNO | MB_SYSTEMMODAL);
			if (yn2 == 6)
			{
				final = 1;
				break;
			}
		}
		if (mx >= 280 + le * 8 && mx <= 360 + le * 8 && my >= 50 && my <= 170)
		{
			yn2 = MessageBox(NULL, "你确定要退出吗？\nAre you sure you want to quit?", "EXIT", MB_YESNO | MB_SYSTEMMODAL);
			if (yn2 == 6)
			{
				final = 1;
				break;
			}
		}
		bKing(bK);

		bQueen(bQ);

		for (k = 0; k < 2; k++)
			bBishop(bB[k]);

		for (k = 0; k < 2; k++)
			bKnight(bN[k]);

		for (k = 0; k < 2; k++)
			bRook(bR[k]);

		wEn_passant = 0;

		for (k = 0; k < 8; k++)
			bPawn(bP[k]);

		for (k = 0; k < 8; k++)
			bQueen(bQp[k]);

		for (k = 0; k < 8; k++)
			bBishop(bBp[k]);

		for (k = 0; k < 8; k++)
			bKnight(bNp[k]);

		for (k = 0; k < 8; k++)
			bRook(bRp[k]);

		display();

		if (sign)
			break;
	}
	EndBatchDraw();
}


/*行棋规则*/;

//白方国王行棋规则
int wKing(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (i = -1; i <= 1; i++)
			for (j = -1; j <= 1; j++)
				if ((i != 0 || j != 0) && (a[0] + i >= 1 && a[0] + i <= 8 && a[1] + j >= 1 && a[1] + j <= 8))
				{
					temp[0] = a[0] + i;
					temp[1] = a[1] + j;
					wBlock(temp);
					if (mark == 0)
					{
						D[n][0] = temp[0];
						D[n][1] = temp[1];
						n++;
					}
				}
		if (wCastling == 1)  //王未移动过
		{
			if (wCastling1 == 1)  //车1未移动过
			{
				for (i = 1; i < 4; i++)
				{
					temp[0] = a[0] - i;
					temp[1] = a[1];
					wBlock(temp);
					if (mark == 1)
						break;
					bBlock(temp);
					if (mark == 1)
						break;
				}
				if (mark == 0)    //王和车之间没有棋子
				{
					D[n][0] = a[0] - 2;  //记入王的可行域
					D[n][1] = a[1];
					n++;
				}
			}
			if (wCastling2 == 1)
			{
				for (i = 1; i < 3; i++)
				{
					temp[0] = a[0] + i;
					temp[1] = a[1];
					wBlock(temp);
					if (mark == 1)
						break;
					bBlock(temp);
					if (mark == 1)
						break;
				}
				if (mark == 0)
				{
					D[n][0] = a[0] + 2;
					D[n][1] = a[1];
					n++;
				}
			}
		}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				if (x[1] == a[0] - 2)
				{
					wR[0][0] = 4;
				}
				if (x[1] == a[0] + 2)
				{
					wR[1][0] = 6;
				}
				a[0] = D[n][0];
				a[1] = D[n][1];
				sign = 1;
				wCastling = 0;
				break;
			}
		}
		wEat(a);
	}
	return 0;
}

//白方王后行棋规则（行棋规则示例）
int wQueen(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])  //判断鼠标单击位置是否为白方王后，若是则执行
	{
		for (i = 1; i <= 7; i++)       //后每个坐标最多移动7，这里从近（1）到远（7）
			if (a[0] - i >= 1 && a[0] - i <= 8)  //考虑后向左移动，移动坐标不得超过棋盘范围（1-8）
			{
				temp[0] = a[0] - i;    //将假设移动后的横纵坐标写入二维数组temp
				temp[1] = a[1];
				wBlock(temp);          //调用wBlock函数，判断temp处是否有白棋，有则mark=1
				if (mark == 0)
				{
					D[n][0] = temp[0]; //没有阻碍则将temp的横纵坐标写入可行域D
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)         //mark=1说明有白棋，无法再向远移动，因而退出循环
					break;
				bBlock(temp);          //调用bBlock函数，判断temp处是否有黑棋，有则mark=1
				if (mark == 1)         //mark=1说明有黑棋，无法再向远移动，因而退出循环
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0];
				temp[1] = a[1] + i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1];
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0];
				temp[1] = a[1] - i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8 && a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1] + i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8 && a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1] + i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8 && a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1] - i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8 && a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1] - i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (n = 0; n <= 63; n++)
		{
			//在可移动的棋盘格上画绿色圆圈
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();    //获取第二次点击
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])  //若第二次点击是可移动的棋盘格
			{
				a[0] = D[n][0];  //横坐标移动
				a[1] = D[n][1];  //纵坐标移动
				sign = 1;        //移动成功标志
				break;           //移动成功退出循环
			}
		}
		wEat(a);
	}
	return 0;
}

//白方两象行棋规则
int wBishop(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8 && a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1] + i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8 && a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1] + i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8 && a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1] - i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8 && a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1] - i;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				a[0] = D[n][0];
				a[1] = D[n][1];
				sign = 1;
				break;
			}
		}
		wEat(a);
	}
	return 0;
}

//白方两马行棋规则
int wKnight(int a[2])
{
	loadimage(&p04, ("p_04.jpg"), le, wi, TRUE);
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (j = 1; j <= 2; j++)
		{
			if (a[0] + j >= 1 && a[0] + j <= 8 && a[1] + 3 - j >= 1 && a[1] + 3 - j <= 8)
			{
				temp[0] = a[0] + j;
				temp[1] = a[1] + 3 - j;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
			if (a[0] - j >= 1 && a[0] - j <= 8 && a[1] + 3 - j >= 1 && a[1] + 3 - j <= 8)
			{
				temp[0] = a[0] - j;
				temp[1] = a[1] + 3 - j;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
			if (a[0] + j >= 1 && a[0] + j <= 8 && a[1] + j - 3 >= 1 && a[1] + j - 3 <= 8)
			{
				temp[0] = a[0] + j;
				temp[1] = a[1] + j - 3;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
			if (a[0] - j >= 1 && a[0] - j <= 8 && a[1] + j - 3 >= 1 && a[1] + j - 3 <= 8)
			{
				temp[0] = a[0] - j;
				temp[1] = a[1] + j - 3;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
		}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				a[0] = D[n][0];
				a[1] = D[n][1];
				sign = 1;
				break;
			}
		}
		putimage(200 + (a[0] - 1) * le, 50 + (a[1] - 1) * wi, &p04);
		wEat(a);
	}
	return 0;
}

//白方两车行棋规则
int wRook(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (j = 1; j <= 7; j++)
			if (a[0] - j >= 1 && a[0] - j <= 8)
			{
				temp[0] = a[0] - j;
				temp[1] = a[1];
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (j = 1; j <= 7; j++)
			if (a[1] + j >= 1 && a[1] + j <= 8)
			{
				temp[0] = a[0];
				temp[1] = a[1] + j;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (j = 1; j <= 7; j++)
			if (a[0] + j >= 1 && a[0] + j <= 8)
			{
				temp[0] = a[0] + j;
				temp[1] = a[1];
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (j = 1; j <= 7; j++)
			if (a[1] - j >= 1 && a[1] - j <= 8)
			{
				temp[0] = a[0];
				temp[1] = a[1] - j;
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				bBlock(temp);
				if (mark == 1)
					break;
			}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				a[0] = D[n][0];
				a[1] = D[n][1];
				if (k == 0)
					wCastling1 = 0;
				if (k == 1)
					wCastling2 = 0;
				sign = 1;
				break;
			}
		}
		wEat(a);
	}
	return 0;
}

//白方士兵行棋规则
int wPawn(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		if (a[0] >= 1 && a[0] <= 8 && a[1] - 2 >= 1 && a[1] - 2 <= 8 && a[1] == 7)
		{
			temp[0] = a[0];
			temp[1] = a[1] - 1;
			wBlock(temp);
			if (mark == 0)
			{
				bBlock(temp);
				if (mark == 0)
				{
					temp[0] = a[0];
					temp[1] = a[1] - 2;
					wBlock(temp);
					if (mark == 0)
					{
						bBlock(temp);
						if (mark == 0)
						{
							D[n][0] = temp[0];
							D[n][1] = temp[1];
							n++;
						}
					}
				}
			}
		}
		if (a[0] >= 1 && a[0] <= 8 && a[1] - 1 >= 1 && a[1] - 1 <= 8)
		{
			temp[0] = a[0];
			temp[1] = a[1] - 1;
			wBlock(temp);
			if (mark == 0)
			{
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
		}
		if (a[0] - 1 >= 1 && a[0] - 1 <= 8 && a[1] - 1 >= 1 && a[1] - 1 <= 8)
		{
			temp[0] = a[0] - 1;
			temp[1] = a[1] - 1;
			bBlock(temp);
			if (mark == 1)
			{
				D[n][0] = temp[0];
				D[n][1] = temp[1];
				n++;
			}
		}
		if (a[0] + 1 >= 1 && a[0] + 1 <= 8 && a[1] - 1 >= 1 && a[1] - 1 <= 8)
		{
			temp[0] = a[0] + 1;
			temp[1] = a[1] - 1;
			bBlock(temp);
			if (mark == 1)
			{
				D[n][0] = temp[0];
				D[n][1] = temp[1];
				n++;
			}
		}
		if (wEn_passant == 1)  //如果黑方士兵上一回合前进两步
		{
			if (a[0] - 1 == wEn_passantx && a[1] == wEn_passanty)  //判断左边是否为该士兵
			{
				D[n][0] = a[0] - 1;  //若是则记入可行域D
				D[n][1] = a[1] - 1;
			}
			if (a[0] + 1 == wEn_passantx && a[1] == wEn_passanty)  //判断左边是否为该士兵
			{
				D[n][0] = a[0] + 1;  //若是则记入可行域D
				D[n][1] = a[1] - 1;
			}
		}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				if (x[1] == wEn_passantx && y[1] == wEn_passanty - 1)
				{
					for (p = 0; p < 8; p++)
					{
						if (wEn_passantx == bP[p][0] && wEn_passanty == bP[p][1])
						{
							bP[p][0] = -1;  //黑方过路兵被吃掉
							bP[p][1] = -1;
							wEn_passant = 2;
						}
					}
				}
				if (y[1] == a[1] - 2)  //白方士兵前进两步
				{
					bEn_passant = 1;   //黑方有吃过路兵的可能
					bEn_passantx = x[1];
					bEn_passanty = y[1];
				}
				a[0] = D[n][0];
				a[1] = D[n][1];
				wEat(a);
				sign = 1;
				//本方任何一个兵直进达到对方底线时，即可升变为除“王”和“兵”以外的任何一种棋子，可升变为“后”、“车”、“马”、“象”，不能不变。
				if (a[1] == 1)
				{
					yn3 = MessageBox(NULL, "你想变成什么(后、象、马、车）\nWhat do you want to be (Queen, Bishop, Knight, Rook)\n后？\nQueen?", "兵升变", MB_YESNO | MB_SYSTEMMODAL);
					if (yn3 == 6)
					{
						wQp[wn][0] = a[0];    //白棋兵升变后坐标
						wQp[wn][1] = a[1];
						wn++;
						a[0] = -1; a[1] = -1; //原兵被舍弃
					}
					else
					{
						yn3 = MessageBox(NULL, "你想变成什么(后、象、马、车）\nWhat do you want to be (Queen, Bishop, Knight, Rook)\n象？\nBishop?", "兵升变", MB_YESNO | MB_SYSTEMMODAL);
						if (yn3 == 6)
						{
							wBp[wn][0] = a[0];
							wBp[wn][1] = a[1];
							wn++;
							a[0] = -1; a[1] = -1;
						}
						else
						{
							yn3 = MessageBox(NULL, "你想变成什么(后、象、马、车）\nWhat do you want to be (Queen, Bishop, Knight, Rook)\n马？\nKnight?", "兵升变", MB_YESNO | MB_SYSTEMMODAL);
							if (yn3 == 6)
							{
								wNp[wn][0] = a[0];
								wNp[wn][1] = a[1];
								wn++;
								a[0] = -1; a[1] = -1;
							}
							else
							{
								MessageBox(NULL, "你想变成什么(后、象、马、车）\nWhat do you want to be (Queen, Bishop, Knight, Rook)\n车？\nRook?", "兵升变", MB_OK | MB_SYSTEMMODAL);
								wRp[wn][0] = a[0];
								wRp[wn][1] = a[1];
								wn++;
								a[0] = -1; a[1] = -1;
							}
						}
					}
				}
				break;
			}
		}
		wEat(a);
	}
	return 0;
}

//黑方国王行棋规则
int bKing(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (i = -1; i <= 1; i++)
			for (j = -1; j <= 1; j++)
				if ((i != 0 || j != 0) && (a[0] + i >= 1 && a[0] + i <= 8 && a[1] + j >= 1 && a[1] + j <= 8))
				{
					temp[0] = a[0] + i;
					temp[1] = a[1] + j;
					bBlock(temp);
					if (mark == 0)
					{
						D[n][0] = temp[0];
						D[n][1] = temp[1];
						n++;
					}
				}
		if (bCastling == 1)
		{
			if (bCastling1 == 1)
			{
				for (i = 1; i < 4; i++)
				{
					temp[0] = a[0] - i;
					temp[1] = a[1];
					wBlock(temp);
					if (mark == 1)
						break;
					bBlock(temp);
					if (mark == 1)
						break;
				}
				if (mark == 0)
				{
					D[n][0] = a[0] - 2;
					D[n][1] = a[1];
					n++;
				}
			}
			if (bCastling2 == 1)
			{
				for (i = 1; i < 3; i++)
				{
					temp[0] = a[0] + i;
					temp[1] = a[1];
					wBlock(temp);
					if (mark == 1)
						break;
					bBlock(temp);
					if (mark == 1)
						break;
				}
				if (mark == 0)
				{
					D[n][0] = a[0] + 2;
					D[n][1] = a[1];
					n++;
				}
			}
		}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				if (x[1] == a[0] - 2)
				{
					bR[0][0] = 4;
				}
				if (x[1] == a[0] + 2)
				{
					bR[1][0] = 6;
				}
				a[0] = D[n][0];
				a[1] = D[n][1];
				sign = 1;
				bCastling = 0;
				break;
			}
		}
		bEat(a);
	}
	return 0;
}

//黑方王后行棋规则
int bQueen(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1];
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0];
				temp[1] = a[1] + i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1];
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0];
				temp[1] = a[1] - i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8 && a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1] + i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8 && a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1] + i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8 && a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1] - i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8 && a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1] - i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				a[0] = D[n][0];
				a[1] = D[n][1];
				sign = 1;
				break;
			}
		}
		bEat(a);
	}
	return 0;
}

//黑方两象行棋规则
int bBishop(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8 && a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1] + i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8 && a[1] + i >= 1 && a[1] + i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1] + i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] - i >= 1 && a[0] - i <= 8 && a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0] - i;
				temp[1] = a[1] - i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (i = 1; i <= 7; i++)
			if (a[0] + i >= 1 && a[0] + i <= 8 && a[1] - i >= 1 && a[1] - i <= 8)
			{
				temp[0] = a[0] + i;
				temp[1] = a[1] - i;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				a[0] = D[n][0];
				a[1] = D[n][1];
				sign = 1;
				break;
			}
		}
		bEat(bB[k]);
	}
	return 0;
}

//黑方两马行棋规则
int bKnight(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (j = 1; j <= 2; j++)
		{
			if (a[0] + j >= 1 && a[0] + j <= 8 && a[1] + 3 - j >= 1 && a[1] + 3 - j <= 8)
			{
				temp[0] = a[0] + j;
				temp[1] = a[1] + 3 - j;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
			if (a[0] - j >= 1 && a[0] - j <= 8 && a[1] + 3 - j >= 1 && a[1] + 3 - j <= 8)
			{
				temp[0] = a[0] - j;
				temp[1] = a[1] + 3 - j;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
			if (a[0] + j >= 1 && a[0] + j <= 8 && a[1] + j - 3 >= 1 && a[1] + j - 3 <= 8)
			{
				temp[0] = a[0] + j;
				temp[1] = a[1] + j - 3;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
			if (a[0] - j >= 1 && a[0] - j <= 8 && a[1] + j - 3 >= 1 && a[1] + j - 3 <= 8)
			{
				temp[0] = a[0] - j;
				temp[1] = a[1] + j - 3;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
		}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				a[0] = D[n][0];
				a[1] = D[n][1];
				sign = 1;
				break;
			}
		}
		bEat(a);
	}
	return 0;
}

//黑方两车行棋规则
int bRook(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		for (j = 1; j <= 7; j++)
			if (a[0] - j >= 1 && a[0] - j <= 8)
			{
				temp[0] = a[0] - j;
				temp[1] = a[1];
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (j = 1; j <= 7; j++)
			if (a[1] + j >= 1 && a[1] + j <= 8)
			{
				temp[0] = a[0];
				temp[1] = a[1] + j;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (j = 1; j <= 7; j++)
			if (a[0] + j >= 1 && a[0] + j <= 8)
			{
				temp[0] = a[0] + j;
				temp[1] = a[1];
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (j = 1; j <= 7; j++)
			if (a[1] - j >= 1 && a[1] - j <= 8)
			{
				temp[0] = a[0];
				temp[1] = a[1] - j;
				bBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
				if (mark == 1)
					break;
				wBlock(temp);
				if (mark == 1)
					break;
			}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				a[0] = D[n][0];
				a[1] = D[n][1];
				sign = 1;
				if (k == 0)
					bCastling1 = 0;
				if (k == 1)
					bCastling2 = 0;
				break;
			}
		}
		bEat(a);
	}
	return 0;
}

//黑方士兵行棋规则
int bPawn(int a[2])
{
	if (x[0] == a[0] && y[0] == a[1])
	{
		if (a[0] >= 1 && a[0] <= 8 && a[1] + 2 >= 1 && a[1] + 2 <= 8 && a[1] == 2)
		{
			temp[0] = a[0];
			temp[1] = a[1] + 1;
			bBlock(temp);
			if (mark == 0)
			{
				wBlock(temp);
				if (mark == 0)
				{
					temp[0] = a[0];
					temp[1] = a[1] + 2;
					bBlock(temp);
					if (mark == 0)
					{
						wBlock(temp);
						if (mark == 0)
						{
							D[n][0] = temp[0];
							D[n][1] = temp[1];
							n++;
						}
					}
				}
			}
		}
		if (a[0] >= 1 && a[0] <= 8 && a[1] + 1 >= 1 && a[1] + 1 <= 8)
		{
			temp[0] = a[0];
			temp[1] = a[1] + 1;
			bBlock(temp);
			if (mark == 0)
			{
				wBlock(temp);
				if (mark == 0)
				{
					D[n][0] = temp[0];
					D[n][1] = temp[1];
					n++;
				}
			}
		}
		if (a[0] - 1 >= 1 && a[0] - 1 <= 8 && a[1] + 1 >= 1 && a[1] + 1 <= 8)
		{
			temp[0] = a[0] - 1;
			temp[1] = a[1] + 1;
			wBlock(temp);
			if (mark == 1)
			{
				D[n][0] = temp[0];
				D[n][1] = temp[1];
				n++;
			}
		}
		if (a[0] + 1 >= 1 && a[0] + 1 <= 8 && a[1] + 1 >= 1 && a[1] + 1 <= 8)
		{
			temp[0] = a[0] + 1;
			temp[1] = a[1] + 1;
			wBlock(temp);
			if (mark == 1)
			{
				D[n][0] = temp[0];
				D[n][1] = temp[1];
				n++;
			}
		}
		if (bEn_passant == 1)
		{
			if (a[0] - 1 == bEn_passantx && a[1] == bEn_passanty)
			{
				D[n][0] = a[0] - 1;
				D[n][1] = a[1] + 1;
			}
			if (a[0] + 1 == bEn_passantx && a[1] == bEn_passanty)
			{
				D[n][0] = a[0] + 1;
				D[n][1] = a[1] + 1;
			}
		}
		for (n = 0; n <= 63; n++)
		{
			if (D[n][0] >= 1 && D[n][0] <= 8 && D[n][1] >= 1 && D[n][1] <= 8)
				ellipse(200 + (D[n][0] - 1) * le, 50 + (D[n][1] - 1) * wi, 200 + D[n][0] * le, 50 + D[n][1] * wi);
		}
		click();
		x[1] = xm;
		y[1] = ym;
		for (n = 0; n <= 63; n++)
		{
			if (x[1] == D[n][0] && y[1] == D[n][1])
			{
				if (x[1] == bEn_passantx && y[1] == bEn_passanty + 1)
				{
					for (p = 0; p < 8; p++)
					{
						if (bEn_passantx == wP[p][0] && bEn_passanty == wP[p][1])
						{
							wP[p][0] = -1;
							wP[p][1] = -1;
							bEn_passant = 2;
						}
					}
				}
				if (y[1] == a[1] + 2)
				{
					wEn_passant = 1;
					wEn_passantx = x[1];
					wEn_passanty = y[1];
				}
				a[0] = D[n][0];
				a[1] = D[n][1];
				bEat(a);
				sign = 1;
				//本方任何一个兵直进达到对方底线时，即可升变为除“王”和“兵”以外的任何一种棋子，可升变为“后”、“车”、“马”、“象”，不能不变。
				if (a[1] == 8)
				{
					yn3 = MessageBox(NULL, "你想变成什么(后、象、马、车）\nWhat do you want to be (Queen, Bishop, Knight, Rook)\n后？\nQueen?", "兵升变", MB_YESNO | MB_SYSTEMMODAL);
					if (yn3 == 6)
					{
						bQp[bn][0] = a[0];
						bQp[bn][1] = a[1];
						bn++;
						a[0] = -1; a[1] = -1;
					}
					else
					{
						yn3 = MessageBox(NULL, "你想变成什么(后、象、马、车）\nWhat do you want to be (Queen, Bishop, Knight, Rook)\n象？\nBishop?", "兵升变", MB_YESNO | MB_SYSTEMMODAL);
						if (yn3 == 6)
						{
							bBp[bn][0] = a[0];
							bBp[bn][1] = a[1];
							bn++;
							a[0] = -1; a[1] = -1;
						}
						else
						{
							yn3 = MessageBox(NULL, "你想变成什么(后、象、马、车）\nWhat do you want to be (Queen, Bishop, Knight, Rook)\n马？\nKnight?", "兵升变", MB_YESNO | MB_SYSTEMMODAL);
							if (yn3 == 6)
							{
								bNp[bn][0] = a[0];
								bNp[bn][1] = a[1];
								bn++;
								a[0] = -1; a[1] = -1;
							}
							else
							{
								MessageBox(NULL, "你想变成什么(后、象、马、车）\nWhat do you want to be (Queen, Bishop, Knight, Rook)\n车？\nRook?", "兵升变", MB_OK | MB_SYSTEMMODAL);
								bRp[bn][0] = a[0];
								bRp[bn][1] = a[1];
								bn++;
								a[0] = -1; a[1] = -1;
							}
						}
					}
				}
				break;
			}
		}
		bEat(a);
	}
	return 0;
}


/*判断*/

//判断白棋能否吃黑棋，若能则执行
int wEat(int a[2])
{
	if (a[0] == bK[0] && a[1] == bK[1])
	{
		bK[0] = -1;
		bK[1] = -1;
	}
	if (a[0] == bQ[0] && a[1] == bQ[1])
	{
		bQ[0] = -1;
		bQ[1] = -1;
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == bB[p][0] && a[1] == bB[p][1])
		{
			bB[p][0] = -1;
			bB[p][1] = -1;
		}
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == bN[p][0] && a[1] == bN[p][1])
		{
			bN[p][0] = -1;
			bN[p][1] = -1;
		}
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == bR[p][0] && a[1] == bR[p][1])
		{
			bR[p][0] = -1;
			bR[p][1] = -1;
		}
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bP[p][0] && a[1] == bP[p][1])
		{
			bP[p][0] = -1;
			bP[p][1] = -1;
		}
	}
	//考虑兵升变
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bQp[p][0] && a[1] == bQp[p][1])
		{
			bQp[p][0] = -1;
			bQp[p][1] = -1;
		}
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bBp[p][0] && a[1] == bBp[p][1])
		{
			bBp[p][0] = -1;
			bBp[p][1] = -1;
		}
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bNp[p][0] && a[1] == bNp[p][1])
		{
			bNp[p][0] = -1;
			bNp[p][1] = -1;
		}
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bRp[p][0] && a[1] == bRp[p][1])
		{
			bRp[p][0] = -1;
			bRp[p][1] = -1;
		}
	}
	return 0;
}

//判断黑棋能否吃白棋，若能则执行
int bEat(int a[2])
{
	if (a[0] == wK[0] && a[1] == wK[1])
	{
		wK[0] = -1;
		wK[1] = -1;
	}
	if (a[0] == wQ[0] && a[1] == wQ[1])
	{
		wQ[0] = -1;
		wQ[1] = -1;
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == wB[p][0] && a[1] == wB[p][1])
		{
			wB[p][0] = -1;
			wB[p][1] = -1;
		}
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == wN[p][0] && a[1] == wN[p][1])
		{
			wN[p][0] = -1;
			wN[p][1] = -1;
		}
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == wR[p][0] && a[1] == wR[p][1])
		{
			wR[p][0] = -1;
			wR[p][1] = -1;
		}
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wP[p][0] && a[1] == wP[p][1])
		{
			wP[p][0] = -1;
			wP[p][1] = -1;
		}
	}
	//考虑兵升变
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wQp[p][0] && a[1] == wQp[p][1])
		{
			wQp[p][0] = -1;
			wQp[p][1] = -1;
		}
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wBp[p][0] && a[1] == wBp[p][1])
		{
			wBp[p][0] = -1;
			wBp[p][1] = -1;
		}
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wNp[p][0] && a[1] == wNp[p][1])
		{
			wNp[p][0] = -1;
			wNp[p][1] = -1;
		}
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wRp[p][0] && a[1] == wRp[p][1])
		{
			wRp[p][0] = -1;
			wRp[p][1] = -1;
		}
	}
	return 0;
}

//判断该位置有无白棋，从而判断能否落子
int wBlock(int a[2])
{
	mark = 0;
	if (a[0] == wK[0] && a[1] == wK[1])
		mark = 1;
	if (a[0] == wQ[0] && a[1] == wQ[1])
		mark = 1;
	for (p = 0; p < 2; p++)
	{
		if (a[0] == wB[p][0] && a[1] == wB[p][1])
			mark = 1;
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == wN[p][0] && a[1] == wN[p][1])
			mark = 1;
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == wR[p][0] && a[1] == wR[p][1])
			mark = 1;
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wP[p][0] && a[1] == wP[p][1])
			mark = 1;
	}
	//考虑兵升变
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wQp[p][0] && a[1] == wQp[p][1])
			mark = 1;
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wBp[p][0] && a[1] == wBp[p][1])
			mark = 1;
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wNp[p][0] && a[1] == wNp[p][1])
			mark = 1;
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == wRp[p][0] && a[1] == wRp[p][1])
			mark = 1;
	}
	return 0;
}

//判断该位置有无黑棋，从而判断能否落子
int bBlock(int a[2])
{
	mark = 0;
	if (a[0] == bK[0] && a[1] == bK[1])
		mark = 1;
	if (a[0] == bQ[0] && a[1] == bQ[1])
		mark = 1;
	for (p = 0; p < 2; p++)
	{
		if (a[0] == bB[p][0] && a[1] == bB[p][1])
			mark = 1;
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == bN[p][0] && a[1] == bN[p][1])
			mark = 1;
	}
	for (p = 0; p < 2; p++)
	{
		if (a[0] == bR[p][0] && a[1] == bR[p][1])
			mark = 1;
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bP[p][0] && a[1] == bP[p][1])
			mark = 1;
	}
	//考虑兵升变
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bQp[p][0] && a[1] == bQp[p][1])
			mark = 1;
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bBp[p][0] && a[1] == bBp[p][1])
			mark = 1;
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bNp[p][0] && a[1] == bNp[p][1])
			mark = 1;
	}
	for (p = 0; p < 8; p++)
	{
		if (a[0] == bRp[p][0] && a[1] == bRp[p][1])
			mark = 1;
	}
	return 0;
}


/*绘制*/;

//依据坐标绘制白棋图像
void putw()
{
	IMAGE p01, p02, p03, p04, p05, p06;
	loadimage(&p01, ("p_01.jpg"), le, wi, TRUE);
	loadimage(&p02, ("p_02.jpg"), le, wi, TRUE);
	loadimage(&p03, ("p_03.jpg"), le, wi, TRUE);
	loadimage(&p04, ("p_04.jpg"), le, wi, TRUE);
	loadimage(&p05, ("p_05.jpg"), le, wi, TRUE);
	loadimage(&p06, ("p_06.jpg"), le, wi, TRUE);
	if (wK[0] >= 1 && wK[0] <= 8 && wK[1] >= 1 && wK[1] <= 8)
		putimage(200 + (wK[0] - 1) * le, 50 + (wK[1] - 1) * wi, &p01);
	if (wQ[0] >= 1 && wQ[0] <= 8 && wQ[1] >= 1 && wQ[1] <= 8)
		putimage(200 + (wQ[0] - 1) * le, 50 + (wQ[1] - 1) * wi, &p02);
	for (p = 0; p < 2; p++)
	{
		if (wB[p][0] >= 1 && wB[p][0] <= 8 && wB[p][1] >= 1 && wB[p][1] <= 8)
			putimage(200 + (wB[p][0] - 1) * le, 50 + (wB[p][1] - 1) * wi, &p03);
	}
	for (p = 0; p < 2; p++)
	{
		if (wN[p][0] >= 1 && wN[p][0] <= 8 && wN[p][1] >= 1 && wN[p][1] <= 8)
			putimage(200 + (wN[p][0] - 1) * le, 50 + (wN[p][1] - 1) * wi, &p04);
	}
	for (p = 0; p < 2; p++)
	{
		if (wR[p][0] >= 1 && wR[p][0] <= 8 && wR[p][1] >= 1 && wR[p][1] <= 8)
			putimage(200 + (wR[p][0] - 1) * le, 50 + (wR[p][1] - 1) * wi, &p05);
	}
	for (p = 0; p < 8; p++)
	{
		if (wP[p][0] >= 1 && wP[p][0] <= 8 && wP[p][1] >= 1 && wP[p][1] <= 8)
			putimage(200 + (wP[p][0] - 1) * le, 50 + (wP[p][1] - 1) * wi, &p06);
	}
	//考虑兵升变
	for (p = 0; p < 8; p++)
	{
		if (wQp[p][0] >= 1 && wQp[p][0] <= 8 && wQp[p][1] >= 1 && wQp[p][1] <= 8)
			putimage(200 + (wQp[p][0] - 1) * le, 50 + (wQp[p][1] - 1) * wi, &p02);
	}
	for (p = 0; p < 8; p++)
	{
		if (wBp[p][0] >= 1 && wBp[p][0] <= 8 && wBp[p][1] >= 1 && wBp[p][1] <= 8)
			putimage(200 + (wBp[p][0] - 1) * le, 50 + (wBp[p][1] - 1) * wi, &p03);
	}
	for (p = 0; p < 8; p++)
	{
		if (wNp[p][0] >= 1 && wNp[p][0] <= 8 && wNp[p][1] >= 1 && wNp[p][1] <= 8)
			putimage(200 + (wNp[p][0] - 1) * le, 50 + (wNp[p][1] - 1) * wi, &p04);
	}
	for (p = 0; p < 8; p++)
	{
		if (wRp[p][0] >= 1 && wRp[p][0] <= 8 && wRp[p][1] >= 1 && wRp[p][1] <= 8)
			putimage(200 + (wRp[p][0] - 1) * le, 50 + (wRp[p][1] - 1) * wi, &p05);
	}
}

//依据坐标绘制黑棋图像
void putb()
{
	IMAGE p11, p12, p13, p14, p15, p16;
	loadimage(&p11, ("p_07.jpg"), le, wi, TRUE);
	loadimage(&p12, ("p_08.jpg"), le, wi, TRUE);
	loadimage(&p13, ("p_09.jpg"), le, wi, TRUE);
	loadimage(&p14, ("p_10.jpg"), le, wi, TRUE);
	loadimage(&p15, ("p_11.jpg"), le, wi, TRUE);
	loadimage(&p16, ("p_12.jpg"), le, wi, TRUE);
	if (bK[0] >= 1 && bK[0] <= 8 && bK[1] >= 1 && bK[1] <= 8)
		putimage(200 + (bK[0] - 1) * le, 50 + (bK[1] - 1) * wi, &p11);
	if (bQ[0] >= 1 && bQ[0] <= 8 && bQ[1] >= 1 && bQ[1] <= 8)
		putimage(200 + (bQ[0] - 1) * le, 50 + (bQ[1] - 1) * wi, &p12);
	for (p = 0; p < 2; p++)
	{
		if (bB[p][0] >= 1 && bB[p][0] <= 8 && bB[p][1] >= 1 && bB[p][1] <= 8)
			putimage(200 + (bB[p][0] - 1) * le, 50 + (bB[p][1] - 1) * wi, &p13);
	}
	for (p = 0; p < 2; p++)
	{
		if (bN[p][0] >= 1 && bN[p][0] <= 8 && bN[p][1] >= 1 && bN[p][1] <= 8)
			putimage(200 + (bN[p][0] - 1) * le, 50 + (bN[p][1] - 1) * wi, &p14);
	}
	for (p = 0; p < 2; p++)
	{
		if (bR[p][0] >= 1 && bR[p][0] <= 8 && bR[p][1] >= 1 && bR[p][1] <= 8)
			putimage(200 + (bR[p][0] - 1) * le, 50 + (bR[p][1] - 1) * wi, &p15);
	}
	for (p = 0; p < 8; p++)
	{
		if (bP[p][0] >= 1 && bP[p][0] <= 8 && bP[p][1] >= 1 && bP[p][1] <= 8)
			putimage(200 + (bP[p][0] - 1) * le, 50 + (bP[p][1] - 1) * wi, &p16);
	}
	//考虑兵升变
	for (p = 0; p < 8; p++)
	{
		if (bQp[p][0] >= 1 && bQp[p][0] <= 8 && bQp[p][1] >= 1 && bQp[p][1] <= 8)
			putimage(200 + (bQp[p][0] - 1) * le, 50 + (bQp[p][1] - 1) * wi, &p12);
	}
	for (p = 0; p < 8; p++)
	{
		if (bBp[p][0] >= 1 && bBp[p][0] <= 8 && bBp[p][1] >= 1 && bBp[p][1] <= 8)
			putimage(200 + (bBp[p][0] - 1) * le, 50 + (bBp[p][1] - 1) * wi, &p13);
	}
	for (p = 0; p < 8; p++)
	{
		if (bNp[p][0] >= 1 && bNp[p][0] <= 8 && bNp[p][1] >= 1 && bNp[p][1] <= 8)
			putimage(200 + (bNp[p][0] - 1) * le, 50 + (bNp[p][1] - 1) * wi, &p14);
	}
	for (p = 0; p < 8; p++)
	{
		if (bRp[p][0] >= 1 && bRp[p][0] <= 8 && bRp[p][1] >= 1 && bRp[p][1] <= 8)
			putimage(200 + (bRp[p][0] - 1) * le, 50 + (bRp[p][1] - 1) * wi, &p15);
	}
}

//更新棋盘
void display()
{
	int i = 0, j = 0, k = 0;
	//绘制黑白相间的格子
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (k == 0)
				setfillcolor(WHITE);
			else if (k == 1)
				setfillcolor(DARKGRAY);
			solidrectangle(200 + le * i, 50 + wi * j, 200 + le * (i + 1), 50 + wi * (j + 1));
			k = 1 - k;
		}
		k = 1 - k;
	}
	putb();
	putw();
}


//判断比赛是否决出胜负，以及谁胜谁负
void judge()
{
	if (wK[0] == -1 && wK[1] == -1)
	{
		final = 2;
	}
	if (bK[0] == -1 && bK[1] == -1)
	{
		final = 1;
	}
}


//主函数
int main()
{
	initial();
	return 0;
}
