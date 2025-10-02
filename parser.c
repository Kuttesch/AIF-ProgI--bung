#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int get_file_content(char *filename, char *buffer);
int write_file_content(char *filename, char *buffer);
int parse(char *buffer);
bool check_char(char source, char comp);
bool is_lower(char *character);
void to_upper(char *character);

int main() {
    char *buffer;
    get_file_content((char *){"file.txt"}, buffer);
    parse(buffer);
    write_file_content((char *){"file.txt"}, buffer);
    return 0;
}

int get_file_content(char *filename, char *buffer) {
    FILE *file;
    if ((file = fopen(filename, "r")) != NULL) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        buffer = malloc(size + 1);
        fread(buffer, 1, size, file);
        buffer[-1] = 0x00;

        // !TODO
        fclose(file);
    } else {return -1;}
}

int write_file_content(char *filename, char *buffer) {
    FILE *file;
    if ((file = fopen(filename, "w")) != NULL) {
        fprintf(file, buffer);
        fclose(file);
    }
}

int parse(char *buffer) {
    bool EOL = false;
    while (!EOL) {
        if (check_char(*buffer, 0x00)) {
            EOL = true;
            break;
        }
        to_upper(buffer);
        if (!check_char(*buffer, 0x20 /* SPACE */)) {
            buffer++;
        }
    }
    *buffer = 0x00;
}

bool check_char(char source, char comp) {
    return (bool)(source == comp);
}

bool is_lower(char* character) {
    return (bool)(97 < *character && *character < 122);
}

void to_upper(char *character) {
    if (is_lower(character)) {
        *character = *character + 32;
    }
}