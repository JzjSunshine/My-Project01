#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
int shuDu[10][10];
int numbers;
int num;//用于记录当前产生的数独终局数 
FILE *fp;
void Print_shuDu(int n) //数独输出函数 
{
	int i, j;
	for (i = 1; i <= 9; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			fputc(shuDu[i][j] + '0', fp);
			if (j == 9 && i != 9) fputc('\n', fp);
			else if (i == 9 && j == 9)
			{
				if (n < numbers) fputc('\n', fp), fputc('\n', fp);
			}
			else
				fputc(' ', fp);
		}
	}
	return;
}
int judge(int i, int j)  //搜索第（ i , j ）位置处可以存储的数字,找到解则返回1，否则返回0
{
	if (i > 9 || j > 9) return 1;//搜索结束 
	for (int k = 1; k <= 9; k++)
	{
		int can = 1;                // can 变量用于记录数字k能否放在 ( i , j ) 处
		for (int m = 1; m < i; m++) // 检查同一列是否出现过数字k
		{
			if (shuDu[m][j] == k)  //该列出现过数字k 
			{
				can = 0;
				break;
			}
		}
		if (can == 1)
		{
			for (int n = 1; n < j; n++) // 检查同一行是否出现过数字k
			{
				if (shuDu[i][n] == k)  //该行出现过数字k 
				{
					can = 0;
					break;
				}
			}
		}
		if (can == 1)                     // 检查在3×3的小方格中是否出现了同一个数字 
		{
			int up1 = (i / 3) * 3 + 3; // (i,j)方格所在的3×3小方格i坐标的上限
			int up2 = (j / 3) * 3 + 3;  // (i,j)方格所在的3×3小方格在j坐标的上限

			if (i % 3 == 0) up1 = i;   //这是针对特殊情况的处理       
			if (j % 3 == 0) up2 = j;

			for (int p = up1 - 2; p <= up1; p++)  /* 检查在3×3的小方格中是否出现了同一个数字 */
			{
				for (int q = up2 - 2; q <= up2; q++)
				{
					if (shuDu[p][q] == k)
					{
						can = 0;
						break;
					}
				}
			}
		}
		if (can == 1) //can==1说明数字k可以放在该位置上 
		{
			shuDu[i][j] = k;
			if (j<9)
			{
				if (judge(i, j + 1) == 1) return 1;  /* 到同一行的下一位置开始搜索 */
			}
			else
			{
				if (i < 9)
				{
					if (judge(i + 1, 1) == 1) return 1;   /* 到下一行的第一个空格开始搜索 */
				}
				else
				{
					num++;
					if (num<numbers)
					{
						//fprintf(fp,"%d\n",num);
						Print_shuDu(num);
					}
					else
					{
						//fprintf(fp,"%d\n",num);
						Print_shuDu(num);
						return 1;   /* i >= 9  && j >= 9  , 搜索结束 */
					}
				}
			}
			shuDu[i][j] = 0;  /* 关键这一步：找不到解就要回复原状，否则会对下面的搜索造成影响 */
		}
		else continue;//继续尝试其他数字 
	}
	return 0;  /*  1到9都尝试过都不行，则返回递归的上一步 */
}
void Creat_ShuDu(char s[])
{
	int temp = 1;
	int i;
	for (i = 0; i<strlen(s); i++)
	{
		if (isdigit(s[i]) == 0)
		{
			printf("Input error!\n");
			break;
		}
		else numbers = numbers * 10 + (s[i] - '0');
	}
	shuDu[1][1] = 2;
	judge(1, 2);
	return;
}
int solve(int i, int j)//递归求解数据残局 
{
	if (i > 9 || j > 9) return 1;//搜索结束 
	if (shuDu[i][j] != 0)
	{
		if (j<9)
		{
			if (solve(i, j + 1) == 1) return 1;  /* 从同一行的下一位置开始判断 */
		}
		else
		{
			if (i < 9)
			{
				if (solve(i + 1, 1) == 1) return 1;   /* 从下一行的第一个空格开始判断 */
			}
		}
	}
	for (int k = 1; k <= 9; k++) //依次寻找适合的数据 
	{
		int can = 1;                // can 变量用于记录数字k能否放在 ( i , j ) 处
		for (int m = 1; m <= 9; m++) // 检查同一列是否出现过数字k
		{
			if (shuDu[m][j] == k)  //该列出现过数字k 
			{
				can = 0;
				break;
			}
		}
		if (can == 1)
		{
			for (int n = 1; n <= 9; n++) // 检查同一行是否出现过数字k
			{
				if (shuDu[i][n] == k)  //该行出现过数字k 
				{
					can = 0;
					break;
				}
			}
		}
		if (can == 1)                     // 检查在3×3的小方格中是否出现了同一个数字 
		{
			int up1 = (i / 3) * 3 + 3; // (i,j)方格所在的3×3小方格i坐标的上限
			int up2 = (j / 3) * 3 + 3;  // (i,j)方格所在的3×3小方格在j坐标的上限

			if (i % 3 == 0) up1 = i;   //这是针对特殊情况的处理       
			if (j % 3 == 0) up2 = j;

			for (int p = up1 - 2; p <= up1; p++)  /* 检查在3×3的小方格中是否出现了同一个数字 */
			{
				for (int q = up2 - 2; q <= up2; q++)
				{
					if (shuDu[p][q] == k)
					{
						can = 0;
						break;
					}
				}
			}
		}
		if (can == 1) //can==1说明数字k可以放在该位置上 
		{
			shuDu[i][j] = k;
			if (j<9)
			{
				if (solve(i, j + 1) == 1) return 1;  /* 到同一行的下一位置开始搜索 */
			}
			else
			{
				if (i < 9)
				{
					if (solve(i + 1, 1) == 1) return 1;   /* 到下一行的第一个空格开始搜索 */
				}
				else
				{
					return 1;   /* i >= 9  && j >= 9  , 搜索结束 */
				}
			}
		}
		else continue;//继续尝试其他数字 
	}
	shuDu[i][j] = 0;  /* 关键这一步：找不到解就要回复原状，否则会对下面的搜索造成影响 */
	return 0;  /*  1到9都尝试过都不行，则返回递归的上一步 */
}
void Solve_shuDu(char FileName[])
{
	FILE *fq;
	int i, j;
	numbers = 1;
	fopen_s(&fq, FileName, "r");
	if (fq == NULL)
	{
		printf("无法打开此文件\n");
		return;
	}
	while (1)
	{
		for (i = 1; i <= 9; i++)  //读取一个数据残局 
		{
			for (j = 1; j <= 9; j++)
			{
				fscanf_s(fq, "%d", &shuDu[i][j]);
			}
		}
		solve(1, 1);
		fgetc(fq);
		if (feof(fq) != 0) //feof()=1表示文件结束 
		{
			Print_shuDu(1);
			break;
		}
		else Print_shuDu(0);
	}
	fclose(fq);
	return;
}
int main(int argc, char* argv[])
{
	fopen_s(&fp, "sudoku.txt", "w");
	if (fp == NULL)
	{
		printf("无法打开此文件\n");
		return 0;
	}
	if (argc == 3 && strcmp("-c", argv[1]) == 0)//生成数独 
	{
		Creat_ShuDu(argv[2]);
	}
	else if (argc == 3 && strcmp("-s", argv[1]) == 0)//解数独
	{
		Solve_shuDu(argv[2]);
	}
	fclose(fp);
	return 0;
}