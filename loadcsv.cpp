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
    for(int k = 0;k<i;k++)
        arr[k] = (double *)malloc(c * sizeof(double));
    FILE *fstream = fopen("matrix.csv","r");
    if(fstream == NULL){
        printf("\n file opening failed ");
        return -1;
    }
    while((line = fgets(buffer, sizeof(buffer),fstream))!= NULL){
        record = strtok(line, ",");
        while(record != NULL){
            printf("record: %s\n", record);
            //arr[i][j++] = atoi(record);
            record = strtok(NULL, ",");
        }
        i++;
    }
    return 0;
}
