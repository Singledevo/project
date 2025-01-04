#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

 int length=50;
 int id=1, progress;
 
void print(void);
void clear_screen(void);
int main()
{
    srand(time(NULL));
    int step=rand() % 3 +1;
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
        clear_screen();
        
   }
    printf("Process Completed\n");
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
            printf("=");
        }
        else{
            printf(" ");
        }
    }
    printf("] %d%%\n",progress);
}
void clear_screen(void)
{
    #ifdef _Win32
        system("cls");
    #else
        system("clear");    
    #endif
}