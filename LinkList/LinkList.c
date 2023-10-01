#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//本程序完成了链表的数据结构及部分算法

typedef struct L {

	int data;
	struct L * pNext;

}Lnode, * pLnode;//定义一个无名结构，并用typedef函数对其重命名


pLnode init_LList(void);//初始化链表
bool insert_LList(pLnode pHead, int pos, int num);//向链表插入元素
bool delete_LList(pLnode pHead);//删除整个链表的所有元素
bool delete_one_LList(pLnode pHead, int pos, int *pNum);
//删除并返回链表中某个元素
int get_LList(pLnode pHead, int pos);//获取链表某个元素
bool show_LList(pLnode pHead);//输出整个链表
bool sort_LList(pLnode pHead);//对整个链表排序
bool isEmpty_LList(pLnode pHead);//判断链表是否为空

//bool inversion_LList(pLnode pHead);//将整个链表倒置


int main(void) {

	int temp = 0;//临时储存被删除结点的值
	int num = 0;//储存用户通过get函数返回的值

	pLnode pHead = NULL;//创建一个链表结构的指针，作为头指针
	pHead = init_LList();
	show_LList(pHead);

	insert_LList(pHead, 1, 400);
	insert_LList(pHead, 2, 300);
	insert_LList(pHead, 3, 200);
	insert_LList(pHead, 1, 500);
	show_LList(pHead);

	if (delete_one_LList(pHead, 1, &temp))
		printf("删除结点成功，删除的值为：%d\n", temp);
	show_LList(pHead);

	if (num = get_LList(pHead, 3)) {
		printf("获取链表数据成功！获取的数为：%d\n",num);
	}

	if (sort_LList(pHead)) {
		printf("链表排序成功！\n");
	}
	show_LList(pHead);

	if (delete_LList(pHead))
		printf("删除所有结点成功！\n");
	show_LList(pHead);

	return 0;
}

//初始化链表
pLnode init_LList(void) {

	int i = 0;
	int cnt = 0;//储存用户需要创建的结点数
	int temp = 0;//临时存储用户需要输入的链表内容

	pLnode p = (pLnode)malloc(sizeof(Lnode));
	//创建一个结点指针，作为头结点指针
	if (p == NULL) {
		printf("动态内存分配失败1！");
		exit(-1);
	}//创建一个新结点的指针,并检查内存是否分配成功
	p->pNext = NULL;//注意指针域为空

	pLnode pLast = p;//创建一个结点，作为尾结点，初始状态为头结点

	printf("请输入需要创建的链表结点数：");
	scanf_s("%d", &cnt);

	for (i = 0; i < cnt; i++) {

		printf("请输入第%d个结点储存的数：", i + 1);
		scanf_s("%d", &temp);

		//printf("a ");

		pLnode pNew = (pLnode*)malloc(sizeof(Lnode));//新结点
		//printf("b ");
		if (pNew == NULL) {
			printf("动态内存分配失败2！");
			exit(-1);
		}
		//printf("c ");
		pNew->data = temp;//储存数据
		pNew->pNext = NULL;//注意指针域为空
		//printf("d ");

		pLast->pNext = pNew;
		pLast = pNew;//将新结点插入尾节点，新结点成为尾结点
		//printf("e ");
	}

	return p;
}


//向链表插入元素
bool insert_LList(pLnode pHead, int pos, int num) {

	int i = 0;//i从1开始的原因是p指向头结点
	//若p指向首结点，可使得i为1
	pLnode p = pHead;//使得p指向头结点

	pLnode pNew = (pLnode*)malloc(sizeof(Lnode));
	if (pNew == NULL) {
		printf("动态内存分配失败3！");
		exit(-1);
	}//创建一个新结点的指针,并检查内存是否分配成功

	pNew->pNext = NULL;
	pNew->data = num;//为该结点赋值
	
	while (p != NULL && i < pos - 1) {
		p = p->pNext;
		i++;
	}//若输入无误，则使得p指针最终指向pos前一个结点
	

	if (p == NULL || i > pos - 1) {
		printf("输入有误，创建失败！");
		return false;
	}//排除错误可能
	/*注意，此处需要留意pos等于1时的边界条件，
	 显然此时上述两个函数都不运行，p指向头结点，
	 即第一个结点的前一个结点*/

	//if (p == NULL)
	//	printf("p为空指针");
	//else
	//	printf("p不为空指针");
	// //测试代码


	pNew->pNext = p->pNext;
	p->pNext = pNew;
	//完成插入

	/*pLnode q = p->pNext;
	p->pNext = pNew;
	pNew->pNext = q;*/
	//另一种插入方式


	return true;

}

