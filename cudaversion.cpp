#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cuda.h>

#define MAXPOINTS 1000000
#define MAXSTEPS 1000000
#define MINPOINTS 20

double **gmat, *sum_arr;

__global__ void get_average(double **arr, double *sum, int row){
    int p=blockIdx.x*blockDim.x+threadIdx.x;
    // add all row and make average
    for(int p = 0;p<r;p++){
        for(int q=0;q<c;q++){
            sum_array[p] += arr[p][q];
        }
        //printf("sum_array=%lf\n",sum_array[p]/c);
        sum_array[p] = sum_array[p]/c;
    }
    if (p < point) {
    for (int k = 0;k<nsteps;k++){
        if ((p== 0) || (p  == point - 1))
            cval = 0.0;
        else
            cval = (2.0 * bval) - aval + (0.09 * (-2.0)*bval);
            
            aval = bval;
            bval = cval;
            __syncthreads();
        }
    }
    b[p] = bval;
}


int main(){
    char *record, *line;
    
    int r = 480000;
    int c = 464;
    char buffer[400000];
    int i =0,j =0;

    double **arr = (double**)malloc(r * sizeof(double*));
    for(int k=0;k<r;k++)
        arr[k] = (double*)malloc(c * sizeof(double));

    double *sum_array = (double*)malloc(r * sizeof(double));

    FILE *fstream = fopen("matrix.csv","r");
    if(fstream == NULL){
        printf("\n file opening failed ");
        return -1;
    }

    printf("Start load csv\n");
    while((line = fgets(buffer, sizeof(buffer),fstream))!= NULL){
        record = strtok(line, ",");
        while(record != NULL){
            double a = atof(record);
            arr[i][j++] = a;
            //printf("%lf\n",a);
            record = strtok(NULL, ",");
        }
        j = 0;
        i++;
    }

    printf("Load Finish\n");

    // Create GPU memory
    cudaMemcpy(gmat, arr, r*c*sizeof(double), cudaMemcpyHostToDevice);
    
    // all row mine average
    for(int p = 0;p<r;p++){
        for(int q=0;q<c;q++){
            arr[p][q] = arr[p][q] - sum_array[p];
            //printf("%lf\n",arr[p][q]);
        }
    }
    FILE *fp;
    fp=fopen("B.csv","w+");
    for(int i=0;i<r;i++){
        fprintf(fp,"\n%d",i+1);
        for(int j=0;j<c;j++)
            fprintf(fp,",%lf ",arr[i][j]);
    }
    /*
    unsigned int seed = time(NULL);
    double *rand_vector = (double*)malloc(r * sizeof(double));
    for(int k =0;k<r;k++){
        rand_vector[k] = (double)rand_r(&seed);
       // printf("%lf\n",rand_vector[k]);
    }
    double rand_v_dot;
    rand_v_dot = dot_pro(rand_vector, rand_vector, r);
    for(int k = 0;k<r;k++){
        rand_vector[k] = rand_vector[k]/rand_v_dot;
        printf("%10lf\n",rand_vector[k]);
        //U[k][1] = rand_vector[k];
    }
    */
    //double *G_vector = (double*)malloc(r * sizeof(double));
    //double *U_vector = (double*)malloc(r * sizeof(double));
    //double *sum_vector = (double*)malloc(r * sizeof(double));
    // init 
    /*
    for(int k= 0;k<r;k++){
        G_vector[k] = arr[k][1];
       // U_vector[k] = U[k][1];
       // sum_vector[k] = 0;
        //sum_vector[k] = dot_pro(G_vector, U_vector, r);
       // printf("%lf\n",sum_vector[k]);
    }*/
   

    return 0;
}
