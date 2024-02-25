/*###########################################
#University of Information Technology		#
#IT007 Operating System						#
#Au Truong Giang, 21522019					#
#File:21522019.c							#
###########################################*/

#include <stdio.h>

static int preArray[10];
static int page_fault[100];
static int number_page_fault = 1;

int Is_in_preArray(int page, int value) {
    for (int i = 0; i < page; i++) {
        if (value == preArray[i]) return i;
    }
    return -1;
}

int Farest_Element(int *ref, int pivot, int page) {
    int min = pivot;
    int vt;
    for (int i = 0; i < page; i++) {
        for (int j = pivot - 1; j >= 0; j--) {
            if (preArray[i] == ref[j]) {
                if (j < min) {
                    min = j;
                    vt = i;
                }
                break;
            }
        }
    }
    return vt;
}

int Farest_Element_Oppsite(int *ref, int pivot, int page, int n) {
    int max = pivot;
    int flag[10];
    for (int i = 0; i < page; i++) {
        flag[i] = 0;
    }
    int vt = -1;
    for (int i = 0; i < page; i++) {
        for (int j = pivot + 1; j < n; j++) {
            if (preArray[i] == ref[j]) {
                if (j > max) {
                    max = j;
                    vt = i;
                }
                flag[i] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < page; i++) {
        if (flag[i] == 0) return i;
    }
    return vt;
}

void Print(int total_page[10][100], int n, int page, int ref[100]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", ref[i]);
    }
    printf("\n");
    for (int i = 0; i < page; i++) {
        for (int j = 0; j < n; j++) {
            if (total_page[i][j] != -1) {
                printf("%d ", total_page[i][j]);
            }
            else {
                printf("  ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        if (page_fault[i] == 1) printf("* ");
        else {
            printf("  ");
        }
    }
    printf("\n");
    printf("Number of Page Fault: %d\n", number_page_fault);
}

void FIFO(int ref[], int n, int page)
{
    int IsFault;
    int total_page[10][100];
    int current_page = 0;
    for (int i = 0; i < page; i++) {
        if (i == 0) { total_page[i][0] = ref[0]; }
        else {
            total_page[i][0] = -1;
        }
    }
    page_fault[0] = 1;

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < page; i++) {
            total_page[i][j] = total_page[i][j - 1];
            preArray[i] = total_page[i][j - 1];
        }
        if (Is_in_preArray(page, ref[j]) != -1) {
            page_fault[j] = -1;
        }
        else {
            current_page++;
            if (current_page == page) current_page = 0;
            total_page[current_page][j] = ref[j];
            page_fault[j] = 1;
            number_page_fault++;
        }
    }
    Print(total_page, n, page, ref);
}

void OPT(int ref[], int n, int page)
{
    int IsFault;
    int total_page[10][100];
    int current_page = 0;
    for (int i = 0; i < page; i++) {
        if (i == 0) { total_page[i][0] = ref[0]; }
        else {
            total_page[i][0] = -1;
        }
    }
    page_fault[0] = 1;

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < page; i++) {
            total_page[i][j] = total_page[i][j - 1];
            preArray[i] = total_page[i][j - 1];
        }

        if (Is_in_preArray(page, ref[j]) != -1) {
            page_fault[j] = 0;
        }
        else {
            if (j < page) {
                current_page++;
                total_page[current_page][j] = ref[j];
            }
            else {
                int pivot = Farest_Element(ref, j, page);
                total_page[pivot][j] = ref[j];
            }
            page_fault[j] = 1;
            number_page_fault++;
        }
    }
    Print(total_page, n, page, ref);
}

void LRU(int ref[], int n, int page)
{
    int IsFault;
    int total_page[10][100];
    int current_page = 0;
    for (int i = 0; i < page; i++) {
        if (i == 0) { total_page[i][0] = ref[0]; }
        else {
            total_page[i][0] = 0;
        }
    }
    page_fault[0] = 1;

    for (int j = 1; j < n; j++) {

        for (int i = 0; i < page; i++) {
            total_page[i][j] = total_page[i][j - 1];
            preArray[i] = total_page[i][j - 1];
        }

        if (Is_in_preArray(page, ref[j]) != -1) {
            page_fault[j] = 0;
        }
        else {
            if (j < page) {
                current_page++;
                total_page[current_page][j] = ref[j];
            }
            else {
                int pivot = Farest_Element_Oppsite(ref, j, page, n);
                total_page[pivot][j] = ref[j];
            }
            page_fault[j] = 1;
            number_page_fault++;
        }
    }
    Print(total_page, n, page, ref);
}

int main() {
    int page;
    int temp;
    int ref[11] = { 2, 1, 5, 2, 2, 0, 1, 9, 0, 0, 7 };
    int n = 11;

    printf("--- Page Replacement algorithm ---\n");
    printf("1. Default referenced sequence\n");
    printf("2. Manual input sequence\n");
    scanf("%d", &temp);

    switch (temp) {
        case 1:
            break;
        case 2:
            printf("Enter length of page referene sequence: ");
            scanf("%d", &n);
            printf("Enter the page reference sequence: ");
            for (int i = 0; i < n; i++) {
                scanf("%d", &ref[i]);
            }
    }

    printf("--- Page Replacement algorithm ---\n");
    printf("Input page frames: ");
    scanf("%d", &page);
    printf("1. FIFO algorithm\n");
    printf("2. OPT algorithm\n");
    printf("3. LRU algorithm\n");
    printf("4. All algorithms\n");

    scanf("%d", &temp);
    printf("--- Page Replacement algorithm --- \n");
    switch (temp) {
        case 1:
            FIFO(ref, n, page);
            break;
        case 2:
            OPT(ref, n, page);
            break;
        case 3:
            LRU(ref, n, page);
            break;
        case 4:
            printf("FIFO algorithm: \n");
            FIFO(ref, n, page);
            printf("\n");
            printf("OPT algorithm: \n");
            OPT(ref, n, page);
            printf("\n");
            printf("LRU algorithm: \n");
            LRU(ref, n, page);
            printf("\n");
            break;
    }

    return 0;
}
