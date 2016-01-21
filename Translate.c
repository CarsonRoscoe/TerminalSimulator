#include "Translate.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: translate
--
-- DATE: January 9th, 2016
--
-- REVISIONS: January 9th, 2016: Initial creation.
--	      January 11th, 2016: Added comments & refactored variable names to be cleaner.
--	      January 14th, 2016: Modified to no longer loop while a flag is true. Now exits when the work is done, not when told essentially.
--
-- DESIGNER: Carson Roscoe
--
-- PROGRAMMER: Carson Roscoe
--
-- INTERFACE: void translate(int pipeToOutput[], int pipeToInput[])
--					int pipeToOutput[]: The pipe that will be read by the Output process.
--					int pipeToInput[]: The pipe to read data from which will be sent from the Input process.
--
-- RETURNS: void.
--
-- NOTES:
-- The translate function is used to take input received from the Input process' pipe, translate it into a new message
-- which changes all 'X' characters to back spaces & all 'a' characters into 'z' characters, which will then send this
-- new message over to the Output process' pipe. This function also has the job of handling receiving the 'E' characters
-- (which denotes the end of a message to translate) and the K characters (erasing everything in the current line).
--
-- The function will loop until terminate is set to false, and then exit naturally.
----------------------------------------------------------------------------------------------------------------------*/
void translate(int pipeToOutput[], int pipeToInput[]) {
	//Boolean to denote whether we need to print out a new line character or not on the next iteration.
	BOOL nextline = TRUE;
	
	//backspace used for erasing the last character printed.
	char * backspace = BACKSPACE;
	
	//newline used for handling the newline character and cariage return.
	char * newline = NEWLINE;
	
	//killLine used for erasing all characters printed to the screen and carriage return back to the start.
	char killline[2];
	
	//Variable which will hold the current char being read from the pipe.
	char charRead;

	//Populate the killine variable with a special character that clears the line, as well as cariage return
	sprintf(killline, "%c%s%c", KILLLINEp1, KILLLINEp2, '\r');

	//While we are not terminating the program
	while(TRUE) {
		//If there is data in the pipe to read
		if (read(pipeToInput[0], &charRead, 1) == 1) {
			//If we need to print a new line
			if (nextline) {
				//Handle printing the new line
				write(pipeToOutput[1], newline, 2);
				nextline = FALSE;
			}
			switch(charRead) {
				case BACKSPACEKEY: //If the character in the pipe is a 'X', do a backspace.
					write(pipeToOutput[1], backspace, 3);
					break;
				case ENTERKEY: //If the character in the pipe is an 'E', handle new line.
					write(pipeToOutput[1], newline, 2);
					break;
				case KILLLINEKEY: //If the character in the pipe is a 'K', erase the current line
					write(pipeToOutput[1], killline, 6);
					break;
				case TERMINATEKEY: //If the character in the pipe is 'T', exit the program naturally
					write(pipeToOutput[1], &charRead, 1);
					return;
				case 'a': //If the character in the pipe is an 'a', transform it into a 'z'
					charRead = 'z';
				default: //If it is any other character or an 'a', write it to the output pipe.
					write(pipeToOutput[1], &charRead, 1);
			}
		} else {
			//If there is no data to be read from the pipe, the next time we print we need it to be on a new line,
			//so set nextline to TRUE.
			nextline = TRUE;
		}
	}
}
