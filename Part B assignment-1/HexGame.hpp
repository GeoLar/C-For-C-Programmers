#ifndef HEXGAME_HPP
#define HEXGAME_HPP

#include <map>
#include <set>
#include <string>

#include "HexBoard.hpp"
#include "HexPlayer.hpp"

class HexGame : public HexBoard {
public:
	// Default constructor
	HexGame():HexGame(HexBoard::kStandardSize) {
	}

	// Main constructor, create players
	HexGame(unsigned side_size):HexBoard(side_size) {
	}

	// Return player data for one of the players
	inline HexPlayer& Player(HexBoard::Direction direction) {
		return(*players_.find(direction)->second);
	}

	void Run(); // Runs the game
	virtual bool IsValidSpot(const unsigned row, const unsigned col); // Checks if the spot is a valid position
	virtual void print(std::ostream& os); // Prints board and the players tiles

protected:
	std::map<HexBoard::Direction, HexPlayer*> players_; // Container of players data
};

#endif // HEXGAME_HPP

