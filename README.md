# 42_minishell
This project is about creating a simple shell. Our own little bash. Team project with Orezek.

## Project description


## Requirements


## Implementation


## How to use
* You have to have readline installed. If not install it with `sudo apt install libreadline-dev`
* Make the minishell with command: `Make`
* Run the program: `./minishell`

## Examples

## How to debug - valgrind
Use this prompt to check for leaks, open fds, etc.:
```
valgrind -s --leak-check=full --show-reachable=yes --error-limit=no --suppressions=minishell.supp --trace-children=yes --track-fds=yes ./minishell
```
- `-s`: same as --show-error-list=yes that shows detected errors list and suppression count at exit
- `--leak-check=full`: shows a full list of memory leaks
- `--show-reachable=yes`: same as `--show-leak-kinds=all` that shows all kinds of memory leaks
- `--error-limit=no`: won't stop showing errors if too many
- `--suppressions=minishell.supp`: suppresses memory leaks from in-built functions (readline and add_history)
- `--trace-children=yes`: checks memory leaks in child process too
- `--track-fds=yes`: tracks open and closed file descriptors

## Contributors
* m-bartos - parser - splitter, expander, heredoc; prompt construction
* orezek - execution, built-ins, signals, environmental variables

## Thanks and kudos
* Appreciate the project discussions with my fellow 42Prague students - loudapet, andreaulicna - Thanks you for your insights!
