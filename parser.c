#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int parse(FILE *in, FILE *out);
bool check_char(char source, char comp);
bool is_lower(char *character);
void to_upper(char *character);

int main() {
    FILE *in, *out;
    char filename[256];
    char outname[300];

    printf("Please provide Filename: ");
    scanf("%255s", filename);
    char *dot = strrchr(filename, '.');
    if (dot) {
        size_t len = dot - filename;
        strncpy(outname, filename, len);
        outname[len] = '\0';
        strcat(outname, "_out");
        strcat(outname, dot);
    } else {
        strcpy(outname, filename);
        strcat(outname, "_out.txt");
    }

    if ((in = fopen(filename, "r")) != NULL &&
        (out = fopen(outname, "w")) != NULL) {

        parse(in, out); 

        fclose(in);
        fclose(out);
    } else {
        perror("");
    }
    return 0;
}

int parse(FILE *in, FILE *out) {
    char character;
    bool EOL;
    while ((character = fgetc(in)) && !EOL) {
        if (check_char(character, EOF)) {EOL = true; break;}
        to_upper(&character);
        if (!check_char(character, 0x20 /* SPACE */)) {
            fputc(character, out);
        }
    }
    return 0;
}

bool check_char(char source, char comp) {
    return (source == comp);
}

bool is_lower(char* character) {
    return (*character >= 97 && *character <= 122);
}

void to_upper(char *character) {
    if (is_lower(character)) {
        *character = *character - 32;
    }
}
