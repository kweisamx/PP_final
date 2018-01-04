#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


double dot_pro(double *arr1, double *arr2, int num){
    double sum = 0;
    for(int i =0; i<num; i++){
        sum += (arr1[i] * arr2[i]);
    }
    return sum;
}

void mat_pro(double **mat1, double **mat2, double **mat3, int p, int q, int r){
    for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            for(int k=0;k<q;k++){
                mat3[i][j]+=mat1[i][k]*mat2[k][j];
            }
        }
    }
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

    double **U = (double**)malloc(r * sizeof(double*));
    for(int k=0;k<31;k++)
        U[k] = (double*)malloc(c * sizeof(double));

    double *sum_array = (double*)malloc(r * sizeof(double));

    FILE *fstream = fopen("matrix.csv","r");
    if(fstream == NULL){
        printf("\n file opening failed ");
        return -1;
    }
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
    // add all row and make average
    for(int p = 0;p<r;p++){
        for(int q=0;q<c;q++){
            sum_array[p] += arr[p][q];
        }
        //printf("sum_array=%lf\n",sum_array[p]/c);
        sum_array[p] = sum_array[p]/c;
    }
    
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
