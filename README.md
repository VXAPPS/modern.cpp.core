# modern.cpp.core
Modern C++ core classes for specific functions in most native and modern C++17.

## Build
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug|Release ../modern.cpp.core
make -j`nproc`
```

## Classes
- **CPUID** - Get CPUID.
- **Double** - Less, Greater, Equal, Round.
- **Serial** - Serial communication class.
- **Timing** - Measering time, cpu and real time.

## Template classes
- **CSVWriter** - write out comma seperated values.
- **Timer** - timeout thread one time or interval.

## Unixservice class
- Main function to run as a unix daemon.
