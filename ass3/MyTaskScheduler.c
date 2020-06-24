#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// This template is only a guide
// You need to include additional fields, data structures and functions

typedef char bool;

// data type for heap nodes
typedef struct HeapNode {
    // each node stores the priority (key), name, execution time,
    // release time and deadline of one task
    int    key;       	// key of this task
    int    TaskName;  	// task name
    int    Etime; 			// execution time of this task
    int    Rtime; 			// release time of this task
    int    Dline; 			// deadline of this task
    // add additional fields here
    struct HeapNode *child;      // each node has multiple children
    struct HeapNode *parent;     // parent node of each child node 
    struct HeapNode *pre;		    // linked-list-like list of nodes
    struct HeapNode *next;		    // linked-list-like list of nodes
                        // store the left most
    int    depth;       // heap depth
} HeapNode;

//data type for a priority queue (heap)
typedef struct BinomialHeap {
	// this is heap header
    int size;      // count of items in the heap
    // add additional fields here
    HeapNode  *roots;	 // a set of roots
} BinomialHeap;

// Forward References
int Min(BinomialHeap *);
// create a new heap node to store an item (task)
HeapNode *newHeapNode(int k, int n, int c, int r, int d)
{
	// k:key, n:task name, c: execution time, r:release time, d:deadline
  	// ... you need to define other parameters yourself)
    HeapNode *new;
    new = malloc(sizeof(HeapNode));
    assert(new != NULL);
    new->key = k;
    new->TaskName = n;
    new->Etime = c;
    new->Rtime = r;
    new->Dline = d;
    // initialise other fields
    new->child = NULL;
    new->pre  = NULL;
    new->next  = NULL;
    new->depth = 0;
    return new;
}

// create a new empty heap-based priority queue
BinomialHeap *newHeap()
{ // this function creates an empty binomial heap-based priority queue
    BinomialHeap *T;
    T = malloc(sizeof(BinomialHeap));
    assert (T != NULL);
    // initialise all the fields here
    T->roots = NULL;
    return T;
}

// helper function - merge two heaps H1 and H2 into a new Heap
// result will be mapped to Heap1
HeapNode *MergeHeap(HeapNode *Heap1, HeapNode *Heap2)
{
    HeapNode *next = Heap1->next;
    if (Heap1->key < Heap2->key)
    {
        if (Heap1->child!=NULL)
        Heap1->child->pre = Heap2;
        Heap2->parent = Heap1;
        Heap2->next = Heap1->child;
        Heap2->pre = NULL;
        Heap1->child = Heap2;
        Heap1->next = next;
        Heap1->depth += 1;
        return Heap1; 
    }
    else if (Heap2->child)
        Heap2->child->pre = Heap1;
        Heap1->parent = Heap2;
        Heap1->next  = Heap2->child;
        Heap1->pre = NULL;
        Heap2->child  = Heap1;      
        Heap2->pre = Heap1->pre;
        Heap2->depth += 1;
        return Heap2;
}

void MergeSelf(HeapNode **Heap)
{
    HeapNode *curNode = *Heap;
    while (curNode->next)
    {   HeapNode *next = curNode->next->next;
        if (curNode->depth == curNode->next->depth)
        {
            curNode = MergeHeap(curNode, curNode->next);
            if (curNode->pre)
            {
                curNode->pre = curNode->pre;
                curNode->pre->next = curNode;
            }
            else
                *Heap = curNode;
                curNode->next = next;
            if (next)
                next->pre = curNode;
                continue;
        }
        curNode = curNode->next;
    }
}

// helper function - merge two Bheaps T1 and T2 into a new Heap
// result will be mapped to T1
// O(logn) 

