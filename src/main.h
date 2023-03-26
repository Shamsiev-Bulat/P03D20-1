#ifndef MAIN_H
#define MAIN_H

/*
 * type=0=x
 * type=1=number
 * type=2=operation
 * value :
 * 1=( p=0
 * 2=) p=0
 * 3=^ p=1
 * 4=* p=2
 * 5=/ p=2
 * 6=+ p=3
 * 7=- p=3
 * type=3=trigonometry
 * 1=sin(
 * 2=cos(
 * 3=tan(
 * 4=ctg(
 * 5=sqrt(
 * 6=ln(
 * */

struct symbol {
    int type;
    int value;
    int priority;
};

struct oper {
    char sym;
    int val;
    int prior;
};
void graph(int(*data));
int calculate(const int num1, const int num2, int oper);
int polish(struct symbol* task, int tasklen, int x);

int istruealpha(char ch);
int checkbalance(struct symbol* task, int tasklen);
int comp(char* str1, char* str2);
void input(char* ch, int* chlen);
void output(struct symbol* task, int tasklen);
int strtoarr(char* ch, int chlen, struct symbol* task);
int isnum(char ch);
int issym(char ch);
int strln(char* str);
int checktrig(struct symbol* sym, const char* ch);
void opercode(struct symbol* sym, char ch);
int getoperval(char ch);
int getoperprior(char ch);
#endif