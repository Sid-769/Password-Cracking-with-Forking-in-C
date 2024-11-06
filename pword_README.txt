
Password Cracking Program with Optional Forking
===============================================

Overview
--------
This program demonstrates brute-force password cracking with optional process forking. 
The user can enable or disable forking using command-line arguments. 
The program systematically attempts to guess a password by dividing it into segments.

Features
--------
1. **Password Cracking**:
   - Divides the password into four 3-character segments.
   - Uses a brute-force approach to crack each segment.

2. **Optional Forking**:
   - Can operate in either single-process mode or multi-process mode.
   - In multi-process mode, child processes are forked to handle specific segments.

3. **Password Validation**:
   - Uses a helper function `checkPassword()` to validate guessed password segments against a predefined password.

How It Works
------------

- **Single-Process Mode** (default):
  - A single process iterates over all possible combinations of characters to crack each segment.

- **Multi-Process Mode** (enabled with `-f` flag):
  - The parent process spawns child processes using `fork()`.
  - Each child process is responsible for cracking a specific password segment.
  - Once a segment is cracked, the child process exits, and the parent continues.

Compilation and Execution
-------------------------

### Compilation
Use the following command to compile the program:
```bash
gcc assignment-1.c checkPassword.o -o assignment-1
```

### Execution
Run the program with or without the forking option:
- **Single-Process Mode**:
  ```bash
  ./assignment-1
  ```
- **Multi-Process Mode**:
  ```bash
  ./assignment-1 -f
  ```

Example Output
--------------

- **Single-Process Mode**:
  ```
  Process 12345 with parent 6789 cracking the password...
  Process 12345 found segment: ABC
  ```

- **Multi-Process Mode**:
  ```
  Process 12345 with parent 6789 cracking the password...
  Child Process 12346 cracking segment 1: DEF
  ```

Screenshots
-----------

### Process Hierarchy
![Process Diagram](ss parent child code.png)

Purpose
-------
This program provides hands-on experience with:
- **Process creation and management using `fork()`**.
- **Brute-force algorithms for password cracking**.
- **Inter-process communication and validation using external functions**.
