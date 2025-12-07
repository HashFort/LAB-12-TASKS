#include <stdio.h>
#include <stdlib.h>
void recu(float **temps, int *count)
{
    printf("\nDo you want to add another reading? (1 = yes): ");
    int q;
    scanf("%d", &q);
    if (q == 0) return;

    float *dd;
    dd = realloc(*temps, (*count + 1) * sizeof(float));
    if (!dd) {
        free(*temps);
        printf("Memory allocation failed!\n");
        exit(1);
    }
    else *temps=dd;

    printf("Enter temperature for reading %d: ", *count + 1);
    scanf("%f", &(*temps)[*count]);

    (*count)++;

    recu(temps, count);
}


int max_(float *temps, int count)
{
    float max = temps[0];
    int k = 0;
    for (int i = 1; i < count; i++)
        if (temps[i] > max) {
            max = temps[i];
            k = i;
        }
    return k;
}


int min_(float *temps, int count)
{
    float min = temps[0];
    int k = 0;
    for (int i = 1; i < count; i++)
        if (temps[i] < min) {
            min = temps[i];
            k = i;
        }
    return k;
}


int threshold1(float *temps, int count, float threshold)
{
    int c = 0;
    for (int i = 0; i < count; i++)
        if (temps[i] > threshold) c++;
    return c;
}

int main()
{
     float threshold;
    int count = 3;
    float *temps = malloc(count * sizeof(float));
    if (temps == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        printf("Enter temperature for reading %d: ", i + 1);
        scanf("%f", &temps[i]);
    }
    recu(&temps, &count);

     FILE *fp = fopen("temperature_summary.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        free(temps);
        return 1;
    }

    int max1= max_(temps, count);
    int min1 = min_(temps, count);

    printf("\nHighest temperature: %.2f at reading %d", temps[max1], max1 + 1);
    printf("\nLowest temperature: %.2f at reading %d", temps[min1], min1 + 1);

   
   
    printf("\nEnter alert threshold temperature: ");
    scanf("%f", &threshold);
    int alert =threshold1(temps, count, threshold);
    printf("Number of readings above threshold: %d\n", alert);

    fprintf(fp, "Temperature Readings:\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "Reading %d: %.2f\n", i + 1, temps[i]);
    }   

    fprintf(fp, "\nHighest temperature: %.2f (Reading %d)\n", temps[max1], max1 + 1);
    fprintf(fp, "Lowest temperature: %.2f (Reading %d)\n", temps[min1], min1 + 1);
    fprintf(fp, "Number of readings above threshold %.2f: %d\n", threshold, alert);

    fclose(fp);

    free(temps);
    return 0;
}
