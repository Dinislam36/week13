#include <stdio.h>
#include <stdlib.h>


int main(){
	int m = 3;
	int n = 5;
	int e[m];
	int a[m];
	int c[n][m];
	int r[n][m];
	FILE *fo = fopen("input_dl.txt", "r");

	for(int i = 0; i < m; i++){
		fscanf(fo, "%d", &e[i]);
	}
	for(int i = 0; i < m; i++){
		fscanf(fo, "%d", &a[i]);
	}
	for(int i = 0; i < n; i++){
		for(int k = 0; k < m; k++){
			fscanf(fo, "%d", &c[i][k]);	
		}
		
	}
	for(int i = 0; i < n; i++){
		for(int k = 0; k < m; k++){
			fscanf(fo, "%d", &r[i][k]);	// 4 loops for imput
		}
	}

	int comp[n];
	for(int i = 0; i < n; i++){ // array of completed processes
		comp[i] = 0;
	}
	fclose(fo);

	int boolean = 1;
	while(boolean){
		boolean = 0;

		for(int i = 0; i < n; i++){ 
			if(comp[i]){ // if process executed, skip it
				continue;
			} 

			for(int k = 0; k < m; k++){
				if(a[k] >= r[i][k]){ // check if we have enough resources
					boolean = 1;
				} else{
					boolean = 0;
					break;
				}
			}

			if(boolean){ // if we have resources
				comp[i] = 1;
				for(int k = 0; k < m; k++){
					a[k] = a[k] + c[i][k]; // add to available resourcesw
				}
			}
		}
	}
	int zeros = 0;
	for(int i = 0; i < n; i++){
		if(comp[i] == 0){ // check is there are deadlocks
			zeros++;
		}
	}
	FILE *f_out = fopen("output_dl.txt", "w");
	if(zeros == 0){
		printf("No deadlock :) \n");
		fprintf(f_out, "No deadlock :)\n");
	} else{
		printf("Oh, there are some deadlocks in these processes: \n");
		fprintf(f_out, "Oh, there are some deadlocks in these processes:\n");
		for(int i = 0; i < n; i++){
			if(comp[i] == 0){
				printf("%d\n", i);
				fprintf(f_out, "%d\n", i);
			}
		}
	}

	return 0;
}