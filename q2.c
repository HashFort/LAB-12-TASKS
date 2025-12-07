/*Design a Student Exam Seating System where a university wants to assign exam seat numbers
dynamically. Write a program to dynamically allocate an array of seat assignments. Each seat
contains: studentName, rollNumber, seatNumber. Validate roll numbers using a recursive
function (e.g., check if alphanumeric). Save final seating plan to seating .txt file. Handle
memory reallocation for additional students.*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct seats{
    char studentName[200];
    char rollNumber[200];
    int seatNumber;
};
void recu(struct seats **s,int *initial)
{
    printf("\n Do you want to continue. (press 1 for yes)"); 
    int q;
    scanf("%d",&q);
    if(q==0) return;
    else{
           while(getchar()!='\n');
        (*initial)++;
        *s=realloc(*s,*initial*sizeof(struct seats));
         printf("\nName of %d student:",*initial);
        fgets((*s)[*initial-1].studentName,200,stdin);
        printf("\n Roll Number of %d student:",*initial);
      fgets((*s)[*initial-1].rollNumber,200,stdin);
         printf("\n Seat number of %d student:",*initial);
        scanf("%d",&(*s)[*initial-1].seatNumber);
        recu(s,initial);
    }

}
int roll(struct seats *s,int b,int i)
 {
    if (s[b].rollNumber[i] == '\0') return 1;           
    if (!((s[b].rollNumber[i] >= '0' && s[b].rollNumber[i] <= '9') || 
          (s[b].rollNumber[i] >= 'A' && s[b].rollNumber[i]<= 'Z') || 
          (s[b].rollNumber[i] >= 'a' && s[b].rollNumber[i] <= 'z'))) return 0; 
        return  roll(s,b,i+1) ;         
}

int main()
{
    FILE *pq=fopen("seating.txt","w");
    int initial=3,p=0,b=0,t;
    struct seats *s=malloc(initial*sizeof(struct seats));
     for(int i=0;i<initial;i++)
    {
         printf("\nName of %d student:",i+1);
        fgets(s[i].studentName,200,stdin);
        printf("\n Roll Number of %d student:",i+1);
        fgets(s[i].rollNumber,200,stdin);
         printf("\n Seat number of %d student:",i+1);
        scanf("%d",&s[i].seatNumber);
        while(getchar()!='\n');
    }
    recu(&s,&initial);
     while(getchar()!='\n');

  for(int b = 0; b < initial; b++)
   {
     s[b].rollNumber[strcspn(s[b].rollNumber, "\n")] = '\0';
    int t = roll(s, b, 0);
    while(t == 0) {
        printf("Student %d has invalid roll number. Re-enter: ", b+1);
        fgets(s[b].rollNumber, 200, stdin);
         s[b].rollNumber[strcspn(s[b].rollNumber, "\n")] = '\0';
        t = roll(s, b, 0);
    }
    printf("Student %d roll number is valid.\n", b+1);
}


for(int i=0;i<initial;i++)
{
 fprintf(pq,"\n%s",s[i].rollNumber);
}
fclose(pq);
free(s);
}