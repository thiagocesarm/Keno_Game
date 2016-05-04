/*! @file keno_library.h
 * 	@brief Library containing declarations of Keno Bet class and several functions.
 * This file contains the inclusion of C++ libraries used in the game, the Keno Bet class
 * declaration, and the declaration of some functions.
 * 
 * The code of the class and the functions are in the src/keno_functions.cpp file.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

#ifndef _KenoBet_library_
#define _KenoBet_library_

//! Divides the vector in two partitions with a number between these. 
//! This number is then in the right position after the array is sorted.
//! This function is used with quicksort function.
//! @param array The vector to be partitioned, passed by reference.
//! @param l Index to start partition from.
//! @param r Index to end partition.
//! @return The vector's index of the number in the right position.
int partition( std::vector<int> & array, int l, int r );
//! Quicksort sorting algorithm.
//! Sorts the array passed as parameter using partition function.
//! @param array The vector to be sorted, passed by reference.
//! @param l Index to start partition from.
//! @param r Index to end partition
void quicksort( std::vector<int> & array, int l, int r );
//! Shuffles the numbers in a vector.
//! @param keno_numbers The vector to be shuffled, passed by reference.
void shuffleNumbers( std::vector<int> & keno_numbers );

class KenoBet 
{
	// ! Creates a Keno bet . It defines the maximum spots a bet may have.
	public:
		explicit KenoBet( unsigned int _maxNum = 15 );
		//! Adds a number to the spots only if the number is not already there.
		//! @param _spot The number we wish to include in the bet.
		//! @return T if number chosen is successfully inserted ; F otherwise .
		bool addNumber( int _spot );
		//! Sets the amount of money the player is betting .
		//! @param _wage The wage .
		//! @return True if we have a wage above zero ; false otherwise .
		bool setWage( float _wage);
		//! Resets a bet to an empty state.
		void reset( void );
		//! Retrieves the player’s wage on this bet.
		//! @return The wage value.
		float getWage( void ) const;
		//! Returns to the current number of spots in the player’s bet.
		//! @return Number of spots present in the bet.
		size_t numChosen( void ) const;
		//! Determine how many spots match the hits passed as argument.
		//! @param _hits List of hits randomly chosen by the computer.
		//! @return An vector with the list of hits.
		std::vector<int> getHits( std::vector<int> &_hits ) const;
		//! Return an vector < int > with the spots the player has picked so far.
		//! @return The vector < int > with the player’s spots picked so far.
		std::vector<int> getSpots( void ) const;
		//! Return the memory address of the vector <int> which stores the spots picked.
		//! @return The memory address of vector <int> m_spots.
		std::vector<int> & getSpotsAddress( void );
		//! Prints on screen the payout table correspondent to the # of spots the player picked.
		//! @param spotsNum The number of spots picked by the player.
		void showPayoutTable( int spotsNum );
		//! Returns the payout rate accordingly with the round numbers the player hit.
		//! @param numSpots Number of spots the player picked.
		//! @param round_hits Amount of round numbers the player hit.
		//! @return The rate to be applied in the player's wage.
		float getPayoutRate(int numSpots, int round_hits);
	private:
		std::vector<int> m_spots; // <! The player’s bet .
		float m_wage; // <! The player’s wage.
		unsigned int m_maxSpots; // <! Max # of spots allowed for this bet .
		std::vector< std::vector<float> > payout_table = // <! The payout rate table.
		{
			{0, 3},
			{0, 1, 9},
			{0, 1, 2, 16},
			{0, 0.5, 2, 6, 12},
			{0, 0.5, 1, 3, 15, 50},
			{0, 0.5, 1, 2, 3, 30, 75},
			{0, 0.5, 0.5, 1, 6, 12, 36, 100},
			{0, 0.5, 0.5, 1, 3, 6, 19, 90, 720},
			{0, 0.5, 0.5, 1, 2, 4, 8, 20, 80, 1200},
	        {0, 0, 0.5, 1, 2, 3, 5, 10, 30, 600, 1800},
	        {0, 0, 0.5, 1, 1, 2, 6, 15, 25, 180, 1000, 3000},
	        {0, 0, 0, 0.5, 1, 2, 4, 24, 72, 250, 500, 2000, 4000},
	        {0, 0, 0, 0.5, 0.5, 3, 4, 5, 20, 80, 240, 500, 3000, 6000},
	        {0, 0, 0, 0.5, 0.5, 2, 3, 5, 12, 50, 150, 500, 1000, 2000, 7500},
	        {0, 0, 0, 0.5, 0.5, 1, 2, 5, 15, 50, 150, 300, 600, 1200, 2500, 10000}
		};
};

#endif