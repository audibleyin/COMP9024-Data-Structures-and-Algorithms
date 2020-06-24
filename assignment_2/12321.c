#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data type for avl tree nodes
typedef struct AVLTreeNode {
    int key; //key of this item
    int value;  //value (int) of this item
    int height; //height of the subtree rooted at this node
    struct AVLTreeNode *parent; //pointer to parent
    struct AVLTreeNode *left; //pointer to left child
    struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree {
    int size;      // count of items in avl tree
    AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v) {
    AVLTreeNode *new;
    new = malloc(sizeof(AVLTreeNode));
    assert(new != NULL);
    new->key = k;
    new->value = v;
    new->height = 0; // height of this new node is set to 0
    new->left = NULL; // this node has no child
    new->right = NULL;
    new->parent = NULL; // no parent
    return new;
}

// create a new empty avl tree
AVLTree *newAVLTree() {
    AVLTree *T;
    T = malloc(sizeof(AVLTree));
    assert (T != NULL);
    T->size = 0;
    T->root = NULL;
    return T;
}


// the time complexity is O(1)
int heightTreeNode(AVLTreeNode *t) {
     if (t == NULL) {
        return 0;
    } else {
        int left = 0, right = 0;
        if (t->left != NULL) {
            left = t->left->height;
        }
        if (t->right != NULL){
            right = t->right->height;
        }

        if (left < right) {
            return right + 1;
        } else {
            return left + 1;
        }
    }
}

int compareTreeNode(int k1, int v1, int k2, int v2) {
    int res = 0;
    // strcmp
    if (k1 == k2) {
        if (v1 == v2) {
            res = 0;
        } else if (v1 > v2) {
            res = 1;
        } else {
            res = -1;
        }
    } else if (k1 > k2) {
        res = 1;
    } else {
        res = -1;
    }
    return res;
}

//Use InOrder to convert AVLTreeNode To Array
void AVLTreeNodeToArray(AVLTreeNode *t, int *keys, int *values, int *index) {

}

//right rotation
AVLTreeNode *Right_rotation(AVLTreeNode *node1) {
    AVLTreeNode *res = NULL;
    if (node1 != NULL) {
        AVLTreeNode *node2;
        node2 = node1->left;
        if (node2!= NULL) {
            AVLTreeNode *t1, *t2, *t3;
            //read node before rotation
            t1 = node1->right;
            t2 = node2->left;
            t3 = node2->right;
            //rotate node, store in node1
            node1->right = t1;
            node1->left = t3;
            node1->height = heightTreeNode(node1);
            // store in node2
            node2->right = node1;
            node2->left = t2;
            res = node2;
        }
    }
    return res;
}

//left rotation
AVLTreeNode *Left_rotation(AVLTreeNode *node2) {
    AVLTreeNode *res = NULL;
    if (node2 != NULL) {
        AVLTreeNode *node1;
        node1 = node2->left;
        if (node1 != NULL) {
            AVLTreeNode *t1, *t2, *t3;
            //read node before rotation
            t1 = node1->right;
            t2 = node2->left;
            t3 = node1->left;
            //rotate node, store in node2
            node2->left = t2;
            node2->right = t3;
            node2->height = heightTreeNode(node1);
            // store in node1
            node1->right = t2;
            node1->left = node2;
            res = node1;
        }
    }
    return res;
}

AVLTreeNode *InsertAVLTreeNode(AVLTreeNode *t, int k, int v) {
    if (t == NULL) {
        t = newAVLTreeNode(k, v);
    } else {
        int compare_res = compareTreeNode(k, v, t->key, t->value);
        if (compare_res == 0) {
            return t;
        }
        if (compare_res > 0) {
            t->right = InsertAVLTreeNode(t->right, k, v);
        }
        if (compare_res < 0) {
            t->left = InsertAVLTreeNode(t->left, k, v);
        }
        int height_leftNode = heightTreeNode(t->left);
        int height_rightNode = heightTreeNode(t->right);
        if (height_rightNode - height_leftNode > 1) {
            compare_res = compareTreeNode(k, v, t->right->key, t->right->value);
            if (compare_res < 0) {
                t->right = Right_rotation((t->right));
            }
            t = Left_rotation(t);
        } else if (height_leftNode - height_rightNode > 1) {
            compare_res = compareTreeNode(k, v, t->left->key, t->left->value);
            if (compare_res > 0) {
                t->left = Left_rotation((t->left));
            }
            t = Right_rotation(t);
        }
    }
    //redefine height
    t->height = heightTreeNode(t);
    return t;
}

// put the time complexity analysis for InsertNode() here
// the time complexity is O(log(n))
int InsertNode(AVLTree *T, int k, int v) {
    //put your code here
    int res = 0;
    if (T != NULL) {
        T->root = InsertAVLTreeNode(T->root, k, v, &res);
    }
    // if res is equal to 1 ,the add is successful.
    if (res == 1) {
        T->size++;
    }
    return 1;
}

// put your time complexity analysis of CreateAVLTree() here
AVLTree *CreateAVLTree(const char *filename) {
    // put your code here
   	char Str[200] = {'\0'};
	char seps[]   = "(), \t\n";
	char *NodeStr;
	int key, value = 0;
	AVLTree *T;
    T = newAVLTree();
	if (strcmp(filename, "stdin") == 0)
	{
		// read all the items from the standard input
		gets(Str);
		while(strlen(Str)!=0)
		{
			NodeStr = strtok(Str, seps);
			while( NodeStr != NULL )
			{
				/* While there are Str in "string" */
				key = atoi(NodeStr);
				NodeStr = strtok( NULL, seps);
				value = atoi(NodeStr);
				NodeStr = strtok( NULL, seps );
				InsertNode(T, key, value);
			}
			gets(Str);
		}
		
	}
	else
	{
		//read all the items from a text file with filename as its full path name
		FILE *FILE = fopen(filename,  "r");
		if (FILE == NULL)
		{
			return NULL;
		}
		while(feof(FILE)==0)
		{
			fgets(Str, sizeof(Str), FILE);
			NodeStr = strtok(Str, seps);
			while( NodeStr != NULL )
			{
				/* While there are Str in "string" */
				key = atoi(NodeStr);
				NodeStr = strtok( NULL, seps );
				value = atoi(NodeStr);
				NodeStr = strtok( NULL, seps );
				InsertNode(T, key, value);
			}
		}
		
		fclose(FILE);
	}
	
	return T;
}

void *CloneAVLTreeNode(AVLTreeNode *t1) {
    AVLTreeNode *cloneNode;
    cloneNode = NULL;
    if (t1 != NULL) {
        cloneNode = newAVLTreeNode(t1->key, t1->value);
        cloneNode->left = CloneAVLTreeNode(t1->left);
        cloneNode->right = CloneAVLTreeNode(t1->right);
    }
    return cloneNode;
}

// put your time complexity analysis for CloneAVLTree() here
//O(T->size)
AVLTree *CloneAVLTree(AVLTree *T) {
    // put your code here
    AVLTree *NewT = newAVLTree();
    if (NewT == NULL)
    {
        return NULL;
    }
    CloneAVLTreeNode(T->root);
    return NewT;
}
// let data store in the array and union in the array

// store data in array and intersect


//Using binary search

// put your time complexity for ALVTreesUnion() here
AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2) {
    //put your code here
}

