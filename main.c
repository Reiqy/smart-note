#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SMART_NOTE_STR_X(x) #x
#define SMART_NOTE_STR(x) SMART_NOTE_STR_X(x)

#define SMART_NOTE_VERSION_MAJOR 0
#define SMART_NOTE_VERSION_MINOR 0
#define SMART_NOTE_VERSION_PATCH 1
#define SMART_NOTE_VERSION SMART_NOTE_STR(SMART_NOTE_VERSION_MAJOR) "." SMART_NOTE_STR(SMART_NOTE_VERSION_MINOR) "." SMART_NOTE_STR(SMART_NOTE_VERSION_PATCH)

#define SMART_NOTE_SUCCESS 0
#define SMART_NOTE_ERROR 1
#define SMART_NOTE_OUT_OF_MEMORY 2
#define SMART_NOTE_IO_ERROR 3

#define SMART_NOTE_GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define SMART_NOTE_GROW_ARRAY(type, ptr, newSize) \
    (type *) reallocate(ptr, sizeof(type) * (newSize))

#define SMART_NOTE_FREE_ARRAY(type, ptr) \
    (type *) reallocate(ptr, 0)

void *reallocate(void *ptr, size_t newSize) {
    if (newSize == 0) {
        free(ptr);
        return NULL;
    }

    ptr = realloc(ptr, newSize);
    if (ptr == NULL) {
        exit(SMART_NOTE_OUT_OF_MEMORY);
    }

    return ptr;
}

typedef struct {
    size_t count;
    size_t capacity;
    char *data;
} DynamicString;

void initDynamicString(DynamicString *string) {
    string->count = 0;
    string->capacity = 0;
    string->data = NULL;
}

void addDynamicString(DynamicString *string, char character) {
    if (string->count + 2 > string->capacity) {
        size_t oldCapacity = string->capacity;
        string->capacity = SMART_NOTE_GROW_CAPACITY(oldCapacity);
        string->data = SMART_NOTE_GROW_ARRAY(char, string->data, string->capacity);
    }
    string->data[string->count] = character;
    string->data[string->count + 1] = '\0';
    string->count++;
}

void freeDynamicString(DynamicString *string) {
    SMART_NOTE_FREE_ARRAY(char, string->data);
    initDynamicString(string);
}

void getLineDynamicString(DynamicString *string) {
    while(true) {
        int c = fgetc(stdin);
        if (c == EOF) {
            exit(SMART_NOTE_IO_ERROR);
        }
        if (c == '\n') {
            break;
        }
        addDynamicString(string, (char) c);
    }
}

void runInteractive() {
    while (true) {
        printf("> ");

        DynamicString line;
        initDynamicString(&line);
        getLineDynamicString(&line);
        bool isLineEmpty = (line.count == 0);
        freeDynamicString(&line);

        if (isLineEmpty) {
            break;
        }
    }
}

int main() {
    printf("Smart Note %s\n", SMART_NOTE_VERSION);
    runInteractive();
    return 0;
}
