.intel_syntax noprefix   # Set assembly syntax to Intel style with no prefix for registers

.global write            # Declare the write function as a global symbol (accessible from outside)
.global read             # Declare the read function as a global symbol (accessible from outside)
.global fork             # Declare the fork function as a global symbol (accessible from outside)
.global execve           # Declare the execve function as a global symbol (accessible from outside)
.global real_waitid      # Declare the real_waitid function as a global symbol (accessible from outside)
.global _exit            # Declare the _exit function as a global symbol (accessible from outside)
.global open             # Declare the open function as a global symbol (accessible from outside)
.global _mkdir            # Declare the mkdir function as a global symbol (accessible from outside)

# Function to perform a write system call
write:
    mov rax, 1           # Set rax to 1, which is the syscall number for write
    syscall              # Make the syscall (write operation)
    ret                  # Return from the function

# Function to perform an open system call
open:
    mov rax, 2           # Set rax to 2, which is the syscall number for open
    syscall              # Make the syscall (open file or directory)
    ret                  # Return from the function

# Function to perform a read system call
read:
    mov rax, 0           # Set rax to 0, which is the syscall number for read
    syscall              # Make the syscall (read operation)
    ret                  # Return from the function

# Function to perform an execve system call
execve:
    mov rax, 59          # Set rax to 59, which is the syscall number for execve (execute program)
    syscall              # Make the syscall (execute a program)
    ret                  # Return from the function

# Function to perform a mkdir system call
_mkdir:
    mov rax, 83          # Set rax to 83, which is the syscall number for mkdir (make directory)
    syscall              # Make the syscall (create directory)
    ret                  # Return from the function

# Function to perform a fork system call
fork:
    mov rax, 57          # Set rax to 57, which is the syscall number for fork (create a new process)
    syscall              # Make the syscall (fork the process)
    ret                  # Return from the function

# Function to perform a waitid system call (with real_waitid function)
real_waitid:
    mov rax, 247         # Set rax to 247, which is the syscall number for waitid (wait for process state change)
    mov r10, rcx         # Move the value of rcx into r10 (set the arguments for waitid)
    syscall              # Make the syscall (wait for process state change)
    ret                  # Return from the function

# Function to perform an exit system call
_exit:
    mov rax, 60          # Set rax to 60, which is the syscall number for exit (terminate process)
    syscall              # Make the syscall (exit the process)
