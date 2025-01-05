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
    
    srand(time(NULL));
    Task t1[6];

    for (int i = 0; i < 6; i++)
    {
        t1[i].id= i+1;
        t1[i].progress=0;
        t1[i].step=rand() %5 +1;
    }
    int incomplete_task=1;
    while(incomplete_task)
    {
        incomplete_task=0;
        clear_screen();
    for (int i = 0; i < 6; i++)
    {
        
        t1[i].progress+=t1[i].step;
        
        if (t1[i].progress < 100)
        {
            incomplete_task=1;
        }
        else if (t1[i].progress >= 100)
        {   
            t1[i].progress=100;
        }  
        print_UI(t1[i]); 
        
    } 
      
    sleep(1); 
   
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