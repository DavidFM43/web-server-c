#include <stdio.h>
#include <string.h>


struct ride 
{
    int id_source;
    int id_dest;
    int hour;
    float avg_time;
    
    int *next_id_source;
    int *next_id_dest;
    int *next_source;
    int *next_avg;
    
};

void main()
{
    FILE* fp = fopen("test_travel_data.csv", "r"); //Open file
    char *value;

    if (!fp){

        printf("Can't open file\n");

    }else{
        char buffer[1024];
        while(fgets(buffer, 1024, fp)){

        value = strtok(buffer,",");

        printf("%s\n", value);
        while (value){
            printf("%s\n", value);
            value = strtok(NULL, ",");
        }
            printf("ola");
        }
    }

    fclose(fp);
}