//删除整个链表
bool delete_LList(pLnode pHead) {

	pLnode p = pHead;//使得p指向头结点

	if (isEmpty_LList(pHead)) {
		printf("链表为空，删除失败！\n");
		return false;
	}

	while (p->pNext != NULL) {

		pLnode r = p->pNext;//临时储存待删除结点
		p->pNext = p->pNext->pNext;//使用下一个结点覆盖待删除结点
		free(r);//手动释放删除结点的内存

	}
	
	return true;
}

//删除并返回链表中某个元素
bool delete_one_LList(pLnode pHead, int pos, int* pNum) {

	int i = 0;
	pLnode p = pHead;//使得p指向头结点

	while (p != NULL && i < pos - 1) {
		p = p->pNext;
		i++;
	}//若输入无误，则使得p指针最终指向pos前一个结点

	if (p == NULL || i > pos - 1) {
		printf("输入有误，删除失败！");
		return false;
	}//排除错误可能
	/*注意，此处需要留意pos等于1时的边界条件，
	 显然此时上述两个函数都不运行，p指向头结点，
	 即第一个结点的前一个结点*/

	*pNum = p->pNext->data;//将所删除结点的值赋给num

	pLnode r = p->pNext;//使得r指向需要删除的结点
	p->pNext = p->pNext->pNext;//用删除结点的下一个结点地址覆盖删除节点
	free(r);
	//注意！！！
	//必须手动释放删除结点的内存！！！！

	return true;
}

//获取链表某个元素
int get_LList(pLnode pHead, int pos) {

	int i = 0;
	pLnode p = pHead;

	for (i = 0; i < pos; i++) {
		p = p->pNext;
	}/*注意这个循环中i与p的微妙关系
	其中i表示p为当前第几个结点，且i为0表示头结点
	循环结束时i=pos，即p为需要获取的结点*/

	return p->data;

}

//输出整个链表
bool show_LList(pLnode p) {

	int i;

	if (isEmpty_LList(p)) {
		printf("链表为空，输出失败！");
		return false;
	}

	for (i = 0; p->pNext != NULL; p = p->pNext, i++) {
		printf("%d:%d   ", i + 1, p->pNext->data);
	}//注意p初始时指向的是头结点，其数据域无有效数据
	printf("\n");

	return true;

}

//对整个链表排序
bool sort_LList(pLnode pHead) {

	if (isEmpty_LList(pHead)) {
		printf("链表为空，排序失败！");
		return false;
	}

	pLnode p = pHead->pNext;//使得p指向首结点
	pLnode r = pHead->pNext->pNext;//使得p指向第二个有效结点

	for (p = pHead->pNext ; p->pNext != NULL ; p = p->pNext) {
		for (r = p->pNext ; r != NULL ; r = r->pNext) {
			if (r->data < p->data) {

				int temp = r->data;
				r->data = p->data;
				p->data = temp;//交换使得小的值永远在链表的前面

			}
		}
	}
	return true;
}

////将整个链表倒置
//bool inversion_LList(pLnode pHead) {
//
//	if (isEmpty_LList(pHead)) {
//		printf("链表为空，排序失败！");
//		return false;
//	}
//
//	pLnode p = pHead;//pLast用来指向链表的头结点
//	pLnode pLast = pHead;//pLast用来指向链表的尾结点
//
//	while (pLast->pNext != NULL) {
//		pLast = pLast->pNext;
//	}//使得pLast指向链表尾结点
//
//	for(;;p = p->pNext)
//
//}

//判断链表是否为空
bool isEmpty_LList(pLnode pHead) {

	return(pHead->pNext == NULL);

}
