#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void **data;
    size_t capacity;
    size_t size;
} DynArray;

void DYNARR_create(DynArray *arr, size_t initial_capacity);

void DYNARR_resize(DynArray *arr);

void DYNARR_push(DynArray *arr, void *data);
void *DYNARR_fetch(DynArray *arr, size_t idx);
void DYNARR_delete(DynArray *arr, size_t idx);

void DYNARR_free(DynArray *arr);

#ifdef __cplusplus
}
#endif
