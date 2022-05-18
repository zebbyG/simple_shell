## SHELL PROJECT

## Objectives

#### There are three objectives to this assignment:

- To familiarize ourselves with the Linux programming environment.

- To learn how processes are created, destroyed, and managed.

- To gain exposure to the necessary functionality in shells.

## Overview

- In this assignment, we implemented a command line interpreter or, as it is more commonly known, a shell. The shell should operate in this basic way: when you type in a command (in response to its prompt), the shell creates a child process that executes the command you entered and then prompts for more user input when it has finished.

- The shells we implemented will be similar to, but simpler than, the one you run every day in Unix. You can find out which shell you are running by typing "echo $SHELL" at a prompt. You may then wish to look at the man pages for 'csh' or the shell you are running (more likely tcsh, or bash, or for those few wacky ones in the crowd, zsh or ksh) to learn more about all of the functionality that can be present. For this project, you do not need to implement too much functionality because its just a simple shell.

## Program Specification

## Basic Shell

#### Simple shell 0.1

- Write a UNIX command line interpreter.

	- Usage: simple-shell
	- Your Shell should:

	- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
	- The prompt is displayed again each time a command has been executed.
	- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
	- The command lines are made only of one word. No arguments will be passed to programs.
	- If an executable cannot be found, print an error message and display the prompt again.
	- Handle errors.
	- You have to handle the “end of file” condition (Ctrl+D)
	- You don’t have to:
	- use the PATH
	- implement built-ins
	- handle special characters : `", ', , \, *, &, #`
	- be able to move the cursor
	- handle commands with arguments

#### Simple shell 0.2

- Simple shell 0.1 +

	- Handle command lines with arguments

#### Simple shell 0.3

- Simple shell 0.2 +

	- Handle the PATH
	- fork must not be called if the command doesn’t exist

#### Simple shell 0.4

- Simple shell 0.3 +

	- Implement the exit built-in, that exits the shell
	- Usage: exit
	- You don’t have to handle any argument to the built-in exit
####  Simple shell 1.0

- Simple shell 0.4 +

	- Implement the env built-in, that prints the current environment
#### Simple shell 0.1.1

- Simple shell 0.1 +

	- Write your own getline function
	- Use a buffer to read many chars at once and call the least possible the read system call
	- You will need to use static variables
	- You are not allowed to use getline
- You don’t have to:

	- be able to move the cursor
#### Simple shell 0.2.1

- Simple shell 0.2 +

	- You are not allowed to use strtok
#### Simple shell 0.4.1

- Simple shell 0.4 +

	- handle arguments for the built-in exit
	- Usage: exit status, where status is an integer used to exit the shell
#### `setenv, unsetenv`

- Simple shell 1.0 +

- Implement the setenv and unsetenv builtin commands

`setenv`
	- Initialize a new environment variable, or modify an existing one
	- Command syntax: `setenv` VARIABLE VALUE
	- Should print something on stderr on failure
`unsetenv`
	- Remove an environment variable
	- Command syntax: `unsetenv` VARIABLE
	- Should print something on stderr on failure
#### `cd`
- Simple shell 1.0 +

	- Implement the builtin command `cd`:

	- Changes the current directory of the process.
	- Command syntax: `cd [DIRECTORY]`
	- If no argument is given to cd the command must be interpreted like `cd $HOME`
	- You have to handle the command `cd -`
	- You have to update the environment variable `PWD` when you change directory
	`man chdir`, `man getcwd`
#### Handler of this separator `;`

- Simple shell 1.0 +

	- Handle the commands separator `;`
#### `&& and ||`

- Simple shell 1.0 +

	- Handle the` &&` and `||` shell logical operators
#### `alias`

- Simple shell 1.0 +

	- Implement the alias builtin command
	- Usage: `alias [name[='value'] ...]`
	- alias: Prints a list of all aliases, one per line, in the form name='value'
	- alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
	- alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value
#### `Comments`

- Simple shell 1.0 +

	- Handle comments (`#`)
#### File as input

- Simple shell 1.0 +

	- Usage: simple_shell [filename]
	- Your shell can take a file as a command line argument
	- The file contains all the commands that your shell should run before exiting
	- The file should contain one command per line
	- In this mode, the shell should not print a prompt and should not read from stdin

---
