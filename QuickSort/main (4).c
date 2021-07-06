#define swap(T, x, y) \
    {                 \
        T tmp = x;    \
        x = y;        \
        y = tmp;      \
    }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct storage {
    char surname[21];
    char name[21];
    char patronymic[21];
    long long phoneNumber;
};

_Bool isLarger(struct storage *a, struct storage *b) {
    int res = (strcmp(a->surname, b->surname));
    if (res > 0) {
        return 1;
    }
    if (res < 0) {
        return 0;
    }
    if (res == 0) {
        res = (strcmp(a->name, b->name));
        if (res > 0) {
            return 1;
        }
        if (res < 0) {
            return 0;
        }
        if (res == 0) {
            res = (strcmp(a->patronymic, b->patronymic));
            if (res > 0) {
                return 1;
            }
            if (res < 0) {
                return 0;
            }
            if (res == 0) {
                res = (a->phoneNumber > b->phoneNumber);
                if (res > 0) {
                    return 1;
                }
                if (res < 0) {
                    return 0;
                }
            }
        }
    }
    return 0;
}

void quickSort(struct storage *arr, int N) {
    if (N > 1) {
        int i = 0, j = N - 1;
        {
            struct storage x = arr[N / 2];
            while (i <= j) {
                while (i <= j && isLarger(&x, &arr[i]))
                    i++;
                while (i <= j && isLarger(&arr[j], &x))
                    j--;
                if (i <= j) {
                    swap(struct storage, arr[i], arr[j]);
                    i++;
                    j--;
                }
            }
        }
        quickSort(arr, j + 1);
        quickSort(arr + i, N - i);
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        printf("Invalid number of arguments\n");
        return 1;
    }
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        printf("Invalid input file name\n");
        return 1;
    }
    struct storage *arr = malloc(sizeof(struct storage));
    if (arr == NULL) {
        printf("No memory allocated\n");
        fclose(fin);
        return 2;
    }
    int n = 0;
    int size = 1;
    char surname[21], name[21], patronymic[21];
    long long phoneNumber;
    while (fscanf(fin, "%s%s%s%lld", surname, name, patronymic, &phoneNumber) != EOF) {
        if (n == size) {
            if (size < 1000000) {
                size *= 2;
            } else {
                size += 100000;
            }
            arr = realloc(arr, size * sizeof(struct storage));
            if (arr == NULL) {
                printf("No memory allocated\n");
                fclose(fin);
                return 2;
            }
        }
        strcpy(arr[n].surname, surname);
        strcpy(arr[n].name, name);
        strcpy(arr[n].patronymic, patronymic);
        arr[n++].phoneNumber = phoneNumber;
    }
    fclose(fin);
    quickSort(arr, n);
    FILE *fout = fopen(argv[2], "w");
    if (fout == NULL) {
        printf("Invalid output file name\n");
        free(arr);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%s ", arr[i].surname);
        fprintf(fout, "%s ", arr[i].name);
        fprintf(fout, "%s ", arr[i].patronymic);
        if (i != n - 1) fprintf(fout, "%lld\n", arr[i].phoneNumber);
        else fprintf(fout, "%lld", arr[i].phoneNumber);
    }
    fclose(fout);
    free(arr);
    return 0;
}