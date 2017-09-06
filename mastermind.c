#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mastermind.h"

//additional functionality
	//how many letters in the sequence
	//AI plays the game and you watch (uses algorithm)

int main()
{
	srand(time(NULL)); //seed the random number generator
	int random_number; 
	int seq_colour; 
	char stored_guesses[SEQ_LEN][MAX_GUESSES]; 
	char seq[SEQ_LEN]; 
	bool game_state = false; 
	int character; 
	char guess[SEQ_LEN]; 
	int position_matches; 
	int colour_matches; 
	int guess_count = 0; 
	int stored_position[MAX_GUESSES]; 
	int stored_colour[MAX_GUESSES]; 

	//this could go into another function - code generator
	for (int k = 0; k < SEQ_LEN; k++)
	{
		random_number = sequence_generator(NUMBER_COLOURS);
		seq_colour = num2char(random_number);
		seq[k] = seq_colour; 
	}

	while (game_state == false && guess_count < MAX_GUESSES) //game state could be called "victory state"
	{

		int i = 0; 

		printf("\nplease enter your 4 colour guess: \n"); //bug, can enter more than 4 characters. 
		printf("the colours are: Red - R, Blue - B, Orange - O, White - W, Purple - P, Green - G\n");
		// subsequent characters above 4 will form the next guess. 
		while ((character = getchar()) != EOF && (i < SEQ_LEN)) //only the first 4 characters will be stored
		{
			//insert lowercase to upper case conversion
			character = case_conversion(character); 
			guess[i] = character; //these could be combined into one array
			stored_guesses[i][guess_count] = character;
			i += 1; 
		}

		// Check the guess
		 position_matches = position_check(guess, seq, SEQ_LEN); 
		 colour_matches = colour_check(guess, seq, SEQ_LEN, position_matches); 
		 //probably should be stored as a structure, since the data is related. 
		 stored_position[guess_count] = position_matches; 
		 stored_colour[guess_count] = colour_matches;

		 // need to print all previous guess to the user. 


		printf("\nYour guesses: \t\tposition match\tcolour match\n"); 
		for (int k = 0; k < (guess_count + 1); k++)
		{	
			printf("guess %i: \t", (k + 1));
			for (int j = 0; j < SEQ_LEN; j++)
			{ 
				printf("%c", stored_guesses[j][k]);
				//printf("The %i sequence is %c. \n", j, seq[j]); 
			} 
			printf("\t%i\t\t%i", stored_position[k], stored_colour[k]); //these will need to be turned into arrays
			printf("\n");
		}
		printf("\n");



		 //check for a win
		 if (position_matches == SEQ_LEN)
		 {
		 	game_state = true; 
		 	printf("\nyou have won the game congradulations scrub\n"); 
		 }
		 guess_count += 1; 

	}
	if (position_matches != SEQ_LEN)
	{
		printf("You have exceeded %i guesses, the code was: ", guess_count);
		for (int n = 0; n < SEQ_LEN; n++)	 
		{
			printf("%c", seq[n]);
		}
		printf("\n");
	}
	return(0); 
}

int position_check(char guess[], char seq[], int len) //pass the address of the first element of the array
{
	int position_matches = 0; 
	for (int j = 0; j < len; j++)
	{
		if (guess[j] == seq[j])
			position_matches += 1; 
	}

	return(position_matches); 
}

int colour_check(char guess[], char seq[], int len, int position_matches)
{
	bool matched_character_flag[SEQ_LEN] = {false};  //if len is used instead of magic number 4 (complile error)
	int colour_matches = 0; 
	bool colour_match_state = false; 
	for (int j = 0; j < len; j++)	//out loop
	{
		//inner loop
		for (int i = 0; i < len; i++)
		{
			//there must be a better way to do this... but the below works. 
			if ((seq[j] == guess[i]) /*&& (i != j)*/ && (colour_match_state == false) && (matched_character_flag[i] == false)) //if the colour matches, and the postions are the same, data excluded
			{
				colour_matches += 1; 
				colour_match_state = true; 
				matched_character_flag[i] = true; 
			}
		}
		colour_match_state = false;
	}
	return(colour_matches - position_matches); 
}

int case_conversion(int character)
	{
		switch(character) //are the capitals and lower cases always seperated by the same number in the 
		//ascii table, could just do a addition or subraction
		{
			case 'r':
				character = 'R';
				break;
			case 'g':
				character = 'G';
				break;
			case 'b':
				character = 'B';
				break;
			case 'p':
				character = 'P';
				break;
			case 'o':
				character = 'O';
				break;
			case 'w':
				character = 'W';
				break;
			// default :
			// 	character = character - 32; // Decimal 32 seperates upper case and lower case in ASCII
				// this indicates invalid data has been entered by the user, fix required. 
				// this bugs the code if valid data is entered. 
		}
		return(character);
	}

	int sequence_generator(int num_colours)
	{
		int r; 
		r = rand(); 
		r = (r % num_colours) + 1; 
		return (r); 
	}

	int num2char(int seed)
	{
		int character; 
		switch(seed)
		{
			case 1 :
				character = 'R';
				break; 
			case 2 :
				character = 'G';
				break; 
			case 3 :
				character = 'B';
				break; 
			case 4 :
				character = 'P';
				break; 
			case 5 :
				character = 'O';
				break; 
			case 6 :
				character = 'W'; 
				break; 						
		}
		return(character); 
	}