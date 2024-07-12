## Pipex

Pipex is a project that simulates the behavior of the shell pipe (`|`) in a Unix-like operating system. This project demonstrates the use of multiple processes and inter-process communication through pipes. The goal is to take command-line arguments and use them to execute shell commands with input/output redirection.

## Project Overview

In this project, we aim to execute two commands with input and output redirection using two child processes and a parent process. The input is read from a file, passed through the first command, then through the second command, and finally written to an output file.

### Execution Flow

1. **Initialization and Input Validation**:
   - The program starts by validating the number of input arguments.
   - It checks the validity and permissions of the input file and output file.

2. **Pipe Creation**:
   - A pipe is created to facilitate communication between the child processes.

3. **Child Processes**:
   - The first child process reads from the input file and writes its output to the pipe.
   - The second child process reads from the pipe and writes its output to the output file.

4. **Parent Process**:
   - The parent process waits for the child processes to complete and handles any errors that occur during execution.

### Detailed Steps

1. **First Child Process (child1_process)**:
   - Checks the existence and readability of the input file.
   - Opens the input file for reading.
   - Duplicates the pipe's write end to the standard output (stdout).
   - Duplicates the input file descriptor to the standard input (stdin).
   - Closes unnecessary file descriptors.
   - Executes the first command using the environment path.

2. **Second Child Process (child2_process)**:
   - Opens the output file for writing.
   - Duplicates the pipe's read end to the standard input (stdin).
   - Duplicates the output file descriptor to the standard output (stdout).
   - Closes unnecessary file descriptors.
   - Executes the second command using the environment path.

3. **Parent Process (parent_process)**:
   - Waits for the child processes to complete.
   - Ensures proper closure of file descriptors.

### Functions Used

1. **File Descriptor and Pipe Management**:
   - `ft_putchar_fd`: Writes a character to a given file descriptor.
   - `ft_strdup`: Duplicates a string.
   - `ft_memcpy`: Copies memory from source to destination.
   - `parse_path`: Parses the PATH environment variable to find executable commands.
   - `execute_command`: Finds and executes a command using the parsed PATH.

2. **Error Handling**:
   - `error`: Prints an error message to stderr and exits the program.

3. **Child and Parent Process Management**:
   - `child1_process`: Handles the operations for the first child process.
   - `child2_process`: Handles the operations for the second child process.
   - `parent_process`: Handles the operations for the parent process.

### Compilation and Execution

To compile and run the `pipex` program, follow these steps:

1. Clone this repository to your local machine.
2. Compile the program using a C compiler, such as GCC. You can use the following command:

    ```bash
    gcc -o pipex pipex.c
    ```

3. Run the program with the required arguments:

    ```bash
    ./pipex infile "cmd1" "cmd2" outfile
    ```

The program will read from `infile`, execute `cmd1` and `cmd2`, and write the result to `outfile`.

### OR simply on your terminal run(cmd1 and cmd2 with commands of your choice):

'git clone https://github.com/tuoreste/pipex.git && cd pipex && make && ./pipex infile "cmd1" "cmd2" outfile'

## Example

Here is an example of how the program works:

```bash
$ ./pipex input.txt "grep 'hello'" "wc -l" output.txt
