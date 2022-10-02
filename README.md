# modern.cpp.core
Modern C++ core classes for specific functions in most native and modern C++17 or C++20.

## Build
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=Debug|Release ../modern.cpp.core
make -j`nproc`
```

## Classes
- **CPU** - Get CPU information.
- **Demangle** - demangle, demangleExtrem
- **DoubleUtils** - Less, Greater, Equal, Between, Round, Split.
- **Exec** - Run command and return stdout or mixed (stdout and stderr) and result code.
- **Keyboard** - Check for caps lock state.
- **Serial** - Serial communication class (Not for Windows).
- **StringUtils** - TrimLeft, TrimRight, Trim, StartsWith, EndsWith, Tokenize, Simplified.
- **Timestamp** - ISO 8601 timestamp.
- **Timing** - Measuring time, cpu and real time.

## Template classes
- **Cpp23** - std::to_underlying, std::unreachable.
- **CSVWriter** - Write out comma-separated values.
- **Singleton** - Singleton templace class.
- **SharedQueue** - Queue, which is thread-safe.
- **Timer** - Timeout thread on time or interval.

## Unixservice class
- Main function to run as a unix daemon (Not for Windows).
