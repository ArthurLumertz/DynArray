#include "dynarray.h"
#include <stdlib.h>

void DYNARR_create(DynArray *arr, size_t initial_capacity) {
    arr->capacity = initial_capacity;
    arr->size = 0;
    arr->data = malloc(initial_capacity * sizeof(void*));
    if (arr->data == NULL) {
        fprintf(stderr, "ERROR: DYNARR_create(arr, initial_capacity): failed to allocate array pointer\n");
        exit(EXIT_FAILURE);
    }
}

void DYNARR_resize(DynArray *arr) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_resize(arr): arr is NULL\n");
        return;
    }

    arr->capacity *= 2;
    arr->data = realloc(arr->data, arr->capacity * sizeof(void*));
    if (arr->data == NULL) {
        fprintf(stderr, "ERROR: DYNARR_resize(arr): failed to reallocate array pointer\n");
        exit(EXIT_FAILURE);
    }
}

void DYNARR_push(DynArray *arr, void *value) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_push(arr, value): arr is NULL\n");
        return;
    }

    if (arr->size == arr->capacity) {
        DYNARR_resize(arr);
    }
    arr->data[arr->size++] = value;
}

void *DYNARR_fetch(DynArray *arr, size_t idx) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_fetch(arr, idx): arr is NULL\n");
        return NULL;
    }

    if (idx > arr->size - 1) {
        fprintf(stderr, "ERROR: DYNARR_fetch(arr, idx): idx out of bounds (%zu out of %zu)\n", idx, arr->size - 1);
        return NULL;
    }
    return arr->data[idx];
}

void DYNARR_delete(DynArray *arr, size_t idx) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_delete(arr, idx): arr is NULL\n");
        return;
    }

    if (idx > arr->size - 1) {
        fprintf(stderr, "ERROR: DYNARR_delete(arr, idx): idx out of bounds (%zu out of %zu)\n", idx, arr->size - 1);
        return;
    }

    free(arr->data[idx]);

    for (size_t i = idx; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->data[arr->size - 1] = NULL;
    arr->size--;
}

void DYNARR_free(DynArray *arr) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_free(arr): arr is NULL\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < arr->size; i++) {
        free(arr->data[i]);
    }
    
    free(arr->data);
}
