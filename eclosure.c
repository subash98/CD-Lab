#include<stdio.h>
#define MAXSIZE 10
int iS,iC;
char closure[MAXSIZE],stack[MAXSIZE];
void stackPush(char arg){
	if(iS==MAXSIZE){
		printf("Stack overflow");
		return;
	}
	stack[iS++]=arg;
}
char stackPop(){
	if(iS==0){
		printf("Stack underflow");
		return ' ';
	}
	return stack[--iS];
}
int stackEmpty(){
	return (iS==0)?1:0;
}
void addToClosure(char arg){
	if(iC==MAXSIZE){
		printf("Closure limit exceeded");
	}
	closure[iC++]=arg;
}
void pushIfNew(char arg){
	int i,flag=0;
	for(i=0;i<iC;i++){
		if(closure[i]==arg){
			flag=1;
			break;
		}
	}
	if(flag==0){
		stackPush(arg);
		addToClosure(arg);
	}
}
int main(){
    int i,j,Nt;
    char arg,transitions[100][3];
	scanf("%d",&Nt);
	while ((getchar()) != '\n');
	for(i=0;i<Nt;i++){
		scanf("%c %c %c",&transitions[i][0],&transitions[i][1],&transitions[i][2]);
		while ((getchar()) != '\n');
    }
    printf("closure of:");
    scanf("%c",&arg);
	while ((getchar()) != '\n');
	stackPush(arg);
	addToClosure(arg);
	while(!stackEmpty()){
		arg=stackPop();
		for(i=0;i<Nt;i++){
			if(transitions[i][0]==arg && transitions[i][1]=='E'){
				pushIfNew(transitions[i][2]);
			}
		}
	}
	printf("Closure : ");
	for(i=0;i<iC;i++){
		printf("%c ",closure[i]);
	}
	
	return 0;
}
