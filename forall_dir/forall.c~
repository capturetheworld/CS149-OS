#include "util.h"




	/********************************************************
	 *  Important: All functions mentioned here should be stored in a utility
	 *  file like util.c. 
	********************************************************/


	/********************************************************
	 *  1) Check the argument to make sure you have argc>1
	 *  You should have it in a function by now.
	 *  Testinig: printf all argv for correctness
	 *  Do the code here before next instruction
	********************************************************/






	/********************************************************
	 *  Optional: The best is to store the argv in your own array of strings by 
	 *  your own function. 
	 *  Testinig: printf all argv for correctness
	 *
	********************************************************/









	/********************************************************
	 * 2) call system("wc /etc/passwd") to see the appropriate output on your screen
	 * Do the same thing now with execlp by using the argv elements. 
	 * You should be able to see the same thing
	********************************************************/









	/********************************************************
	 * 3) Now create a file handler,fd1_out. But since we are using open() instead of
	 *   	fopen(), integer type for the file handler is used instead of FILE *
	 * 4) Now redirect your stdout to a file by using close() to close the stdout and 
	 * 	dup() to duplicate and replace and redirect;
	 * 	Now you should see the same messages earlier now direct to 1.out as the 
	 * 	assignment requires.
	 * 	Testing: if (fd < 1) error message.
	********************************************************/












	/********************************************************
	 * 5) At this point, I use a function for the following steps because
	 * 	you are repeating this "wc" --- word count unix program on the
	 * 	first file /etc/passwd now and  2nd file /etc/issue
	 * 	later. So a function call would make sense.
	 * 	Anyway this is what you need to do:
	 * 	a) printf() the lines required by your assignment namely
	 * 	Executing .....
	 * 	b) move your execlp() from the main() to here.
	 * 	c) check if 1.out still printing the right message 
	********************************************************/








		
	/********************************************************
	 * d) Create your fork()
	 * e) Move your execlp() to your child process
	 * Testing: see if you still see the same 1.out
	********************************************************/











	/********************************************************
	 * g) Now in your parent process, do the waitpid() for the child
	 * 	to send you the process status.
	 * h) printf() the last line required in your assignment,
	 * 	namely, Finshed executing..... status = 0
	********************************************************/











	/********************************************************
	 * fflush() is going to help you if the order of output is not right
	 * in your 1.out
	********************************************************/







	/********************************************************
	 * 6) Back to the main program, now you have to repeat the same
	 * 	steps for the second file 2.out
	 * GOOD LUCK !!
	********************************************************/
	int fd1_out =open("1.out",O_WRONLY | O_CREAT | O_APPEND);
	close(1);
	dup(fd1_out);
	wcCmd(fd1_out,argv[1],argv[2]);


	int fd2_out =open("2.out",O_WRONLY | O_CREAT | O_APPEND);
	close(1);
	dup(fd2_out);
	wcCmd(fd2_out,argv[1],argv[3]);
	close(fd2_out);



}


