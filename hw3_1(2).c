#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
}Pos;
int M=0;
int N=0;
int step=0;
Pos start,end,kstart;
int i,j,k;
int imove[8] = {-1,0,1,-1,1,-1,0,1};
int jmove[8] = {-1,-1,-1,0,0,1,1,1};

void verify_MN();
void read_map(char *map);
Pos position(int,int);
void solve_puzzle(char *map,Pos start,Pos end,void (*keep)(char*,FILE *),FILE *out);
void print(char *map,FILE *out);

int main(){
	FILE *out;
	out = fopen("out.txt","w");
	verify_MN();
	char map[M*N];
	read_map(map);

	step = 0;
	map[start.x+start.y*M] = '0';
	map[end.x+end.y*M] = '0';
	solve_puzzle(map,start,end,print,out);

	fclose(out);

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

			kstart = start;
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

}
Pos position(int x,int y){
	Pos p;
	p.x = x;
	p.y = y;
	return p;
}
void solve_puzzle(char *map,Pos start,Pos end,void (*keep)(char*,FILE*),FILE *out){
	if(map[start.x+start.y*M] == '0'){
		map[start.x+start.y*M] = '*';
		step++;
		if(map[end.x+end.y*M] == '*'){
				map[kstart.x+kstart.y*M] = 's';
				map[end.x+end.y*M] = 'd';	


				keep(map,out);

				fprintf(out,"step:%d\n",step);
				fprintf(out, "-------------------\n" );
				// printf("step:%d\n",step);
				step = 0;

				map[start.x+start.y*M] = '0';
				map[end.x+end.y*M] = '0';	
		}
		else{
				solve_puzzle(map,position((start.x+imove[0]),(start.y+jmove[0])),end,keep,out);
				solve_puzzle(map,position((start.x+imove[1]),(start.y+jmove[1])),end,keep,out);
				solve_puzzle(map,position((start.x+imove[2]),(start.y+jmove[2])),end,keep,out);
				solve_puzzle(map,position((start.x+imove[3]),(start.y+jmove[3])),end,keep,out);
				solve_puzzle(map,position((start.x+imove[4]),(start.y+jmove[4])),end,keep,out);
				solve_puzzle(map,position((start.x+imove[5]),(start.y+jmove[5])),end,keep,out);
				solve_puzzle(map,position((start.x+imove[6]),(start.y+jmove[6])),end,keep,out);
				solve_puzzle(map,position((start.x+imove[7]),(start.y+jmove[7])),end,keep,out);
		}
		map[start.x+start.y*M] = '0';
	}
}
void print(char map[N*M],FILE *out){
	for(j=0;j<N;j++){
		for(i=0;i<M;i++){
			switch(map[i+j*M]){
				case 's':
					fprintf(out,"s");
					// printf("s");
				break;
				case 'd':
					fprintf(out,"d");
					// printf("d");
				break;
				case '1':
					fprintf(out,"1");
					// printf("1");
				break;
				case '0':
					fprintf(out,"0");
					// printf("0");
				break;
				case '*':
					fprintf(out,"*");
					// printf("*");
				break;
				case 'w':
					fprintf(out," ");
					// printf(" ");
				break;
				default:
					fprintf(out,"x");
					// printf("x");
				break;
			}
		}
		fprintf(out,"\n");
		// printf("\n");
	}
}