BinomialHeap *Merge(BinomialHeap *T1, BinomialHeap *T2)
{
    // directly return - one node results in zero depth
    if( (T1->roots == NULL) || (T2->roots==NULL)){
        if (T1->roots == NULL){
            return T2;
        }else{return T1;}}
    HeapNode *curNode1 = T1->roots;	// start with the B_0 in both Ts
    HeapNode *curNode2 = T2->roots;
    BinomialHeap *base = newHeap();
    HeapNode *nw_heap = NULL;
    HeapNode **newNode = &nw_heap;
       
    HeapNode *pre = NULL;	// previous relation builds up by callback
    while (1)
    {
        base->size += 1;
        if (curNode1==NULL && curNode2==NULL) break;
        else if (curNode1==NULL)
        {
            *newNode = curNode2;
            (*newNode)->pre = pre;
            if (!curNode2->next)
                {break;} 
            else
                {curNode2 = curNode2->next;}
        }
        else if (!curNode2)
        {
            *newNode = curNode1;
            (*newNode)->pre = pre;
            if (!curNode1->next){
            break;}else{
            curNode1 = curNode1->next;}     
        }
        else if (curNode1->depth < curNode2->depth)
        {
            *newNode = curNode1;
            curNode1 = curNode1->next;
            (*newNode)->pre =pre; 
        }
        else if (curNode1->depth > curNode2->depth)
        {
            *newNode = curNode2;
            curNode2 = curNode2->next;
            (*newNode)->pre = pre;
        }
        else if (curNode1->depth == curNode2->depth)
        {  
            HeapNode *curr1_next = curNode1->next;
            HeapNode *curr2_next = curNode2->next;
            *newNode = MergeHeap(curNode1, curNode2);
            (*newNode)->pre = pre;
            curNode1 = curr1_next;
            curNode2 = curr2_next;
        }
        pre = (*newNode);
        newNode = &((*newNode)->next);
    }
    MergeSelf(&nw_heap);
    base->roots = nw_heap;
    return base;
}

// put the time complexity analysis for Insert() here
// O(logn) - As bottom-up construction somehow costs much more than
void Insert(BinomialHeap *T, int k, int n, int c, int r, int d)
{
    // k: key, n: task name, c: execution time, r: release time, d:deadline
    HeapNode *newNode;
    newNode = newHeapNode(k, n, c, r, d);
    BinomialHeap *new_heap = newHeap();
    new_heap->roots = newNode;
    new_heap->size  = 1;
    *T = *Merge(T, new_heap);	// assign new BinomialHeap
}

// put your time complexity for RemoveMin() here
// O(log n) - As RemoveMin only cares about the roots node
HeapNode *RemoveMin(BinomialHeap *T)
{
    // put your code here
    HeapNode *result = NULL;
    HeapNode *newT = T->roots;
    int min = Min(T);
    while (newT!=NULL)
    {
        if (newT->key == min)
        {
            // store the entry
            result = newT;
            // rearrange the remaining
            HeapNode *next = newT->next;
            if (newT->pre){
                newT->pre->next = next;
            }else{
                T->roots = newT->next;
            }
            // generating new forest
            BinomialHeap *newforest = newHeap();
            HeapNode *prev1 = NULL;
            HeapNode **root = (&result->child);
            HeapNode *curNode = *root;
            HeapNode *next1 = NULL;
            while (curNode)
            {
            next1 = curNode->next;
            curNode->next = prev1;
            prev1 = curNode;
            curNode = next1;
            if (prev1)
            prev1->pre = curNode;
            }
            *root = prev1;
            newforest->roots = result->child;
            if (next){
                next->pre = newT->pre;
                }
            *T = *Merge(T, newforest);
            T->size -= 1;
            break;
        }
        newT = newT->next;
    }
    return result;
}

int Min(BinomialHeap *T)
{
    // put your code here
    HeapNode *root;
    root = T->roots;
    if(root != NULL){	// empty BinomialHeap does not have a min here

    int result = root->key;
    while (root!=NULL)
    {
        if (root -> key < result)
            result = root -> key;
        root = root->next;
    }
    return result;
}}

