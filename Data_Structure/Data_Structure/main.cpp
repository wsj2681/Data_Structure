#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Champion
{
	int data;
	char cData;
}Champ;

void PrintAllData_Recrusive(Champ* champ, Champ* tail); // champ = array name, tail = array's last index pointer
Champ* SearchData_Recrusive(Champ* champ, Champ* tail, int data);
void SortByData_Recrusive(Champ* champIndex1, Champ* champIndex2, Champ* tail);
void FindMaxData_Recrusive(Champ* champ, Champ* tail, Champ* maxChamp);
void FindMaxDatas_Recrusive(Champ* champ, Champ* tail, Champ** maxChamp, int* maxChampIndex);

int main()
{
	Champ cmp[10];
	Champ* tail = &cmp[9];

	for (int i = 0; i < 10; ++i)
	{
		cmp[i].data = rand() % 100;
		cmp[i].cData = 'a' + (rand() % 26);
	}

	PrintAllData_Recrusive(cmp, cmp + 9);

	int search = 0;
	scanf_s("%d", &search);

	Champ* resultData = SearchData_Recrusive(cmp, tail, search);
	if (resultData != NULL)
	{
		printf("data = %d - cData = %c\n", resultData->data, resultData->cData);
	}
	else
	{
		printf("can not find\n");
	}

	SortByData_Recrusive(cmp, cmp, tail);

	PrintAllData_Recrusive(cmp, tail);

	Champ** maxChamp[10] = { &cmp[0] };
	int maxChampIndex = 0;
	FindMaxData_Recrusive(cmp, tail, *maxChamp[0]);
	
	FindMaxDatas_Recrusive(cmp, tail, *maxChamp, &maxChampIndex);

	PrintAllData_Recrusive(*maxChamp[0], *(*maxChamp + (maxChampIndex -1)));
	
}

void PrintAllData_Recrusive(Champ* champ, Champ* tail)
{

	if (champ == tail + 1)
	{
		return;
	}

	printf("data = %d - cData = %c\n", champ->data, champ->cData);

	PrintAllData_Recrusive(champ + 1, tail);
}

Champ* SearchData_Recrusive(Champ* champ, Champ* tail, int data)
{
	if (champ == tail + 1)
	{
		return NULL;
	}

	if (champ->data == data)
	{
		return champ;
	}

	SearchData_Recrusive(champ + 1, tail, data);
}

void SortByData_Recrusive(Champ* champIndex1, Champ* champIndex2, Champ* tail)
{
	if (champIndex2 == tail + 1)
	{
		champIndex1 = (champIndex1 + 1);
		champIndex2 = (tail - 9);
	}

	if (champIndex1 == tail + 1)
	{
		return;
	}

	if (champIndex2->data < (champIndex2 + 1)->data)
	{
		Champ temp = *champIndex2;
		*champIndex2 = *(champIndex2 + 1);
		*(champIndex2 + 1) = temp;
	}

	SortByData_Recrusive(champIndex1, champIndex2 + 1, tail);
}

void FindMaxData_Recrusive(Champ* champ, Champ* tail, Champ* maxChamp)
{
	if (champ == tail + 1)
	{
		return;
	}

	if (champ->data > maxChamp->data)
	{
		maxChamp = champ;
	}

	FindMaxData_Recrusive(champ + 1, tail, maxChamp);
	
}

void FindMaxDatas_Recrusive(Champ* champ, Champ* tail, Champ** maxChamp, int* maxChampIndex)
{
	if (champ == tail + 1)
	{
		return;
	}

	if (maxChamp[*maxChampIndex]->data == champ->data && (strcmp(maxChamp[*maxChampIndex]->cData, champ->data) != 0))
	{
		maxChamp[++ * maxChampIndex] = champ;
	}

	FindMaxDatas_Recrusive(champ + 1, tail, maxChamp, maxChampIndex);
}
