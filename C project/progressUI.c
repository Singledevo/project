#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

 int length=50;
 int id=1, progress;
 
void print(void);

int main()
{
    srand(time(NULL));
    int step=rand() % 3 ;
   for (int i = 0; i < length; i++)
   {
        if (progress>100)
        {
            break;
        }
        
        else if(progress < 100)
        {
        progress = progress+ step;
        }
        print();
        sleep(1);
   }
   
    return 0;
}

void print(void)
{
    printf("Task %d [", id);
    int progress_print =(progress * length)/100;
    for(int i=0; i< length; i++)
    {
        if(i<progress_print)
        {
            printf("-");
        }
        else{
            printf(" ");
        }
    }
    printf("] %d%%\n",progress);
}