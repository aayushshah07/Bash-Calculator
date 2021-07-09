#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "list.h"
#include "functions.h"

//Function to equal the digits after decimal point.
void decimalEqual(number *a, number *b) {
	int aDec = a->dec;
	int bDec = b->dec;
	int d;
	if(aDec > bDec){

         d = aDec - bDec;
        while(d--){

            appendRight(b,'0');
            b->dec++;
        }
	}
	else{
        d = bDec - aDec;
        while(d--){

            appendRight(a,'0');
            a->dec++;
        }
	}
}

//equals the length of both numbers by prepending zeros to small number.
void lengthEqual(number *a, number *b) {
	int d;
	d = length(*a)-length(*b);
	if(d>0){

        while(d--){

            appendleft(b,0);
        }
	}
	else{

        d = d*(-1);
        while(d--){

            appendleft(a,0);
        }
	}
}

//checks whether the number is zero or not. returns 0 if it is zero number.
int isZero(number a){

    node* n = a.head;
    int flg = 0;
    while(n!= NULL){

        int tmp = n->num;
        if(tmp != 0){
            flg = 1;
            break;
        }
        n = n->next;
    }
    if(flg) return 0;
    else return 1;

}

//this function will return 1 when there are zero decimal points or if there is only one digit after decimal point then it should be 0
int isInteger(number * a){

    removeZeros(a);
    if(a->dec == 0){

        return 1;
    }
    else if(a->dec == 1){

        if(a->tail->num == 0){

            return 1;
        }
        else return 0;
    }
    else return 0;


}

//copy number a in number b.
void copy(number *a, number *b) {
	int i, no, len;
	char ch;
	len = length(*a);
	node *t1 = a->head;
	for(i = 0; i < len; i++) {
		no = t1->num;
		ch = no + '0';
		appendRight(b, ch);
		t1 = t1->next;
	}
	b->dec = a->dec;
	b->sign = a->sign;
	return;
}
//Addition Operation
number *add(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	init(ans);
	decimalEqual(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = sub(b, a);
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = sub(a, b);
		}
	}
	else if(a->sign == b->sign) {

		lengthEqual(a,b);
		int n1,n2;
		node *tmp1,*tmp2;
		tmp1 = a->tail;
		tmp2 = b->tail;
		int carry = 0, sum = 0;
		while(tmp1!=NULL){

            n1 = tmp1->num;
            n2 = tmp2->num;
            sum = n1+n2+carry;
            carry = sum/10;
            sum = sum%10;
            appendleft(ans,sum);
            tmp1 = tmp1->prev;
            tmp2 = tmp2->prev;
		}
		if(a->sign == PLUS){

            ans->sign = PLUS;
		}
		else{

            ans->sign = MINUS;
		}
		ans->dec = a->dec;
		if(carry != 0)
			appendleft(ans, carry);
	}
	roundoff(ans);
	return ans;
}

