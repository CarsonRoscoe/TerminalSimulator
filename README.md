# Terminal Simulator

A small C program created with the intention of learning how to use fork, pipes and signals in *nix.

This was built and tested on Fedora, however it should run on any *nix platform.

To accomplish this goal of learning fork/pipes/signals, all input processing in the terminal is disabled at the start of the program and the program was built assuming it must adhere to the following constraints:  
* typing 'E' will send the input to the other process to be interpreted
* typing 'T' will quit the program typing 'K'will remove all characters preceding it 
* typing 'X' will remove the previous character 
* all 'a' characters will be replaced with 'z' characters in the output.

# How To Compile

Clone or download the files onto your *nix system.

Open up terminal, navigate to the directory of the files and then type "make" into the terminal. This should invoke the Makefile which will compile the program.

# Design Document

The design document for the program is the DesignDocument.pdf. That is where you will see state diagrams regarding how the program was planned to be structured, along with pseudocode. The end program did not perfectly match the design, however it is, for the most part, the same as the end structure.

# Testing Document

The testing document for the program is the TestingDocument.pdf. This is where all the test cases were run with test summaries at the top and more detailed test breakdowns (with screenshots) in the pages proceeding the summary.
