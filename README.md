## Learning more about microcontrollers.

## Conditional Preprocessor Execution

Pass preprocessor definitions dynamically via the Makefile using `CMAKE_CXX_FLAGS`:

```bash
# Single definition
make clean && make run CMAKE_FLAGS='-DCMAKE_CXX_FLAGS="-DFUN"'

# Multiple definitions
make clean && make run CMAKE_FLAGS='-DCMAKE_CXX_FLAGS="-DFUN -DDEBUG -DVERSION=2"'

# With values
make clean && make run CMAKE_FLAGS='-DCMAKE_CXX_FLAGS="-DMAX_SIZE=200"'
```

### Using in Code

```cpp
// Check if defined (no value needed)
#ifdef DEBUG
    std::cout << "Debug mode" << std::endl;
#endif

// Check if NOT defined
#ifndef PRODUCTION
    std::cout << "Not production" << std::endl;
#endif

// Compare values (use #if, not #ifdef)
#if VERSION == 1
    std::cout << "Version 1" << std::endl;
#elif VERSION == 2
    std::cout << "Version 2" << std::endl;
#else
    std::cout << "Unknown version" << std::endl;
#endif

// Check if defined AND has value
#ifdef MAX_SIZE
    int buffer[MAX_SIZE];
#endif
```
