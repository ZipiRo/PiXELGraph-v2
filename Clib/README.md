# Incremental C++ Static Library Builder

This is a simple C++ program that performs **incremental compilation** of `.cpp` files in a source directory and builds a static library (`.a`). It only recompiles files that have changed since the last build, reducing unnecessary compilation time. This was made by me in batch file then give to AI to implement it in C++. The AI made the implemetation and the if changed file creation.

---

## Features

- **Incremental compilation**: Only compiles `.cpp` files whose content has changed.  
- **Incremental static library creation**: Only updates `.o` files that changed in the library.  
- Tracks **file sizes and object timestamps** using `.last_sizes.txt`.  
- **Excludes `main.cpp`** from compilation.  
- **Colored output** for compilation progress, success, and errors.  
- Stops immediately if a compilation or library creation fails.  

---

## Requirements

- **C++17 compiler** (`g++` recommended)  
- **`ar` tool** for creating static libraries (comes with GCC/MinGW on Windows or Linux).  
- **ANSI-compatible terminal** for colored output (Windows 10+ terminal or Linux/macOS).  

---

## Usage

```bash
./build_incremental <source_dir> <include_dir> <output_dir> <static_lib_name>
