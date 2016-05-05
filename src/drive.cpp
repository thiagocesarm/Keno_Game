/*
TO DO

- Fix problem with double sorting the array rigth before 'getHits' call during gameplay (line 249)
- Memory leak - no destructor

*/




/*! @file drive.cpp
 * 	@brief The main function of the game.
 * This file contains the inclusion of C++ libraries used in the main function 
 * and the library which contains the Keno Game class and functions.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "keno_library.h"

/*! @brief This function checks if the content of a string is an integer.
 *
 *	This function is someone else's authorship.
 *	Extracted from: http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int.
 */
inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}


//! The main function receives the spot file as argument.
int main( int argc, char * argv[] ){

	//! Initial Credit, the total amount of money the player will bet.
	float IC; 
	//! Number of Rounds.
	int NR;
	//! Vector to store the spot numbers read from file.
	std::vector<int> spot_numbers;
	//! Variable used to store each line read from the file, so it can be processed.
	std::string string_input; 
	//! Stream to read information from the spot file.
	std::ifstream bet_file; 
	//! The numbers that can be picked ([1, 80]).
	std::vector<int> keno_numbers; 

	//! Filling keno_numbers.
	for (int i = 1; i <= 80; ++i)
	{
		keno_numbers.push_back(i);
	}	

	//! Vector to store the round's numbers.
	std::vector<int> numbers_drawn(20);

	//! Checks if bet file was passed via command line.
	if ( argc > 1 )
	{
		bet_file.open(argv[1]);
	} 
	else
	{
		std::cout << "Bet file not provided. Please try again with the right arguments.\n";
		return EXIT_SUCCESS;
	}

	//! Checks if the stream could open the file passed via command line.
	if (bet_file.is_open())
	{
		std::cout << ">>> Preparing to read bet file [" << argv[1]<< "], please wait...\n";
		std::cout << "--------------------------------------------------\n";
		
		/*! Reads string from file. If the string is an integer, Initial Credit receives the value.
		 * If the value is greater than 0, the rest of the line is ignored and the loop breaks.
		 * If either the value is less than 0 or it is not an integer, it keeps reading from file
		 * until a valid integer is read or end of file is reached.
		 */
		while( bet_file >> string_input )
		{
			if ( isInteger(string_input) ) 
			{
				std::stringstream( string_input ) >> IC;
				if ( IC > 0)
				{
					std::getline( bet_file, string_input);
					break;
				}
				else
					continue;
			}
			else
			{
				continue;				
			}
		}

		//! If the file has reached its end, there is nothing more to be read.
		//! Thus, an error message is printed and the program exits.
		if (bet_file.eof())
		{
			std::cout << "Error reading bet value. Please try again.\n";
			return EXIT_SUCCESS;
		}
		
		/*! Reads string from file. If the string is an integer, Number of Rounds receives the value.
		 * If the value is greater than 0, the rest of the line is ignored and the loop breaks.
		 * If either the value is less than 0 or it is not an integer, it keeps reading from file
		 * until a valid integer is read or end of file is reached.
		 */
		while( bet_file >> string_input )
		{
			if ( isInteger(string_input) ) 
			{
				std::stringstream( string_input ) >> NR;
				if ( NR > 0)
				{
					std::getline( bet_file, string_input);
					break;
				}
				else
					continue;
			}
			else
			{
				continue;				
			}
		}

		//! If the file has reached its end, there is nothing more to be read.
		//! Thus, an error message is printed and the program exits.
		if (bet_file.eof())
		{
			std::cout << "Error reading number of rounds. Please try again.\n";
			return EXIT_SUCCESS;
		}

		/*! Reads string from file. If the string is an integer, it is added to spot_numbers.
		 * If the string is not an integer, it continues to read next string.
		 * The loop keeps going until end of file is reached.
		 */
		while( bet_file >> string_input )
		{

			if ( isInteger(string_input) )
			{
				spot_numbers.push_back( stoi(string_input) );
			}
			else
			{
				continue;			
			}
			
		}

		/*! If the file has reached its end and no spot numbers were read, 
		 * an error message is printed and the program exits.
		 */
		if ( bet_file.eof() and spot_numbers.size() == 0 )
		{
			std::cout << "Error reading bet numbers. Please try again.\n";
			return EXIT_SUCCESS;
		}

	}
	//! If bet file could not be opened, and error message is printed and the program exits.
	else
	{
		std::cout << "Error reading file. Please try again.";
		return EXIT_SUCCESS;
	}

	//! Object of the class KenoBet to store the informations of the Keno Bet.
	KenoBet kenoPlay;
	kenoPlay.setWage(IC/NR);

	//! Adding numbers stored in spot_numbers to kenoPlay.
	for ( auto i(0u); i < spot_numbers.size(); ++i)
	{
		kenoPlay.addNumber(spot_numbers[i]);
	}

	//! Sort the spot numbers added to the bet.
	quicksort(kenoPlay.getSpotsAddress(), 0, kenoPlay.numChosen() - 1);

	std::cout << ">>> Bet successfully read!\n";
	std::cout << "\tYou are going to wage a total of $" << IC << " dollars.\n";
	std::cout << "\tGoing for a total of "<< NR <<" rounds, waging $"<< kenoPlay.getWage() <<" per round.\n\n";
	std::cout << "\tYour bet has " << kenoPlay.numChosen() << " numbers. They are: ";

	//! Printing on screen the spot numbers picked by the player.
	std::cout << "[ ";
	for ( auto i(0u); i < kenoPlay.numChosen(); ++i)
	{
		std::cout << ( kenoPlay.getSpots() )[i] << " ";
	}
	std::cout << "]\n\n";

	//! Shows the payout table correspondent to the amount of the spot numbers.
	kenoPlay.showPayoutTable( kenoPlay.numChosen() );

	int round_hits = 0;
	float round_payout_rate = 0;
	//! Net Balance, the current amount of money the player holds in the end of each round.
	float NB = IC;	

	/*! Set precision to 0 decimal digits. It was preferred over 2 decimal 
	 * digits for style purposes.
	 */
	std::cout << std::setprecision(0) << std::fixed;

	//! For loop to play number of rounds chosen by player.
	for (int i = 1; i <= NR; ++i)
	{
		//! Net Balance is decremented by the round wage.
		NB -= kenoPlay.getWage();

		std::cout << "\t\t--------------------------------------------------\n";
		std::cout << "\t\tThis is round #" << i << " of " << NR 
		<< ", and your wage is $" << kenoPlay.getWage() << ". Good luck!\n";

		//! Shuffles the Keno numbers to prepare the round hits.
		shuffleNumbers(keno_numbers);

		//! The round hits. numbers_drawn is filled with the 20 first numbers shuffled.
		for ( auto j = 0; j < 20; ++j)
		{
			numbers_drawn[j] = keno_numbers[j];
		}

		//! Sorts the round hits.
		quicksort(numbers_drawn, 0, 19);

		std::cout << "\t\tThe hits are: [ ";
		for ( auto j = 0; j < 20; ++j)
		{
			std::cout << numbers_drawn[j] << " ";
		}
		std::cout << "]\n\n";

		//! round_hits gets the amount of numbers the player hit.
		round_hits = ( kenoPlay.getHits(numbers_drawn) ).size();

		std::cout << "\t\tYou hit the following number(s) [ ";
		for (int j = 0; j < round_hits; ++j)
		{
			std::cout << ( kenoPlay.getHits(numbers_drawn) )[j] << " ";
		}
		std::cout << "] a total of " << round_hits << " hit(s) out of " << kenoPlay.numChosen() << "\n";

		//! round_payout_rate gets the payout rate accordingly with the numbers the player hit.
		round_payout_rate = kenoPlay.getPayoutRate( kenoPlay.numChosen(), round_hits );

		//! Net Balance is incremented by the amount of money the player won in the round.
		NB += kenoPlay.getWage() * round_payout_rate;

		std::cout << "\t\tPayout rate is " << round_payout_rate << 
		" thus you came out with: $" << kenoPlay.getWage() * round_payout_rate  << "\n";
		std::cout << "\t\tYour net balance so far is: $" << NB << " dollars.\n\n";

	}

	//! Resets the Keno bet to an empty state.
	kenoPlay.reset();

	/*! Actual Net Balance minus the player's Initial Credit: The amount of money 
	 * the player had as profit (or loss).
	 */
	float profits = NB - IC;

	std::cout << ">>> End of rounds!\n";
	std::cout << "--------------------------------------------------\n\n";
	std::cout << "===== SUMMARY =====\n";

	std::cout << ">>> You spent in this game a total of $" << IC << " dollars.\n";

	//If profits is higher than 0, the player won money.
	if ( profits > 0)
	{
		std::cout << ">>> Hooray, you won $" << profits << " dollars. See you next time! ;-)\n";
	}
	//If profits is lower than 0, the player lost money.
	else if ( profits < 0)
	{
		std::cout << ">>> Sorry, you have lost $" << -profits << " dollars. Better luck next time.\n";
	}
	//If profits is equal to 0, the player neither won nor lost money.
	else
		std::cout << ">>> You have won $" << profits << " dollars. Not bad, it was fun. See you next time.\n";	

	std::cout << ">>> You are leaving the Keno table with $" << NB << " dollars.\n\n";

	return EXIT_SUCCESS;
}