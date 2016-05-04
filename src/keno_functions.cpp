/*! @file keno_functions.cpp
 *	@brief All functions and class methods implemented to use in the Keno Game.
 * This file contains the code of all functions and Keno Bet methods that had to be 
 * implemented for the Keno Game.
 */
#include "keno_library.h"

//! Divides the vector in two partitions with a number between these. 
//! This number is then in the right position after the array is sorted.
//! This function is used with quicksort function.
//! @param array The vector to be partitioned, passed by reference.
//! @param l Index to start partition from.
//! @param r Index to end partition.
//! @return The vector's index of the number in the right position.
int partition( std::vector<int> & array, int l, int r )
{
	int wall = l - 1;
	int pivot = array[r];
	for (int i = l; i < r; ++i)
	{
		if (array[i] <= pivot)
		{
			std::swap(array[++wall], array[i]);
		}
	}
	std::swap(array[r], array[++wall]);
	return wall;
}

//! Quicksort sorting algorithm.
//! Sorts the array passed as parameter using partition function.
//! @param array The vector to be sorted, passed by reference.
//! @param l Index to start partition from.
//! @param r Index to end partition
void quicksort( std::vector<int> & array, int l, int r )
{
	if (l < r)
	{
		int pivot = partition(array, l, r);
		quicksort(array, l, pivot - 1);
		quicksort(array, pivot + 1, r);
	}
}

//! Shuffles the numbers in a vector.
//! @param keno_numbers The vector to be shuffled, passed by reference.
void shuffleNumbers( std::vector<int> & keno_numbers )
{
	//! Seeding standard random function with actual time in seconds.
	srand(time(0));
	//! Shuffling the vector passed using random_shuffle from <algorithm> library.
	std::random_shuffle( keno_numbers.begin(), keno_numbers.end() );
}

//-----------------------------------------------------------
// CLASS METHODS
//-----------------------------------------------------------

//! Constructor of Keno Bet class. Creates a Keno bet and defines the maximum spots a bet may have.
//! @param The maximum number of spots a bet may have.
KenoBet::KenoBet( unsigned int _maxNum )
{
	if ( !(_maxNum > 15) )
	{
		this->m_maxSpots = _maxNum;
	}
}

//! Adds a number to the spots only if the number is not already there.
//! @param _spot The number we wish to include in the bet.
//! @return T if number chosen is successfully inserted ; F otherwise.
bool KenoBet::addNumber( int _spot )
{
	/*! Checks if the number is in the correct range ([1, 80]) 
	 * and if the spots have reached its maximum.
	 * Returns false in case it doesn't.
	 */
	if ( _spot < 1 || _spot > 80 || m_spots.size() >= this->m_maxSpots )
	{
		return false;
	}
	//! If it's the first number to be added, adds directly.
	if (m_spots.size() == 0)
	{
		this->m_spots.push_back(_spot);
		return true;
	}
	else
	{
		for (auto i(0u); i < m_spots.size(); ++i)
		{
			//! Checks if the number is already in the spots. Returns false in case it is.
			if ( _spot == m_spots[i] )
			{
				return false;
			}		
		}
		//! Add the number if it is in the proper range and if it's not already in the spots.
		this->m_spots.push_back( _spot );
		return true;
	}
}

//! Sets the amount of money the player is betting.
//! @param _wage The wage.
//! @return True if we have a wage above zero ; false otherwise.
bool KenoBet::setWage( float _wage )
{
	if ( _wage > 0 )
	{
		this->m_wage = _wage;
		return false;
	}
	else
	{
		return true;
	}
	return 0;
}

//! Resets a bet to an empty state.
void KenoBet::reset( void )
{
	this->m_spots.clear();
	this->m_spots.resize(0);
}

//! Retrieves the player’s wage on this bet.
//! @return The wage value.
float KenoBet::getWage( void ) const
{
	return this->m_wage;
}

//! Returns to the current number of spots in the player’s bet.
//! @return Number of spots present in the bet.
size_t KenoBet::numChosen( void ) const
{
	return this->m_spots.size();
}

//! Determine how many spots match the hits passed as argument.
//! @param _hits List of hits randomly chosen by the computer.
//! @return An vector with the list of hits.
std::vector<int> KenoBet::getHits( std::vector<int> &_hits ) const
{
	//! Vector to store the player's hits.
	std::vector<int> hits;
	//! Sort the round numbers generated.
	quicksort( _hits, 0, 19);
	//! Iterator to store the result of the number's seek.
	std::vector<int>::iterator find_result;
	/*! The for loop runs through the round numbers to check which of the player's
	 * numbers match the round numbers. The function used to perform the search is
	 * 'find' from <algorithm>.
	 */
	for (auto j(0u); j < numChosen(); ++j)
	{
		//! find_result receives the result of the function 'find'.
		find_result = std::find( _hits.begin(), _hits.end(), m_spots[j]);
		//! If the number matches any of the round numbers, it is added to vector 'hits'.
		if (find_result != _hits.end())
		{
			hits.push_back(m_spots[j]);
		}
	}
	return hits;
}

//! Return an vector < int > with the spots the player has picked so far.
//! @return The vector < int > with the player’s spots picked so far.
std::vector<int> KenoBet::getSpots( void ) const
{
	return this->m_spots;
}

//! Prints on screen the payout table correspondent to the # of spots the player picked.
//! This function is used when sorting the spots in KenoBet class (see line 147 at drive.cpp).
//! @param spotsNum The number of spots picked by the player.
std::vector<int> & KenoBet::getSpotsAddress( void )
{
	return this->m_spots;
}

//! Prints on screen the payout table correspondent to the # of spots the player picked.
//! @param spotsNum The number of spots picked by the player.
void KenoBet::showPayoutTable( int spotsNum )
{
	std::cout << "\t\t-------+---------\n";
	std::cout << "\t\tHits   + Payout  \n";
	std::cout << "\t\t-------+---------\n";
	for (int i = 0; i <= spotsNum; ++i)
	{
		// Condition used only for style purposes.
		// If number to be printed on screen is greater than 10, one less space is showed after it.
		if (i < 10)
		{
			std::cout << "\t\t"
			<< i << "      | " 
			<< this->payout_table[spotsNum - 1][i] << "        \n";
		}
		else
		{
			std::cout << "\t\t"
			<< i << "     | " 
			<< this->payout_table[spotsNum - 1][i] << "        \n";
		}

	}
}

//! Returns the payout rate accordingly with the round numbers the player hit.
//! @param numSpots Number of spots the player picked.
//! @param round_hits Amount of round numbers the player hit.
//! @return The rate to be applied in the player's wage.
float KenoBet::getPayoutRate(int numSpots, int round_hits)
{
	return this->payout_table[numSpots - 1][round_hits];
}