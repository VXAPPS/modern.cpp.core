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
- **CPU** - Get CPU informations.
- **Double** - Less, Greater, Equal, Between, Round.
- **Exec** - Run command and return stdout.
- **Serial** - Serial communication class.
- **Timing** - Measering time, cpu and real time.

## Template classes
- **CSVWriter** - Write out comma seperated values.
- **Timer** - Timeout thread on time or interval.

## Unixservice class
- Main function to run as a unix daemon.
