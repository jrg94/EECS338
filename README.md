The code contained within this directory is written by Jeremy Griffith.

DESCRIPTION:
	The code contained in this directory implements a solution
	to Assignment 4 in EECS 338 (Fall 2015)

HOW TO BUILD:
	1. Navigate to the src directory using 'cd src'
	2. Enter the command 'make'
	3. If this fails, enter the command 'make clean'
	4. Repeat step 2

HOW TO RUN:
	1. Enter the command './as4' followed by an integer
	   Ex. > ./as4 2
	2. If the integer is within the range of test functions
	   the program will execute
	3. Otherwise, try a different integer

NOTES:
	Unfortunately, this solution is not complete. Linked Lists are
	proving to be incredibly difficult to work with in shared memory.
	It seems that malloc does not play nice with shared memory due
	to the local heap address used when allocating the memory. As a
	result, this solution can end up with the case where a withdraw
	waits for any deposit before continuing. Of course, this means
	that withdraws can cause the balance to go negative.
