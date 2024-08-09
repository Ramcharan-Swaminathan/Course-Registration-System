#include "all_includes_and_macros.h"


int split_string(char arr[][10], char *str, char *sep) {
    char str_copy[strlen(str) + 1];
    strcpy(str_copy, str);

    char *part = strtok(str_copy, sep);
    int i = 0;
    while (part != NULL) {
        strcpy(arr[i], part);
        part = strtok(NULL, sep);
        i++;
    }
    return i;
}

void list_to_str(char arr[][10], int records, char str[], char *sep) {
    char str_new[9 * records];
    strcpy(str_new, arr[0]);
    for (int i = 1; i < records; i++) {

        strcat(str_new, "|");
        strcat(str_new, arr[i]);

    }
    strcpy(str, str_new);

}


void delete_element_in_array(char arr[][10], int *records, char element[]) {
    int i;
    for (i = 0; i < *records; i++) {
        if (strcmp(arr[i], element) == 0) {
            break;
        }
    }
    for (int j = i; j < *records - 1; j++) {
        strcpy(arr[j], arr[j + 1]);
    }
    *records = *records - 1;
}


void delete_element_in_int_array(int arr[], int *records, int element) {
    int i;
    for (i = 0; i < *records; i++) {
        if (arr[i] == element) {
            break;
        }
    }
    for (int j = i; j < *records - 1; j++) {
        arr[j] = arr[j + 1];
    }
    *records = *records - 1;
}


void add_element_in_array(char arr[][10], int *records, char element[]) {
    strcpy(arr[*records], element);
    *records = *records + 1;
}



