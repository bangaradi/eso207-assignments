/*
    ESO207 ASSIGNMENT-5
    Name: Aditya Bangar (210069)
    Name: Pratham Sahu (210755)

    TOPIC: QuickSort vs MergeSort
*/

/*
    This program carries out all the parts of the question in one go. 
    Just run the program and it will create 5 .csv files in the same directory and all the readings will be filled in them.
    The progress of the program is shown on the terminal. So, just keep an eye on the terminal. To make sure that the program is running.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

#define ARR_SIZE 1000000
#define MAX_RANGE 10000
#define N_ITER 500

double times[500];
int times_variation[500];
double times_qs[500];
double times_ms[500];
double times_ims[500];

double arr[ARR_SIZE];
double arr2[ARR_SIZE];
long long int qs_compares = 0;
long long int ms_compares = 0;
//utility
void fillArray(double* arr, int size){
    srand((unsigned)time(NULL));
    for(int i = 0; i < size; i++){
        int random_num = rand() % MAX_RANGE;
        arr[i] = random_num;
    }
}

//utility functions - partition an array given a key
void partition(double* arr, int low, int high, int* i, int* j){
    double key = arr[low];
    *i = low;
    *j = high;
    while(*i <= *j){
        while(arr[*i] < key){
            (*i)++;
            qs_compares++;
        }
        while(arr[*j] > key){
            (*j)--;
            qs_compares++;
        }
        if(*i <= *j){
            double temp = arr[*i];
            arr[*i] = arr[*j];
            arr[*j] = temp;
            (*i)++;
            (*j)--;
        }
    }
}

//utility function - merge two sorted arrays
void merge(double* arr, int low, int mid, int high){
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;
    double L[n1], R[n2];
    for(i = 0; i < n1; i++){
        L[i] = arr[low + i];
    }
    for(j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }
    i = 0;
    j = 0;
    k = low;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
        ms_compares++;
    }
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

/*
    This various sorting functions used in the program -->
*/
void QSort(double* arr, int l, int r){
    if(l < r){
        int i, j;
        partition(arr, l, r, &i, &j);
        QSort(arr, l, j);
        QSort(arr, i, r);
    }
}