void PrintBinomialHeap(HeapNode *H)
{
    HeapNode *curNode = H;
    while (curNode!=NULL)
    { 
        PrintBinomialHeap(curNode->child);
        curNode = curNode->next;
    }
}
void readTasksFromFile(char *fileName, BinomialHeap *T) {

    fprintf(stderr, "%s\n", "file1 does not exsit");
    exit(1);
}
// put your time complexity analysis for MyTaskScheduler here
int TaskScheduler(char *f1, char *f2, int m)
{
    // put your code here
    
    
    BinomialHeap *r_heap = newHeap();	// release time as key
    BinomialHeap *d_heap = newHeap();	// deadline as key
    BinomialHeap *cores  = newHeap();	// core scheduling priority queue
    FILE *fp_in  = fopen(f1, "r");
    if(!f1){
    readTasksFromFile(f1,r_heap);} 
    else{   
    int v = 0;	// priority key
    int c = 0;	// execution time
    int r = 0;	// release time
    int d = 0;	// deadline

    int count = 0;	// increment variable
    while ((fscanf(fp_in, "%d %d %d %d", &v, &c, &r, &d)) != EOF)
    {
        Insert(r_heap, r, v, c, r, d);
        count++;
    }
    int size = count;
    int i = 0;
    int index = 1;
    int curtime = 0;	// scheduling point
    FILE *fp_out = fopen(f2, "w");	// exception 2:
    // "w" destory contents create new
    while (r_heap->size>0 || d_heap->size)
    {
        if (i == size) break;
        while (r_heap->roots && Min(r_heap) == curtime)	// task is ready
        {
            HeapNode *node = RemoveMin(r_heap);
            // store all tasks with the same release time and sort them by deadline as key in ascending depth
            Insert(d_heap, node->Dline, node->TaskName,
                   node->Etime, node->Rtime, node->Dline);
            if(r_heap->roots){continue;}else{break;}
        }
        PrintBinomialHeap(d_heap->roots);
        while (cores->roots)	// empty the in-time free cpu
        {
            if (Min(cores) == curtime){ 
                if(curtime != 0)
            {
                RemoveMin(cores);
                index--;
            }}
            else break;
        }
        while (d_heap->roots)
        {
  
            if (index <= m){
                HeapNode *task = RemoveMin(d_heap);
                if (task->Etime + curtime > task->Dline) // infesaible condition
                {
                    fprintf(fp_out, "Infeasible\n");
                    fclose(fp_in);
                    fclose(fp_out);
                    return 0;
                }
                Insert(cores, task->Etime + curtime, index, 0, 0, 0);
                fprintf(fp_out, "%d Core%d %d ", task->TaskName, index++, curtime);
                i++;
            }
            else{ break;}
        }
        curtime++;
    }
    fprintf(fp_out, "\n");
    fclose(fp_in);
    fclose(fp_out);
    return 1;
    }
}

int main() //sample main for testing 
{ 
  int i;
  i=TaskScheduler("samplefile1.txt", "feasibleschedule1.txt", 4);
  if (i==0) printf("No feasible schedule!\n");
  /* There is a feasible schedule on 4 cores */
  i=TaskScheduler("samplefile1.txt", "feasibleschedule2.txt", 3);
  if (i==0) printf("No feasible schedule!\n");
  /* There is no feasible schedule on 3 cores */
  i=TaskScheduler("samplefile2.txt", "feasibleschedule3.txt", 5);
  if (i==0) printf("No feasible schedule!\n");
  /* There is a feasible schedule on 5 cores */
  i=TaskScheduler("samplefile2.txt", "feasibleschedule4.txt", 4);
  if (i==0) printf("No feasible schedule!\n");
  /* There is no feasible schedule on 4 cores */
  i=TaskScheduler("samplefile3.txt", "feasibleschedule5.txt", 2);
  if (i==0) printf("No feasible schedule!3\n");
  /* There is no feasible schedule on 2 cores */
  i=TaskScheduler("samplefile4.txt", "feasibleschedule6.txt", 2);
  if (i==0) printf("No feasible schedule!\n");
  return 0; 
}