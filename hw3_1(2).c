#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
}Pos;
int M,N;
Pos start,end;
int i,j,k;
int imove[8] = {-1,0,1,-1,1,-1,0,1};
int jmove[8] = {-1,-1,-1,0,0,1,1,1};

void verify_MN();
void read_map(char *map);
Pos position(int,int);
char solve_puzzle(char *map,Pos start,Pos end);
void print(char *map);

int main(){
	verify_MN();
	char map[N*M];
	read_map(map);
	printf("%d %d\n", M,N);
	printf("%d %d\n%d %d\n", start.x,start.y,end.x,end.y);

	map[start.x+start.y*M] = '0';
	map[end.x+end.y*M] = '0';
	if(!solve_puzzle(map,start,end)){
		printf("No solution\n");
	}
	print(map);
}

/************************************************************/
void verify_MN(){
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
			k++;
			start.x = i++;
			start.y = j;
		}
		if(c == 'd'){
			k++;
			end.x = i;
			end.y = j;
		}
		else if(c == '\n'){
			i=0;
			j++;			
		}
		else if(c == '1' || c == '0'){
			i++;
			k++;
		}
		else continue;
	}


	N = j+1;
	M = (k+1)/(j+1);
	fclose(in);
}
void read_map(char *map){
	FILE * in;
	char c;


	if(!in){
		printf("No such file");
		exit(1);
	}
	i=0;
	j=0;
	in = fopen("in.txt","r");

	while((c = fgetc(in))!=EOF){
		if(c == 's' || c == 'd' || c == '1' || c == '0'){
			map[j*M+i] = c;
			i++;
		}
		else if(c == '\n'){
			i=0;
			j++;			
		}
		else continue;
	}
	fclose(in);

}
Pos position(int x,int y){
	Pos p ={x,y};
	return p;
}
char solve_puzzle(char *map,Pos start,Pos end){
	if(!map[start.x+start.y*M]){
		map[start.x+start.y*M] = '1';

		if(!map[end.x+end.y*M]){
			for(i=0;i<8;i++){
				if(!solve_puzzle(map,position(start.x+imove[i],start.y+jmove
					[i]),end))
					map[start.x+start.y*M] = '0';
			}
		}
	}
	return map[end.x+end.y*M];
}
void print(char map[N*M]){
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			switch(map[i+j*M]){
				case 's':
					printf("s");
				break;
				case 'd':
					printf("d");
				break;
				case '0':
					printf("*");
				break;
				case '1':
					printf("1");
				break;
			}
		}
		printf("\n");
	}
}