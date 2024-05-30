## Overview:
A function that returns a line read from a file descriptor. 

---

## Compiling: 

1. `make` creates the executable named "pipex" 

2. `make clean` removes object files
   
3. `make fclean` removes object files and the executable
   
4. `make re` calls `fclean` followed by `all`

5. `make bonus` compiles bonus part where multiple commands can be used

---

## Usage:

Simple:
```
./pipex [infile] [command1] [command2] [outfile]
```

Bonus:
```
./pipex [infile] [command_1] [command_2] ... [command_n] [outfile]
```

## Example:

Simple:
`./pipex infile "ls -l" "wc -l" outfile` should behave like `< infile ls -l | wc -l > outfile`

Bonus:
`./pipex infile cmd_1 cmd_2 ... cmd_n outfile` should behave like `< infile cmd_1 | cmd_2 | ... | cmd_n > outfile`

### Parameters:

infile: file that is redirected to STDIN (input of the program)

outfile: file that is redirected to STDOUT (output of the program)

command_1/ command_2 /... / command_n: bash commands
