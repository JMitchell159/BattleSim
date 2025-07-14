#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "team.h"

void print_team(team_t t) {
    printf("%s\n", t.name);
    char empty[] = "";
    char line1[4 * t.size + 2];
    strcpy(line1, empty);
    strcat(line1, "=");
    for(int i = 0; i < t.size; i++) {
        strcat(line1, "====");
    }
    strcat(line1, "=\n");
    printf("%s", line1);
    char line2[4 * t.size + 2];
    strcpy(line2, empty);
    strcat(line2, "|");
    for(int i = 0; i < t.size; i++) {
        strcat(line2, "\\|/ ");
    }
    strcat(line2, "|\n");
    printf("%s", line2);
    char line3[4 * t.size + 2];
    strcpy(line3, empty);
    strcat(line3, "|");
    for(int i = 0; i < t.size; i++) {
        strcat(line3, "(_) ");
    }
    strcat(line3, "|\n");
    printf("%s", line3);
    char line4[4 * t.size + 2];
    strcpy(line4, empty);
    strcat(line4, "|");
    for(int i = 0; i < t.size; i++) {
        strcat(line4, "\\|/ ");
    }
    strcat(line4, "|\n");
    printf("%s", line4);
    char line5[4 * t.size + 2];
    strcpy(line5, empty);
    strcat(line5, "|");
    for(int i = 0; i < t.size; i++) {
        strcat(line5, "/ \\ ");
    }
    strcat(line5, "|\n");
    printf("%s", line5);
    char line6[4 * t.size + 2];
    strcpy(line6, empty);
    strcat(line6, "=");
    for(int i = 0; i < t.size; i++) {
        strcat(line6, "====");
    }
    strcat(line6, "=\n");
    printf("%s", line6);
}