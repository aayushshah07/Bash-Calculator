#include<stdlib.h>
#include"istack.h"

// Stack implementation to store number list.
void initIstack(istack *s)
{
	s->top = NULL;
	s->size= 0;
}


void istackPush(istack *s, number *a)
{
    if(a == NULL)return;
	inode *tmp;
	tmp = (inode*)(malloc(sizeof(inode)));
	tmp->a = a;
	tmp->i = s->top;
	s->top = tmp;
	s->size++;
}

//we will always call when stack is not empty.
number* istackPop(istack*s)
{

	inode *tmp;
	number *r;
	tmp = s->top;
	r = tmp->a;
	s->top = tmp->i;
	free(tmp);
	s->size--;
	return r;
}
//we will call top when stack is not empty.
number* istackTop(istack s)
{
	inode *tmp;
	tmp = s.top;
	return tmp->a;
}

int istackEmpty(istack s)
{
	if(s.size == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


void initCstack(cstack *s){

	s->top = NULL;
	s->size = 0;
}

void cstackPush(cstack *s, char a)
{

	cnode *tmp;
	tmp = (cnode*)(malloc(sizeof(cnode)));
	tmp->a = a;
	tmp->i = s->top;
	s->top = tmp;
	s->size = s->size+1;

}

char cstackPop(cstack *s)
{
	char r;
	cnode *tmp;
	tmp = s->top;
	r = tmp->a;
	s->top = tmp->i;
	free(tmp);
	s->size--;
	return r;
}

char cstackTop(cstack s)
{
	char r;
	cnode *tmp;
	tmp = s.top;
	r = tmp->a;
	return r;
}


int cstackEmpty(cstack s)
{
	if(s.size == 0)
	{
		return 1;
	}
	else{
		return 0;
	}
}

//########################################################################################################

