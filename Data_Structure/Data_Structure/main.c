#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct NODE
{
	int data;
	struct NODE* next;

}Node;

Node* head = NULL;
Node* tail = NULL;

void InitList();
void SearchNode(int data);
void InsertNode(Node* insert, int isSorted);
void DeleteNode(int data);
void DeleteAllNode(int data);
void PrintNode(Node* node);
void PrintList();
void FindMaxNode();
void Swap(Node* a, Node* b);
bool SortList();
void FreeList();

int main()
{	
	bool isSorted = false;
	InitList();
	printf("Init - ");
	PrintList();

	printf("Find - ");
	FindMaxNode();

	Node* insert = (Node*)malloc(sizeof(Node));
	insert->data = 999;
	insert->next = NULL;

	InsertNode(insert, isSorted);
	printf("\nInsert'999' ");
	PrintList();

	isSorted = SortList();
	printf("Sort - ");
	PrintList();

	insert = (Node*)malloc(sizeof(Node));
	insert->data = -999;
	insert->next = NULL;
	InsertNode(insert, isSorted);
	printf("Insert'-999' ");
	PrintList();

	insert = (Node*)malloc(sizeof(Node));
	insert->data = 50;
	insert->next = NULL;
	InsertNode(insert, isSorted);
	printf("Insert'50' ");
	PrintList();

}

void InitList()
{
	for (int i = 0; i < 10; ++i)
	{
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->data = rand() % 100;
		temp->next = NULL;

		if (head == NULL)
		{
			head = temp;
		}
		else
		{
			tail->next = temp;
		}
		tail = temp;
	}
}

void SearchNode(int data)
{
	Node* curr = head;
	while (curr != NULL)
	{
		if (curr->data == data)
		{
			PrintNode(curr);
			return;
		}
		curr = curr->next;
	}

	printf("There are no values found in the list.\n");
}

void InsertNode(Node* insert, int isSorted)
{
	// TODO : ���� ����(��������)�� ���� �ϸ鼭 insert�ϴ� ���
	if (isSorted && (head != NULL))
	{
		if (head->data < insert->data) // insert -> head
		{
			insert->next = head;
			head = insert;
			return;
		}
		else if (tail->data > insert->data) // tail -> insert
		{
			tail->next = insert;
			tail = insert;
			return;
		}

		Node* curr = head;
		while (curr != NULL)
		{
			// curr.next - > insert -> curr.next.next
			if ((curr->next->data > insert->data) && (curr->next->next->data < insert->data))// curr -> insert
			{
				Node* temp = curr->next;
				insert->next = temp;
				curr->next = insert;
				return;
			}
			curr = curr->next;
		}
	}
	else
	{
		// ����Ʈ�� ����� �� insert �ϴ� ���
		if (head == NULL)
		{
			head = insert;
			tail = insert;
			return;
		}

		// ����Ʈ�� ��尡 �ϳ��� ���
		if (head == tail)
		{
			head = insert;
			head->next = tail;
			return;
		}

		// ����Ʈ�� �� �������� insert �ϴ� ���
		tail->next = insert;
		tail = insert;
		return;
	}
}

void DeleteNode(int data)
{
	// ����Ʈ�� ����� �� delete�� �ϴ� ���
	if (head == NULL)
	{
		return;
	}

	// ����Ʈ�� ��尡 �ϳ��̰� �� ��带 �����ϴ� ���
	if ((head == tail) && (head->data == data))
	{
		free(head);
		head = NULL;
		tail = NULL;
		return;
	}

	// �����Ϸ��� ���� ��ġ�� head�� ���
	if (head->data == data)
	{
		Node* temp = head->next;
		head->next = temp->next;
		free(head);
		head = temp;
		return;
	}

	Node* curr = head;

	while (curr != NULL)
	{
		// �Ϲ����� ���� �˰���
		if (curr->next->data == data)
		{
			Node* temp = curr->next;
			curr->next = temp->next;
			free(temp);
			return;
		}

		// �����Ϸ��� ����� ��ġ�� tail �� ���
		if ((curr->next == tail) && (tail->data == data))
		{
			free(tail);
			tail = curr;
			tail->next = NULL;
			return;
		}
		curr = curr->next;
	}
}

void DeleteAllNode(int data)
{
}

void PrintNode(Node* node)
{
	printf("%d ", node->data);
}

void PrintList()
{
	Node* curr = head;

	while (curr != NULL)
	{
		PrintNode(curr);
		curr = curr->next;
	}
	printf("\n");

	curr = NULL;
}

void FindMaxNode()
{
	Node* curr = head;

	int maxData = 0;

	// ����Ʈ ������ ���� ū �� ã��
	while (curr != NULL)
	{
		if (curr->data > maxData)
		{
			maxData = curr->data;
		}
		curr = curr->next;
	}

	printf("max = %d / ", maxData);

	// ���� ū ���� ���� ��� ���
	curr = head;

	while (curr != NULL)
	{
		if (curr->data == maxData)
		{
			PrintNode(curr);
		}
		curr = curr->next;
	}

	curr = NULL;
}

void Swap(Node* a, Node* b)
{
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}

bool SortList()
{
	for (Node* curr = head; curr != NULL; curr = curr->next)
	{
		for (Node* prev = curr->next; prev != NULL; prev = prev->next)
		{
			if (curr->data < prev->data)
			{
				Swap(curr, prev);
			}
		}
	}
	
	return true;
}

void FreeList()
{
	Node* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	head = NULL;
	tail = NULL;
	temp = NULL;
}
