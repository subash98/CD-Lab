#include<stdio.h>

/****************************/
// input: row 1: Length of language
//         row 2: Input symbols
//         row 3: No of Transitions
//         row >3: "qi input qj"
/****************************/

typedef struct trans TRANS;
struct trans{
    int from;
    char input;
    int to;
};
int indexOf(char *arr,int n,char ch){
    int i;
    for(i=0;i<n;i++){
        if(arr[i]==ch){
            return i;
        }
    }
    return -1;
}
int toBitMask(int n){
    return 1<<n;
}
void printFromMask(int n){
    int i;
    // printf("%d",n);
    for(i=0;i<31;i++){
        if( ( (1<<i)&n ) != 0 ){
            printf("%d ",i);
        }
        else 
            printf("NULL");
    }
}
int addnew(int *arr,int n, int x){
    int i,flag=0;
    for(i=0;i<n;i++){
        if(arr[i]==x){
            flag=1;
            break;
        }
    }
    if(flag==0){
        arr[n]=x;
        // printf("%d is new\n",x);
        return n+1;
    }
    return n;
}
int main(){
    int Nl,i,j;
    char language[10];
    scanf("%d",&Nl);
    // printf("Nl: %d\n",Nl);
    while(getchar()!='\n');
    for(i=0;i<Nl;i++){
        scanf("%c ",&language[i]);
    }
    // for(i=0;i<Nl;i++){
    //     printf(">>%c\n",language[i]);
    // }
    TRANS transistions[100];
    int Nt,a,c;
    char b;
    scanf("%d",&Nt);
    for(i=0;i<Nt;i++){
        scanf("%d %c %d",&a,&b,&c);
        // printf("%d %c %d",a,b,c);
        transistions[i].from=toBitMask(a);
        transistions[i].input=b;
        transistions[i].to=toBitMask(c);
    }
    // for(i=0;i<Nt;i++){
    //     printf(">> %d %c %d\n",transistions[i].from,transistions[i].input,transistions[i].to);
    // }
    int DFA[20][10];
    for(i=0;i<20;i++){
        for(j=0;j<10;j++){
            DFA[i][j]=0;
        }
    }
    int states[20],statecount=1,state,t,l,column;
    states[0]=2;
    for(i=0;i<statecount;i++){
        for(state=1;state<0x40000000;state=state<<1){
            //printf("%d ",state );
            if((state & states[i]) == state){
                //for(l=0;l<Nl;l++){
                    // printf("%d in %d\n",state,states[i]);
                    for(t=0;t<Nt;t++){
                        if(transistions[t].from==state){
                            column=indexOf(language,Nl,transistions[t].input);
                            // printf("Transition for %d on %c to %d \n",state,language[column],transistions[t].to);
                            DFA[i][column] |= transistions[t].to;
                            // printf("DFA:from %d on %c to %d\n",states[i],language[column],DFA[i][column]);
                        }
                    }
                //}
            }
            // else{
            //     printf("not in %d\n",states[i]);
            // }
        }
        for(l=0;l<Nl;l++){
            if(DFA[i][l]!=0){
                statecount=addnew(states,statecount,DFA[i][l]);
            }
        }
    }
    printf("DFA:\n");
    printf("input\t");
    for(l=0;l<Nl;l++){
        printf("%c\t",language[l]);
    }
    printf("\n");
    for(i=0;i<statecount;i++){
        // printf("\n%d\t",states[i]);
        printFromMask(states[i]);
        printf("\t");
        for(l=0;l<Nl;l++){
            // printf("%d\t",DFA[i][l]);
            printFromMask(DFA[i][l]);
            printf("\t");
        }
        printf("\n");
    }
    return 0;
}