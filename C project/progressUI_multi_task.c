#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

 typedef struct  {
    int id;
    int progress;
    int step;
} Task;

const int length=50;

void clear_screen(void);
void print_UI(Task t1);
int main()
{
    unsigned int incomplete_task=1;
    srand(time(NULL));
    Task t1[6];
    while(incomplete_task)
    {
    for (int i = 0; i < 6; i++)
    {
        t1[i].id= i+1;
        t1[i].step=rand() %5 +1;
        if (t1[i].progress < 100)
        {
            t1[i].progress+=t1[i].step;
        }
        else if (t1[i].progress >= 100)
        {   
            incomplete_task=0;
            t1[i].progress=100;
        }  
        print_UI(t1[i]);
        sleep(1);
        // clear_screen();
    } 
    }
    
   printf("All process are completed");
    return 0;
}

void print_UI(Task t1)
{
   
    int indicator= ((t1.progress)*length)/100;
    printf("Task %d [",t1.id);
    for (int i = 0; i < length; i++)
    {
        if(i<indicator)
        {
            printf("-");
        }
        else
        {
            printf(" ");
        }
    }
    
    printf("] %d%%\n",t1.progress);
   }

void clear_screen(void)
{
    #ifdef _Win32
        system("cls");
    #else
        system("clear");
    #endif   
}