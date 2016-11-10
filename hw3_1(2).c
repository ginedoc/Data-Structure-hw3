#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
}Pos;
int M=0;
int N=0;
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
	// print(map);

	map[start.x+start.y*M] = '0';
	map[end.x+end.y*M] = '0';
	if(solve_puzzle(map,start,end) == '0'){
		printf("No solution\n");
	}
	else{
		map[start.x+start.y*M] = 's';
		map[end.x+end.y*M] = 'd';	
		print(map);
	}	
	

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


	M = j+1;
	N = (k+1)/(j+1);
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
	in = fopen("in.txt","r");

	while((c = fgetc(in))!=EOF){
		if(c == 's' || c == 'd' || c == '1' || c == '0'){
			map[i++] = c;
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
	if(map[start.x+start.y*M] == '0'){
		map[start.x+start.y*M] = '*';

		if(map[end.x+end.y*M] == '0'){
			for(i=0;i<8;i++){
				printf("%c\n",  map[end.x+end.y*M]);
				if(!solve_puzzle(map,position(start.x+imove[i],start.y+jmove[i]),end) == '0')
				{
					map[start.x+start.y*M] = '0';
					printf("go\n");
				}
			}
		}
	}
	return map[end.x+end.y*M];
}
void print(char map[N*M]){
	for(j=0;j<N;j++){
		for(i=0;i<M;i++){
			switch(map[i+j*M]){
				case 's':
					printf("s");
				break;
				case 'd':
					printf("d");
				break;
				case '1':
					printf("1");
				break;
				case '0':
					printf("0");
				break;
				case '*':
					printf("*");
				break;
				default:
					printf("x\n");
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}