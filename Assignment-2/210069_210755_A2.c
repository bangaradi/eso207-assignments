#include<stdio.h>
#include<stdlib.h>

//Define a single node in the linked list structure with address of next element in row and column and data fields
struct node
{
    int row;
    int col;
    int data;
    struct node *next_row;
    struct node *next_col;

};


//Print function to print the sparse matrix taking the address of row header array as input

void print(struct node** head,int n){

    struct node* next=NULL;

    int x=0;


    for(int i=0;i<n;i++){
        next=head[i];

        while(next!=NULL){
            printf("%d %d %d", next->row, next->col, next->data);
            printf("\n");
            next=next->next_row;// go to next row when the current row terminates at null
        }
    }

//checking wether the multiplied matrix is empty.
    for(int i=0;i<n;i++){
        if(head[i]!=NULL){
            x=1; 
        }
        }

    if(x==0){
        printf("NULL MATRIX!");
    }

    

}

//multiply function taking the address of row header array of matrix1 and column header array of matrix2 as input and return the address of row header array of resultant multiplied matrix

struct node** multiply(struct node** hr1, struct node** hc2, int n){

    struct node** multiplied_row= (struct node**)malloc(n*sizeof(struct node)); //declare the resultant matrix row header array

    for(int i=0;i<n;i++){
        multiplied_row[i]=NULL; //initialize the resultant matrix row header array to NULL
    }
    
    struct node* next1;// declare the next pointer of matrix1
    struct node* next2;// declare the next pointer of matrix2 

    for(int i=0;i<n;i++){
        next1=hr1[i]; // we are going to traverse the matrix1 row by row
        
        for(int j=0;j<n;j++){
            struct node* new_node=(struct node*)malloc(sizeof(struct node)); //declare a new node to store the resultant element

            new_node->row=i+1; //store the row of resultant element
            new_node->col=j+1; //store the column of resultant element
            new_node->data=0; //initialize the data of resultant element to 0
            new_node->next_row=NULL; //initialize the next row of resultant element to null
            new_node->next_col=NULL; //initialize the next column of resultant element to null

            next2=hc2[j];// we are traversing the column header array of matrix2

            int sum=0; //initialize the sum of the resultant element to 0

            while(next1!=NULL){ //traverse the matrix1 row by row and exit when null encountered
                while(next2!=NULL){ //traverse the matrix2 column by column and exit when null encountered
                    if(next1->col==next2->row){ //if the column of matrix1 is equal to the row of matrix2 multiply them
                        sum+=next1->data*next2->data; //add the data of matrix1 and matrix2 and store it in sum
                    }
                    next2=next2->next_col; //go to next column of matrix2
                }
                next2=hc2[j]; // again reset the next2 pointer to the start of the column header array
                next1=next1->next_row; //go to next row of matrix1
            }

            new_node->data=sum; //update the data of resultant element with the sum


            // if the resultant element is not zero then add it to the resultant matrix row header array
           if(new_node->data!=0){

            // if multiplied_row[i] is null then add the new_node to it
                if(multiplied_row[i]==NULL){
                    multiplied_row[i]=new_node;  
                }
                else{ //else traverse the row header array of resultant matrix and add the new_node to the end of the row
                    struct node* temp=multiplied_row[i];
                    while(temp->next_row!=NULL){
                        temp=temp->next_row;
                    }
                    temp->next_row=new_node; //add the new_node to the end of the row
                }
            }

            next1=hr1[i]; //again reset the next pointer of matrix1 to the beginning of the row for i, j+1 .
            

        }

    }

    return multiplied_row; //return the address of the resultant matrix row header array
}