// put your time complexity for ALVTreesIntersection() here
AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2) {
    //put your code here
}


// put your time complexity for DeleteNode() here
int DeleteNode(AVLTree *T, int k, int v) {
    // put your code here
}

AVLTreeNode *SearchTreeNode(AVLTreeNode *t, int k) {
    AVLTreeNode *res;
    res = NULL;
    if (Judge_t(t) == 1) {
        int compare_res = compareTreeNode(k, v, t->key);
        if (compare_res == 0) {
            res = t;
        } else if (compare_res < 0) {
            res = SearchTreeNode(t->left, k);
        } else {
            res = SearchTreeNode(t->right, k);
        }
    }
    return res;
}

// put your time complexity analysis for Search() here
// the time complexity is O(log(n))
AVLTreeNode *Search(AVLTree *T, int k, int v) {
    // put your code here 
    
    return SearchTreeNode(T->root, k, v);

}

void FreeAVLTreeNode(AVLTreeNode *tree) {
    if (tree->left != NULL)
        FreeAVLTreeNode(tree->left);
    if (tree->right != NULL)
        FreeAVLTreeNode(tree->right);

    free(tree);
}

// put your time complexity analysis for freeAVLTree() here
// the time complexity is O(n)
void FreeAVLTree(AVLTree *T) {
// put your code here
        FreeAVLTreeNode(T->root);
        T->size = 0;
}


void Inorder_avltree(AVLTreeNode *tree) {
    if (tree != NULL) {
        Inorder_avltree(tree->left);
        printf("(%d, %d), %d\n", tree->key, tree->value);
        Inorder_avltree(tree->right);
    }
}
// put your time complexity analysis for PrintAVLTree() here
// the time complexity is O(n)
void PrintAVLTree(AVLTree *T) {
    // put your code here{
        Inorder_avltree(T->root);
}

int main() //sample main for testing 
{
    int i, j;
    AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
    AVLTreeNode *node1;

    tree1 = CreateAVLTree("stdin");
    PrintAVLTree(tree1);
    FreeAVLTree(tree1);
    //you need to create the text file file1.txt
    // to store a set of items without duplicate items
    tree2 = CreateAVLTree("file2.txt");
    PrintAVLTree(tree2);
    tree3 = CloneAVLTree(tree2);
    PrintAVLTree(tree3);
    FreeAVLTree(tree2);
    FreeAVLTree(tree3);
    //Create tree4
    tree4 = newAVLTree();
    j = InsertNode(tree4, 10, 10);
    for (i = 0; i < 15; i++) {
        j = InsertNode(tree4, i, i);
        if (j == 0) printf("(%d, %d) already exists\n", i, i);
    }
    PrintAVLTree(tree4);
    node1 = Search(tree4, 20, 20);
    if (node1 != NULL)
        printf("key= %d value= %d\n", node1->key, node1->value);
    else
        printf("Key 20 does not exist\n");

    for (i = 17; i > 0; i--) {
        j = DeleteNode(tree4, i, i);
        if (j == 0)
            printf("Key %d does not exist\n", i);
        PrintAVLTree(tree4);
    }
    FreeAVLTree(tree4);
    //Create tree5
    tree5 = newAVLTree();
    j = InsertNode(tree5, 6, 25);
    j = InsertNode(tree5, 6, 10);
    j = InsertNode(tree5, 6, 12);
    j = InsertNode(tree5, 6, 20);
    j = InsertNode(tree5, 9, 25);
    j = InsertNode(tree5, 10, 25);
    PrintAVLTree(tree5);
    //Create tree6
    tree6 = newAVLTree();
    j = InsertNode(tree6, 6, 25);
    j = InsertNode(tree6, 5, 10);
    j = InsertNode(tree6, 6, 12);
    j = InsertNode(tree6, 6, 20);
    j = InsertNode(tree6, 8, 35);
    j = InsertNode(tree6, 10, 25);
    PrintAVLTree(tree6);
    tree7 = AVLTreesIntersection(tree5, tree6);
    tree8 = AVLTreesUnion(tree5, tree6);
    PrintAVLTree(tree7);
    PrintAVLTree(tree8);
    return 0;
}
