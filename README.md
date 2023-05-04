# Pipex

## 🗣️ About
---

Pipex is a CS project of School 42. The goal is to write a program in C that emulates the behaviour of two important features of a shell : the redirections and the pipes.

Basically, the programm should works like this : ```$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2```.

The program will modify the standard input to be ```file1``` and the standard output to be ```file2```. Every command will be separated by a pipe like the ```|``` in Bash. In other words, ```cmd1``` will have ```file1``` as input, and will transfer its output to ```cmd2``` via a pipe. The process will repeat until we reach the last command. Then, the output of the last command will be transfered to ```file2```. Don't hesitate to check the links in 'external resources' if you are not familiar with pipes and redirections.

More information can be found in the PDF.

## 💿 Compilation and Execution
---

A Makefile is included on the project. Just write ```make``` to create the executable and objects files.

To execute the program, verify that you have execution rights (the ```chmod``` command can help to change that if needed). Then, write ```$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2``` that should behave like ```< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2``` in Bash.

## 🗑️ Deletion
---

To destroy the executable and the obj files, write ```make fclean```. To destroy the obj files but not the executable, write ```make clean```.

## 🛠️ External Resources
---

Learn what is a pipe in Bash and how to use it : https://linuxhint.com/bash_pipe_tutorial/

What are redirections in Bash : https://linuxhint.com/redirection-operators-bash/

## ✅ Validation of the project
---

The project has been validated with a mark of 115/100 (with bonus completion).
