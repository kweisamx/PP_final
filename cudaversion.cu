#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXPOINTS 1000000
#define MAXSTEPS 1000000
#define MINPOINTS 20

int row = 480000;
int col = 464;
float *gmat, *gsum;

__global__ void get_average(float *arr, float *sum, int row, int col){
    //int i = blockIdx.x * blockDim.x + threadIdx.x;
    // add all row and make average
    for(int k=threadIdx.x; k<row; k+=blockDim.x){
        for(int q = 0; q<col;q++){
            sum[k] += arr[col*k + q];
        }
        sum[k] /= col;
        for(int q = 0; q<col;q++){
            arr[col*k + q] -= sum[k];
        }

    }


}

int main(){
    char *record, *line;
    
    char buffer[400000];
    int i =0;
    int grid = 1;
    int block = 512;

    /*double **arr = (double**)malloc(row * sizeof(double*));
    for(int k=0;k<row;k++)
        arr[k] = (double*)malloc(col * sizeof(double));
    */
    float *arr = (float*)malloc(row *  col * sizeof(float));
    
    float *sum_array = (float*)malloc(row * sizeof(float));

    FILE *fstream = fopen("matrix.csv","r");
    if(fstream == NULL){
        printf("\n file opening failed ");
        return -1;
    }

    printf("Start load csv\n");
    while((line = fgets(buffer, sizeof(buffer),fstream))!= NULL){
        record = strtok(line, ",");
        while(record != NULL){
            float a = atof(record);
            arr[i++] = a;
            record = strtok(NULL, ",");
        }
    }

    printf("Load Finish%lf\n",arr[5]);


    // Create GPU memory
    int err=  cudaMalloc((void**)&gmat, row*col*sizeof(float));
    printf("err is %d\n",err);
    cudaMalloc((void**)&gsum, row*sizeof(float));
    cudaMemcpy(gmat, arr, row*col*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(gsum, sum_array, row*sizeof(float), cudaMemcpyHostToDevice);
    

    printf("Start calaute\n");
    // Use Cuda kernel
    get_average<<<grid,block>>>(gmat, gsum, row, col);
    
    cudaMemcpy(arr, gmat, row*col*sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(sum_array, gsum, row*sizeof(float), cudaMemcpyDeviceToHost);
    // all row mine average

    
   
    printf("Now write\n");
    FILE *fp;
    fp=fopen("B1.csv","w+");
    for(int i=0;i<row;i++){
        fprintf(fp,"\n%d",i+1);
        for(int j=0;j<col;j++)
            fprintf(fp,",%lf ",arr[j+i*col]);
    }
    return 0;
}
