/*Design a Fitness Tracker Data Analyzer where a fitness tracker stores the number of steps
taken every hour. Write a program to dynamically allocate an integer array for hourly step
data, allow user to add more hours (realloc). Use pointer arithmetic to compute: Max steps,
total steps, hours with steps above a threshold and Save data in fitness_tracker.txt file.
*/
#include<stdio.h>
#include<stdlib.h>
void recu(int **steps,int *a)
{
    printf("\n Do you want to continue. (press 1 for yes)"); 
    int q;
    scanf("%d",&q);
    if(q==0) return;
    else{
        (*a)++;
        *steps=realloc(*steps,*a*sizeof(int));
        printf("\n Enter The %d Hour Step:",*a);
        scanf("%d",&(*steps)[*a-1]);
        recu(steps,a);
    }

}


int max(int *steps,int *a)
{
    int max=(steps)[0];
    int k=0,i;
    for(i=1;i<*a;i++)
    {
        if(max<(steps)[i])
        {
            max=(steps)[i];
            k=i;
        }
    }
     
    return k;
}



int total(int *steps,int *a)
{
    int total1=0;
for(int i=0;i<*a;i++)
{
    total1+=(steps)[i];
}
return total1;
}




void thre(int *steps,int *a)
{
    int thres1;
printf("\nEnter threshold: ");
scanf("%d", &thres1);
    for(int i=0;i<*a;i++)
    {
        if((steps)[i]>thres1)
        {
            printf("\n Hour %d has steps above the threshold",i+1);
        }
    }
}

int main()
{
    FILE *ptr=fopen("fitness_tracker.txt","w+");
    int a=3,m1,t1;
    int *steps=malloc(a*sizeof(int));
    for(int i=0;i<a;i++)
    {
         printf("\n Print %d Hourly Steps:",i+1);
        scanf("%d",&steps[i]);
    }
     recu(&steps,&a);
     m1=max(steps,&a);
    printf("\n %d was the max steps made",*(steps+m1));
     t1=total(steps,&a);
    printf("\n The total steps made was: %d",t1);
    thre(steps,&a);

    for(int i=0;i<a;i++)
    {
        fprintf(ptr,"\n %d",steps[i]);
    }
   fclose(ptr);

   for(int i=0;i<a;i++)
   {
    free(steps[i]);
   }
   free(steps);

  
    

}