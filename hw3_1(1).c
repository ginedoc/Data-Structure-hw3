#include <stdio.h>
#include <stdlib.h>

typedef struct coord{
	int x;
	int y;
	struct coord *next;
}pos;
int M,N;
int s_x,s_y;
int t_x,t_y;
char light;
int i,j,k;
int imove[8] = {-1,0,1,-1,1,-1,0,1};
int jmove[8] = {-1,-1,-1,0,0,1,1,1};


void verify_MN();
void read_map(char* map);
void solve_puzzle(char *map,int n,pos *,pos*);
int all_dark(char*);
void print_map(char *map);
void print_lists(pos* lists);
void free_lists(pos* lists);

int main(){
	verify_MN();
	char map[M*N];
	read_map(map);

	int n=0;
	pos * first = (pos*)malloc(sizeof(pos));
	first->x = s_x;
	first->y = s_y;
	first->next = NULL;
	// print_map(map);
	solve_puzzle(map,n,first,first);
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
			s_x = i++;
			s_y = j;
		}
		else if(c == '\n'){
			j++;			
		}
		else if(c == 'd' || c == '1' || c == '0')
			i++;
		else continue;
	}


	N = j+1;
	M = (i+1)/(j+1);
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
			map[i] = c;
			i++;
		}
		else if(c == '\n'){
			j++;			
		}
		else continue;
	}
	fclose(in);

}

int test = 0;

void solve_puzzle(char *map,int n,pos *p,pos *first){
	char new_map[M*N];
	for(i=0;i<M*N;i++) new_map[i] = map[i];	

	//	break condition
	if(n>7){
		printf("No route\n");
		return;
	}

	// determine light
	if (p->x+imove[n]>=0 && p->y+jmove[n]>=0)
	{
		printf("%d is okay to entry\n", n);
		light = new_map[(p->x+imove[n])+(p->y+jmove[n])*M];
	}
	else if(all_dark(new_map)){
		printf("No route1\n");
		return;
	}
	else {
		solve_puzzle(map,++n,p,first);
		return;
	}

	// general situation
	if(light == '0'){
		printf("%d %d %d\n", p->x,p->y,p->x+p->y*M);
		new_map[p->x+p->y*M] = '*';		
		t_x = p->x + imove[n];
		t_y = p->y + jmove[n];
		// keep the path
		pos*nblock= (pos*)malloc(sizeof(pos));
		p->next = nblock;
		nblock->x = t_x;	nblock->y = t_y;	nblock->next = NULL;

		printf("new block %d %d\n",nblock->x,nblock->y );
		test++;
		if(test ==  16) exit(1);
		print_map(new_map);
		n = 0;
		printf("%d\n",n );
		solve_puzzle(new_map,n,nblock,first);
		return;
	}
	else if(light == 'd'){
		print_lists(first);
		free_lists(p);
		solve_puzzle(map,++n,p,first);
		return;
	}
	else{

		free_lists(p);
		solve_puzzle(map,++n,first,first);
		return;
	}	
}
int all_dark(char* map){
	j=0;
	for(i=0;i<M*N;i++){
		if(map[i]== '1' || map[i]=='*') j++;
	}
	if(j==M*N) return 1;
	else return 0;
}

void print_map(char*map){
	for(i=0;i<M*N;i++){
		printf("%c", map[i]);
		if((i%M)==M-1)printf("\n");
	}
	printf("\n");
}



void print_lists(pos* lists)
{
	i = 0;
    pos* n = lists; 

    // 依序印出節點內容
    while (n != NULL)
    {
        printf("%d ", n->x);
        n = n->next;
        i++;
        while(i%M==0)	printf("\n");
    }

    printf("\n");
}

void free_lists(pos* lists)
{
    // 遞迴刪除串列所有節點
    if (lists->next != NULL)
    {
        free_lists(lists->next);
    }

    free(lists);
}