void MSort(double* arr, int l, int r){
    if(l < r){
        int m = l + (r - l) / 2;
        MSort(arr, l, m);
        MSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void ISort(double* arr, int l, int r){
    for(int i = l + 1; i <= r; i++){
        double key = arr[i];
        int j = i - 1;
        while(j >= l && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void ImprovedMSort(double* arr, int l, int r){
    if(l < r){
        if(r - l < 20){
            ISort(arr, l, r);
        }
        else{
            int m = l + (r - l) / 2;
            ImprovedMSort(arr, l, m);
            ImprovedMSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }
}

// main program
int main(){

    printf("program started -->\n");

    FILE *fptr1_1, *fptr1_2, *fptr1_3, *fptr1_4, *fptr2;

    //creating 5 .csv files for storing the reading of the various parts of the question.
    fptr1_1 = fopen("part1_1.csv", "w+");
    fptr1_2 = fopen("part1_2.csv", "w+");
    fptr1_3 = fopen("part1_3.csv", "w+");
    fptr1_4 = fopen("part1_4.csv", "w+");
    fptr2 = fopen("part2.csv", "w+");


    clock_t start, end;
    clock_t start_f, end_f;

    start_f = clock();

    double cpu_time_used = 0;

/* ------------------------------------------------ part1.1 number of comparisons of QuickSort and MergeSort. --------------------------------------------------------*/
    printf("start of part1.1\n");
    int avg_qs_compares[5];
    int avg_ms_compares[5];
    double _2nlogn[5];
    double _nlog2n[5];

    for(int size_of_array = 100; size_of_array <=1000000; size_of_array *= 10){
        printf("running part 1.1 for size of array: %d \n", size_of_array);
        int temp_index = 0;
        qs_compares = 0;
        ms_compares = 0;
        for(int i = 0; i < N_ITER; i++){
            fillArray(arr, size_of_array);

            QSort(arr, 0, size_of_array - 1);

            MSort(arr, 0, size_of_array - 1);
        }
        temp_index = (int)log10(size_of_array) - 2;
        avg_qs_compares[temp_index] = qs_compares / N_ITER;
        avg_ms_compares[temp_index] = ms_compares / N_ITER;
        _2nlogn[temp_index] = 2 * size_of_array * log2(size_of_array);
        _nlog2n[temp_index] = size_of_array * log2(size_of_array);

    }

    end_f = clock();
    printf("time till part 1.1 ended is %f seconds\n", (double)(end_f - start_f) / CLOCKS_PER_SEC);

    //printing to file
    printf("writing data to file part1_1.csv -> \n");
    fprintf(fptr1_1, "size of array, avg_qs_compares, 2nlogn, avg_ms_compares, nlog2\n");
    for(int i = 0; i < 5; i++){
        fprintf(fptr1_1, "%d, %d, %f, %d, %f\n", (int)pow(10, i + 2), avg_qs_compares[i], _2nlogn[i], avg_ms_compares[i], _nlog2n[i]);
    }
    fclose(fptr1_1);
    


/*-------------------------------------------------- part1.2 analysing the time complexity fo QuickSort. ---------------------------------------------------------------*/

    double avg_time_qs[5];
    for(int size_of_array = 100000; size_of_array <= 9*100000; size_of_array += 200000){
        printf("running part 1.2 for size of array: %d\n", size_of_array);

        cpu_time_used = 0;
        for(int i=0; i<N_ITER; i++){
            fillArray(arr, size_of_array);
            start = clock();
            QSort(arr, 0, size_of_array - 1);
            end = clock();
            cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
        }
        avg_time_qs[((size_of_array/100000) - 1)/2] = cpu_time_used / N_ITER;
    }    

    end_f = clock();

    printf("time till part 1.2 ended is %f seconds\n", (double)(end_f - start_f) / CLOCKS_PER_SEC);

    //printing to file
    printf("writing data to file part1_2.csv ->\n");
    fprintf(fptr1_2, "size of array, avg_time_qs\n");
    for(int i = 0; i < 5; i++){
        fprintf(fptr1_2, "%d, %f\n", (int)pow(10, i + 2), avg_time_qs[i]);
    }


/*------------------------------------------------------- part1.3 analysing and comparing the time-complexity of QuickSort and MergeSort. ---------------------------------------- */

    double avg_time_ms[5];
    int outperforms[5] = {0,0,0,0,0};

    for(int size_of_array=100; size_of_array<=1000000; size_of_array *= 10){
        printf("running part 1.3 for size of array: %d\n", size_of_array);

        int temp_index = 0;
        temp_index = log10(size_of_array) - 2;

        double cpu_time_used_ms = 0;
        double cpu_time_used_qs = 0;
        for(int i=0; i<N_ITER; i++){
            fillArray(arr, size_of_array);
            for(int j=0; j<size_of_array; j++){
                arr2[j] = arr[j];
            }

            start = clock();
                QSort(arr, 0, size_of_array - 1);
            end = clock();

            times_qs[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
            cpu_time_used_qs += ((double) (end - start)) / CLOCKS_PER_SEC;

            start = clock();
                MSort(arr2, 0, size_of_array - 1);
            end = clock();
            times_ms[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
            cpu_time_used_ms += ((double) (end - start)) / CLOCKS_PER_SEC;
        }

        avg_time_ms[temp_index] = cpu_time_used_ms / N_ITER;
        avg_time_qs[temp_index] = cpu_time_used_qs / N_ITER;

        for(int i=0; i<N_ITER; i++){
            if(times_qs[i] > times_ms[i]){
                outperforms[temp_index]++;
            }
        }
        
    }

    end_f = clock();
    printf("time till part 1.3 ended is %f seconds\n", (double)(end_f - start_f) / CLOCKS_PER_SEC);

    //printing to file
    printf("writing data to file part1_3.csv ->\n");
    fprintf(fptr1_3, "size of array, avg_time_qs, avg_time_ms, outperforms\n");
    for(int i = 0; i < 5; i++){
        fprintf(fptr1_3, "%d, %f, %f, %d\n", (int)pow(10, i + 2), avg_time_qs[i], avg_time_ms[i], outperforms[i]);
    }
    fclose(fptr1_3);


/*---------------------------------------------------- part1.4 analysing and comparing the time-complexity of QuickSort and ImproveMergeSort. -----------------------------------------------*/

    double avg_time_qs_2[5];
    double avg_time_ims_2[5];
    int outperforms_2[5] = {0,0,0,0,0};

    for(int size_of_array=100; size_of_array<=1000000; size_of_array *= 10){
        printf("running part 1.4 for size of array: %d\n", size_of_array);

        int temp_index = 0;
        temp_index = log10(size_of_array) - 2;

        cpu_time_used = 0;
        double cpu_time_used_qs  = 0;
        double cpu_time_used_ims = 0;
        for(int i=0; i<N_ITER; i++){
            fillArray(arr, size_of_array);
            
            for(int j=0; j<size_of_array; j++){
                arr2[j] = arr[j];
            }

            start = clock();    
                QSort(arr, 0, size_of_array-1);
            end = clock();

            times_qs[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
            cpu_time_used_qs += ((double) (end - start)) / CLOCKS_PER_SEC;

            start = clock();
                ImprovedMSort(arr2, 0, size_of_array-1);
            end = clock();

            times_ims[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
            cpu_time_used_ims += ((double) (end - start)) / CLOCKS_PER_SEC;
        }

        avg_time_qs_2[temp_index] = cpu_time_used_qs / N_ITER;
        avg_time_ims_2[temp_index] = cpu_time_used_ims / N_ITER;

        for(int i=0; i<N_ITER; i++){
            if(times_qs[i] > times_ims[i]){
                outperforms_2[temp_index]++;
            }
        }

    }

    end_f = clock();
    printf("time till part 1.4 ended is %f seconds\n", (double)(end_f - start_f) / CLOCKS_PER_SEC);

    //printing to file
    printf("writing data to file part1_4.csv -->\n");
    fprintf(fptr1_4,"size_of_array, avg_time_qs_2, avg_time_ims_2, outperforms_2\n");
    for(int i=0; i<5; i++){
        fprintf(fptr1_4, "%d, %f, %f, %d\n", (int)pow(10, i+2), avg_time_qs_2[i], avg_time_ims_2[i], outperforms_2[i]);
    }
    fclose(fptr1_4);


/*---------------------------------------------- part2 checking the reliability of QuickSort in practice. ---------------------------------------------------------------------------*/
    double quicksort_avg_time[5];
    double t_5_percent;
    double t_10_percent;
    double t_20_percent;
    double t_30_percent;
    double t_50_percent;
    double t_100_percent;

    int exceeding_times[5][6] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for(int size_of_array = 100; size_of_array <= 1000000; size_of_array *= 10){
        printf("running part 2 for size of array: %d\n", size_of_array);
        int temp_index = 0;
        temp_index = log10(size_of_array) - 2;

        cpu_time_used = 0;
        for(int i=0; i<N_ITER; i++){
            fillArray(arr, size_of_array);

            start = clock();
                QSort(arr, 0, size_of_array-1);
            end = clock();

            times_qs[i] = ((double) (end - start)) / CLOCKS_PER_SEC;
            cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
        }
        quicksort_avg_time[temp_index] = cpu_time_used / N_ITER;

        t_5_percent = quicksort_avg_time[temp_index] * 0.05;
        t_10_percent = quicksort_avg_time[temp_index] * 0.1;
        t_20_percent = quicksort_avg_time[temp_index] * 0.2;
        t_30_percent = quicksort_avg_time[temp_index] * 0.3;
        t_50_percent = quicksort_avg_time[temp_index] * 0.5;
        t_100_percent = quicksort_avg_time[temp_index] * 1;

        for(int i=0; i<N_ITER; i++){
            if(fabs(times_qs[i] - quicksort_avg_time[temp_index]) >= t_5_percent){
                exceeding_times[temp_index][0]++;
            }
            if(fabs(times_qs[i] - quicksort_avg_time[temp_index]) >= t_10_percent){
                exceeding_times[temp_index][1]++;
            }
            if(fabs(times_qs[i] - quicksort_avg_time[temp_index]) >= t_20_percent){
                exceeding_times[temp_index][2]++;
            }
            if(fabs(times_qs[i] - quicksort_avg_time[temp_index]) >= t_30_percent){
                exceeding_times[temp_index][3]++;
            }
            if(fabs(times_qs[i] - quicksort_avg_time[temp_index]) >= t_50_percent){
                exceeding_times[temp_index][4]++;
            }
            if(fabs(times_qs[i] - quicksort_avg_time[temp_index]) >= t_100_percent){
                exceeding_times[temp_index][5]++;
            }
        }

    }

    end_f = clock();
    printf("time till part 2 ended is %f seconds\n", (double)(end_f - start_f) / CLOCKS_PER_SEC);

    //printing to file
    printf("writing data to file part2.csv -->\n");
    fprintf(fptr2,"size_of_array, quicksort_avg_time, exceeding_times_5, exceeding_times_10, exceeding_times_20, exceeding_times_30, exceeding_times_50, exceeding_times_100\n");
    for(int i=0; i<5; i++){
        fprintf(fptr2, "%d, %f, %d, %d, %d, %d, %d, %d\n", (int)pow(10, i+2), quicksort_avg_time[i], exceeding_times[i][0], exceeding_times[i][1], exceeding_times[i][2], exceeding_times[i][3], exceeding_times[i][4], exceeding_times[i][5]);
    }


    
    return 0;
}
    