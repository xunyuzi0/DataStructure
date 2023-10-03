#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//！！基于链式存储结构的栈！！
//本程序完成了链式栈的数据结构和部分算法

//定义每一个结点的结构，和链表结构相同
typedef struct Node {

	int data;
	struct Node* PNext;

}NODE, * PNODE;

/*定义栈的结构, 需要和结点结构配合
栈包含两个结点指针，其中pBottom指向栈的最后一个结点
pTop指向栈的第一个结点*/
typedef struct Stack {

	PNODE pTop;
	PNODE pBottom;

}STACK, * PSTACK;

bool init_Stack(PSTACK);
bool push_Stack(PSTACK, int);
bool pop_Stack(PSTACK, int*);
void show_Stack(PSTACK);
bool isEmpty_Stack(PSTACK);
bool clear_Stack(PSTACK);

int main() {

	int temp = 0;//临时储存出栈结点数据

	STACK S;
	if (init_Stack(&S)) {
		printf("初始化栈成功！\n");
	}
	show_Stack(&S);

	push_Stack(&S, 3);
	push_Stack(&S, -45);
	push_Stack(&S, 99);
	push_Stack(&S, 0);
	push_Stack(&S, 100);
	push_Stack(&S, 3);
	show_Stack(&S);

	if (pop_Stack(&S, &temp)) {
		printf("出栈成功，出栈结点数据为：%d\n", temp);
	}
	show_Stack(&S);

	if (pop_Stack(&S, &temp)) {
		printf("出栈成功，出栈结点数据为：%d\n", temp);
	}
	show_Stack(&S);

	if (clear_Stack(&S)) {
		printf("清空栈成功！\n");
	}
	show_Stack(&S);

	return 0;
}


//初始化栈————结果为创建一个结点，并使得pTop和pBottom指向该结点
//类似于链表的头结点，该结点数据域不储存有效值，仅为了方便算法处理
//但不同在于其指针域为NULL，在栈的地位实际上为尾结点
bool init_Stack(PSTACK ps) {

	if (!isEmpty_Stack(ps)) {
		printf("栈不为空，初始化失败！\n");
		return false;
	}

	ps->pTop = (PNODE)malloc(sizeof(NODE));//创建一个结点
	if (ps->pTop == NULL) {
		printf("内存分配失败,初始化失败！\n");
		exit(-1);
	}
	else {
		ps->pTop->PNext = NULL;
		ps->pTop->data = NULL;
		//注意该结点数据域与指针域都为NULL

		ps->pBottom = ps->pTop;
		//由于是初始化，pTop与篇pBottom都指向该结点
	}

	return true;
}

//实现压栈操作，即将一个数据储存进栈中
//值得注意的是，由于栈的特点——先进后出，且只能从pTop处压栈与出栈
//使得压栈函数的参数不需要也不可以选择压入位置
bool push_Stack(PSTACK ps, int val) {

	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if (pNew == NULL) {
		printf("动态内存分配失败！\n");
		exit(-1);
	}

	pNew->PNext = ps->pTop;//将新结点插入pTop之上
	pNew->data = val;//将数据录入新结点
	ps->pTop = pNew;//更新pTop为新结点

	return true;
}

//实现出栈操作，
//将pTop指向的结点释放，被释放结点的数据通过*val传回
//同时pTop指向下一个结点
bool pop_Stack(PSTACK ps, int* val) {

	if (isEmpty_Stack(ps)) {
		printf("栈为空，出栈失败！");
		return false;
	}

	PNODE p = ps->pTop;//临时储存pTop
	ps->pTop = p->PNext;//令pTop指向下一个结点

	*val = p->data;//通过指针传回出栈数据

	free(p);//释放p结点的内存！！！
	p = NULL;

	return true;
}

//实现栈的遍历输出
void show_Stack(PSTACK ps) {

	if (isEmpty_Stack(ps)) {
		printf("栈为空，遍历输出失败！\n");
		return false;
	}

	int i = 1;
	PNODE p = ps->pTop;
	/*为了不改变原有pTop与pBottom，
	新建一个临时结点作为跑标*/

	while (p != ps->pBottom)
	{
		printf("%d:%d  ", i, p->data);
		i++;
		p = p->PNext;
	}
	printf("\n");

}

//实现对栈的判空，空返回true，否则返回false
bool isEmpty_Stack(PSTACK ps) {

	return (ps->pTop == ps->pBottom);

}

//实现将栈置空，即清空每个元素，但栈不销毁
bool clear_Stack(PSTACK ps) {

	PNODE p = ps->pTop;
	PNODE q = NULL;//定义两个指针变量做为跑标遍历栈
	//其中一个指向待删除的结点，一个指向下一个结点

	if (isEmpty_Stack(ps)) {
		printf("栈为空，置空失败！\n");
		return false;
	}

	while (p != ps->pBottom) {
		q = p->PNext;
		free(p);//释放p指向的结点的空间
		p = q;
	}
	ps->pTop = ps->pBottom;//注意！！

	p = NULL;
	q = NULL;

	return true;
}