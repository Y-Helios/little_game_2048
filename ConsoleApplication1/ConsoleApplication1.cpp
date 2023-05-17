#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<random>
#include<graphics.h>  // 好像是一个什么easy库，c++的
#include<Windows.h>
#include<stdlib.h>

#define s0 0
#define s2 2
#define s4 4
#define s8 8
#define s16 16
#define s32 32
#define s64 64
#define s128 128
#define s256 256
#define s512 512
#define s1024 1024
#define s2048 2048
#define s4096 4096
#define s8192 8192
#define s16384 16384

int OverInterface();

IMAGE i0, i2, i4, i8, i16, i32, i64, i128, i256, i512, i1024, i2048, i4096, i8192, image_over,itongguan;
IMAGE putong, qingtong, baiyin, bojin, huangjin, zuanshi;//游戏结束时等级图片

//分数
unsigned long score=0;  
int stop = 0;
//判断是否发生合并
int flag = 1; 
//最终成绩
int finalscore = 0;
//最好成绩
int maxscore = 0;
TCHAR str[5];
TCHAR ss[5];


int p[4][4] = { {s0,s0,s0,s0},{s0,s0,s0,s0},{s0,s0,s0,s0},{s0,s0,s0,s0} };

//一个用来判断相等的函数
int equal(int num) {   
	return 2 * num;
}

