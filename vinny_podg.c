#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 1000
#define MAX_NAME_LENGTH 50
#define MAX_DATE_LENGTH 20

struct reader{
    char date[MAX_DATE_LENGTH];
    char name[MAX_NAME_LENGTH];
    int count;
};

int main() {
    struct reader entries[1000];
    int num_entries = 0;

    FILE *input_file = fopen("in_podg.txt", "r");

    while (fscanf(input_file, "%s %s %d",
                  entries[num_entries].date,
                  entries[num_entries].name,
                  &entries[num_entries].count) == 3) {
        num_entries++;
    }
    fclose(input_file);

    struct reader lux_entries[1000];
    int num_lux_entries = 0;

    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].count, "Винни-Пух") == 0) {
            strcpy(lux_entries[num_lux_entries].name, entries[i].name);
            lux_entries[num_lux_entries].count = entries[i].count;
            num_lux_entries++;
        }
    }

    for (int i = 0; i < num_lux_entries; i++) {
        for (int j = i + 1; j < num_lux_entries; j++) {
            if (strcmp(lux_entries[i].name, lux_entries[j].name) > 0) {
                struct reader temp = lux_entries[i];
                lux_entries[i] = lux_entries[j];
                lux_entries[j] = temp;
            }
        }
    }

    FILE *output_file = fopen("out.txt", "w");

    fprintf(output_file, "Фамилия\tКолиество\n");
    for (int i = 0; i < num_lux_entries; i++) {
        fprintf(output_file, "%s\t%d\n", lux_entries[i].name, lux_entries[i].count);
    }
    fclose(output_file);

    return 0;
}
