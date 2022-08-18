//Comment out other codes while running the specific algo..

//---------------Recursive Fibonacci-------------
#include<stdio.h>
#include<time.h>

int Rfib(int n, int m){
    if(n==0){
        return 0;
    }
    else if(n==1){
        return 1;
    }
    else{
        return (Rfib(n-1,m)+Rfib(n-2,m))%m;
    }
}

int main(){
    int n=0;
    int m=0;
    printf("ENTER n,m :");
    scanf("%i, %i", &n, &m);
     clock_t start, end;
    double cpu_time_used;
    start = clock();

    int c=Rfib(n,m);
    printf("Output: %d",c);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nTime taken: %f\n", cpu_time_used);

    return 0;
}

//-------------------------Iterative Fibonacci------------------------

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    double time_taken=0;
    long long int n;
    long long int m=2022;
    printf("Enter n : ");
    scanf("%lld", &n);
    long long int a=0,b=1,c;

    clock_t start = clock();
    for(long long int i=2;i<=n;i++){
        c=(a+b)%2022;
        a=b;
        b=c;
    }
    clock_t end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("output: %lld \n", c);
    printf("time taken: %lf \n", time_taken);
    return 0;
}

//---------------------Clever Fibonacci------------------

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

long long int m=0;

struct mat{
    long long int a11;
    long long int a12; 
    long long int a21;
    long long int a22;
   };

struct mat multiply(struct mat a, struct mat b){
    struct mat c;
    c.a11=(a.a11*b.a11+a.a12*b.a21)%m;
    c.a12=(a.a11*b.a12+a.a12*b.a22)%m;
    c.a21=(a.a21*b.a11+a.a22*b.a21)%m;
    c.a22=(a.a21*b.a12+a.a22*b.a22)%m;
    return c;
}


struct mat power(struct mat a, long long int n){
    if(n==0){
        struct mat i;
        i.a11=1;
        i.a12=0;
        i.a21=0;
        i.a22=1;
        return i;
    }
    // else if(n==1){
    //     return a;
    // }
    else{
        struct mat temp=power(a,n/2);
        temp=multiply(temp,temp);
        if(n%2==1){
            temp=multiply(temp,a);
        }
        return temp;
    }

}

int main(){
    long long int n=0;
    printf("ENTER n,m: ");
    scanf("%lld, %lld", &n, &m);
    struct mat a;
    a.a11=1;
    a.a12=1;
    a.a21=1;
    a.a22=0;
   
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    struct mat c=power(a, n-1);
    printf("Output: %lld",(c.a11));
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f\n", cpu_time_used);
    return 0;
}