int main(){
    int n;
    scanf("%d", &n);

    struct node ** head_row1=(struct node**)malloc(n*sizeof(struct node*)); //declare the row header array of matrix1
    struct node ** head_col1=(struct node**)malloc(n*sizeof(struct node*)); //declare the column header array of matrix1
    struct node ** head_row2=(struct node**)malloc(n*sizeof(struct node*)); //declare the row header array of matrix2
    struct node ** head_col2=(struct node**)malloc(n*sizeof(struct node*)); //declare the column header array of matrix2
    struct node ** tail1col=(struct node**)malloc(n*sizeof(struct node*)); //declare the tail pointer array of matrix1
    struct node ** tail2col=(struct node**)malloc(n*sizeof(struct node*)); //declare the tail pointer array of matrix2  
    

    
    // initialize the row,col header array of matrix1 and matrix2 to NULL
    for(int i=0;i<n;i++){
        head_row1[i]=NULL;
        head_col1[i]=NULL;
        head_row2[i]=NULL;
        head_col2[i]=NULL;
        tail1col[i]=NULL;
        tail2col[i]=NULL;
    }

    struct node* tail1row=NULL; 
    struct node* tail2row=NULL;
    
    // m stores the matrix number
    int m;
    scanf("%d", &m); 

    while(m!=0){
        if(m==1){ //if m is 1 then read the matrix1

            struct node* element=(struct node*)malloc(sizeof(struct node)); //declare a new node to store the element

            scanf("%d %d %d", &element->row, &element->col, &element->data); //read the element from the input
            element->next_row=NULL; //initialize the next row of the element to null
            element->next_col=NULL; // initialize the next column of the element to null

            //row linked list creation
            
            if(tail1row==NULL){ //if tail1row is null then add the element to the row header array of matrix1
                head_row1[element->row-1]=element;
                tail1row=element;
            }
            else if(tail1row->row!=element->row){ //else if the row of the element is not equal to the row of the last element of the row header list of matrix1 then add the element to the next row header  of matrix1
                head_row1[element->row-1]=element;
                tail1row=element;
            }
            else if(tail1row->row==element->row){ // else if the row of the element is equal to the row of the last element of the row header list of matrix1 then add the element to the next column of the last element of the row header list of matrix1
                tail1row->next_row=element;
                tail1row=element;
            }

            //column linked list creation

            if(tail1col[element->col-1]==NULL){ //if tail1col[element->col-1] is null then add the element to the column header array of matrix1
                head_col1[element->col-1]=element;
                tail1col[element->col-1]=element;

            }
            else{ //else add the element to the next column of the last element of the column header array of matrix1
                tail1col[element->col-1]->next_col=element;
                tail1col[element->col-1]=element;
            }



        }
        
        else if(m==2){ // if m is 2 then read the matrix2
            struct node* element=(struct node*)malloc(sizeof(struct node)); //declare a new node to store the element

            scanf("%d %d %d", &element->row, &element->col, &element->data); //read the element from the input
            element->next_row=NULL; //  initialize the next row of the element to null
            element->next_col=NULL; //initialize the next column of the element to null
            
            //row linked list creation
            if(tail2row==NULL){ //if tail2row is null then add the element to the row header array of matrix2
                head_row2[element->row-1]=element;
                tail2row=element;
            }
            else if(tail2row->row!=element->row){ //else if the row of the element is not equal to the row of the last element of the row header list of matrix2 then add the element to the next row header  of matrix2
                head_row2[element->row-1]=element;
                tail2row=element;
            }
            else if(tail2row->row==element->row){ // else if the row of the element is equal to the row of the last element of the row header list of matrix2 then add the element to the next column of the last element of the row header list of matrix2
                tail2row->next_row=element;
                tail2row=element;
            }
            //column linked list creation

            if(tail2col[element->col-1]==NULL){ //if tail2col[element->col-1] is null then add the element to the column header array of matrix2
                head_col2[element->col-1]=element;
                tail2col[element->col-1]=element;

            }
            else{ //else add the element to the next column of the last element of the column header array of matrix2
                tail2col[element->col-1]->next_col=element;
                tail2col[element->col-1]=element;
            }

        }

        scanf("%d", &m); //read the next matrix number
    }

    free(tail1col); //free the tail1col array
    free(tail2col); //free the tail2col array

    struct node** multiplied=multiply(head_row1, head_col2, n); //call the multiply function to multiply the two matrices and store the resultant matrix in a new matrix

    print(multiplied,n); //print the resultant matrix

}