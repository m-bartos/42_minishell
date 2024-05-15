# 42_minishell
This project is about creating a simple shell. Our own little bash. Team project with Orezek.

## What kind of features our minishell have?
* displays prompt as a bash - with path to current directory
* working history
* working redirections (`<`, `>`, `>>`), heredoc (`<<`), pipes (`||`)
* execute commands as bash with argumets - `ls`, `cat`, `head`, `git` ...
* launch executables - try launch `./minishell` in `./minishell`
* handle environmental variables
* woking expansion of environmental variables ($)
* working built-ins
* handle CTRL-C, CTRL-D, CTRL-\ like bash
* builtins:
	- `echo` with option `-n`
	- `cd` with only a relative or absolute path
	- `pwd` with no options
	- `export` with no options
	- `unset` with no options
	- `env` with no options or arguments
	- `exit` with no options


## Requirements


* NO BONUS - Cannot handle &&, || and wildcards *
* Cannot handle open quotes or open double quotes
* Cannot handle special characters such as backslash \ or semicolon ;

## Implementation


## How to use
* You have to have readline installed. If not, install it with
```
sudo apt install libreadline-dev
```
* Make the minishell with command
```
Make
```
* Run the program
```
./minishell
```

## Examples

## How to debug - valgrind
Use this prompt to check for leaks, open fds, etc.:
```
valgrind -s --leak-check=full --show-reachable=yes --error-limit=no --suppressions=minishell.supp --trace-children=yes --track-fds=yes ./minishell
```
- `-s` same as --show-error-list=yes that shows detected errors list and suppression count at exit
- `--leak-check=full` shows a full list of memory leaks
- `--show-reachable=yes` same as `--show-leak-kinds=all` that shows all kinds of memory leaks
- `--error-limit=no` won't stop showing errors if too many
- `--suppressions=minishell.supp` suppresses memory leaks from in-built functions (readline and add_history)
- `--trace-children=yes` checks memory leaks in child process too
- `--track-fds=yes` tracks open and closed file descriptors

## Contributors
* [m-bartos](https://github.com/m-bartos) - parser - splitter, expander, heredoc; prompt construction
* [orezek](https://github.com/orezek) - execution, built-ins, signals, environmental variables

## Thanks and kudos
* Thanks [LukasKuhn](https://github.com/LucasKuhn) for the [minishell tester](https://github.com/LucasKuhn/minishell_tester) 
* Appreciate the project discussions with my fellow 42Prague students - [loudapet](https://github.com/loudapet), [andreaulicna](https://github.com/andreaulicna) - Thanks you for your insights!
