#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define MAX_KEY_LENGTH 10
#define MAX_VALUE_LENGTH 10
#define MAX_ENTRIES 1000

typedef struct {
    char key[MAX_KEY_LENGTH + 1];
    char value[MAX_VALUE_LENGTH + 1];
} KeyValuePair;

void trim(char* str) {
    int start = 0, end = strlen(str) - 1;

    while (isspace((unsigned char)str[start])) start++;
    while (end >= start && isspace((unsigned char)str[end])) end--;

    if (start > 0) {
        memmove(str, str + start, end - start + 1);
    }

    str[end - start + 1] = '\0';
}
int isValidString(const char* str) {
    if (strlen(str) == 0)
        return 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum((unsigned char)str[i]) && str[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int parseFile(const char* filename, KeyValuePair* pairs, int maxPairs) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: 无法打开文件 %s\n", filename);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL && count < maxPairs) {
        line[strcspn(line, "\n")] = '\0';

        trim(line);

        if (strlen(line) == 0) {
            continue;
        }

        char* colon = strchr(line, ':');
        if (colon == NULL) {
            continue;
        }

        *colon = '\0';
        char* key = line;
        char* value = colon + 1;

        trim(key);
        trim(value);

        if (strlen(key) == 0 || strlen(key) > MAX_KEY_LENGTH ||
            strlen(value) == 0 || strlen(value) > MAX_VALUE_LENGTH) {
            continue;
        }

        if (!isValidString(key) || !isValidString(value)) {
            continue;
        }

        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(pairs[i].key, key) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            snprintf(pairs[count].key, sizeof(pairs[count].key), "%s", key);
            snprintf(pairs[count].value, sizeof(pairs[count].value), "%s", value);
            count++;
        }
    }

    fclose(file);
    return count;
}

const char* findValue(const KeyValuePair* pairs, int count, const char* key) {
    for (int i = 0; i < count; i++) {
        if (strcmp(pairs[i].key, key) == 0) {
            return pairs[i].value;
        }
    }
    return NULL;
}

int main() {
    KeyValuePair pairs[MAX_ENTRIES];
    const char* filename = "data.txt";

    int entryCount = parseFile(filename, pairs, MAX_ENTRIES);

    char input[50];
    while (1) {
        printf("请输入:");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        trim(input);

        if (strcmp(input, "Quit") == 0) {
            printf("程序退出。\n");
            break;
        }

        if (strlen(input) == 0) {
            printf("Error\n");
            continue;
        }

        const char* value = findValue(pairs, entryCount, input);
        if (value != NULL) {
            printf("%s\n", value);
        }
        else {
            printf("Error\n");
        }
    }

    return 0;
}