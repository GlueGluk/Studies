#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define FGETS_BUFSIZE 5

//Функция, позволяющая считать строку неограниченной длины.
char *getline_unlim (void) {
      char *s, *ec, *serr;
      s=NULL;
      int c;
      c=getc(stdin);
      if (c==EOF)  
              return NULL;
      else {
      ungetc(c,stdin);
      s=(char*)malloc(FGETS_BUFSIZE);
      int i=5,p=0;
      for(;;) {
                ec=fgets(s+(FGETS_BUFSIZE-1)*p,FGETS_BUFSIZE,stdin);
                if((ec==NULL)&&(!feof(stdin))) {
                            serr=strerror(errno);
                            printf("%s",serr);
                            fprintf(stderr,"%d",errno);
                            exit(EXIT_FAILURE);
                            }
                if ((strlen(s+(FGETS_BUFSIZE-1)*p)!=(FGETS_BUFSIZE-1))||(*(s+(FGETS_BUFSIZE-1)*(p+1)-1)=='\n')) break;
                 s=(char*)realloc(s,i+=FGETS_BUFSIZE);
                 p++;
                 }
      return s;
     }
}