int i,j;
void change(int n)
{
	switch (n)
	{
	//左移
	case 3:    
		//检查第一列是否已满， 满足两个条件中的一个即可生成：1，第一列不满，2，发生了合并
		for (i = 0; i < 4; i++)   
		{
			if (p[i][0] == s0)
			{
				int tag = 0;
				//对于空格，检查它对应的一行，如果有非空的格子，生成新格子
				for (j = 0; j < 4; j++)    
				{
					if (p[i][j] != s0)
					{
						tag = 1;
					}
				}
				if (tag == 1) {
					flag = 1;
				}
					
			}
		}

		for (i = 0; i < 4; i++)    //第一个循环实现移动
		{
			if (p[i][0] == s0)        //一直执行移动，直到第一列有数字
			{
				p[i][0] = p[i][1];
				p[i][1] = p[i][2];
				p[i][2] = p[i][3];
				p[i][3] = s0;
			}
			if (p[i][0] == s0)
			{
				p[i][0] = p[i][1];
				p[i][1] = p[i][2];
				p[i][2] = s0;
			}
			if (p[i][0] == s0)
			{
				p[i][0] = p[i][1];
				p[i][1] = s0;
			}
			if (p[i][1] == s0)       //一直执行移动，直到第二列有数字
			{
				p[i][1] = p[i][2];
				p[i][2] = p[i][3];
				p[i][3] = s0;
			}
			if (p[i][1] == s0)
			{
				p[i][1] = p[i][2];
				p[i][2] = s0;
			}
			if (p[i][2] == s0)			//一直执行移动，直到第三列有数字
			{
				p[i][2] = p[i][3];
				p[i][3] = s0;
			}
		} 
		//第二个循环执行合并
		for (i = 0; i < 4; i++)   
		{ 
			//合并第一个和第二个
			if (p[i][0] == p[i][1] && p[i][0] != s0)   
			{
				p[i][0] = equal(p[i][0]);
				score += p[i][0];
				p[i][1] = p[i][2];
				p[i][2] = p[i][3];
				p[i][3] = s0;
				//出现唯一的特殊情况形如：2244  此时需要合并两次
				if (p[i][1] == p[i][2] && p[i][1] != s0) 
				{
					p[i][1] = equal(p[i][1]);
					score += p[i][1];
					p[i][2] = p[i][3];
				}
				flag = 1;
				continue;
			}

			//检查第二个位置是否合并
			else if (p[i][1] == p[i][2] && p[i][1] != s0)  
			{
				p[i][1] = equal(p[i][1]);
				score += p[i][1];
				p[i][2] = p[i][3];
				p[i][3] = s0;
				flag = 1;
				continue;
			} 
 
			//检查第三个位置是否合并
			else if (p[i][2] == p[i][3] && p[i][2] != s0)  
			{
				p[i][2] = equal(p[i][2]);
				score += p[i][2];
				p[i][3] = s0;
				flag = 1;
				continue;
			}
		}

		break;

		//右移
	case 4:  
		//检查第四列是否已满， 满足两个条件中的一个即可生成：1，第一列不满，2，发生了合并
		for (i = 0; i < 4; i++)   
		{
			if (p[i][3] == s0)
			{
				int tag = 0;
				for (j = 0; j < 4; j++)
				{
					if (p[i][j] != s0)
					{
						tag = 1;
					}
				}
				if (tag == 1)
				{
					flag = 1;
				}
			}
		}
		//同理 只是方向变了而已
		for (i = 0; i < 4; i++) {   
			if (p[i][3] == s0)
			{
				p[i][3] = p[i][2];
				p[i][2] = p[i][1];
				p[i][1] = p[i][0];
				p[i][0] = s0;
			}
			if (p[i][3] == s0)
			{
				p[i][3] = p[i][2];
				p[i][2] = p[i][1];
				p[i][1] = s0;
			}
			if (p[i][3] == s0)
			{
				p[i][3] = p[i][2];
				p[i][2] = s0;
			}
			if (p[i][2] == s0)
			{
				p[i][2] = p[i][1];
				p[i][1] = p[i][0];
				p[i][0] = s0;
			}
			if (p[i][2] == s0)
			{
				p[i][2] = p[i][1];
				p[i][1] = s0;
			}
			if (p[i][1] == s0)
			{
				p[i][1] = p[i][0];
				p[i][0] = s0;
			}
		}

		for (i = 0; i < 4; i++)
		{
			if (p[i][3] == p[i][2] && p[i][3] != s0)
			{
				p[i][3] = equal(p[i][3]);
				score += p[i][3];
				p[i][2] = p[i][1];
				p[i][1] = p[i][0];
				p[i][0] = s0;
				if (p[i][2] == p[i][1] && p[i][2] != s0)
				{
					p[i][2] = equal(p[i][2]);
					score += p[i][2];
					p[i][1] = p[i][0];
				}
				flag = 1;
				continue;
			}
			else if (p[i][2] == p[i][1] && p[i][2] != s0)
			{
				p[i][2] = equal(p[i][2]);
				score += p[i][2];
				p[i][1] = p[i][0];
				p[i][0] = s0;
				flag = 1;
				continue;
			}
			else if (p[i][1] == p[i][0] && p[i][1] != s0)
			{
				p[i][1] = equal(p[i][1]);
				score += p[i][1];
				p[i][0] = s0;
				flag = 1;
				continue;
			}
		}
		break;

		//上移
	case 1:  
		//检查第一行是否已满， 满足两个条件中的一个即可生成：1，第一列不满，2，发生了合并
		for (i = 0; i < 4; i++)   
		{
			if (p[0][i] == s0)
			{
				int tag = 0;
				for (j = 0; j < 4; j++)
				{
					if (p[j][i] != s0)
					{
						tag = 1;
					}
				}
				if (tag == 1)
				{
					flag = 1;
				}
			}
		}
		for (i = 0; i < 4; i++)
		{
			if (p[0][i] == s0)
			{
				p[0][i] = p[1][i];
				p[1][i] = p[2][i];
				p[2][i] = p[3][i];
				p[3][i] = s0;
			}
			if (p[0][i] == s0)
			{
				p[0][i] = p[1][i];
				p[1][i] = p[2][i];
				p[2][i] = s0;
			}
			if (p[0][i] == s0)
			{
				p[0][i] = p[1][i];
				p[1][i] = s0;
			}
			if (p[1][i] == s0)
			{
				p[1][i] = p[2][i];
				p[2][i] = p[3][i];
				p[3][i] = s0;
			}
			if (p[1][i] == s0)
			{
				p[1][i] = p[2][i];
				p[2][i] = s0;
			}
			if (p[2][i] == s0)
			{
				p[2][i] = p[3][i];
				p[3][i] = s0;
			}
		}

		for (i = 0; i < 4; i++)
		{
			if (p[0][i] == p[1][i] && p[0][i] != s0)
			{
				p[0][i] = equal(p[0][i]);
				score += p[0][i];
				p[1][i] = p[2][i];
				p[2][i] = p[3][i];
				p[3][i] = s0;
				if (p[1][i] == p[2][i] && p[1][i] != s0)
				{
					p[1][i] = equal(p[1][i]);
					score += p[1][i];
					p[2][i] = p[3][i];
				}
				flag = 1;
				continue;
			}
			else if (p[1][i] == p[2][i] && p[1][i] != s0)
			{
				p[1][i] = equal(p[1][i]);
				score += p[1][i];
				p[2][i] = p[3][i];
				p[3][i] = s0;
				flag = 1;
				continue;
			}
			else if (p[2][i] == p[3][i] && p[2][i] != s0)
			{
				p[2][i] = equal(p[2][i]);
				score += p[2][i];
				p[3][i] = s0;
				flag = 1;
			}
		}
		break;

		//向下移动
	case 2:  
		//检查第四行是否已满， 满足两个条件中的一个即可生成：1，第一列不满，2，发生了合并
		for (i = 0; i < 4; i++)  
		{
			if (p[3][i] == s0)
			{
				int tag = 0;
				for (j = 0; j < 4; j++)
				{
					if (p[j][i] != s0)
					{
						tag = 1;
					}
				}
				if (tag == 1)
				{
					flag = 1;
				}
			}
		}
			for (i = 0; i < 4; i++)
			{
				if (p[3][i] == s0)
				{
					p[3][i] = p[2][i];
					p[2][i] = p[1][i];
					p[1][i] = p[0][i];
					p[0][i] = s0;
				}
				if (p[3][i] == s0)
				{
					p[3][i] = p[2][i];
					p[2][i] = p[1][i];
					p[1][i] = s0;
				}
				if (p[3][i] == s0)
				{
					p[3][i] = p[2][i];
					p[2][i] = s0;
				}
				if (p[2][i] == s0)
				{
					p[2][i] = p[1][i];
					p[1][i] = p[0][i];
					p[0][i] = s0;
				}
				if (p[2][i] == s0)
				{
					p[2][i] = p[1][i];
					p[1][i] = s0;
				}
				if (p[1][i] == s0)
				{
					p[1][i] = p[0][i];
					p[0][i] = s0;
				}
			}

		for (i = 0; i < 4; i++)
		{
			if (p[3][i] == p[2][i] && p[3][i] != s0)
			{
				p[3][i] = equal(p[3][i]);
				score += p[3][i];
				p[2][i] = p[1][i];
				p[1][i] = p[0][i];
				p[0][i] = s0;
				if (p[2][i] == p[1][i] && p[2][i] != s0)
				{
					p[2][i] = equal(p[2][i]);
					score += p[2][i];
					p[1][i] = p[0][i];
				}
				flag = 1;
				continue;
			}
			else if (p[2][i] == p[1][i] && p[2][i] != s0)
			{
				p[2][i] = equal(p[2][i]);
				score += p[2][i];
				p[1][i] = p[0][i];
				p[0][i] = s0;
				flag = 1;
				continue;
			}
			else if (p[1][i] == p[0][i] && p[1][i] != s0)
			{
				p[1][i] = equal(p[1][i]);
				score += p[1][i];
				p[0][i] = s0;
				flag = 1;
			}
		}
		break;
	default:
		break;
	}
}

