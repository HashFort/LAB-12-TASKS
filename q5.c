/*Design a Car Rental Duration & Cost Calculator where a car rental service stores rental
durations dynamically. Write a program to dynamically store rental durations (hours or days).
Expand the array whenever a new car is rented, using pointers, compute: Total rental time for
the day, highest rental duration, cost per customer and write invoices to a Rental _Invoices.txt
file.*/
#include <stdio.h>
#include <stdlib.h>
void addHour(int **hour, int *h) {
    (*h)++;
    int *temp = realloc(*hour, (*h) * sizeof(int));
    if (!temp) {
        printf("Memory allocation failed for hours!\n");
        free(*hour);
        exit(1);
    }
    *hour = temp;

    printf("Enter hours: ");
    scanf("%d", &(*hour)[*h - 1]);
}

void addDay(int **days, int *d) {
    (*d)++;
    int *temp = realloc(*days, (*d) * sizeof(int));
    if (!temp) {
        printf("Memory allocation failed for days!\n");
        free(*days);
        exit(1);
    }
    *days = temp;

    printf("Enter days: ");
    scanf("%d", &(*days)[*d - 1]);
}

int totalTime(int *days, int *hours, int daysCount, int hoursCount) {
    int total = 0;
    for (int i = 0; i < daysCount; i++) {
        days[i]*=24;
        total += days[i]; 
    }
    for (int i = 0; i < hoursCount; i++) {
        total += hours[i];
    }
    return total;
}
int max(int *days,int *hour, int dayscount, int hourscount)
{
    
    int max3=days[0];
    for(int i=1;i<dayscount;i++)
    {
        if(max3<days[i])
        {
            max3=days[i];
        }
    }
    int max4=hour[0];
    for(int i=1;i<hourscount;i++)
    {
        if(max4<hour[i])
        {
            max4=hour[i];
        }
    }

    if(max3>max4) return max3;
    else return max4;

}
void writeInvoices(int *days, int *hours, int daysCount, int hoursCount, int cost) {
    FILE *fp = fopen("Rental_Invoices.txt", "w");
    if (!fp) {
        printf("Failed to open file!\n");
        return;
    }

   
    for (int i = 0; i < hoursCount; i++) {
        int totalCost = hours[i] * cost;
        fprintf(fp, "Rental %d: %d hours -> Cost: $%d\n", i + 1, hours[i], totalCost);
    }

   
    for (int i = 0; i < daysCount; i++) {
        int totalHours = days[i] * 24;
        int totalCost = totalHours * cost;
        fprintf(fp, "Rental %d: %d days (%d hours) -> Cost: $%d\n", i + 1 + hoursCount, days[i], totalHours, totalCost);
    }

    fclose(fp);
  
}

int main() {
    int cost=14;
    int h = 0, d = 0;
    int *hour = NULL, *days = NULL;
    int choice;

    do {
        printf("\nDo you want to store duration in Hours(1) or Days(2)? ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addHour(&hour, &h);
                break;
            case 2:
                addDay(&days, &d);
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        printf("Do you want to add another rental? (1 = yes, 0 = no): ");
        scanf("%d", &choice);

    } while (choice == 1);

    int total = totalTime(days, hour, d, h);
    printf("\nTotal rental time for the day: %d hours\n", total);
    int max1=max(days,hour,d,h);

    printf("\n MAX duration is:%d",max1);
    writeInvoices(days,hour,d,h,cost); 



   
    free(hour);
    free(days);

    return 0;
}