/*Function for finding bigger number among equal length numbers.*/
int compareEqual(number a, number b) {
	lengthEqual(&a, &b);
	decimalEqual(&a, &b);
	node *p, *q;
	int len;
	int i;
	len = length(a);
	p = a.head;
	q = b.head;
	for(i = 1; i <= len; i++) {
		if(p->num > q->num)
			return 1;  //i.e. number a greater than number b.
		else if(p->num < q->num)
			return -1;  //i.e. a is less than b.
		p = p->next;
		q = q->next;
	}
	return 0;    //i.e. both numbers are equal.
}
//Substraction operation.
number *sub(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	init(ans);
	decimalEqual(a, b);
	lengthEqual(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = add(a, b);
			ans->sign = MINUS;
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = add(a, b);
			ans->sign = PLUS;
		}
	}
	else if(a->sign == b->sign) {

            if(a->sign == PLUS){

                if(compareEqual(*a,*b) == -1){

                    node* tmp;
                    tmp = a;
                    a = b;
                    b = tmp;
                    ans->sign = MINUS;
                }
                int len = length(*a);
                node *tmp1, *tmp2;
                int n1,n2,carry = 0;
                int diff = 0;
                tmp1 = a->tail;
                tmp2 = b->tail;
                while(tmp1!=NULL){

                    n1 = tmp1->num ;
                    n2 = tmp2->num;
                    diff = n1 - n2 - carry;
                    if(diff < 0){

                        diff+=10;
                        carry = 1;
                    }
                    else carry = 0;

                    appendleft(ans,diff);
                    tmp1 = tmp1->prev;
                    tmp2 = tmp2->prev;
                }

            }
            else{
                b->sign = PLUS;
                a->sign = PLUS;

                ans = sub(b,a);
            }
		}

	ans->dec = a->dec;
	roundoff(ans);
	return ans;
}
//Multiplication Operation.
number *mult(number *a, number *b) {
	number* ans;
    ans = (number*)(malloc(sizeof(number)));
    init(ans);
    if(isZero(*a) == 1 || isZero(*b) == 1){
        appendRight(ans,'0');
        return ans;
    }
    if(a->sign == b->sign){

        ans->sign = PLUS;
    }
    else{
        ans->sign = MINUS;
    }
    int lenA , lenB;
    lenA = length(*a);
    lenB = length(*b);
    int len = (lenA>lenB)?lenA:lenB;
    int result[2*len];
    for(int i=0; i< (2*len); i++){
        result[i] = 0;
    }

    node* n1 = a->tail;
    node* n2 = b->tail;
    int i_n1 = 0, i_n2 = 0;
    while(n1 != NULL){

        int carry = 0;
        n2 = b->tail;
        i_n1 = 0;
        while(n2 != NULL){

            int d1 = n1->num;
            int d2 = n2->num;
            int sum = d1*d2 + result[i_n1+i_n2]+carry;
            carry = sum/10;
            result[i_n1+i_n2] = sum % 10;
            i_n1++;
            n2 = n2->prev;
        }
        if(carry){
            result[i_n1 + i_n2] += carry;
        }

        i_n2++;
        n1 = n1->prev;

    }
    int i = 2*len-1;
    while(i>=0 && result[i] == 0){
        i--;
    }

    for(int j = 0;j <= i;j++){
        appendleft(ans,result[j]);
    }
    ans->dec = (a->dec)+(b->dec);
    roundoff(ans);
    return ans;
}
//Division Operation.
number *fun(number *m , number *n,int pre){
    int i;
    i = 9;
	number *c, *d, *ans, *q, *pro;
	c = (number *)malloc(sizeof(number));
	d = (number *)malloc(sizeof(number));
	ans = (number *)malloc(sizeof(number));
	pro = (number *)malloc(sizeof(number));
	q = (number *)malloc(sizeof(number));
    n->dec = 0;
    m->dec = 0;
	init(ans);
	init(c);
	init(q);
	init(d);
	if(m->sign == n->sign) {
		q->sign = PLUS;
		m->sign = n->sign = PLUS;
	}
	else {
		q->sign = MINUS;
		m->sign = n->sign = PLUS;
	}
	node *p = m->head;
	char ch = p->num + '0';
	appendRight(d, ch);
	while(q->dec < SCALE+pre){
		while(i >= 0){
			appendleft(c, i);
			pro = mult(n, c);
			ans = sub(d, pro);
			if(ans->sign != MINUS) {
				appendRight(q, i + '0');
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				break;
			}
			else{
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				i--;
			}
		}
		d = ans;
		if(p->next != NULL) {
			p = p->next;
			ch = p->num + '0';
			appendRight(d, ch);
		}
		else{
			q->dec++;
			appendRight(d, '0');
		}
		i = 9;
		node *tmp = c->head;
		free(tmp);
		c->head = c->tail = NULL;
	}
	q->dec--;
    return q;
}
number *division(number *m, number *n){
	if(isZero(*n) == 1) {
		printf("Dividing by Zero is not allowed.\n");
		return NULL;
	}
	removeZeros(m);
	removeZeros(n);

	int numerator = n->dec;
	int denominator = m->dec;
	int d = numerator-denominator;
	number *q;

	if(d>0){


        q = fun(m,n,d);
        q->dec-= d;
	}
	else{

        q = fun(m,n,d);
        d = d*(-1);
        q->dec = q->dec + d;
	}

	roundoff(q);
	return q;
}

//FORMULA :- remainder = a - floor_division(a/b) * b
number *modulus(number *a, number *b) {
	if(isZero(*b) == 1){

        fprintf(stderr,"Can not perform modulo operation with zero\n");
        return NULL;
	}
	if(isInteger(a) == 0 || isInteger(b) == 0){

        fprintf(stderr,"Can not perform modulo operation on float values\n");
        return NULL;
	}
	number *ans;
	ans = (number*)(malloc(sizeof(number)));
	number *copyA, *copyB;
	copyA = (number*)(malloc(sizeof(number)));
	copyB = (number*)(malloc(sizeof(number)));
    init(copyA);
    init(copyB);
    copy(a,copyA);
    copy(b,copyB);
    copyA->sign = PLUS;
    copyB->sign = PLUS;
	init(ans);
	int ansSign ;
	if(a->sign == PLUS){

        a->sign = b->sign = PLUS;
        ansSign = PLUS;
	}
	else{

        a->sign = b->sign = PLUS;
        ansSign = MINUS;
	}
	decimalEqual(a,b);
	ans = division(a,b);
	while(ans->dec !=0 ){

        ans->tail = ans->tail->prev;
        ans->dec--;
	}
	ans->tail->next = NULL;
	ans = mult(ans,copyB);
	ans = sub(copyA,ans);
	ans->sign = ansSign;
	
	return ans;
}

