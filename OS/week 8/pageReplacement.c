#include <stdio.h>

void FIFO(int pages[], int n, int f) {
    int frames[10], i, j, k = 0, found, faults = 0;

    for(i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            frames[k] = pages[i];
            k = (k + 1) % f;
            faults++;
        }

        printf("%d -> ", pages[i]);
        for(j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int f) {
    int frames[10], time[10];
    int i, j, pos, faults = 0, found;
    int counter = 0, least;

    for(i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\n--- LRU Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found) {
            least = time[0];
            pos = 0;

            for(j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    pos = j;
                    break;
                }

                if(time[j] < least) {
                    least = time[j];
                    pos = j;
                }
            }

            counter++;
            frames[pos] = pages[i];
            time[pos] = counter;
            faults++;
        }

        printf("%d -> ", pages[i]);
        for(j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

void Optimal(int pages[], int n, int f) {
    int frames[10];
    int i, j, k, pos, farthest;
    int faults = 0, found;

    for(i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            int replace = -1;
            farthest = i + 1;

            for(j = 0; j < f; j++) {
                int flag = 0;

                for(k = i + 1; k < n; k++) {
                    if(frames[j] == pages[k]) {
                        if(k > farthest) {
                            farthest = k;
                            replace = j;
                        }
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0) {
                    replace = j;
                    break;
                }
            }

            if(replace == -1)
                replace = 0;

            frames[replace] = pages[i];
            faults++;
        }

        printf("%d -> ", pages[i]);
        for(j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

int main() {
    int pages[50], n, f, i, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\nChoose Algorithm");
    printf("\n1. FIFO");
    printf("\n2. LRU");
    printf("\n3. Optimal");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            FIFO(pages, n, f);
            break;

        case 2:
            LRU(pages, n, f);
            break;

        case 3:
            Optimal(pages, n, f);
            break;

        default:
            printf("Invalid Choice!\n");
    }

    return 0;
}
