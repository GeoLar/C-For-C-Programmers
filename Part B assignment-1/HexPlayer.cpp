
#include <ctime>
#include <iostream>
#include <random>

#include "HexBoard.hpp"
#include "HexPlayer.hpp"


// Checks if the player has built a continous path from the spot_id position to the opposit border 
bool HexPlayer::CheckIfBordersConnected(unsigned spot_id, std::set<unsigned>& visited) {
	// Lamdas to check if opposit border reached
	auto fSN = [this](unsigned spot_id)->bool {return (spot_id / this->board_.SideLen()) == (this->board_.SideLen() - 1); };
	auto fEW = [this](unsigned spot_id)->bool {return (spot_id % this->board_.SideLen()) == (this->board_.SideLen() - 1); };

	visited.insert(spot_id);
	if (HasTileInSpot(spot_id)) {
		// Check if we have reached the opposit border
		if (((Direction() == HexBoard::Direction::SN) && fSN(spot_id)) ||
			((Direction() == HexBoard::Direction::EW) && fEW(spot_id)))
			return true;

		// Find all reachable spots and check if anyone of theese leads to the opposit border
		Node& node = board_.FindNode(spot_id);
		for (auto node_path : node.paths) {
			if (visited.find(node_path.other_node_id) != visited.end())
				continue;

			if (CheckIfBordersConnected(node_path.other_node_id, visited))
				return true;
		}
	}

	return false;
}

// Checks if one of the player finished building a connection between the borders. 
bool HexPlayer::Done() {
	std::set <unsigned> visited; // To avoid circular lookups 

	if (Direction() == HexBoard::Direction::SN) {
		// Start looking for a continuous path from  every column in the first row (northenmost)
		for (unsigned col = 0; col < board_.SideLen(); col++) {
			if (CheckIfBordersConnected(board_.SpotId(0, col), visited))
				return true;
		}
	} else { // Direction is EW
		// Start looking for a continuous path from every row in the first column (easternmost)
		for (unsigned row = 0; row < board_.SideLen(); row++)
			if (CheckIfBordersConnected(board_.SpotId(row, 0), visited))
				return true;
	}

	return false;
}

// Reads a move from a player and places the tile on the spot the player choosed.
bool HexPlayer::InputMove() {
	bool move_done = false;

	while (!move_done) {
		std::string s;
		unsigned row, col;
		char col_ch = 'a' + (board_.SideLen() - 1);

		std::cout << Direction() << " Input position col(a-" << col_ch << ") row(1-" << board_.SideLen() << "), quit by setting col to x: ";
		std::cin >> col_ch;
		col_ch = std::tolower(col_ch);
		if (col_ch == 'x')
			return true; // Player wants to quit the game
		col = col_ch - 'a';

		std::cin >> row;
		row--;

		if (board_.IsValidSpot(row, col)) {
			MarkSpot(board_.SpotId(row, col));
			move_done = true;
		} else {
			std::cout << "Invalid position, please give another" << std::endl;
		}
	}

	return(false);
}

bool AIHexPlayer::InputMove() {
	static std::default_random_engine random_engine_; // Used to random generate paths (edges) between nodes  
	std::uniform_int_distribution<unsigned> random_id(0, board_.SideLen()-1);

	static bool once = false;
	if (!once) {
		random_engine_ = std::default_random_engine(std::time(0));
		once = true;
	}

	bool move_done = false;
	while (!move_done) {
		unsigned row = random_id(random_engine_);
		unsigned col = random_id(random_engine_);

		if (board_.IsValidSpot(row, col)) {
			MarkSpot(board_.SpotId(row, col));
			move_done = true;
		}
	}
	
	return false;
}
