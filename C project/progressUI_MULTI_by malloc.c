#include<stdio.h>



typedef struct {
    int id;
    int progress;
    int step;
} Task ;

void print_task();
int main()
{
    int *ptr= (Task *)malloc(sizeof(Task));

    
    return 0;
}

void print_task(Task *t1)
{
    printf(" Task  %d [", t1->id);
    
    printf("] %d%%\n", t1->progress);
}
