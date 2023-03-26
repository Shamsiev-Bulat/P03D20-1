#include "main.h"

#include <math.h>
#include <stdio.h>

#define LEN_MAX 1000

int main() {
    struct symbol task[LEN_MAX];
    struct symbol taskcp[LEN_MAX];
    char ch[5 * LEN_MAX];
    int chlen = 0;
    input(ch, &chlen);
    int tasklen = 0;
    if (chlen != -1) tasklen = strtoarr(ch, chlen, task);
    if (tasklen > 0 && checkbalance(task, tasklen) == 0) {
        int coord[14];
        for (int i = 0; i < tasklen; ++i) {
            taskcp[i] = task[i];
        }
        for (int i = 0; i <= 13; ++i) {
            coord[i] = polish(task, tasklen, i);
            for (int j = 0; j < tasklen; ++j) {
                task[j] = taskcp[j];
            }
            //            printf("%d %d\n", i, coord[i]);
        }
        graph(coord);
        // output(task, tasklen);
    } else {
        printf("n/a");
    }
    return 0;
}

void graph(int(*data)) {
    for (int i = 10; i >= 0; --i) {
        for (int j = 1; j <= 13; ++j) {
            if (i == data[j])
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

int checkbalance(struct symbol *task, int tasklen) {
    int it = 0, flag = 0;
    int brac[tasklen];
    for (int i = 0; i < tasklen && flag == 0; ++i) {
        if (task[i].type == 2 && task[i].value == 2) {
            if (it == 0) {
                flag = 1;
            } else {
                if (brac[it - 1] != 1) {
                    flag = 1;
                } else {
                    brac[it - 1] = 0;
                    it--;
                }
            }
        } else {
            if ((task[i].type == 2 && task[i].value == 1) || (task[i].type == 3)) {
                brac[it] = 1;
                it++;
            }
        }
    }
    if (it != 0) flag = 1;
    for (int i = 1; i < tasklen; ++i) {
        if (task[i - 1].type == 2 && task[i - 1].value == 1 && task[i].type == 2 && task[i].value == 2)
            flag = 1;
    }
    return flag;
}

void input(char *ch, int *chlen) {
    char rd;
    int len = 0;
    while (1) {
        scanf("%c", &rd);
        if (rd == '\n')
            break;
        else {
            ch[len] = rd;
            len++;
        }
    }
    for (int i = 0; i < len; ++i) {
        if (!isnum(ch[i]) && !issym(ch[i]) && !istruealpha(ch[i])) len = -1;
    }
    *chlen = len;
}

int istruealpha(char ch) {
    return (ch == 's' || ch == 'i' || ch == 'n' || ch == 'c' || ch == 'o' || ch == 't' || ch == 'a' ||
            ch == 'g' || ch == 'q' || ch == 'r' || ch == 'l' || ch == 'x');
}

int strtoarr(char *ch, int chlen, struct symbol *task) {
    int curr = 0;
    int it = 0;
    while (curr < chlen && it != -1) {
        if (issym(ch[curr])) {
            task[it].type = 2;
            opercode(&task[it], ch[curr]);
            it++;
            curr++;
        } else {
            if (isnum(ch[curr])) {
                int num = 0;
                for (; curr < chlen && isnum(ch[curr]) == 1; curr++) {
                    num *= 10;
                    num += ch[curr] - 48;
                }
                //                if (task[it - 1].type == 2 && task[it - 1].value == 7 &&
                //                    (it == 1 || (task[it - 2].type != 1))) {
                //                    it--;
                //                    task[it].type = 1;
                //                    task[it].value = num * (-1);
                //                    task[it].priority = 0;
                //                } else {
                task[it].type = 1;
                task[it].value = num;
                task[it].priority = 0;
                it++;
                //                }
            } else {
                if (ch[curr] >= 'a' && ch[curr] <= 'z') {
                    if (ch[curr] == 'x') {
                        task[it].type = 0;
                        task[it].value = 0;
                        task[it].priority = 0;
                        it++;
                        curr++;
                    } else {
                        char trig[5] = {'#', '#', '#', '#', '#'};
                        int trigit = 0;
                        for (; curr < chlen && (ch[curr - 1] != '(' || trig[0] == '#'); curr++) {
                            trig[trigit] = ch[curr];
                            trigit++;
                        }
                        // printf("%c%c%c%c%c\n", trig[0], trig[1], trig[2], trig[3], trig[4]);
                        int k = checktrig(&task[it], trig);
                        if (k > 0) {
                            it++;
                        } else {
                            it = -1;
                        }
                    }
                }
            }
        }
        //        printf("%d %d %d\n", task[it - 1].type, task[it - 1].value, task[it - 1].priority);
    }
    return it;
}

int checktrig(struct symbol *sym, const char *ch) {
    if (ch[0] == 's' && ch[1] == 'i' && ch[2] == 'n' && ch[3] == '(') {
        sym->type = 3;
        sym->value = 1;
        sym->priority = 1;
    }
    if (ch[0] == 'c' && ch[1] == 'o' && ch[2] == 's' && ch[3] == '(') {
        sym->type = 3;
        sym->value = 2;
        sym->priority = 1;
    }
    if (ch[0] == 't' && ch[1] == 'a' && ch[2] == 'n' && ch[3] == '(') {
        sym->type = 3;
        sym->value = 3;
        sym->priority = 1;
    }
    if (ch[0] == 'c' && ch[1] == 't' && ch[2] == 'g' && ch[3] == '(') {
        sym->type = 3;
        sym->value = 4;
        sym->priority = 1;
    }
    if (ch[0] == 's' && ch[1] == 'q' && ch[2] == 'r' && ch[3] == 't' && ch[4] == '(') {
        sym->type = 3;
        sym->value = 5;
        sym->priority = 1;
    }
    if (ch[0] == 'l' && ch[1] == 'n' && ch[2] == '(') {
        sym->type = 3;
        sym->value = 6;
        sym->priority = 1;
    }
    int flag = -1;
    if (sym->type == 3) {
        if (sym->value == 5)
            flag = 5;
        else {
            if (sym->value == 6)
                flag = 3;
            else {
                flag = 4;
            }
        }
    }
    return flag;
}

int isnum(char ch) { return (ch >= '0' && ch <= '9'); }

int issym(char ch) {
    int flag = 0;
    if (ch == '^' || ch == '+' || ch == '*' || ch == '-' || ch == '/' || ch == '(' || ch == ')') flag = 1;
    return flag;
}
void opercode(struct symbol *sym, char ch) {
    sym->value = getoperval(ch);
    sym->priority = getoperprior(ch);
}

int getoperval(char ch) {
    int ans = -1;
    struct oper operations[8] = {{' ', 0, 0}, {'(', 1, 0}, {')', 2, 0}, {'^', 3, 1},
                                 {'*', 4, 2}, {'/', 5, 2}, {'+', 6, 3}, {'-', 7, 3}};
    for (int i = 0; i < 8; ++i) {
        if (ch == operations[i].sym) {
            ans = operations[i].val;
        }
    }
    return ans;
}

int getoperprior(char ch) {
    int ans = -1;
    struct oper operations[8] = {{' ', 0, 0}, {'(', 1, 0}, {')', 2, 0}, {'^', 3, 1},
                                 {'*', 4, 2}, {'/', 5, 2}, {'+', 6, 3}, {'-', 7, 3}};
    for (int i = 0; i < 8; ++i) {
        if (ch == operations[i].sym) {
            ans = operations[i].prior;
        }
    }
    return ans;
}

int polish(struct symbol *task, int tasklen, int x) {
    //    printf("----> x = %d\n", x);
    for (int i = 0; i < tasklen; ++i) {
        //        printf("%d %d %d   ===>   ", task[i].type, task[i].value, task[i].priority);
        if (task[i].type == 0) {
            task[i].type = 1;
            task[i].value = x;
            task[i].priority = -1;
        }
        //        printf("%d %d %d\n", task[i].type, task[i].value, task[i].priority);
    }
    struct symbol arr1[LEN_MAX];
    struct symbol arr2[LEN_MAX];
    int arrlen1 = 0, arrlen2 = 0, j = 0;
    while (j < tasklen) {
        if (task[j].type == 0 || task[j].type == 1) {
            arr1[arrlen1] = task[j];
            ++arrlen1;
            ++j;
        } else {
            if (task[j].type == 3) {
                arr2[arrlen2] = task[j];
                arrlen2++;
            } else {
                if (task[j].type == 2 && task[j].value != 2) {
                    while (arr2[arrlen2 - 1].priority <= task[j].priority && arr2[arrlen2 - 1].value > 2 &&
                           task[j].value > 2) {
                        int oper = arr2[arrlen2 - 1].value;
                        arr1[arrlen1 - 2].value =
                            calculate(arr1[arrlen1 - 1].value, arr1[arrlen1 - 2].value, oper);
                        arrlen1 -= 1;
                        arrlen2--;
                    }
                    arr2[arrlen2] = task[j];
                    ++arrlen2;
                    ++j;
                } else {
                    while (1) {
                        int oper = arr2[arrlen2 - 1].value;
                        arr1[arrlen1 - 2].value =
                            calculate(arr1[arrlen1 - 1].value, arr1[arrlen1 - 2].value, oper);
                        arrlen1 -= 1;
                        arrlen2--;
                        // printf("%d %d\n", arr2[arrlen2].type, arr2[arrlen2].value);
                        if (arr2[arrlen2].type == 3 || (arr2[arrlen2].type == 2 && arr2[arrlen2].value == 1))
                            break;
                    }
                    ++arrlen2;
                    ++j;
                }
            }
        }
        //        printf("stack-1:  ");
        //        for (int i = 0; i < arrlen1; ++i) printf("%d ", arr1[i].value);
        //        printf("\nstack-2:  ");
        //        for (int i = 0; i < arrlen2; ++i) printf("%d ", arr2[i].value);
        //        printf("\n");
    }
    while (arrlen2 > 0) {
        int oper = arr2[arrlen2 - 1].value;
        arr1[arrlen1 - 2].value = calculate(arr1[arrlen1 - 1].value, arr1[arrlen1 - 2].value, oper);
        arrlen1 -= 1;
        arrlen2--;
    }
    //    for (int i = 0; i < arrlen1; ++i) printf("%d ", arr1[i].value);
    //    printf("\n");
    //    for (int i = 0; i < arrlen2; ++i) printf("%d ", arr2[i].value);
    //    printf("\n");
    //    printf("%d", arr1[0].value);
    return arr1[0].value;
}

int calculate(const int num1, const int num2, int oper) {
    //    printf("%d %d %d\n", num1, num2, oper);
    int ans = 0;
    switch (oper) {
        case 3: {
            ans = pow(num1, num2);
            break;
        }
        case 4: {
            ans = num1 * num2;
            break;
        }
        case 5: {
            ans = num1 / num2;
            break;
        }
        case 6: {
            ans = num1 + num2;
            break;
        }
        case 7: {
            ans = num1 - num2;
            break;
        }
    }
    return ans;
}