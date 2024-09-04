# UNIX Command Interpreter

A simple UNIX command interpreter built from scratch.

## Overview

This project is a simple UNIX command interpreter, developed to understand systems programming and the workings of a command-line interface (CLI). It was built in collaboration with [Basem1166](#).

## Features

- Basic UNIX command execution such as `ls`, `cd`, `pwd`, `echo`, etc.
- Supports input/output redirection and piping.
- Custom-built command parser and executor.
- Error handling for command execution and input.

## Project Structure

- **`shell.c`**: Contains the main loop for the shell interpreter.
- **`shell.h`**: Header file with definitions and function prototypes used across the program.
- **`execution.c`**: Handles the execution of commands.
- **`shellutil.c`**: Utility functions for managing shell operations.
- **`utilities1.c`**, **`utilities2.c`**: Additional utility functions to support command processing.
- **`hsh`**: Executable file for the interpreter.
- **`TEST_SUITE/`**: Directory containing test cases to validate different functionalities.
- **`.gitignore`**: Specifies files and directories to be ignored by Git.
- **`AUTHORS`**: Contains the names and contact details of the authors.
- **`README.md`**: Documentation file (this file).

## Getting Started

### Prerequisites

To run this interpreter, you will need:

- A UNIX-like operating system (Linux, macOS, etc.)
- A C compiler (such as `gcc`)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/tahaaa22/simple_shell.git
    cd simple_shell
    ```

2. Compile the source code:

    ```bash
    gcc -o hsh shell.c execution.c shellutil.c utilities1.c utilities2.c
    ```

3. Run the interpreter:

    ```bash
    ./hsh
    ```

## Usage

Once you run the interpreter, you can execute UNIX commands directly from the CLI. For example:

```bash
$ ls -l
$ cd /home/user
$ echo "Hello, World!"
$ cat file.txt | grep "search_term"
```

## Design

The interpreter consists of several modules:

- **`shell.c`**: Implements the main loop that reads user input and triggers command processing.
- **`execution.c`**: Contains the logic to execute commands, handle processes, and manage I/O redirection.
- **`shellutil.c`, `utilities1.c`, `utilities2.c`**: Provide various utility functions for parsing commands, handling errors, and other operations.

## Testing

To test the interpreter, run the test scripts available in the `TEST_SUITE/` directory:

```bash
cd TEST_SUITE
./run_tests.sh
```

## Authors

- [Ahmed Taha](https://github.com/tahaaa22)
- [Basem el-galfy](https://github.com/simple_shell)

## Acknowledgments

Thanks to the open-source community for the resources and inspiration.

---
