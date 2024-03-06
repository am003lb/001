// 3_verification.c

#include "3_verification.h"
#include <stdio.h>
#include <string.h>

#define ID_PROFS_FILE "0_ID_Profs.txt"

int verifier_id_prof(const char *idProf) {
    FILE *file = fopen(ID_PROFS_FILE, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;  // File not found or unable to open
    }

    char line[MAX_STRING_SIZE * 5];  // Assuming the maximum line size is 5 times the maximum string size
    while (fgets(line, sizeof(line), file) != NULL) {
        char currentId[MAX_ID_SIZE];
        sscanf(line, "%[^,],", currentId);  // Read the ID from the CSV line

        if (strcmp(idProf, currentId) == 0) {
            fclose(file);
            return 1;  // ID found in the file
        }
    }

    fclose(file);
    return 0;  // ID not found in the file
}