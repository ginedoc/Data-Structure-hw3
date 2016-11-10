#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0
#define MAX_SIZE 100000

int M=0,N=0;
int i,j;
int s;

struct Path{
	int position_x;
	int position_y;
	bool node;
};


void M_N_et_Map();
void Print_Map(char **map);

int main(){
	M_N_et_Map();

	struct Path P[M*N];
	// P[0].position_x = s%(i+1);
	// P[0].position_y = s/i;

	// printf("%d\n %d\n", P[0].position_x,P[0].position_y);
	Print_Map(map);


}


void M_N_et_Map(){
	FILE * in;
	char c;

	
	in = fopen("in.txt","r");
	if(!in){
		printf("No such file");
		exit(1);
	}
	
	i = 0; j = 0;	
	while((c=fgetc(in))!=EOF){			
		if(c == 's'){
			s = i;
		}
		else if(c == '\n'){
			j++;			
		}
		else if(c == 's' || c == 'd' || c == '1' || c == '0')
			i++;
		else continue;
	}

	N = j+1;
	M = (i+1)/(j+1);
	fclose(in);

	in = fopen("in.txt","r");
	char map[M][N];	
	i=0;j=0;
	while((c=fgetc(in))!=EOF){	
		map[i][j] = c;
		// printf("%c", map[i][j]);
		if(c == '\n'){
			j++;			
		}
		else i++;
	}
	fclose(in);
}

void Print_Map(char **map){
	for(i=0;i<10;i++){
			printf("%c ", map[i]);

	}
}
