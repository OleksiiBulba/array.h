# C Dynamic array.h Library

This C library provides a simple and efficient mechanism for creating and managing dynamic arrays, inspired by the stb libraries and [nob library](https://github.com/tsoding/musializer/blob/master/src/nob.h) by [Tsoding](https://github.com/tsoding/). The library is designed as a header-only library to ease integration into other projects.

## Features

- **Header-only**: No need for separate compilation, just include it in your project.
- **Type Safety**: Generic implementation using macros ensures type safety.
- **Easy to Use**: Simple API for array operations like append and get.
- **Customizable Memory Management**: Defaults to standard memory functions but allows for overriding.
- **Support for Pointer Arrays**: Provides support for arrays of pointers, which can be managed or unmanaged by the library itself.

## Installation

Since the library is header-only, the installation process is straightforward. Simply copy the `array.h` file into your project's include directory or anywhere in your include path.

## Usage

First, include the header file in your source file:
```c
#include "array.h"
```
To use the library, follow these steps:

- Define the array type for your specific item type using `ARRAY_DEFINE(item_type)` or `ARRAY_PTR_DEFINE(item_type)` for pointer arrays.
- Create an array instance and initialize it.
- Append items to the array.
- Access items using the `ARRAY_GET` macro.
- Free the array when it's no longer needed.

### Example

Here's an example of using the dynamic array library with an int type:

```c
#include <stdio.h>

#include "array.h"

ARRAY_DEFINE(int); // Define the array type for integers

int main() {
    ARRAY(int) my_array = {NULL, 0, 0}; // Initialize the array

    // Append items
    array_append(&my_array, 10);
    array_append(&my_array, 20);

    // Access and print items
    printf("Item at index 0: %d\n", ARRAY_GET(&my_array, 0));
    printf("Item at index 1: %d\n", ARRAY_GET(&my_array, 1));

    // Free the array
    array_free(&my_array);

    return 0;
}
```

### Example with Pointers

Here's an example of using the dynamic array library with pointer types:

```c
#include <stdio.h>
#include <stdlib.h>

#include "array.h"

ARRAY_PTR_DEFINE(int); // Define the array type for int pointers

int main() {
    ARRAY_PTR(int) *my_array = array_new(ARRAY_PTR(int)); // Create a new pointer array

    int *item1 = malloc(sizeof(int));
    int *item2 = malloc(sizeof(int));
    *item1 = 10;
    *item2 = 20;

    // Append items
    array_ptr_append(my_array, item1);
    array_ptr_append(my_array, item2);

    // Access and print items
    printf("Item at index 0: %d\n", *ARRAY_PTR_GET(my_array, 0));
    printf("Item at index 1: %d\n", *ARRAY_PTR_GET(my_array, 1));

    // Free the array (items will also be freed since they are managed by the library)
    array_ptr_free(my_array);

    return 0;
}
```

## Customizing Memory Management

By default, the library uses the standard realloc and free functions for memory management. You can customize these by defining `ARRAY_REALLOC` and `ARRAY_FREE` before including array.h.

## License

This project is licensed under the MIT License. You can use it freely in both personal and commercial projects.

For complete license details, refer to the LICENSE file in the array.h project repository.

## Contributing

Contributions to the library are welcome! To contribute, please fork the repository, make your changes, and submit a pull request.

## Contact

For questions and support, please open an issue in the project's GitHub repository.
