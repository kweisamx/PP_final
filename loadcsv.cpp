#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    return 0;
}
