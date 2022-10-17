#include <stdio.h>
#include <stdlib.h>


/*
Declaring required structures
1. Node : for storing each individual value in the stack, such that it also points to the next element in the stack
2. Stack : for storing the stack, such that it also contains the size of the stack
*/
struct Node{
    int val;
    struct Node* next;
};

struct Stack{
    int size;
    struct Node* head;
};


/*
Declaring required functions of Stack
1. stackPush(s, val)
2. stackPop(s)
3. stackTop(s)
4. stackSize(s)
*/

// Functions -->
    //push functionality: stackPush(s, 5);
void stackPush(struct Stack* s, int in){
    s->size++;
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->val = in;
    temp->next = s->head;

    s->head = temp;
}

    //pop functionality: stackPop(s);
void stackPop(struct Stack* s){
    if(s->head == NULL){
        printf("!\n");
        return;
    }
    struct Node* temp = s->head;
    s->head = s->head->next;
    printf("%d\n", temp->val);
    free(temp);
    s->size--;
}

    //top functionality: stackTop(s);
void stackTop(struct Stack* s){
    if(s->head == NULL) printf("!\n");
    else printf("%d\n", s->head->val);
}

    //size functionality: stackSize(s);
void stackSize(struct Stack* s){
    printf("%d\n", s->size);
}
// <-- Functions


int main(){
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));

    //initialize stack
    s->size = 0;
    s->head = NULL;


    int n;
    scanf("%d", &n);
    int q, val;
    while(n--){
        scanf("%d", &q);
        switch(q){
            case 0:
                scanf("%d", &val);
                stackPush(s, val);
            break;

            case 1:
                stackPop(s);
            break;

            case 2:
                stackTop(s);
            break;

            case 3:
                stackSize(s);
            break;
        }
    }

    return 0;
}