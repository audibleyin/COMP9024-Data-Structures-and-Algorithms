// Author:
// Student ID:
// Platform: (select one of Windows, Unix, Mac)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 
// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
	int  value;  // value (int) of this list item 
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
	int  size;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	DLList *L;

	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}
//**************************

void TraverList(DLList *plist,void(*Traver)(DLListNode *pnode)){
	
	DLListNode *ptemp = plist->first;
	int list_size = plist->size;;
	while(list_size){
		Traver(ptemp);
		ptemp = ptemp->next;
		list_size--;
	}
}

void ShowData(DLListNode *pnode){
	printf("%d\n",pnode->value );
}

void Clear(DLListNode *pnode){
	free(pnode->prev);
}

int Is_Empty(DLList *plist){

	if(plist->size == 0)
		return 1;
	else
		return 0;
}

void Insert_List(DLList *plist, DLListNode *pnode){
	if(Is_Empty(plist)){
		plist->first = pnode;
		plist->last = pnode;
	}
	else{
		plist->last->next = pnode;
		pnode->prev = plist->last;
	}
	plist->last = pnode;
	plist->size++;
}


int cutnumber(int a[],int length){
for (int i = 0; i < length - 1; i++){
	for (int j = i + 1; j < length; ){
		if (a[i] == a[j]){
			for (int k = j; k < length - 1; k++)
				a[k] = a[k + 1];
			length--;
		}
		else
			j++;
	}
	}
	return length;
}


//**************************


// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here
DLList *CreateDLListFromFileDlist(const char *filename)
{
 // put your code here
	DLList *list1;
	DLListNode *node;
	list1 = newDLList();
    FILE *fp;
    char buff[4];
    fp = fopen(filename,"r");
	while (fscanf(fp, "%s", buff) != EOF)
	    {
	        node = newDLListNode(atoi(buff));
			Insert_List(list1, node);
	    }
    fclose(fp);

	return list1;
}

// clone a DLList
// put your time complexity analysis for cloneList() here
DLList *cloneList(DLList *u)
{
 // put your code here
	DLListNode *ptemp = u->first;
	DLList *list_copy;
	DLListNode *node_copy;
	list_copy = newDLList();
	int list_size = u->size;
	while(list_size){
		node_copy = newDLListNode(ptemp->value);
		Insert_List(list_copy, node_copy);
		ptemp = ptemp->next;
		list_size--;
	}
	return list_copy;
}

// compute the union of two DLLists u and v
DLList *setUnion(DLList *u, DLList *v)
{
 // put your code here
	DLList *set;
	DLListNode *node, *ptemp = u->first;
	int u_size = u->size,v_size = v->size;
	int size = u_size + v_size;
	int arr[size], count=0;
	set = newDLList();
	while(u_size){
		arr[count] = ptemp->value;
		ptemp = ptemp->next;
		u_size--;
		count++;
	}
	DLListNode *ptemp2 = v->first;
	while(v_size){
		arr[count] = ptemp2->value;
		ptemp2 = ptemp2->next;
		v_size--;
		count++;
	}
	size = cutnumber(arr,size);
	for (int i = 0; i < size; ++i)
	{	
		node = newDLListNode(arr[i]);
		Insert_List(set, node);
	}
	return set;
}

// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here
DLList *setIntersection(DLList *u, DLList *v)
{
  // put your code here
	DLList *set;
	DLListNode *node, *ptemp = u->first;
	int u_size = u->size,v_size = v->size;
	int size = u_size + v_size;
	int arr1[u_size],arr2[v_size],count=0;
	set = newDLList();
	while(u_size){
		arr1[count] = ptemp->value;
		ptemp = ptemp->next;
		u_size--;
		count++;
	}
	count=0;
	DLListNode *ptemp2 = v->first;
	while(v_size){
		arr2[count] = ptemp2->value;
		ptemp2 = ptemp2->next;
		v_size--;
		count++;
	}
	u_size = u->size,v_size = v->size;
	u_size = cutnumber(arr1,u_size);
	v_size = cutnumber(arr2,v_size);
	for(int i = 0; i< u_size; i++){
		for (int j = 0; j < v_size; j++)
		{
			if (arr1[i]==arr2[j]) {
				node = newDLListNode(arr1[i]);
				Insert_List(set, node);
			}
		}

	}
	
	return set;
}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here
void freeDLList(DLList *L)
{
// put your code here	
	// TraverList(L,Clear);
	DLListNode *head = L->first, *node;
	while(head != NULL){
		node = head;
		head = head->next;
		free(node);
	}

}


// display items of a DLList
// put your time complexity analysis for printDDList() here
void printDLList(DLList *u)
{
 	TraverList(u,ShowData);
}

int main()
{
 DLList *list1, *list2, *list3, *list4;

 list1=CreateDLListFromFileDlist("File1.txt");
 printDLList(list1);
 list2=CreateDLListFromFileDlist("File2.txt");
 printDLList(list2);

 list3=setUnion(list1, list2);
 printDLList(list3);

 list4=setIntersection(list1, list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 printf("please type all the integers of list1\n");
 list1=CreateDLListFromFileDlist("stdin");

 printf("please type all the integers of list2\n");
 list2=CreateDLListFromFileDlist("stdin");

 list3=cloneList(list1);
 printDLList(list3);
 list4=cloneList(list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 printDLList(list1);

 freeDLList(list3);
 freeDLList(list4);

 return 0; 
}