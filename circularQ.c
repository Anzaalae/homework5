/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear, size;
	// isFull(), isEmpty()�� ���� Ȯ���� ���� ť�� ����� �������� ���� size ���� �߰�
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
int enQueue(QueueType *cQ, element item);
int deQueue(QueueType *cQ);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{	// �й��� �̸��� ���� ��� ù �ٿ� ���
	printf("[----- [Kim Yejun]  [2020025051] -----]\n\n");

	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
		// 'q' �Ǵ� 'Q'�Է��� �� ���� �Է��� Ŀ�ǵ� ���� ���� ����
		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{	// ���α׷� ���� �� ���� ť ����
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	cQ->size = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{	// ���α׷� ���� �� ���� ť �迭 �޸� ���� �Ҵ� ����
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
{	// ť�� �����͸� �ֱ� �� �ش� �����͸� �Է� ����
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

int isEmpty(QueueType *cQ)
{	// ����ť�� ������� Ȯ��
	// cQ����ü ������� size�� front�� rear�� �������� ����Ű���� Ȯ��
	if(cQ->front == cQ->rear && cQ->size == 0) return 1;
	else return 0;
}

int isFull(QueueType *cQ)
{	// ����ť�� ���� á���� Ȯ��
	// cQ����ü ������� size�� front�� rear�� �������� ����Ű���� Ȯ��
	if(cQ->front == cQ->rear && cQ->size == 4) return 1;
    else return 0;
}


int enQueue(QueueType *cQ, element item)
{   // ť�� ���� á���� ���� Ȯ�� �� ���� á�ٸ� ���� á�ٴ� �޽��� ���
	if(isFull(cQ)) {
		printf("Queue is fully occupied!!!\n");
		return 0;
	}
	// rear ���� ��ĭ ������ �̵���Ų �� rear�� ��ġ�� �ش��ϴ� ť �迭 ��ġ�� ������ �߰�
	cQ->rear= (cQ->rear+ 1) %4;
	cQ->queue[cQ->rear]= item;
	cQ->size++;
	// ������ ���� ������ �ǹ�
	return 0;
}

int deQueue(QueueType *cQ)
{	// ť�� �̹� ����ִ��� ���� Ȯ�� �� ����ִٸ� �̹� ť�� ����ִٴ� �޽��� ���
	if(isEmpty(cQ)) {
		printf("Queue is already empty!!!\n");
		return 0;
	}
	// ť�� ���� ù �������� ��ġ�� ����Ű�� front ������ ������Ŵ
	cQ->front= (cQ->front+ 1) %4;
	cQ->size--;
	// ������ ���� ���Ҹ� �ǹ�
    return 0;
}


void printQ(QueueType *cQ)
{	// size ������ ũ�⸸ŭ ť�� ������ ���
	int first, i= 0;
	// first ������ ť�� ������ ���� �� ������ �ǹ�
	first = (cQ->front + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	while(i != cQ->size){
		printf("%3c", cQ->queue[first]);
		first = (first+ 1)% MAX_QUEUE_SIZE;
		i++;
	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{
	// front ������ ������ ũ�⸦ �̿��� ť���� ���� �տ� �ش��ϴ� �迭 ��ġ�� front ���
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}