#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
}Pos;
int M=0;
int N=0;
int step=0;
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
	char map[M*N];
	read_map(map);

	map[start.x+start.y*M] = '0';
	map[end.x+end.y*M] = '0';
	if(!solve_puzzle(map,start,end)){
		printf("No solution\n");
	}
	else{
		map[start.x+start.y*M] = 's';
		map[end.x+end.y*M] = 'd';	
		print(map);
		printf("%d steps\n", step-1);
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
			start.x = 1+i++;
			start.y = 1+j;
		}
		if(c == 'd'){
			k++;
			end.x = 1+i;
			end.y = 1+j;
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

	M = (j+1)+2;
	N = ((k+1)/(j+1))+2;	
	printf("%d %d\n", M,N);
	fclose(in);
}
void read_map(char *map){
	FILE * in;
	char c;


	if(!in){
		printf("No such file");
		exit(1);
	}
	in = fopen("in.txt","r");

	for(i=0;i<M*N;i++){
		if(i%M==0 || i%M==M-1 || i/M==0 || i/M==N-1) map[i] = 'w';
	}
	i=M+1;
	while((c = fgetc(in))!=EOF){
			while(i%M==0 || i%M==M-1 || i/M==0 || i/M==N-1)++i;
			if(c == '\n') continue;
			else if(c=='s' || c=='d' ||
					c=='0' || c=='1') map[i++] = c;
	}
	fclose(in);

	print(map);
}
Pos position(int x,int y){
	Pos p ={x,y};
	return p;
}
char solve_puzzle(char *map,Pos start,Pos end){
	if(map[start.x+start.y*M] == '0'){
		step++;
		map[start.x+start.y*M] = '*';

		if(map[end.x+end.y*M] == '0'){
			for(i=0;i<8;i++){
				if(!solve_puzzle(map,position(start.x+imove[i],start.y+jmove[i]),end))
				{
					map[start.x+start.y*M] = '0';
				}
			}
		}
	}
	return map[end.x+end.y*M];
}
void print(char map[N*M]){
	for(j=0;j<N;j++){
		for(i=0;i<M;i++){
			switch(map[i+j*(M)]){
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
				case 'w':
					printf(" ");
				break;
				default:
					printf("x");
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}