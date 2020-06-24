#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSTRING 1000
#define DELIM " \n"

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
    int value;  // value (int) of this list item
    struct DLListNode *prev;
    // pointer previous node in list
    struct DLListNode *next;
    // pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList {
    int size;      // count of items in list
    DLListNode *first; // first node in list
    DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it) {
    DLListNode *new;
    new = malloc(sizeof(DLListNode));
    assert(new != NULL);
    new->value = it;
    new->prev = new->next = NULL;
    return new;
}

// create a new empty DLList
DLList *newDLList() {
    DLList *L;

    L = malloc(sizeof(struct DLList));
    assert (L != NULL);
    L->size = 0;
    L->first = NULL;
    L->last = NULL;
    return L;
}

void insertList(DLList *list, int data) {
    // create new node
    DLListNode *newNode = newDLListNode(data);
    if (list != NULL) {
        if (list->first == NULL) {
            list->first = newNode;
            list->last = newNode;
            list->size++;
        } else {
            // 1,3,4,5,6
            // newNode 6
            newNode->prev = list->last;
            list->last->next = newNode;
            list->last = newNode;
            list->size++;
        }
    }

}

// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here
DLList *CreateDLListFromFileDlist(const char *filename) {
    // put your code here
    FILE *file = NULL;
    // read file context
    DLList *result = newDLList();;

    // check input
    if (strcmp(filename, "stdin") == 0) {
        char word[30];
        int input = 0, index = 0;
        while ((input = getchar()) != EOF) {
            if (!isalnum(input)) {
                if (strlen(word) > 0) {
                    if (strcmp(word, "end") == 0) {
                        break;
                    }
                    insertList(result, atoi(word));
                }
                index = 0;
            } else {
                word[index] = input;
                index++;
            }
            word[index] = '\0';
        }

    } else {
        file = fopen(filename, "r");
        if (file == NULL) {
            puts("Invalid input!");
        } else {
            char line[MAXSTRING];
            char *token;

            while (fgets(line, MAXSTRING, file) != NULL) {
                /* first token */
                token = strtok(line, DELIM);
                /* iterate over the rest of the tokens */
                while (token != NULL) {
                    for (int i = 1; i < strlen(token); i++) {
                        if (isdigit(token[i]) == false) {
                            puts("Invalid input!");
                        }
                    }
                    insertList(result, atoi(token));
                    // continue to get string
                    token = strtok(NULL, DELIM);
                }
            }
            fclose(file);
        }

    }

    return result;
}

// clone a DLList
// put your time complexity analysis for cloneList() here
DLList *cloneList(DLList *u) {
    // put your code here
    // read file context
    DLList *result = NULL;
    if (u != NULL && u->size > 0) {
        result = newDLList();
        DLListNode *first = u->first;
        while (first != NULL) {
            insertList(result, first->value);
            first = first->next;
        }
    }

    return result;
}

bool exists(DLList *u, int value) {
    bool result = false;
    if (u != NULL && u->size > 0) {
        DLListNode *first = u->first;
        while (first != NULL) {
            if (first->value == value) {
                result = true;
                break;
            }
            first = first->next;
        }
    }
    return result;
}

// compute the union of two DLLists u and v
DLList *setUnion(DLList *u, DLList *v) {
    // put your code here
    if (u == NULL) {
        return cloneList(v);
    }

    if (v == NULL) {
        return cloneList(u);
    }
    DLList *result = cloneList(u);
    DLListNode *first = v->first;
    while (first != NULL) {
        // insert
        if (exists(u, first->value) == false) {
            insertList(result, first->value);
        }
        first = first->next;
    }

    return result;

}

// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here
DLList *setIntersection(DLList *u, DLList *v) {
    // put your code here
    if (u == NULL || v == NULL) {
        return NULL;
    }

    DLList *result = newDLList();
    DLListNode *first = u->first;
    while (first != NULL) {
        // insert
        if (exists(v, first->value) == true) {
            insertList(result, first->value);
        }
        first = first->next;
    }

    return result;
}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here
void freeDLList(DLList *L) {
// put your code here
    if (L != NULL && L->size > 0) {
        DLListNode *first = L->first;
        DLListNode *temp;
        while (first != NULL) {
            temp = first;
            first = first->next;
            free(temp);
        }
        // free l
        free(L);
    }
}


// display items of a DLList
// put your time complexity analysis for printDDList() here
void printDLList(DLList *u) {
    // put your code here
    if (u != NULL && u->size > 0) {

        DLListNode *first = u->first;
        while (first != NULL) {
            printf("%d\n", first->value);
            first = first->next;
        }
    }
}

int main() {
    DLList *list1, *list2, *list3, *list4;

    list1 = CreateDLListFromFileDlist("File1.txt");
    printDLList(list1);

    list2 = CreateDLListFromFileDlist("File2.txt");
    printDLList(list2);

    list3 = setUnion(list1, list2);
    printDLList(list3);

    list4 = setIntersection(list1, list2);
    printDLList(list4);

    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(list4);

    printf("please type all the integers of list1\n");
    list1 = CreateDLListFromFileDlist("stdin");

    printf("please type all the integers of list2\n");
    list2 = CreateDLListFromFileDlist("stdin");

    list3 = cloneList(list1);
    printDLList(list3);
    list4 = cloneList(list2);
    printDLList(list4);

    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(list4);
    system("pause");

    return 0;
}
