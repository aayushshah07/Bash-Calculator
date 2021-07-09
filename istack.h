#ifndef ISTACK_H_INCLUDED
#define ISTACK_H_INCLUDED


#include "list.h"

typedef struct inode{

	struct inode* i;
	number *a;
}inode;


typedef struct istack{

	inode* top;
	int size;

}istack;



typedef struct cnode{

	struct cnode* i;
	char a;

}cnode;

typedef struct cstack{

	cnode *top;
	int size;

}cstack;

void initIstack(istack *s);
void istackPush(istack *s, number *a);
number* istackPop(istack *s);
number* istackTop(istack s);
int istackEmpty(istack s);
void initCstack(cstack *s);
void cstackPush(cstack *s,char a);
char cstackPop(cstack *s);
char cstackTop(cstack s);
int cstackEmpty(cstack s);





#endif // ISTACK_H_INCLUDED
