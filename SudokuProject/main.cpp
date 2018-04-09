#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
int shuDu[10][10];
int numbers;
int num;//���ڼ�¼��ǰ�����������վ��� 
FILE *fp;
void Print_shuDu(int n) //����������� 
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
int judge(int i, int j)  //�����ڣ� i , j ��λ�ô����Դ洢������,�ҵ����򷵻�1�����򷵻�0
{
	if (i > 9 || j > 9) return 1;//�������� 
	for (int k = 1; k <= 9; k++)
	{
		int can = 1;                // can �������ڼ�¼����k�ܷ���� ( i , j ) ��
		for (int m = 1; m < i; m++) // ���ͬһ���Ƿ���ֹ�����k
		{
			if (shuDu[m][j] == k)  //���г��ֹ�����k 
			{
				can = 0;
				break;
			}
		}
		if (can == 1)
		{
			for (int n = 1; n < j; n++) // ���ͬһ���Ƿ���ֹ�����k
			{
				if (shuDu[i][n] == k)  //���г��ֹ�����k 
				{
					can = 0;
					break;
				}
			}
		}
		if (can == 1)                     // �����3��3��С�������Ƿ������ͬһ������ 
		{
			int up1 = (i / 3) * 3 + 3; // (i,j)�������ڵ�3��3С����i���������
			int up2 = (j / 3) * 3 + 3;  // (i,j)�������ڵ�3��3С������j���������

			if (i % 3 == 0) up1 = i;   //���������������Ĵ���       
			if (j % 3 == 0) up2 = j;

			for (int p = up1 - 2; p <= up1; p++)  /* �����3��3��С�������Ƿ������ͬһ������ */
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
		if (can == 1) //can==1˵������k���Է��ڸ�λ���� 
		{
			shuDu[i][j] = k;
			if (j<9)
			{
				if (judge(i, j + 1) == 1) return 1;  /* ��ͬһ�е���һλ�ÿ�ʼ���� */
			}
			else
			{
				if (i < 9)
				{
					if (judge(i + 1, 1) == 1) return 1;   /* ����һ�еĵ�һ���ո�ʼ���� */
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
						return 1;   /* i >= 9  && j >= 9  , �������� */
					}
				}
			}
			shuDu[i][j] = 0;  /* �ؼ���һ�����Ҳ������Ҫ�ظ�ԭ״��������������������Ӱ�� */
		}
		else continue;//���������������� 
	}
	return 0;  /*  1��9�����Թ������У��򷵻صݹ����һ�� */
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
int solve(int i, int j)//�ݹ�������ݲо� 
{
	if (i > 9 || j > 9) return 1;//�������� 
	if (shuDu[i][j] != 0)
	{
		if (j<9)
		{
			if (solve(i, j + 1) == 1) return 1;  /* ��ͬһ�е���һλ�ÿ�ʼ�ж� */
		}
		else
		{
			if (i < 9)
			{
				if (solve(i + 1, 1) == 1) return 1;   /* ����һ�еĵ�һ���ո�ʼ�ж� */
			}
		}
	}
	for (int k = 1; k <= 9; k++) //����Ѱ���ʺϵ����� 
	{
		int can = 1;                // can �������ڼ�¼����k�ܷ���� ( i , j ) ��
		for (int m = 1; m <= 9; m++) // ���ͬһ���Ƿ���ֹ�����k
		{
			if (shuDu[m][j] == k)  //���г��ֹ�����k 
			{
				can = 0;
				break;
			}
		}
		if (can == 1)
		{
			for (int n = 1; n <= 9; n++) // ���ͬһ���Ƿ���ֹ�����k
			{
				if (shuDu[i][n] == k)  //���г��ֹ�����k 
				{
					can = 0;
					break;
				}
			}
		}
		if (can == 1)                     // �����3��3��С�������Ƿ������ͬһ������ 
		{
			int up1 = (i / 3) * 3 + 3; // (i,j)�������ڵ�3��3С����i���������
			int up2 = (j / 3) * 3 + 3;  // (i,j)�������ڵ�3��3С������j���������

			if (i % 3 == 0) up1 = i;   //���������������Ĵ���       
			if (j % 3 == 0) up2 = j;

			for (int p = up1 - 2; p <= up1; p++)  /* �����3��3��С�������Ƿ������ͬһ������ */
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
		if (can == 1) //can==1˵������k���Է��ڸ�λ���� 
		{
			shuDu[i][j] = k;
			if (j<9)
			{
				if (solve(i, j + 1) == 1) return 1;  /* ��ͬһ�е���һλ�ÿ�ʼ���� */
			}
			else
			{
				if (i < 9)
				{
					if (solve(i + 1, 1) == 1) return 1;   /* ����һ�еĵ�һ���ո�ʼ���� */
				}
				else
				{
					return 1;   /* i >= 9  && j >= 9  , �������� */
				}
			}
		}
		else continue;//���������������� 
	}
	shuDu[i][j] = 0;  /* �ؼ���һ�����Ҳ������Ҫ�ظ�ԭ״��������������������Ӱ�� */
	return 0;  /*  1��9�����Թ������У��򷵻صݹ����һ�� */
}
void Solve_shuDu(char FileName[])
{
	FILE *fq;
	int i, j;
	numbers = 1;
	fopen_s(&fq, FileName, "r");
	if (fq == NULL)
	{
		printf("�޷��򿪴��ļ�\n");
		return;
	}
	while (1)
	{
		for (i = 1; i <= 9; i++)  //��ȡһ�����ݲо� 
		{
			for (j = 1; j <= 9; j++)
			{
				fscanf_s(fq, "%d", &shuDu[i][j]);
			}
		}
		solve(1, 1);
		fgetc(fq);
		if (feof(fq) != 0) //feof()=1��ʾ�ļ����� 
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
		printf("�޷��򿪴��ļ�\n");
		return 0;
	}
	if (argc == 3 && strcmp("-c", argv[1]) == 0)//�������� 
	{
		Creat_ShuDu(argv[2]);
	}
	else if (argc == 3 && strcmp("-s", argv[1]) == 0)//������
	{
		Solve_shuDu(argv[2]);
	}
	fclose(fp);
	return 0;
}