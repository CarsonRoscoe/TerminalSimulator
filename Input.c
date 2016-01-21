#include "Input.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: input
--
-- DATE: January 9th, 2016
--
-- REVISIONS: January 9th, 2016: Initial creation.
--	      January 11th, 2016: Added comments & refactored variable names to be cleaner.
--	      January 14th, 2016: Removed the children's PID's as a parameter due to kill(0, SIGKILL) functionality
--			making it redundant. Also modified the loop to exit when done instead of rely on a terminate
--			flag to determine when to exit the loop.
--
-- DESIGNER: Carson Roscoe
--
-- PROGRAMMER: Carson Roscoe
--
-- INTERFACE: void input(int pipeToOutput[], int pipeToTranslate[])
--					int pipeToOutput[]: Pipe that will be read by the Output process.
--					int pipeToTranslate[]: Pipe that will be read by the Translate process.
--
-- RETURNS: void.
--
-- NOTES:
-- The input function is used to read user input and handle critical logic needed before passing it over to
-- the next process. The function will loop forever until the terminate variable is set to true, at which
-- point it will exit on its own.
--
-- The critical logic that needed to be done at this stage is handling the inputs for ctrl-k (Forcefully exiting 
-- the processes), T (Naturally exiting the processes) and E (Writing the buffered message over to the Translate pipe). 
-- All input which was not stated above is simply written to the Output's pipe.
----------------------------------------------------------------------------------------------------------------------*/
void input(int pipeToOutput[], int pipeToTranslate[]) {
	//Buffer of input that will be sent to the Translate process once the enter key ('E') is pressed.
	char buffer[PIPEMAXSIZE];
	
	//Keeps tracks of the curent buffers index (or size).
	size_t translateIndex = 0;
	
	//While we are not terminating the process
	while(TRUE) {
		//Get the next key pressed from the user
		char readChar = getchar();
		switch(readChar) {
			case KILLKEY: //On KILLKEY, kill all processes.
				kill(0, SIGKILL);
				break;
			case TERMINATEKEY: //On TERMINATEKEY, pass that the key was pressed to Output/Translate then terminate self.
				buffer[translateIndex++] = readChar;
				write(pipeToOutput[1], &readChar, 1);
				write(pipeToTranslate[1], buffer, translateIndex);
				return;
			case ENTERKEY: //On ENTERKEY, write all data in the buffer to the Translate process' pipe.
				buffer[translateIndex++] = readChar;
				write(pipeToOutput[1], &readChar, 1);
				write(pipeToTranslate[1], buffer, translateIndex);
				translateIndex = 0;
				break;
			default: //On all other input, store into buffer, increment counter and write to the Output pipe.
				buffer[translateIndex++] = readChar;
				write(pipeToOutput[1], &readChar, 1);
				break;
	}
}
