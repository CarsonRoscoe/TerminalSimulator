#include "Output.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: output
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
-- INTERFACE: void output(int pipeToInput[])
--					int pipeToInput[]: Pipe that will be written by the Input and Translate processes. All information
--						read from this pipe will be displayed no matter what. All logic is a precondition to this call.
--
-- RETURNS: void.
--
-- NOTES:
-- The output function is used to write the users input onto the screen, as well as write the translated input
-- onto the screen. It will loop doing this until the terminate variable is set to TRUE.
----------------------------------------------------------------------------------------------------------------------*/
void output(int pipeToInput[]) {
	//Off by default. Once it gets a TERMINATEKEY, it is set to true. Essentially used to tell the program we are in terminate mode.
	BOOL exit = FALSE;
	//Holds a character being read by the pipe
	char buffer[1];
	//While we are not terminating the process
	while(TRUE) {
		//If there is a character in the buffer to be read
		if (read(pipeToInput[0], buffer, 1) == 1) {
			//If we receive a terminate key, we know we are planning on terminating
			if (buffer[0] == TERMINATEKEY) {
				//If we are already in terminate mode, we have received a TERMIANTEKEY before, so BOTH other processes have terminated
				if (exit) {
					break;
				} else {
					//Otherwise, only one of the two have terminated. We need to set exit to true and wait for the second key before finishing.
					exit = TRUE;
				}
			} 
			//Display it to the screen
			printf("%c", buffer[0]);
			fflush(stdout);
		}
	}
	//At the end of our programs execution, we return the terminal's cursor back to normal.
	printf("%s", NEWLINE);
	fflush(stdout);
}
