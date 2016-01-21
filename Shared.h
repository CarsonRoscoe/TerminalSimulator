#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

//////Magic Numbers//////
#define PIPESIZE 2		//Array size needed when creating pipes
#define PIPEMAXSIZE 512		//Max buffer size for communicating through our pipe

//////Boolean defines//////
#define BOOL int  		//Stating using BOOL is essentially the same as int
#define FALSE 0	  		//Stating FALSE is equal to zero, since 0 is considered false in statements
#define TRUE 1	  		//Stating TRUE is equal to one, since any number except 0 is considered false in statements

//////Keyboard defines//////
#define BACKSPACE "\b \b"	//Breakspace
#define NEWLINE "\n\r"		//Prints a new line character and then cariage returns the cursor to the start of the line
#define KILLLINEp1 (char)27	//Escape character. If printed with KILLLINEp2, the current line on the terminal is erased.
#define KILLLINEp2 "[2K"	//Second part of KILLLINE. If printed after KILLLINEp1, erases the current line
#define KILLKEY '\xB'		//Control-k character
#define TERMINATEKEY 'T'	//Character invoked when a natural termination is occuring.
#define BACKSPACEKEY 'X'	//Character invoked when the user wants a backspace to take place.
#define ENTERKEY 'E'		//Character invoked when the user wants to send the message to be translated
#define KILLLINEKEY 'K'		//Character invoked when the user wants to kill the line

#endif //SHARED_H
