#include <stdio.h>
#include<stdlib.h>
#include<string.h>

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
        return;
    }
    struct Node* temp = s->head;
    s->head = s->head->next;
    free(temp);
    s->size--;
}

    //top functionality: stackTop(s);
int stackTop(struct Stack* s){
    if(s->head == NULL) return 0;
    else return s->head->val;
}

    //size functionality: stackSize(s);
int stackSize(struct Stack* s){
    return s->size;
}
// <-- Functions

//this global variable is used to increase the priority value of the operator->
int PRIORITY_INCREASER = 0;

//returns a priority of the operator
int chValue(char c){
    switch(c){
        case '+':
            return 11 + PRIORITY_INCREASER;
        case '-':
            return 12 + PRIORITY_INCREASER;
        case '*':
            return 21 + PRIORITY_INCREASER;
        case '/':
            return 22 + PRIORITY_INCREASER;
        case '^':
            return 31 + PRIORITY_INCREASER;
        case '(':
            return 0 + PRIORITY_INCREASER;
        break;
        default:
            return -1;
    }
}

//function to check if the given character is a number or not->
int isNumber(char c){
    if(c >= '0' && c <= '9') return 1;
    else return 0;
}

//function to evaluate the expression->
void Evaluate(struct Stack* operators, struct Stack* numbers){
    int op1, op2, res;
    char op;
    op1 = stackTop(numbers);
    stackPop(numbers);
    op2 = stackTop(numbers);
    stackPop(numbers);
    op = stackTop(operators) - PRIORITY_INCREASER;
    stackPop(operators);
    switch(op){
        case 11:
            res = op1 + op2;
        break;
        case 12:
            res = op2 - op1;
        break;
        case 21:
            res = op1 * op2;
        break;
        case 22:
            res = op2 / op1;
        break;
        case 31:
            res = op2;
            for(int i = 1; i < op1; i++){
                res *= op2;
            }
        break;
    }
    stackPush(numbers, res);
}

int main(){
    struct Stack* operators = (struct Stack*)malloc(sizeof(struct Stack));
    struct Stack* numbers = (struct Stack*)malloc(sizeof(struct Stack));
    operators->size = 0;
    numbers->size = 0;
    int n;
    scanf("%d", &n);
    char* expression = (char*)malloc(sizeof(char)*(n+1));
    char c;
    int i = 0;
    scanf("%s", expression);

    while(i<n){
        //checking if the given character of the string is a number, so that we can push it onto the stack
        if(isNumber(expression[i])){
            int j = i;
            int mult = 1;
            int sum = 0;

            //handling the case where the number is a multidigit one->->
            while(isNumber(expression[j])){
                j++;
                i++;
            }
            j--;
            while(isNumber(expression[j])){
                sum += (expression[j] - '0')*mult;
                mult *= 10;
                j--;
            }
            //<-<-handling the case where the number is a  multidigit one.

            stackPush(numbers, sum);
        
        //if the given numeber is  a opening parentheses, the following if else block will run->
        }else if(expression[i] == '('){
            //1. we store the parentheses on the operators stack
            stackPush(operators, chValue(expression[i]));
            i++;
            //2. we increase the priority of all the operators appearing after the parentheses->
            PRIORITY_INCREASER += 10;

        //checking for the closing parentheses, we run the following if else block->
        }else if(expression[i] == ')'){
            //if the closing parentheses is found, execute all the operators till we reach the closing parentheses->
            while(stackTop(operators) != chValue('(')-10){
                Evaluate(operators, numbers);
            }
            //pop out the parentheses now
            stackPop(operators);
            i++;
            //decrease the priority of the operators now as we have reached outside the parentheses block.
            PRIORITY_INCREASER -= 10;

        //now if the character is not a number or a closing or opening parentheses, we run the following block->
        }else{
            //if it is the first operator, push it onto the operator block->
            if(stackSize(operators) == 0){
                stackPush(operators, chValue(expression[i]));
                i++;
            
            //if it is not the first operator on the operator stack, check for the following various conditions->
            }else{
                //check if the operator has a higher priority than the top of the operator stack and by how much->
                int check = chValue(expression[i]) - stackTop(operators);

                //if the operator has a higher priority by more that 5, push it onto the operator stack->
                if(check > 5){
                    stackPush(operators, chValue(expression[i]));
                    i++;
                
                //if the operator has the same priority->
                }else if(check == 0){
                    //if operator is left associative, evaluate the top of the operator stack->
                    if(chValue(expression[i]) == 11 || chValue(expression[i]) == 21){
                        Evaluate(operators, numbers);
                    
                    //if operator is right associative, push it onto the operator stack->
                    }else{
                        stackPush(operators, chValue(expression[i]));
                        i++;
                    }
                
                //if the operator has a higher priority by less than 5 or has less priority, evaluate the top of the operator stacka->
                }else{
                    Evaluate(operators, numbers);
                }
            }
        }
    }

    //if the expression is over, evaluate all the operators left on the operator stack->
    while(stackSize(operators) != 0){
        Evaluate(operators, numbers);
    }

    printf("%d", stackTop(numbers));

    return 0;
}