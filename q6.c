/*Design a Real-Time Event Attendance Counter where an event venue wants to dynamically
track attendance at different entry gates. Write a program to allocate an array storing
headcounts at each gate, add more gates using realloc. Find: Total attendees recursively, gate
with highest attendance. Save all data to attendance.txt file with timestamps.*/

#include<stdio.h>
#include<stdlib.h>
void recur(int **gates,int *a)
{
    printf("\n Press 1 if you want to add more :");
    int t;
    scanf("%d",&t);
    if(t!=1) return;
    else
    {
    (*a)++;
    int *temp=realloc(*gates,*a*sizeof(int));
    if(temp==NULL)
    {
        free(*gates);
        exit(1);
    }
    else *gates=temp;
    printf("\n  Enter Attendees for gate %d:",*a);
    scanf("%d",&(*gates)[*a-1]);
    return recur(gates,a);
}
}
int total(int *gates,int count,int index,int total1)
{
    if(index>=count)return 0;
    else
  return gates[index]+ total(gates, count, index+1, total1);

}
int atten(int *gates,int count)
{   
    int g;
    int max=gates[0];
    for(int i=1;i<count;i++)
    {
        if(max<gates[i])
        {
            max=gates[i];
            g=i;

        }
    }
    return g;
}
int main()
{
    int a=2;
    int *gates=malloc(a*sizeof(int));
    if(gates==NULL)
    {
        exit(1);
    }
    for(int i=0;i<a;i++)
    {
        printf("\n Enter Attendees for gate %d:",i+1);
        scanf("%d",&gates[i]);
    }
    recur(&gates,&a);
    int q=total(gates,a,0,0);
    printf("\n Total is :%d",q);
    int high=atten(gates,a);
    printf("\n The gate with the highest Attendees is:%d",high+1);
    FILE *fp = fopen("attendance.txt","a");
    if(fp == NULL)
    {
        printf("\n Error opening file!");
        return 1;
    }
     time_t now = time(NULL);
    char *t = ctime(&now);
     for(int i=0;i<a;i++)
    {
        fprintf(fp,"Gate %d : %d attendees\n", i+1, gates[i]);
    }
    
    fprintf(fp,"Total attendees: %d\n", q);
    fprintf(fp,"Gate with highest attendance: %d\n", high+1);
    fprintf(fp,"----------------------------------------------------\n");

    fclose(fp);
    free(gates);
    return 0;
     


}