/*Design a Digital Library Checkout Logger where a librarian wants to track book checkouts for
the day. Write a program to dynamically allocate an array for book checkout logs. Each record:
bookTitle, memberID, checkoutTime, returnDueDays, automatically compute due
dates and append data to a file in CSV format.*/
#include<stdio.h>
#include <stdlib.h>
struct lib{
    char bookTitle[100];
    char memberID[100];
     int checkoutTime;
     int returnDueDays;
};
void recu(struct lib **a, int *am)
{
    printf("\n Press 1 if you want to add more :");
    int t;
    scanf("%d",&t);
    if(t!=1) return;
    else
    {
        while(getchar()!='\n');
        (*am)++;
        *a=realloc(*a,*am*sizeof(struct lib));
        printf("\n Checkout Number %d",*am);
        printf("\n Name:");
        fgets((*a)[*am-1].bookTitle,100,stdin);
        printf("\n Member ID:");
        fgets((*a)[*am-1].memberID,100,stdin);
        printf("\n checkout date:");
        scanf("%d",&(*a)[*am-1].checkoutTime);
        printf("\n How many days:");
        scanf("%d",&(*a)[*am-1].returnDueDays);
    }
    recu(a,am);
}
int time(struct lib *a,int count,int num)
{
     if(a[num].checkoutTime>30) 
     a[num].checkoutTime=2;
   else if(count>a[num].returnDueDays) 
   return a[num].checkoutTime;
    else
    {
        a[num].checkoutTime++;
      
    }
     return time(a,count+1,num);
}
int main()
{
    
    int cap=2,i=0,b=0,x;

    struct lib*a;
    a=malloc(cap*sizeof(struct lib));
    for(int i=0;i<cap;i++)
    {
        printf("\n Checkout Number %d",i+1);
        printf("\n Name:");
        fgets(a[i].bookTitle,100,stdin);
        printf("\n Member ID:");
        fgets(a[i].memberID,100,stdin);
        printf("\n checkout date:");
        scanf("%d",&a[i].checkoutTime);
        printf("\n How many days:");
        scanf("%d",&a[i].returnDueDays);
        while(getchar()!='\n');
    }
   recu(&a,&cap);
   int f[cap];
do
{
   x=time(a,1,i);
   printf("\n The due date of book %d is:%d",i+1,x);
   f[i]=x;
   i++;
}while(i<cap);

        FILE *pq=fopen("data.txt","w");
        printf("\n");
        for(int i=0;i<cap;i++)
        {
            fprintf(pq,"\nName:%s",a[i].bookTitle);
            fprintf(pq,"\nMemberId:%s",a[i].memberID);
             fprintf(pq,"\nCheckoutDate:%d",a[i].checkoutTime);
             fprintf(pq,"\nReturndays:%d",a[i].returnDueDays);
              fprintf(pq,"\nDueDate:%d",f[i]);
        }
        fclose(pq);
        free(a);


}