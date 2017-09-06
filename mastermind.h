#ifndef MASTERMIND_H
#define MASTERMIND_H


#define SEQ_LEN 4			//the length of the code
#define NUMBER_COLOURS 6    //the number of colour options
#define bool int			//define boolean type
#define true 1				//define true bool type
#define false 0				//define false bool type
#define MAX_GUESSES 10		//max number of guesses by the user

// function prototypes
// returns the number of matched positions
int position_check (char guess_array[], char sequence_array[], int length); 

// returns the number of colour matches (excluding position matches)
int colour_check (char guess_array[], char sequence_array[], int length, int position_matches); 
int case_conversion (int character); 
int sequence_generator (int number_colours); //will call this X number of times from main, need to consider expanding the  length of the 
//sequence. 
int num2char(int random_seed); // seed less than 6, for 6 colour options

#endif