//输入 上下左右

int input()
{
	//char c1 = _getch();
	char c2 = _getch();
	switch (c2)
	{
	case 'q':
		return 1;

	case 'i':
	case 'w': //上
		change(1);
		break;

	case 'k':
	case 's':// 下
		change(2);
		break;

	case 'j':
	case 'a': //左
		change(3);
		break;

	case 'l':
	case 'd': //右
		change(4);
		break;
	default:
		break;
	}
	return 0;

}

// 检查棋盘状态

void check_rand(int n,int t)
{
	
	int x[16], y[16]; //最多有16个空格子，（其实应该是14个。。。)
	memset(x, -1, 16);
	memset(y, -1, 16);
	char c = 'A';
	int i, j, k = 0;   //k为目前的x，y的大小
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (p[i][j] == s0)
			{
				x[k] = i;
				y[k++] = j;
				c++;
			}
		}
	}
	if (t == 1) 
	{
		srand((unsigned)time(NULL));
		int rand_pos = rand() % (c - 'A');  //在一个随机的空格上生成数字；
		int rand_num = (n % 7 == 6) ? s4 : s2;   //生成数字的值也是随机的
		p[x[rand_pos]][y[rand_pos]] = rand_num;
	}

	//如果已满，则开始判断是否结束
	if (c == 'A')  
	{
		stop = 1;
		for (i = 0; i < 4; i++)  //直接暴力搜索，找邻近空格
		{
			for (j = 0; j < 4; j++)
			{
				if (i != 0)
				{
					if (p[i - 1][j] == p[i][j])
					{
						stop = 0;
						break;
					}
				}
				if (i != 3)
				{
					if (p[i + 1][j] == p[i][j])
					{
						stop = 0;
						break;
					}
				}
				if (j != 0)
				{
					if (p[i][j - 1] == p[i][j])
					{
						stop = 0;
						break;
					}
				}
				if (j != 3)
				{
					if (p[i][j + 1] == p[i][j])
					{
						stop = 0;
						break;
					}
				}
			}
		}
	}

}

