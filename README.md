# modern.cpp.core
Modern C++ core classes for specific functions in most native and modern C++23 or C++20 or at least C++17.

## Build
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=Debug|Release ../modern.cpp.core
make -j`nproc`
```

## Classes
- **CPU** - Get CPU information.
- **Demangle** - abi, simple, extreme
- **Exec** - Run command and return stdout or mixed (stdout and stderr) and result code.
- **Keyboard** - Check for caps lock state.
- **Logger** - Log everything, everywhere.
- **Serial** - Serial communication class (Not for Windows).
- **StringUtils** - TrimLeft, TrimRight, Trim, StartsWith, EndsWith, Tokenize, Simplified.
- **Timestamp** - ISO 8601 timestamp.
- **Timing** - Measuring time, cpu and wall time.

## Templates
- **Cpp23** - std::is_scoped_enum, std::to_underlying, std::unreachable.
- **CSVWriter** - Write out comma-separated values.
- **FloatingPoint** - Less, Greater, Equal, Between, Round, Split.
- **SharedQueue** - Queue, which is thread-safe.
- **Singleton** - Singleton template class.
- **Timer** - Timeout thread on time or interval.
- **TypeCheck** - Template variant for typename check.

## Rectangle templates
- **Line** - Line based on two points.
- **Point** - Point from x and y.
- **Rect** - Rectangle template based on Point and Size.
- **Size** - Size from width and height.

## Unix daemon body
- Main function to run as a unix daemon (Not for Windows).
