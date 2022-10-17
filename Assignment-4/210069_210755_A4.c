#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#include<time.h> 


FILE *fpt1, *fpt2;


//define the node structure
struct node{
    long long int data;
    struct node *left;
    struct node *right;
    long long int size;
};


//define the tree structure
struct tree{
    struct node *root;
};


//function to create a Perfectly Balanced BST from a sorted array
struct node* createPBBST(long long int* arr, int s, int e){

    if(s>e){
        return NULL;
    }

    int mid=(s+e)/2;
    struct node* v=(struct node*)malloc(sizeof(struct node));
    v->size=(e-s+1);
    v->data=arr[mid];
    v->left=createPBBST(arr, s,mid-1);
    v->right=createPBBST(arr,mid+1,e);

    return v;

}

//function to unfold a BST into sorted array by inorder traversal
void Unfold(struct node* uroot, long long int* arr, long long int* i){
    if(uroot==NULL){
        return;
    }
    Unfold(uroot->left, arr, i);
    arr[*i] =uroot->data;
    *i = *i + 1;
    Unfold(uroot->right, arr, i);

}

//function to convert a BST into a Perfectly Balanced BST by using two helper functions
void Convert(struct node* uroot){
   
    long long int n = uroot->size;
    long long int* arr=(long long int*)malloc((uroot->size)*(sizeof(long long int)));
    long long int i=0;

    Unfold(uroot, arr, &i);
      

    int mid=n/2;

    struct node* root_new=(struct node*)malloc(sizeof(struct node));

    root_new->data=arr[mid];
    root_new->size=n;
    root_new->left = createPBBST(arr,0,mid-1);
    root_new->right = createPBBST(arr,mid+1,n-1);

    uroot->data=root_new->data;
    uroot->size=root_new->size;
    uroot->left=root_new->left;
    uroot->right=root_new->right;
}

//function to check whether a node is nearly balanced or not
bool isNearlyBalanced(struct node* v){

    long long int x= 3*(v->size)/4;
    
    if(v==NULL){
        return true;
    }
    if(v->left==NULL && v->right==NULL){
        return true;
    }
    if(v->left==NULL){
        if(v->right->size<=1){
            return true;
        }
        else{
            return false;
        }
    }
    if(v->right==NULL){
        if(v->left->size<=1){
            return true;
        }
        else{
            return false;
        }
    }
    if(v->left->size<=x && v->right->size<=x){
        return true;
    }
    else{
        return false;
    }

}


void Insert(long long int x, struct tree* T){
    
    struct node* v=(struct node*)malloc(sizeof(struct node));
    v->data=x;
    v->left=NULL;
    v->right=NULL;
    v->size=1;

    if(T->root==NULL){
        T->root=v;
    }
    else{

        struct node* r=T->root;
        struct node* prev;

        while(r!=NULL){
            
            prev=r;

            /*
            convert a subtree into perfectly balanced BST if it is not nearly balanced
            Convert function called on the topmost node that is not nearly balanced, it makes all the nodes below it perfectly balanced
            */
            
            if(!(isNearlyBalanced(r))){
                Convert(r);
            }
            
            //update the size of the node at each node traversed
            r->size=r->size+1;  

            //perform general BST insertion        
            if(x<r->data){
                r=r->left;
            }
            else{
                r=r->right;
            }
        }

        if(x<prev->data){
            prev->left=v;
        }
        else{
            prev->right=v;
        }

    }
}

int main(){
    struct tree* T=(struct tree*)malloc(sizeof(struct tree));
    T->root=NULL;
    //creates/opens csv file
    fpt1 = fopen("myfile1.csv", "w+"); 
    fpt2 = fopen("myfile2.csv", "w+");

    clock_t start_t, end_t;
    double total_t;

    int prev=0;

    start_t = clock();
    //first part of the assignment
    for(int j=50000;j<=10000000;j+=50000){ //loop to run through all the values of n required

        
        for(int i=prev;i<j;i++){
            Insert(i, T);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        fprintf(fpt1, "%d, %f\n", j, total_t);  // writes to csv file for all values of n
        prev=j;
    }

    //second part of the assignment
    struct tree* T1=(struct tree*)malloc(sizeof(struct tree));
    T1->root=NULL;

    //first insert the 100000 elements
    for(int i=0;i<100000;i++){
        Insert(i, T1);
    }

    for(int i=100000;i<=1000000;i++){
        start_t=clock();
        Insert(i, T1);
        end_t=clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        fprintf(fpt2, "%d, %f\n", i, total_t); // writes to csv file for all values of i in the range
    }

    fclose(fpt1); //closes csv file
    fclose(fpt2); //closes csv file
    // CLOCKS_PER_SEC is a constant defined in time.h and its value is 10^6.
    // printLevelOrder(T->root);
    // printf("Total time taken: %f\n", total_t );
    return 0;

}




