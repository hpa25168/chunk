#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "chunkFunction.c"

/* GLOBALS */
int lines = 1000;
int lines_check = 1;
int words;
int words_check;
int characters;
int char_check;

char *prefix = "x";
char letters[3] = {'a','a','\0'};
char *suffix = letters;
#define BUFSIZE  1
int input_fd = 0;
int output_fd;
char *buffer;

//Changes the suffix using char
void  suffixchanger() {
    if (suffix[0] >= 'a' && suffix[0] <= 'z' ) {
	if (suffix[1] >= 'a' && suffix[1] <= 'y' ) {
	    suffix[1]++;

	} else if (suffix[1] == 'z') {
	    suffix[1] = 'a';
	    suffix[0]++;
	}
    } else if (suffix[0] >= '0' && suffix[0] <= '9') {
	if (suffix[1] >= '0' && suffix[1] <= '9') {
	    suffix[1]++;
	} else if (suffix[0] == ':') {
	    suffix[0]++;
	    suffix[1] = '0';
	}
    }

} // End of suffixchanger;

// creates a new FIle and check if it already existed if file already exist it will end the program.
void outfile() {
    char* txt = ".txt";
    char wor[80];
    strcpy(wor,prefix);
    strcat(wor,suffix);
    strcat(wor,txt);
    //strcat(fileName,txt);
    if (access(wor,F_OK)==0) {
	fprintf(stderr,"file already exists\n");
	exit(0);
    }else {
	output_fd = open(wor, O_RDWR | O_CREAT | O_EXCL,0644 );
    }
}

// writing to the new file with specific characters
void characterFunction() {
    buffer = ( char * ) calloc( BUFSIZE, sizeof(char));
    outfile();
    int count = 0;
    while(read(input_fd,buffer,BUFSIZE) >  0) {

	if (count < characters) {
	    if (buffer[0] == '\n') {
		write(output_fd,buffer,BUFSIZE);
		count++;
	    } else {
		write(output_fd,buffer,BUFSIZE);
		count++;
	    }
	} else {
	    close(output_fd);
	    suffixchanger();
	    outfile();
	    count = 0;
	    if (count < characters) {
		if (buffer[0] == '\n') {
		    write(output_fd,buffer,BUFSIZE);
		    count++;
		} else {
		    write(output_fd,buffer,BUFSIZE);
		    count++;
		}
	    }
	}
    } // while
} // End of Character Function

// writing to the new file with specific number words
void wordFunction() {
    buffer = ( char * ) calloc( BUFSIZE, sizeof(char));
    outfile();
    int count = 0;
    while(read(input_fd,buffer,BUFSIZE) >  0) {

	if (count < words) {
	    if (buffer[0] == ' ' || buffer[0] ==  '\n') {
		write(output_fd,buffer,BUFSIZE);
		count++;
	    } else
		  write(output_fd,buffer,BUFSIZE);
	} else {
	    close(output_fd);
	    suffixchanger();
	    outfile();
	    count = 0;
	    if (count < words) {
	    if (buffer[0] == ' ' || buffer[0] ==  '\n') {
		write(output_fd,buffer,BUFSIZE);
		count++;
	    } else
		write(output_fd,buffer,BUFSIZE);
	    }
	}
    } // while
} //End of Word Function

// copying certain lines from the file to the new line.
void lineFunction() {
    buffer = ( char * ) calloc( BUFSIZE, sizeof(char));
    outfile();
    int count = 0;
    while(read(input_fd,buffer,BUFSIZE) >  0) {
	if (count <  lines) {
	    if (buffer[0] == '\n') {
		count++;
		write(output_fd,buffer,BUFSIZE);
	    } else{
		 write(output_fd,buffer,BUFSIZE);
	    }
	} else
	{
	    close(output_fd);
	    suffixchanger();
	    outfile();
	    count = 0;
	    if (count <  lines) {
		if (buffer[0] == '\n') {
		count++;
		write(output_fd,buffer,BUFSIZE);
		} else{
		    write(output_fd,buffer,BUFSIZE);
		} // if /else
	    } // if
	}// if /else

    } // while
} // End of LineFunction

//Check which function the user wants.
void checkOptions() {
    if (words_check == 1) {
	wordFunction();
    } else if (lines_check == 1) {
	lineFunction();
    } else if (char_check == 1) {
	characterFunction();
    }
}
// parse the command line prompt
void getCommanLine( int argc, char **argv )
{
    int 		ch;

    while ( ( ch = getopt ( argc, argv, "l:w:c:f:p:s:" ) ) != EOF )
    {
        switch ( ch )
	{
	    // Getting inforamtion from the user
	case 'l':
	    // with optional integer argument
	{
	    // Handle errors
	    if (errorHandle(optarg) == -1) {
		fprintf ( stderr,"Invalid Arguement \n");
		exit(0);
	    }
	    //checks the value if it not under 0.
	    if (valueChecker(atoi(optarg)) == 1) {
		lines = atoi( optarg );
	    }
	    break;
	}
	case 'c':
	{
	    //error handler
	    if (errorHandle(optarg) == -1) {
	        fprintf ( stderr,"Invalid Arguement\n");
		exit(0);
	    }
	    // checks input from the user
	    if (valueChecker(atoi(optarg)) == 1) {
		characters = atoi( optarg );
		char_check = 1;
		lines_check = 0;
	    }
	    break;
	}
	// gets the input from the user
	case 'w':
	{

	    if (errorHandle(optarg) == -1) {
	        fprintf ( stderr,"Invalid Arguement\n");
		exit(0);
	    }

	    if (valueChecker(atoi(optarg)) == 1) {
		words = atoi(optarg);
		words_check = 1;
		lines_check = 0;
	    }
	    break;
	}
	// check for the file
	case 'f':
	{
	    if (errorHandle(optarg) == -1)
	    {
		fprintf ( stderr,"Invalid Arguement\n");
		exit(0);
	    }
	    input_fd = inputFile(optarg);
	    break;
	}
	//gets the suffix
	case 's':
	{
	    if (errorHandle(optarg) == -1) {
		fprintf ( stderr,"Invalid Arguement\n");
		exit(0);
	    }
	    if (checker(optarg) == 1) {
		suffix = optarg;

	    }
	    break;
	}
	// gets the prefix
	case 'p':
	{
	    if (errorHandle(optarg) == -1) {

		fprintf ( stderr,"Invalid Arguement\n");
		exit(0);
	    }
	    prefix = optarg;

	    break;
	}
	case '?':
	default:
	{
	    fprintf ( stderr, "%s: unrecognized option -%c\n",
	    argv[0], ch );
	    exit(0);
	    break ;
	}
	} /* switch */
    } /* while */
}

int main( int argc, char *argv[] )
{

	getCommanLine(argc,argv);
	checkOptions();
	return 0;
} // main
