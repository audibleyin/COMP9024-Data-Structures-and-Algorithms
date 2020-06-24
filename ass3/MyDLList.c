#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


//Creating the data structures for the Doubly linked list
//Struct of a node.
typedef struct DLListNode {
	int  value; 
	struct DLListNode *prev;
	struct DLListNode *next;
} DLListNode;
// Struct of a list
typedef struct DLList{
	int  size;
	DLListNode *first; 
	DLListNode *last;  
} DLList;

// Create a new DListnode.
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}
//Creating a new DLList.
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

//helper Functions...
// 1) connecting 2 nodes
// The function below connects two nodes to form a doubly linked list...
void connecting_2_nodes(DLListNode *node_1, DLListNode *node_2){ 
	node_1->next = node_2; //Setting the next node to the second node.
	node_2->prev = node_1; //Setting the prev node of node_2 to the first
}
//2) converting an array to a doubly linked list..
// This function takes an array and he size of the array and returns a DLL.. 
// Time complexity is o(n) where n is the size of the array entered.
DLList *DLL_from_array(DLList *DLL, int numbers[], int size_array){
	DLListNode *p; 
	DLListNode *p_2[size_array];				//Intializing an array of List nodes.
	int i;
	for (i = 0; i<= size_array-1; i++){			//Looping through the array and storing the nodes in the array of nodes.
		p_2[i] = newDLListNode(numbers[i]);
	}
	for(i = 0; i< size_array-1; i++){			//Connecting the nodes 1 by 1 using the hlper function 1.
		connecting_2_nodes(p_2[i], p_2[i+1]);
	}
	DLL -> first = p_2[0];						//Setting the first node.
	DLL -> last = p_2 [size_array-1];			//Setting the last node of the list.
	DLL ->size = size_array;					//Saving the size of the array on the DLL. 
	return (DLL);
}
//3)Checking if an element is in an array
//Used in setunion code. Has time complexity of o(m) where m is the size of the array in which checking is done. 
int element_checker(int element,int array[], int size)
{
	int i;
	for(i = 0; i<= size; i++){
		if(array[i] == element){
			return(1);
		}
	}
	return(0);
}