// 设置文字样式和颜色
void settext(int height, int weight, UINT color)
{
	settextstyle(height, 0, _T("Arial"), 0, 0, weight, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(color);
}

// 在指定矩形区域内居中输出字符串
void printtext(LPCTSTR s, int left, int top, int right, int width)
{
	RECT r = { left, top, right, width };
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//初始化游戏界面，确定分区
void init()
{
	//可作开屏图，讲解游戏规则等
	//loadimage(0, _T("test1.jpg"));
	//Sleep(3000);

	//loadimage(0, _T("test2.jpg"));
	//Sleep(3000);

	//载入背景
	loadimage(0, _T("background.jpg"));
	//Sleep(100);
	//setfillcolor(WHITE);

	//loadimage(&background2, _T("background2.jpg"));
	//putimage(15, 190, &background2);

	//下面两行和上面两行功能一样，设置4*4小方格的局部背景
	setfillcolor(RGB(208, 173, 68));
	fillrectangle(15, 190, 465, 640);

	//左上角的标题
	setbkcolor(RGB(229, 228, 176));
	settextstyle(80, 0, _T("Cooper Black"));
	settextcolor(0x707b83);
	outtextxy(25, 20, _T("2048"));

}

//通关界面
void tongguan() {
	loadimage(&itongguan, _T("tongguan.jpg"));
	putimage(0, 0, &itongguan);
	Sleep(3000);

	//通关后直接退出游戏
	exit(0);

}

//载入图片
void print1(size_t i, size_t j)
{
	if (p[i][j] == s0)
	{
		loadimage(&i0, _T("0.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i0);
	}
	else if (p[i][j] == s2)
	{
		loadimage(&i2, _T("2.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i2);
	}
	else if (p[i][j] == s4)
	{
		loadimage(&i4, _T("4.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i4);
	}
	else if (p[i][j] == s8)
	{
		loadimage(&i8, _T("8.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i8);
	}
	else if (p[i][j] == s16)
	{
		loadimage(&i16, _T("16.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i16);
	}
	else if (p[i][j] == s32)
	{
		loadimage(&i32, _T("32.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i32);
	}
	else if (p[i][j] == s64)
	{
		loadimage(&i64, _T("64.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i64);
	}
	else if (p[i][j] == s128)
	{
		loadimage(&i128, _T("128.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i128);
	}
	else if (p[i][j] == s256)
	{
		loadimage(&i256, _T("256.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i256);
	}
	else if (p[i][j] == s512)
	{
		loadimage(&i512, _T("512.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i512);
	}
	else if (p[i][j] == s1024)
	{
		loadimage(&i1024, _T("1024.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i1024);
	}
	else if (p[i][j] == s2048)
	{
		loadimage(&i2048, _T("2048.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i2048);
	}
	else if (p[i][j] == s4096)
	{
		loadimage(&i4096, _T("4096.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i4096);
	}
	else if (p[i][j] == s8192)
	{
		loadimage(&i8192, _T("8192.jpg"));
		putimage(25 + 110 * j, 200 + 110 * i, &i8192);
	}
	else if (p[i][j] == s16384) {
		//应该是直接在这里调用通关函数
		tongguan();
	}
}

void print()
{
	for (size_t i = 0; i != 4; i++)
	{
		for (size_t j = 0; j != 4; j++)
		{
			print1(i, j); //逐一打印方格
		}
	}

}


//成绩输出
void print_score(unsigned n)
{
	//输出当前成绩

	//矩形框
	setfillcolor(RGB(208, 173, 68));
	solidroundrect(85, 110, 455, 180, 10, 10);

	//score:
	setbkcolor(RGB(208, 173, 68)); 
	settextstyle(40, 0, _T("Arial")); 
	settextcolor(WHITE); // set the color
	outtextxy(105, 125, _T("SCORE:"));

	//当前分数：
	settextstyle(70, 30, _T("Arial")); // set the sytle
	settextcolor(WHITE); // set the color

	TCHAR s01[5], s02[5], s03[5], s04[5], s05[5];

	finalscore = score;

	swprintf_s(s01, _T("%d"), score % 10);
	swprintf_s(s02, _T("%d"), (score / 10) % 10);
	swprintf_s(s03, _T("%d"), (score / 100) % 10);
	swprintf_s(s04, _T("%d"), (score / 1000) % 10);
	swprintf_s(s05, _T("%d"), (score / 10000) % 10);
	outtextxy(250, 110, s05);
	outtextxy(285, 110, s04);
	outtextxy(320, 110, s03);
	outtextxy(355, 110, s02);
	outtextxy(390, 110, s01); // 输出


	//输出最好成绩
	//矩形框
	setfillcolor(RGB(208, 173, 68));
	solidroundrect(215, 30, 455, 90, 10, 10);

	//best:
	setbkcolor(RGB(208, 173, 68)); // set the background colour
	settextstyle(40, 0, _T("Arial")); // set the sytle
	settextcolor(WHITE); // set the color
	outtextxy(225, 40, _T("BEST:"));

	//当前成绩超过历史最好成绩
	if (finalscore > maxscore) {
		maxscore = finalscore;
	}

	//历史最高分
	swprintf_s(str, _T("%d"), maxscore);

	//settext(44, 800, WHITE);
	//printtext(str, 275, 70, 427, 114);
	outtextxy(365, 40, str);

	swprintf_s(ss, _T("%d"), finalscore);//用于游戏结束时输出分数
}


int OverInterface()//游戏结束时，返回1，重新开始游戏；返回0，退出游戏
{
	// 保存最高纪录
	//std::wstringstream ss;
	//保存历史最高成绩
	//ss << maxScore;
	WritePrivateProfileString(_T("2048"), _T("MaxScore"), str, _T(".\\data.ini"));
	//ss.str(_T(""));
	//没地方放了，放弃！
	//ss << maxBlock;
	//WritePrivateProfileString(_T("2048"), _T("MaxBlock"), ss.str().c_str(), _T(".\\data.ini"));

	setbkmode(TRANSPARENT);
	setbkcolor(0x8eecff);
	cleardevice();//清除图形屏幕

	// Game Over
	settext(60, 1000, 0x696f78);
	printtext(_T("Game Over!"), 0, 0, 439, 199);

	//绘制最终成绩
	settextcolor(0x00c5e);
	settextstyle(40, 0, _T("Arial"));
	//solidroundrect(120, 170, 319, 389, 10, 10);//选择输出的成绩不绘制方格所以注释掉
	//settext(36, 1000, WHITE);
	//printtext(ss, 120, 310, 319, 389);
	outtextxy(105, 165, _T("YOUR SCORE:"));

	settextstyle(80, 0, _T("Comic Sans MS"));
	outtextxy(115, 205, ss);

	if (finalscore <= 500) {
		loadimage(&putong, _T("putong.png"));
		//setfillcolor(0x8eecff);//好像没有用，注释掉
		putimage(275, 210, &putong);
	}
	else if (finalscore <= 1000) {
		loadimage(&qingtong, _T("qingtong.png"));
		//setfillcolor(0x8eecff);
		putimage(275, 210, &qingtong);
	}
	else if (finalscore <= 2000) {
		loadimage(&baiyin, _T("baiyin.png"));
		//setfillcolor(0x8eecff);
		putimage(275, 210, &baiyin);
	}
	else if (finalscore <= 5000) {
		loadimage(&huangjin, _T("huangjin.png"));
		//setfillcolor(0x8eecff);
		putimage(275, 210, &huangjin);
	}
	else if (finalscore <= 10000) {
		loadimage(&bojin, _T("bojin.png"));
		//setfillcolor(0x8eecff);
		putimage(275, 210, &bojin);
	}
	else {
		loadimage(&zuanshi, _T("zuanshi.png"));
		//setfillcolor(0x8eecff);
		putimage(275, 210, &zuanshi);
	}

	// 绘制最大方块
	//TransparentBlt(GetImageHDC(NULL), 175, 150, 90, 90, GetImageHDC(&image[currentMaxBlock]), 0, 0, 90, 90, 0x9eaebb);

	// ReStart
	setfillcolor(0x9dadba);
	solidroundrect(120, 310, 319, 389, 10, 10);
	settext(36, 1000, WHITE);
	printtext(_T("ReStart"), 120, 310, 319, 389);

	// Exit
	solidroundrect(120, 460, 319, 539, 10, 10);
	printtext(_T("Exit"), 120, 460, 319, 539);

	FlushBatchDraw();

	FlushMouseMsgBuffer();

	while (1)
	{
		while (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton)
			{
				int x = msg.x;
				int y = msg.y;
				if (x >= 120 && x <= 319 && y >= 310 && y <= 389)
					return 1;
				if (x >= 120 && x <= 319 && y >= 460 && y <= 539)
					return 0;
			}
		}
		Sleep(100);
	}
	return 1;
}

// 部分重置
void ReSet()
{
	cleardevice();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
				p[i][j] = s0;
		}
	}
}

//读取存档部分
void read_reocrd() 
{
	FILE* fp;

	if ((fp = fopen("save.txt", "r")) != NULL) {
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				fscanf_s(fp, "%d", &p[i][j]);
			}
		}
		fscanf_s(fp, "%d\t", &score);
		fscanf_s(fp, "%d\t", &flag);
		fclose(fp);
	}

}

void save_record()
{
	FILE* fp = fopen("save.txt", "w");
	int i,j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			fprintf(fp, "%d\t", p[i][j]);
		}
	}
	fprintf(fp, "%d\t", score);
	fprintf(fp, "%d\t", flag);
	fclose(fp);
}

//开始界面
int start() {

	setbkmode(TRANSPARENT);
	setbkcolor(0x8eecff);
	cleardevice();

	//游戏标题
	setbkcolor(RGB(229, 228, 176));
	settextstyle(120, 0, _T("Cooper Black"));
	settextcolor(0x707b83);
	outtextxy(120, 20, _T("2048"));

	//提示
	setfillcolor(0x707b83);
	fillroundrect(15, 540, 468, 610, 20, 20);
	settextstyle(25, 0, _T("Comic Sans MS"));
	settextcolor(WHITE);
	outtextxy(35, 550, _T("TIPS: In the case of English keyboard,anytime use"));
	outtextxy(18, 580, _T("\"ASWD\" or \"IJKL\"to move and \"Q\" to exit or restart."));

	//Restart按钮
	setfillcolor(0x707b83);
	fillroundrect(120, 220, 360, 300, 20, 20);
	settextstyle(60, 0, _T("Comic Sans MS"));
	settextcolor(WHITE);
	outtextxy(170, 230, _T("Restart"));

	//Load按钮
	setfillcolor(0x707b83);
	fillroundrect(120, 360, 360, 440, 20, 20);
	settextcolor(WHITE);
	outtextxy(180, 375, _T("Load"));

	FlushBatchDraw();

	FlushMouseMsgBuffer();

	while (1) {
		while (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.mkLButton)
			{
				int x = msg.x;
				int y = msg.y;
				if (x >= 120 && x <= 360 && y >= 220 && y <= 300) {
					return 1;
				}
				if (x >= 120 && x <= 360 && y >= 360 && y <= 440) {
					return 0;
				}
			}
		}
		Sleep(100);
	}

	return 1;

}



int main()
{

	//480*650
	initgraph(480, 650);

	if (start() == 1) {
		init();
	}
	else {
		init();
		read_reocrd();
	}
	
	while(1){

		FlushMouseMsgBuffer();

		stop = 0;

		unsigned cnt = 0;

		
		//check_rand(cnt, flag);
		

		print();

		maxscore = 0;

		// 读取最高分
		maxscore = GetPrivateProfileInt(_T("2048"), _T("MaxScore"), 0, _T(".\\data.ini"));
		// 读取最大方块
		//maxBlock = GetPrivateProfileInt(_T("2048"), _T("MaxBlock"), 2, _T(".\\data.ini"));

		while (stop == 0) //没有结束
		{
			print_score(score);
			if (input() == 1)
			{
				break;
			}
			check_rand(cnt, flag);
			print();
			
			if (cnt > 1)
			{
				flag = 0;
			}
			++cnt;
			save_record();
		}
	
		if (OverInterface() == 1) {//重新开始游戏的准备
			closegraph();
			initgraph(480, 650);
			ReSet();
			score = 0;
			init();
			flag = 1;
			stop = 0;
		}
		else {
			break;
		}

	}

	//加载gameover的图片，即游戏结束后没有重新开始和退出的选项（旧版本）
	//loadimage(&imageOver, _T("test4.jpg"));
	//putimage(100, 200, &imageOver);

	//getchar();

	closegraph();

	return 0;
}