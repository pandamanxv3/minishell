# Minishell Project README

## Introduction
Minishell is a challenging C programming project aimed at creating a basic yet functional shell, similar to Bash. It's an educational venture that offers students hands-on experience with system programming, process management, and the implementation of a command-line interface. This project demands a deep understanding of how shells work, including command parsing, environment variable management, and signal handling.

## Project Overview
- **Language**: Implemented entirely in C.
- **Objective**: To build a shell that can interpret and execute commands, manage input/output redirection, and handle signals appropriately.
- **Key Components**:
  - Custom prompt display.
  - Command history functionality.
  - Execution of executables using PATH variable or absolute/relative paths.
  - Signal handling with minimal use of global variables.

## Features
- **Command Parsing**: Handles quotes and interprets environment variables and special characters like `$`.
- **Redirections**: Implements input (`<`), output (`>`), append mode output (`>>`), and heredoc (`<<`) redirections.
- **Pipes**: Ability to create pipelines using the `|` character, where the output of one command serves as input to the next.
- **Built-ins**: Includes built-in commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Signal Handling**: Manages signals such as `CTRL-C`, `CTRL-D`, and `CTRL-\` in interactive mode.
- **Memory Management**: Ensures efficient memory usage, with proper allocation and deallocation practices.

## Technical Specifications
- **Written in C**: Strict adherence to C programming language.
- **Norm Compliance**: Code must follow specific coding standards and guidelines.
- **Makefile**: Submission includes a Makefile with rules: NAME, all, clean, fclean, and re, and must not relink.
- **Libft**: Permitted to use the 'libft' library, which must be included in the project's repository.
- **Error Handling**: Robust error management and proper handling of unexpected behavior.

## Additional Information
- **Testing**: Encouraged to create test programs for self-evaluation and peer review.
- **Submission**: Code must be submitted through the assigned git repository.
- **Reference**: Bash shell is used as a reference for any ambiguities in requirements.