// Assignment start....
//Reading a file and outputiing the Doubly linked list...
//Time Compexity for the function CreateDLListFromFileDlist:
//case (stdin): o(2n) + constant  = o(n). 
//case (file): O(3n) = o(n).
//Time complexity is o(n)(Only one while loop) where n is the number of integers inputted.
//1
DLList *CreateDLListFromFileDlist(const char *file_name){
	if ((strcmp(file_name, "stdin")) == 0){ // If the input is on stdin 
		DLList *list_1; 					// Intializing an array
		list_1 = newDLList();
		DLList *list_return;
	    int numbers[1000], l = 0, c, bytes; // Numbers is to store the input as ints in the array 
	    char input[1000];					//character string to store the chars.
	    fgets(input, sizeof(input), stdin); // fgets to get the inout, size and from stdin.
	    char* input1 = input;				//Pointer to the char array.
	    while (sscanf(input1, "%d%n", &c, &bytes) > 0) { //sscanf function to scan input and get the number of bytes
	        numbers[l++] = c;							 //Storing the numbers in an array.
	        input1 += bytes;							 //Jumping the pointer by the inputted number of bytes. 
	    }
	    list_return = DLL_from_array(list_1, numbers, l); // helper function for getting a DLL from an array. 
	    return list_return;
	}
	int c=0;  						// Creating a counter c for counting the size of the integers in the file
	DLList *list_1; 				// Intializing an array
	list_1 = newDLList(); 
	DLList *list_return;  			// Defining an DLL for returning
	FILE *fp; 						// Creating a file pointer
	int numbers[1000]; 				// Creating an array of size 1000 
	int i =0; 
	fp = fopen(file_name, "r"); 	// opening the file which is passed to the function.
		while (!feof (fp)) 			//Looping till end of file is found
		    {
		      numbers[c] = i; 		//storing the inputer int into an array.
		      fscanf (fp, "%d", &i);//scanning the file for 1 integer
		      c++;      			// Increasing the length for every loop
		    }
   	fclose(fp);
   	int j;
   	for(j =0; j<c-1;j++){ 			//Looping through the list to accomodate the head and tail of a doubly linked list
   		numbers[j] = numbers[j+1];
   	}
   	list_return = DLL_from_array(list_1, numbers, c-1); // calling the helper function..
   	return (list_return);			//Returning the list.
}
//2) Printing a Doubly linked list...
//TIme complexity o(n) + constant = o(n).
//Time complexity for printDLLList is o(n) where n is the length of the list 
void printDLList(DLList *u)
{

	DLListNode *p;					//Pointer for pointing to the head
	printf("\n"); 					
	int i;						
	p = u->first;					//Pointer points to the first node of the inputted list
	while(p != NULL){				//Checking if the pointer is NULL to end the loop
		printf("%d\n",p->value);	//Printing the value
		p= p->next;					//Traversing through all the
	}
}
//3) Cloning a list from an orignal list...
//This code is to make a new list out of a doubly linked list
//o(2n) because of a for loop and the other one because of the helper function. = o(n)
//Time complexity for this code is o(n) where n is the length of the list...
DLList *cloneList(DLList *u)
{
	DLList *list_return; //Defining The lis for an return
	DLList *list_1;		 // New list for our operations...
	list_1 = newDLList();//New DLL_list being created
	DLListNode *pointer;
	int length = 0;     // Intialising the length for The DLL...
	int array[100];		//Array to save the values from a doubly linked list
	
	for(pointer = u -> first; pointer!= NULL; pointer = pointer->next){ //Looping through the list to get all the values.
		array[length] = pointer -> value;
		length++;
	}
	list_return = DLL_from_array(list_1,array,length); // Using the helper function to return a doubly linked list.
	return (list_return);	
}
//4) Set union operations on DDL...
//Function for finding Intersection of the two Doubly linked list
//Time complexity is o(mn) where m and n are the lengths of u and v respectively. 
DLList *setIntersection(DLList *u, DLList *v)
{
 DLList *list_return;        // Defining a DDl for returning..
 list_return = newDLList();	 // Creating a new DDL
 DLList *list_1;			
 int array[100];			 //Arrray to store the values from the union of the DDLs
 DLListNode *p_1, *p_2;		 //Intialising two node pointers Which will point to each list
 int length = 0;			 //Length of the doubly linked list

 for(p_1 = u->first; p_1 != NULL; p_1 = p_1 ->next){ // Looping through the first DDL
 	for (p_2 = v -> first; p_2!= NULL; p_2 = p_2 -> next){ //Looping through the second DLL
 		if (p_1->value == p_2->value){				//Checking if value is the same in both the DLL 
 			array[length] = p_1->value;				//Saving the value in an array...
 			length++;								//increasing the length of each matrix
 			break;
 		}
 	}
  }
  list_return = DLL_from_array(list_return, array,length);
  return (list_return);								//Returning the list...
} 
//5) Set Union operations on Doubly linked list....
// Time complexity: o(mn) where m and n are the lengths of the lists respectively..
DLList *setUnion(DLList *u, DLList *v)
{
 DLList *list_return;
 DLList *list_1;
 list_return = newDLList();
 int array[100];  							//Intialising an array for storing the values of a list in 
 DLListNode *p_1, *p_2;
 int length = 0;
 for(p_1 = u->first; p_1 != NULL; p_1 = p_1 ->next){ // Loop for storing the values of list 1.
 	array[length] = p_1->value;

 	length++;
 }
 int length_1 = length;

 for (p_2 = v-> first; p_2 != NULL;p_2= p_2->next){  // Comparing if a value is there in the array 
 	if(element_checker(p_2->value, array, length-1)== 0){ // Running an helper function. Which has a time complexity of o(n) Where n is the length of the first list.
 		array[length_1] = p_2->value; 					  // Adding the value if it is not there in the array but there in list 2
 		length_1++;
 	}
 }
  list_return = DLL_from_array(list_return, array,length_1); //Helper function to return the array in the form of a DLL.(o(m)) Time complexity. 
  return (list_return);
} 
//6) Freeing the Doubly linked list...
//Time complexity of freeDLList is o(n) where n is the length of the list L.
void freeDLList(DLList *L)
{
	DLListNode *current;
	DLListNode *next_node;
	int i  = 0; 
	current = L->first;
	while (current!= NULL){
		next_node = current -> next;
		free(current);
		current = next_node;
	}
	L->first = NULL;
	L-> last = NULL;
}



//main function
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
  freeDLList(list3);
  freeDLList(list4);

 return 0; 
}














