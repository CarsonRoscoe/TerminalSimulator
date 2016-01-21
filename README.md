# TerminalSimulator

Created as a basic C assignment with the intention of learning how to use forks, pipes and signals.

From the assignment description, the objective was "to use fork, pipe and signals in a program that reads and processes characters entered on a terminal keyboard". 

To accomplish this, students disable all input processing in the terminal and must adhere to the following constraints:  
* typing 'E' will send the input to the other process to be interpreted
* typing 'T' will quit the program typing 'K'will remove all characters preceding it 
* typing 'X' will remove the previous character 
* all 'a' characters will be replaced with 'z' characters in the output.

Neglecting to re-enable terminal processing when the program exits is a bad idea.
