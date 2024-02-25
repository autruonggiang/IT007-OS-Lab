/*###########################################
#University of Information Technology		#
#IT007 Operating System						#
#Au Truong Giang, 21522019					#
#File:srt.c									#
###########################################*/


#include<stdio.h>

void main() {
    FILE *inputFile, *outputFile;
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    int pn[10];
    int arr[10], bur[10], star[10], finish[10], tat[10], wt[10], rt[10], i, j, n;
    int totwt = 0, tottat = 0;
    float avgwt, avgtat;

    fscanf(inputFile, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(inputFile, "%d%d%d", &pn[i], &arr[i], &bur[i]);
        rt[i] = bur[i];
    }

    int complete = 0, t = 0, min_burst = 9999, shortest = 0, check = 0;

    while (complete != n) {
        for (i = 0; i < n; i++) {
            if ((arr[i] <= t) && (rt[i] < min_burst) && (rt[i] > 0)) {
                min_burst = rt[i];
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        rt[shortest]--;
        min_burst = rt[shortest];
        if (min_burst == 0)
            min_burst = 9999;

        if (rt[shortest] == 0) {
            complete++;
            finish[shortest] = t + 1;
            tat[shortest] = finish[shortest] - arr[shortest];
            wt[shortest] = tat[shortest] - bur[shortest];

            totwt += wt[shortest];
            tottat += tat[shortest];
        }
        t++;
    }

    avgwt = (float) totwt / n;
    avgtat = (float) tottat / n;

    for (i = 0; i < n; i++) {
        fprintf(outputFile, "%d %d %d %d\n", pn[i], arr[i], wt[i], tat[i]);
    }

    fprintf(outputFile, "%.2f\n", avgwt);
    fprintf(outputFile, "%.2f", avgtat);

    fclose(inputFile);
    fclose(outputFile);
}
