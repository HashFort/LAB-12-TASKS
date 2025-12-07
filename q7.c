/*Design a Medication Inventory Manager where a pharmacy wants to manage medication
inventory. Write a program to use dynamic arrays to store:
medicineName,quantityAvailable,unitPrice, Let user add/remove medicines by
resizing arrays. Compute: Total inventory value, low-stock alerts and save all the data in
medicine_inventory.txt file on exit.*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct med{
    char medicineName[100];
    int quantityAvailable;
    float unitPrice;
};
void recur(struct med **medi,int *a)
{
    printf("\n Press 1 if you want to add more :");
    int t;
    scanf("%d",&t);
      while(getchar()!='\n');
    if(t!=1) return;
    else
    {
        (*a)++;
        struct med *temp=realloc(*medi,*a*sizeof(struct med));
        if(temp==NULL)
         {
        free(*medi);
        exit(1);
        }
        else *medi=temp;
         printf("\n MEDICINE NO # %d",*a);
        printf("\n Enter name of Medicine:");
        fgets((*medi)[*a-1].medicineName,100,stdin);
         (*medi)[*a - 1].medicineName[strcspn((*medi)[*a - 1].medicineName, "\n")] = '\0';
        printf("\n Quantity of Medicine:");
        scanf("%d",&(*medi)[*a-1].quantityAvailable);
         printf("\n Base Price of Medicine:");
        scanf("%f",&(*medi)[*a-1].unitPrice);
          while(getchar()!='\n');
        return recur(medi,a);

    }
}

int total(struct med *med,int count)
{
    float t=0;
    for(int i=0;i<count;i++)
    {
        t+=med[i].quantityAvailable*med[i].unitPrice;
    }
    return t;
}

void low(struct med *med, int count)
{
    for(int i=0;i<count;i++)
    {
        if(med[i].quantityAvailable<5)
        {
            printf("\n MEDICINE NO# %d",i+1);
            printf("\n LOW STOCKS!");

        }
    }
}
int main()
{
    int a=2,n,quan,choose;
    char str[100];
    struct med *medi=malloc(a*sizeof(struct med));
    if(medi==NULL)
    {
        exit(1);
    }
    for(int i=0;i<a;i++)
    {
        printf("\n MEDICINE NO # %d",i+1);
        printf("\n Enter name of Medicine:");
        fgets(medi[i].medicineName,100,stdin);
         medi[i].medicineName[strcspn(medi[i].medicineName, "\n")] = '\0';
        printf("\n Quantity of Medicine:");
        scanf("%d",&medi[i].quantityAvailable);
         printf("\n Base Price of Medicine:");
        scanf("%f",&medi[i].unitPrice);
         while(getchar()!='\n');

    }
    recur(&medi,&a);
    do
    {

        printf("\n Do you want to add(1) or remove(0) a medicine?");
        scanf("%d",&n);
        while(getchar()!='\n'); 
        switch(n)
        {
            case 1:
             printf("\n Enter the medicine Name you want to add:");
             fgets(str,100,stdin);
             str[strcspn(str,"\n")]='\0';
             for(int i=0;i<a;i++)
             {
                if(strcmp(str,medi[i].medicineName)==0)
                {  
                  
                    printf("\n Enter Quantity to add:");
                    scanf("%d",&quan);
                    medi[i].quantityAvailable+=quan;
                    printf("\nUpdated Quantity:%d",medi[i].quantityAvailable);
                    break;
                }
             }
             break;

             case 0:
           
             printf("\n Enter the medicine Name you want to remove:");
             fgets(str,100,stdin);
             str[strcspn(str,"\n")]='\0';
             for(int i=0;i<a;i++)
             {
                if(strcmp(str,medi[i].medicineName)==0)
                {
                    printf("\n Enter Quantity to remove:");
                    scanf("%d",&quan);
                    if(quan<medi[i].quantityAvailable)
                    {
                    medi[i].quantityAvailable-=quan;
                    printf("\nUpdated Quantity:%d",medi[i].quantityAvailable);
                    }
                    else printf("\n Insuffidient Quantity");
                }
             }
             break;

        }
        printf("\n Do you want to modify more?:(1 for yes) ");
        scanf("%d",&choose);
    } while(choose!=0);

    float t=total(medi,a);
    printf("\n Total is:%f",t);

    low(medi,a); 

    FILE *fp = fopen("medicine_inventory.txt", "w");
if(fp == NULL)
{
    printf("\nError opening file!");
    exit(1);
}

fprintf(fp, "MEDICINE INVENTORY DATA\n");
fprintf(fp, "------------------------\n");
fprintf(fp, "Total Medicines: %d\n\n", a);

for(int i=0;i<a;i++)
{
    fprintf(fp, "Medicine #%d\n", i+1);
    fprintf(fp, "Name: %s\n", medi[i].medicineName);
    fprintf(fp, "Quantity: %d\n", medi[i].quantityAvailable);
    fprintf(fp, "Unit Price: %.2f\n", medi[i].unitPrice);
    fprintf(fp, "---------------------------------\n");
}

fclose(fp);
printf("\n Data saved to medicine_inventory.txt successfully.\n");
free(medi);
   
    
}
