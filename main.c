#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"istack.h"
#include "functions.h"
#include <limits.h>
#include<time.h>

#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400

typedef struct token{
	int type;
	number *num;
	char op;
}token;
enum state { NUMBER, DOT, OP, FINISH, ERROR, SPC };
token gettoken(char *expr, int *reset) {
	static int i = 0;
	number *a = (number *)malloc(sizeof(number));
	init(a);
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	token t;
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;
	}
	while(1) {
		currchar = expr[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						nextstate = NUMBER;
						appendRight(a, currchar);
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case 'S': case 'C' : case 'T':
						nextstate = OP;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default: // anything else
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case DOT:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						appendRight(a, currchar);
						a->dec++;
						nextstate = DOT;
						currstate = nextstate;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case 'S': case 'C' : case 'T':
						nextstate = OP;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						t.type = OPERATOR;
						t.op = expr[i - 1];
						nextstate = NUMBER;
						currstate = nextstate;
						//i++;
						return t;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case 'S': case 'C' : case 'T':
						nextstate = OP;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						t.type = OPERATOR;
						t.op = expr[i -1];
						currstate = nextstate;
						i++;
						return t;
						break;

					default: // anything else
						nextstate = ERROR;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						//no = currchar - '0';
						appendRight(a, currchar);
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case 'S': case 'C' : case 'T':
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;

					case '.':
						nextstate = DOT;
						i++;
						break;

					default: // anything else
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}

int precedece(char o) {
	switch(o) {
		case 'S':
		case 'C':
		case 'T':
			return -1;
			break;
		case ')' :
			return 0;
			break;
		case '+' :
		case '-' :
			return 1;
			break;
		case '*' :
		case '/' :
			return 2;
			break;
		case '%' :
			return 3;
			break;
		case '(' :
			return 4;
			break;
		default :
			return 5;
			break;
	}
	return 5;
}
number * infix(char *input){

	//initiate stack for number
	istack s1;
	cstack s2;
	initIstack(&s1);
	initCstack(&s2);
	number *a,*b,*z;
	a = (number*)malloc(sizeof(number));
	b = (number*)malloc(sizeof(number));
	z = (number*)malloc(sizeof(number));
	init(a);
	init(b);
	init(z);
	char currOp,prevOp;
	int reset = 1;
	int cntCb = 0;
	int cntOb = 0;

	while(1)
	{
		token t;
		t = gettoken(input,&reset);
		if(t.type == OPERAND)
		{

			istackPush(&s1,t.num);
			//printNumber(*(t.num));
			continue;
		}
		else if(t.type == OPERATOR)
		{
			if(t.op == ')'){

				cntCb++;
			}
			else if(t.op == '('){

				cntOb++;
			}
			if(cntOb < cntCb){
				return NULL;
			}
			if(t.op == '('){
				cstackPush(&s2,t.op);
				continue;

			}
			 currOp = t.op;

			while(!cstackEmpty(s2)  && precedece(cstackTop(s2))>= precedece(currOp)){


				 prevOp = cstackPop(&s2);
				 if(prevOp == '('){

                    cstackPush(&s2,prevOp);
                    break;

                }
				if(!istackEmpty(s1)){

					a = istackPop(&s1);
				}
				else {
					fprintf(stderr, "Less operands\n");
					return NULL;
				}
				if(!istackEmpty(s1)){

					b = istackPop(&s1);

				}
				else{
					fprintf(stderr,"Less operands\n");
					return NULL;
				}
				if(prevOp == '/' || prevOp == '%' ){

					if(isZero(a)){
						fprintf(stderr,"Mathematical error\n");
						return NULL;
					}
				}
				switch(prevOp){

					case '+':

						z = add(a,b);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;
					case '-':
						z = sub(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;

					case '*':
						z = mult(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;

					case '/':
						z = division(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;

                    case '%':
                        z = modulus(b,a);
                        if(z == NULL) return NULL;
                        istackPush(&s1,z);
                        break;

					default :
						return NULL;


				}
			}
			if(currOp == ')'){

				if(cstackTop(s2) == '('){

                    //printf("YES\n");
					char tmp = cstackPop(&s2);
				}
			}
			else{
				cstackPush(&s2,currOp);
			}
		}
		else if(t.type == ERR){

			fprintf(stderr,"Error in expression\n");
			return NULL;
		}
		//change here
		else if(t.type == END){


			if(cntOb == cntCb){

				while(!cstackEmpty(s2)){

					if(!istackEmpty(s1)){

						a = istackPop(&s1);
					}
					else{
						fprintf(stderr,"Less operands\n");
						return NULL;
					}
					if(!istackEmpty(s1)){

						b = istackPop(&s1);
					}
					else{

						fprintf(stderr,"Less operands\n");
						return NULL;
					}
					char ch ;
					ch = cstackPop(&s2);
					switch(ch){

					case '+':
						z = add(a,b);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;
					case '-':
						z = sub(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);

						break;

					case '*':
						z = mult(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;

					case '/':
						z = division(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;

                    case '%':
                        z = modulus(b,a);
                        if(z == NULL) return NULL;
                        istackPush(&s1,z);
                        break;

					default :
						return NULL;

					}




				}
				if(!istackEmpty(s1)){

						z = istackPop(&s1);
						if(istackEmpty(s1)){
                        //

							return z;

						}
						else {

							fprintf(stderr,"Less operators\n");
							return NULL;
						}
					}
					else {

						fprintf(stderr,"Less operands\n");
						return NULL;
					}


			}
			else{

             
				fprintf(stderr,"Error in expression\n");
				return NULL;

			}

		}






	}

}
void modify(char *line) {
	int i;
	for(i = 0; i < strlen(line); i++) {
		if(line[i] == '(') {
			int j = 1;
			while(1) {
				if(line[i + j] == ' ') {
					j++;
				}
				else {
					break;
				}
			}
			if((line[i + j] == '-') || (line[i + j] == '+')) {
				int temp = strlen(line);
				while(temp >= i + j) {
					line[temp + 1] = line[temp];
					temp--;
				}
				line[i + j] = '0';
			}
		}
	}
	/*for(int i=0;i<strlen(line);i++){
        printf("%c",line[i]);
	}*/

}
int readline(char *line, int len) {
	int i;
	char ch;
	i = 0;
	while(i < len - 1) {
		ch = getchar();
		if(ch == '\n') {
			line[i++] = '\0';
			return i - 1;
		}
		else
			line[i++] = ch;
	}
	line[len - 1] = '\0';
	return len - 1;
}
int main(int argc, char *argv[]) {

	number *r;
	char line[2048];
	FILE *fptr;
	fptr = fopen("log.txt","w");
	while(readline(line, 2048)){

        fputs(line,fptr);
        fputs("\n",fptr);
        //opnumber++;
		modify(line);
		//printf("%s\n",line);
		r = infix(line);
		if(r != NULL){

            char output[2001];
            printNumber(*r,output);
            fputs(output,fptr);
            fputs("\n",fptr);
		}


		else{

            fprintf(stderr, "Error in expression\n");
            fputs("Error in expression\n",fptr);
		}

	}
	fclose(fptr);
	return 0;
}
