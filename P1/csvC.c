#include <stdio.h>
#include <stdlib.h>
#include <search.h>

int main(){
	FILE *fp;
	fp = fopen("HashTables.csv", "w+");
	fprintf(fp, "o_ID, d_ID, time. hour\n");
	fclose(fp);
	return 0;
}
