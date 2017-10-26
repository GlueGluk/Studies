#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


struct node {
    char *str;
    struct node *next;
};

int lngt(struct node *st) {
    int i=0;
    for(;st!=NULL;st=(st->next)) i++;
    return i;
}

struct node *merge2gtr(struct node *l1, struct node *l2) {
  struct node *r, *head;
  r=(struct node *)malloc(sizeof(struct node));
  if (strcmp(l1->str,l2->str)<0) {
                                r->str=l1->str;
                                l1=l1->next;
                                  }
  else {
       r->str=l2->str;
       l2=l2->next;
       }
  head=r;                     
  while((l1!=NULL)&&(l2!=NULL)) {
                         r=r->next=(struct node *)malloc(sizeof(struct node));
                         if (strcmp((l1->str),(l2->str))>0) {
                                               r->str=l2->str;
                                               l2=l2->next;
                                               }
                         else {
                              r->str=l1->str;
                              l1=l1->next;
                              }
                        }
  if (l1==NULL) {
               while (l2!=NULL) {
                    r=r->next=(struct node *)malloc(sizeof(struct node));
                    r->str=l2->str;
                    l2=l2->next;
                    }
   }
  else {
       while(l1!=NULL) {
            r=r->next=(struct node *)malloc(sizeof(struct node));
            r->str=l1->str;
            l1=l1->next;
            }
   }
  r->next=NULL;
  return head;
}
       
struct node *merge_sort (struct node *st) {
  int n,k;
  struct node *tmp,*mid,*res;
  if (st->next==NULL) return st;
  else {
     n=lngt(st)/2;
     tmp=st;
     for(k=1;k<n;k++) tmp=(tmp->next);
     mid=(tmp->next);
     (tmp->next)=NULL;
     st=merge_sort(st);
     mid=merge_sort(mid);
     res=merge2gtr(st,mid);
     return res;
     }
}


void print_list(struct node *list) {
     struct node *tmp;
     char *s;
     int i=1;
     tmp=list;
     while (strcmp(tmp->str,"\n")==0) tmp=tmp->next;
     s=tmp->str;
     tmp=tmp->next;
     for(;tmp!=NULL;tmp=(tmp->next)) {
       if(strcmp(tmp->str,s)==0) i++;
       else {
	 printf("%4d %s",i,s);
	 i=1;
	 s=tmp->str;
       }
     }
}  

void free_list(struct node *list) {
     struct node *tmp;
     while(list!=NULL) {
          tmp=list->next;
          free(list);
          list=tmp;
         }
}

int main (int argc, char *argv[]) {
    char *s;
    struct node *list,*memb;
    list=memb;
    if ((s=getline_unlim())==NULL) {
                                        list=NULL;
                                        printf("empty list");
                                        }
    else {
        list=memb=(struct node *)malloc(sizeof(struct node));
        memb->str=s;
        while((s=getline_unlim())!=NULL) {
            memb=memb->next=(struct node *)malloc(sizeof(struct node));
            (memb->str)=s;
                 }
        memb->next=NULL;
        list=merge_sort(list);
      
        }
    print_list(list);
    free_list(list);
    return 0;
}
 


