#include<stdio.h>
#include<stdbool.h>//提供bool数据类型 
#include<stdlib.h>//提供malloc函数 

//本程序完成了顺序表数据结构以及部分算法 

//创建一个结构体用来描述顺序表数据结构 
typedef struct Array {

	int* pArr;//存放顺序表首元素地址的指针变量 
	int length;//存放顺序表的长度 
	int cnt;//有效元素个数 

} ArrayList, pArrayList;

bool init(ArrayList* pArray, int len);
bool append(ArrayList* pArray, int num);
bool insert(ArrayList* pArray, int pos, int num);
bool delete_Arr(ArrayList* pArray, int pos, int* num);
bool clear(ArrayList* pArray);
int get(ArrayList* pArray, int pos);
bool is_full(ArrayList* pArray);
bool is_empty(ArrayList* pArray);
void sort(ArrayList* pArray);
void show(ArrayList* pArray);
void inversion(ArrayList* pArray);

int main(void) {

	int len = 0;//存放顺序表长度 
	int cnt = 0;//存放顺序表有效元素个数 
	int num = 0;
	int num2 = 0;

	ArrayList arr;//创建一个模拟顺序表的结构体变量 

	printf_s("请输入需要创建的顺序表长度");
	scanf_s("%d", &len);
	if (init(&arr, len))
		printf_s("顺序表创建成功！\n");
	else
		printf_s("顺序表创建成功！\n");

	append(&arr, 41);
	append(&arr, 5);
	append(&arr, -54);
	append(&arr, 44);
	append(&arr, 14);
	show(&arr);

	if (insert(&arr, 3, 1000)) {
		printf("插入元素成功！\n");
	}
	show(&arr);

	if (delete_Arr(&arr, 4, &num)) {
		printf_s("删除元素成功！删除的元素是：%d\n", num);
	}
	show(&arr);

	sort(&arr);
	printf_s("排序后顺序表内容为：\n");
	show(&arr);

	inversion(&arr);
	printf_s("倒置后顺序表内容为：\n");
	show(&arr);

	num2 = get(&arr, 4);
	printf_s("取得的元素为%d\n", num2);

	if (clear(&arr)) {
		printf_s("清空顺序表成功！\n");
	}
	show(&arr);

	return 0;
}

//实现顺序表的初始化 
bool init(ArrayList* pArray, int len) {
	
	if (len <= 0) {
		printf_s("顺序表长度应该大于或等于1！\n");
		return false;
	}

	//为顺序表开辟一个长度为len的连续空间，并将首地址返回给顺序表结构体的pArr域 
	pArray->pArr = (int*)malloc(len * sizeof(int));

	//注意！需要检查动态内存是否分配成功，若失败malloc函数将返回NULL 
	if (NULL == pArray->pArr) {
		printf_s("动态内存分配失败！\n");
		exit(-1);
	}
	else {
		pArray->length = len;
		pArray->cnt = 0;
	}
	return true;

}

//实现顺序表的判满，若满则返回true，否则返回false 
bool is_full(ArrayList* pArray) {
	
	return (pArray->cnt == pArray->length);

}

//实现顺序表的判空，若空则返回true，否则返回false 
bool is_empty(ArrayList* pArray) {
	
	return (pArray->cnt == 0);

}

//在顺序表末尾追加一个元素 
bool append(ArrayList* pArray, int num) {
	
	if (is_full(pArray)) {
		printf_s("\n");
		return false;
	}
	else {
		pArray->pArr[pArray->cnt] = num;
		pArray->cnt++;
		return true;
	}

}

//将顺序表遍历输出 
void show(ArrayList* pArray) {

	if (is_empty(pArray)) {
		printf_s("顺序表为空，输出失败！\n");
		return false;
	}

	for (int i = 0; i < pArray->cnt; i++) {
		printf_s("%d:%d   ", i + 1, pArray->pArr[i]);
	}
	printf_s("\n");

}

//将某个元素插入到顺序表第pos个位置上，0<pos<=cnt+1
bool insert(ArrayList* pArray, int pos, int num) {

	if (is_full(pArray)) {
		printf_s("顺序表已满，插入失败！\n");
		return false;
	}
	for (int i = pArray->cnt - 1; i >= pos - 1; i--) {
		pArray->pArr[i + 1] = pArray->pArr[i];
	}
	pArray->pArr[pos - 1] = num;
	pArray->cnt++;
	return true;
	
}

//删除顺序表第pos个元素，0<pos<=cnt，并将被删除元素通过*num传回 
bool delete_Arr(ArrayList* pArray, int pos, int* num) {

	if (is_empty(pArray)) {
		printf_s("顺序表为空，删除失败！\n");
		return false;
	}

	*num = pArray->pArr[pos - 1];

	for (int i = pos; i < pArray->cnt; i++) {
		pArray->pArr[i - 1] = pArray->pArr[i];
	}
	pArray->cnt--;
	return true;

}


//清空整个顺序表 
bool clear(ArrayList* pArray) {

	if (is_empty(pArray)) {
		printf_s("顺序表为空，清空失败！\n");
		return false;
	}
	for (int i = 0; i < pArray->cnt; i++) {
		pArray->pArr[i] = 0;
	}
	pArray->cnt = 0;
	return true;

}

//将顺序表元素按从小到大排序 
void sort(ArrayList* pArray) {

	int temp = 0;

	if (is_empty(pArray)) {
		printf_s("顺序表为空，排序失败！\n");
		return false;
	}

	for (int i = 0; i < pArray->cnt - 1; i++) {
		for (int j = i + 1; j < pArray->cnt; j++) {
			if (pArray->pArr[i] > pArray->pArr[j]) {
				temp = pArray->pArr[i];
				pArray->pArr[i] = pArray->pArr[j];
				pArray->pArr[j] = temp;
			}
		}
	}
	
}

//将顺序表元素倒置 
void inversion(ArrayList* pArray) {

	int temp = 0;

	if (is_empty(pArray)) {
		printf_s("顺序表为空，倒置失败！\n");
		return false;
	}

	for (int i = 0, j = pArray->cnt - 1; i < j; i++, j--) {
		temp = pArray->pArr[i];
		pArray->pArr[i] = pArray->pArr[j];
		pArray->pArr[j] = temp;
	}

}

//返回顺序表第pos个元素，0<pos<=cnt 
int get(ArrayList* pArray, int pos) {
	
	return pArray->pArr[pos - 1];

}
