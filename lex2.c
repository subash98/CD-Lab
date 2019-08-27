#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
char buff[255];
FILE *fpout;
int i;
void append(char ch){buff[i++]=ch;buff[i]='\0';}
int identify(){
	char keywords[32][8] = {"auto","break","case","char","const","continue","default",
                            "do","double","else","enum","extern","float","for","goto",
                            "if","int","long","register","return","short","signed",
                            "sizeof","static","struct","switch","typedef","union",
                            "unsigned","void","volatile","while"};
	//char op[][3]={"+","-","%","*","/","<","<=",">",">=","==","!=","&&","||"};
	//complete this
	int j;
	for(j=0;j<32;j++){
		if(strcmp(buff,keywords[j])==0){
			return 0;
		}
	}	
	return 1;
}
int categorizeFirst(char ch){
	if(isalpha(ch)) return 1;  // kw and id starts with alpha
	if(isdigit(ch)) return 5; // num lit start with num
	if(ch=='_') return 2; //if _ surely id
	if(ch=='"') return 5; // str lit start with quotes
	if(ch=='\'') return 5; // same as above
	if(isspace(ch)) return 6; // spaces and stuff
	if( ch=='=' || ch=='+' ||  ch=='<' ||  ch=='>' ||  ch=='*' ||  ch=='/' || ch=='-' || ch=='%' || ch=='&' ) return 3;
	if(ch=='#') return 7; // compiler directives 
	if(ispunct(ch)) return 4; // dl or op
	if(ch=='/') return 8; //comments
	return 16;
}
int tokenize(int type){
	if(i==0){ return 1; }
	i=0;
	char types[5][3]={"KeyWord","Identifier","Operator","Delimiter","Literal"};
	if(type==1) type=identify();
	printf("<%s,%s>\n",buff,types[type]);
	fprintf(fpout,"<%s,%s>\n",buff,types[type]);
	return 0;
}
int main(){

	FILE *fp;
	char ch,head;
	int count=0;
	int curr,prev;
	fp=fopen("source.txt","r");
	fpout=fopen("output.txt","w");
	if(fp==NULL){
		printf("file doesn't exist\n");
		return 0;
	}
	ch=fgetc(fp);
	curr=categorizeFirst(ch);
	while(ch!=EOF){
		curr=categorizeFirst(ch);
		switch(curr){
			case 1:append(ch);
				while((ch=fgetc(fp))!=EOF && (isalnum(ch) || ch=='_')) { // for words that can be KW or ID
						append(ch);
				}
				tokenize(1);break;
			case 2:append(ch);
				while((ch=fgetc(fp))!=EOF && (isalnum(ch) || ch=='_')) { // for words that can be ID
						append(ch);
				}
				tokenize(1);break;
			case 3:append(ch); // Char is OP (XD
				ch=fgetc(fp);
				curr=categorizeFirst(ch);
				if(ch=='*'){  
					while((ch=fgetc(fp))!='*'){} // skip comments
					ch=getc(fp); // skip end of comment
					ch=getc(fp);
					i=0;
					break;
				}
				if(ch=='/'){
					while((ch=fgetc(fp))!='\n'){}
					ch=getc(fp);
					i=0;
					break;
				}
				if(curr==3){
					append(ch);
					ch=fgetc(fp);
				}
				tokenize(2);break;
			case 4:append(ch); // Char is DL
				ch=fgetc(fp);
				tokenize(3);break;
			case 5:if(ch=='"'){  // LITERAL IN DOUBLE quotes
					append(ch);
					while((ch=fgetc(fp))!='"'){
						if(ch=='\\'){
							append(ch);
							ch=fgetc(fp);
						}
						append(ch);
					}
					append(ch);
					ch=fgetc(fp);
				}
				if(ch=='\''){ // LITERAL IN single quotes
					append(ch);
					while((ch=fgetc(fp))!='\''){
						if(ch=='\\'){
							append(ch);
							ch=fgetc(fp);
						}
						append(ch);
					}
					append(ch);
					ch=fgetc(fp);
				}
				if(isdigit(ch)){ // numeric literals
					append(ch);
					while(isdigit((ch=fgetc(fp)))){
						append(ch);
					}
					if(ch=='.' || ch=='e' || ch=='E'){
						append(ch);
						while(isdigit((ch=fgetc(fp)))){
							append(ch);
						}
					}
				}
				
				tokenize(4);
				break;
			case 7:while((ch=fgetc(fp))!='\n'){}
				ch=getc(fp);
				break;
			/*case 8:ch=getc(fp);
				if(ch=='*'){
					while((ch=fgetc(fp))!='*'){} // skip comments
					ch=getc(fp); // skip end of comment
				}
				if(ch=='/'){
					while((ch=fgetc(fp))!='\n'){}
				}
				
				ch=getc(fp);
				break;*/
			default:tokenize(0);ch=fgetc(fp);
		}
			
	}
	
	fclose(fp);
	fclose(fpout);
	return 0;
}
