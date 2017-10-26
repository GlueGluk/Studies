#include "util.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    char *str;
    struct node *next;
};

void print_list(struct node *list) {
     struct node *tmp;
     tmp=list;
     for(tmp=list;tmp!=NULL;tmp=(tmp->next)) 
         printf("%s",(tmp->str));
     
}  

void free_list(struct node *list) {
     struct node *tmp;
     while(list!=NULL) {
          tmp=list->next;
          free(list);
          list=tmp;
         }
}

//Делит строку на слова, сохраняя их в список.
int main(int argc,char *argv[]) {
	char *s;
	struct node *list, *memb;
	int l=0,i;
	if ((argc>1)&&(strcmp(argv[1],"-l")==0)) l=1; 
	s=getline_unlim();
	if (s==NULL) {
			printf("empty text\n");
			list=NULL;
			}
	else {
		list=memb=malloc(sizeof(struct node));
		i=0;
		while (s[i]!='\0') {
			if (isspace(s[i])||ispunct(s[i])) s[i]='\n';
			if (l==1) {
				s[i]=tolower(s[i]);
				}
			i++;
			}
		memb->str=s;
		while((s=getline_unlim())!=NULL) {
			i=0;
			while (s[i]!='\0') {
				if (isspace(s[i])||ispunct(s[i])) s[i]='\n';
				if(l==1) {
					s[i]=tolower(s[i]);
					}
				i++;
				}
			memb=memb->next=(struct node *)malloc(sizeof(struct node));
            (memb->str)=s;
			}
		memb->next=NULL;
		print_list(list);
		free_list(list);
		}
	return 0;
}
		
