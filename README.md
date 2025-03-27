# DynArray - A Dynamic Array Library for C

## Overview

DynArray is a simple yet powerful dynamic array implementation for the C programming language. It provides automatic resizing, type-agnostic storage (via `void*`), and basic memory management for arrays that need to grow dynamically at runtime.

## Features

- **Automatic resizing**: The array doubles in capacity when full
- **Memory safety**: Includes proper error checking and NULL handling
- **Type flexibility**: Stores any pointer type using `void*`
- **Simple API**: Easy-to-use functions for common operations
- **Memory management**: Handles cleanup of both the array structure and stored elements

## Why Use DynArray?

- **Performance**: More efficient than linked lists for random access
- **Convenience**: Saves you from rewriting dynamic array logic for every project
- **Safety**: Built-in error checking prevents common memory issues
- **Portability**: Pure C implementation works across platforms

## Example Usage

Here's a comprehensive example demonstrating the library's capabilities:

```c
#include "dynarray.h"
#include <stdio.h>
#include <string.h>

// A simple structure to store in our array
typedef struct {
    int id;
    char name[50];
} Person;

int main() {
    DynArray people;
    
    // Initialize the array with capacity for 2 elements
    DYNARR_create(&people, 2);
    
    // Create and add some people to the array
    for (int i = 0; i < 5; i++) {
        // Allocate memory for each person
        Person *p = malloc(sizeof(Person));
        if (!p) {
            perror("Failed to allocate person");
            return EXIT_FAILURE;
        }
        
        p->id = i;
        snprintf(p->name, sizeof(p->name), "Person %d", i);
        
        // The array will automatically resize when needed
        DYNARR_push(&people, p);
        
        printf("Added %s (array size: %zu, capacity: %zu)\n", 
               p->name, people.size, people.capacity);
    }
    
    // Access elements by index
    Person *third = DYNARR_fetch(&people, 2);
    if (third) {
        printf("\nThird person: %s (ID: %d)\n", third->name, third->id);
    }
    
    // Remove an element from the middle
    printf("\nRemoving element at index 1...\n");
    DYNARR_delete(&people, 1);
    
    // Print all remaining people
    printf("\nRemaining people:\n");
    for (size_t i = 0; i < people.size; i++) {
        Person *p = DYNARR_fetch(&people, i);
        printf("- %s (ID: %d)\n", p->name, p->id);
    }
    
    // Clean up all allocated memory
    DYNARR_free(&people);
    
    return 0;
}
```

## Advanced Example: Storing Different Types

DynArray can store any pointer type. Here's an example with mixed data:

```c
#include "dynarray.h"
#include <stdio.h>

int main() {
    DynArray mixedData;
    DYNARR_create(&mixedData, 4);
    
    // Store an integer (allocated on heap)
    int *num = malloc(sizeof(int));
    *num = 42;
    DYNARR_push(&mixedData, num);
    
    // Store a string
    char *str = strdup("Hello, Dynamic Array!");
    DYNARR_push(&mixedData, str);
    
    // Store a structure
    typedef struct { double x, y; } Point;
    Point *p = malloc(sizeof(Point));
    p->x = 3.14; p->y = 2.71;
    DYNARR_push(&mixedData, p);
    
    // Retrieve and use the elements
    printf("Integer: %d\n", *(int*)DYNARR_fetch(&mixedData, 0));
    printf("String: %s\n", (char*)DYNARR_fetch(&mixedData, 1));
    Point *retrieved = DYNARR_fetch(&mixedData, 2);
    printf("Point: (%.2f, %.2f)\n", retrieved->x, retrieved->y);
    
    // Clean up
    DYNARR_free(&mixedData);
    
    return 0;
}
```

## Performance Characteristics

- **Push operations**: Amortized O(1) time complexity
- **Fetch operations**: O(1) time complexity
- **Delete operations**: O(n) time complexity (due to element shifting)
- **Memory overhead**: Minimal - just the array structure and pointer storage

## Best Practices

1. Always check return values from `DYNARR_fetch`
2. Initialize with a reasonable initial capacity to minimize reallocations
3. Use `DYNARR_free` when done to prevent memory leaks
4. Store only heap-allocated pointers (the array will free them for you)

## Limitations

- Not thread-safe (for multithreaded use, add synchronization)
- Delete operations can be expensive for large arrays
- Stores only pointers (not direct values)

## Contributing

Contributions are welcome! Open issues or pull requests for:
- Bug fixes
- Performance improvements
- Additional features (like sorting or searching)
