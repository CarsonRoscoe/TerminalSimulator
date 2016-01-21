/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Assignment1.c - An application which will recreate disabled terminal features and allow the user
-- to translate a string of input into a new desired string. The application will utilize forks, signals and pipes.
--
-- PROGRAM: Assignment1
--
-- FUNCTIONS:
-- int main(void)
-- void input(int pipeToOutput[], int pipeToTranslate[])
-- void output(int pipeToInput[])
-- void translate(int pipeToOutput[], int pipeToInput[])
--
-- DATE: January 9th, 2016
--
-- REVISIONS: January 9th, 2016: Initial creation.
--	      January 11th, 2016: Added comments & refactored variable names to be cleaner.
--	      January 14th, 2016: Fixed bug where 'T' would not do one final translation, refactored the code to move
--			all magic numbers into defined & split up the program into multiple files.
--
-- DESIGNER: Carson Roscoe
--
-- PROGRAMMER: Carson Roscoe
--
-- NOTES:
-- The program's purpose is to take input given by the user, display it to the screen as they type, and once
-- the user presses the enter key (which in our case is 'E'), it redisplays the input to the screen in the
-- translated form. This translated form, for the sake of simplicity, is simply changing all 'a' characters
-- into 'z' characters, as well as have the 'X' character act as a backspace.
--
-- The constraint of this program is that a large amount of terminal functionality is disabled (echo, cariage return
-- and the processing of input/output). To get the program to achieve the goal above, we must recreate these missing
-- functionalities programmatically. We will recreate it in a way where K clears the line, T terminates the
-- program naturally and ctrl-k kills all three processes.
-- 
-- The program goes about this by forking into three seperate processes, one with the job of handling input from the
-- user, one that handles output to the user and a third which handles translating the input. These three processes
-- are split using the fork command, communicate through two pipes and handle their own cleanup once they receive
-- a interrupt signal.
----------------------------------------------------------------------------------------------------------------------*/
#include "Shared.h"
#include "Input.h"
#include "Output.h"
#include "Translate.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: main
--
-- DATE: January 9th, 2016
--
-- REVISIONS: January 9th, 2016: Initial creation.
--	      January 11th, 2016: Added comments & refactored variable names to be cleaner.
--	      January 14th, 2016: Removed the PIDs array due to it becoming uneeded after utilizing kill(0, SIGKILL)
--
-- DESIGNER: Carson Roscoe
--
-- PROGRAMMER: Carson Roscoe
--
-- INTERFACE: int main(void)
--
-- RETURNS: Returns an integer that relates to the reason the program exited.
--
-- NOTES:
-- The main function is the starting point of the program. It is used to setup all the processes before spliting
-- so they can be exited properly when the time comes and to be able to communicate between each other, and then splits
-- into three seperate processes.
--
-- The setup stage sets the global terminate variable to false. It then creates local variables for the two pipes. 
-- It attempts to open both pipes, and then modify the pipes to both be non-blocking.
--
-- Once it has successfully completed setup, it forks twice. The first time it forks, the child will become our
-- 'Output' process and will invoke the output function. The second time it forks, the child will become our 'Translate'
-- process and will invoke the translate function. The parent of the second fork will become our 'Input' process.
----------------------------------------------------------------------------------------------------------------------*/
int main(void) {
	//References to two pipes, once which will be read by Output and the other will be read by Translate
	int pipeToOutput[PIPESIZE], pipeToTranslate[PIPESIZE];
	
	//An array of process ID for each of the processes. This will be used by Input.
	long outputPID, inputPID;
	
	//Notifies the system to disable I/O processing, cariage return on new line and echo'ing to the screen.
	system ("stty raw igncr -echo");

	//Try to open the Output pipe and the Translate pipe
	if ((pipe(pipeToOutput) < 0) || (pipe(pipeToTranslate) < 0)) {
		//Error openning one of the pipes
		perror("Failed to open pipes");
		exit(1);
	}

	//Try to make both pipes non-blocking
	if ((fcntl (pipeToOutput[0], F_SETFL, O_NDELAY) < 0) || (fcntl (pipeToTranslate[0], F_SETFL, O_NDELAY) < 0)) {
		//Error in making the pipes non-blocking
		perror("Failed to set O_NDELAY for pipes");
		exit(1);
	}

	//Fork into two processes and store the ID into pids[0]. The child will become our Output process.
	switch (outputPID = fork()) {
		case -1:
			//Error forking
			perror("Failed to fork");
			exit(1);
		case 0:
			//Child is now known as our Output process and invokes output.
			//It takes in the pipeToOutput to read input given to it by the Translate and Input processes.
			output(pipeToOutput);
			break;
		default:
			//Fork into two processes and store the ID into pids[1]. The child will become our Translate process.
			switch(inputPID = fork()) {
				case -1:
					//Error forking
					perror("Failed to fork");
					exit(1);
				case 0:
					//Child is now known as our Translate process and invokes translate.
					//It takes in pipeToOutput in order to send translated messages to the Output process,
					//and pipeToTranslate in order to receive input to be translated from the Input process.
					translate(pipeToOutput, pipeToTranslate);
					break;
				default:					
					//It takes in pipeToOutput & pipeToTranslate in order to send input to the appropriate process.
					//It also takes in the array of PID's in order to notify all processes when they need to be interrupted.
					input(pipeToOutput, pipeToTranslate);
					
					//Return the ability to process I/O, carriage return and echo back to terminal.
					system ("stty -raw -igncr echo");
					break;
			}
			break;
	}
}
