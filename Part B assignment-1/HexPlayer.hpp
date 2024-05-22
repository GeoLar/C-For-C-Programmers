#ifndef HEXPLAYER_HPP
#define HEXPLAYER_HPP


#include <set>
#include <string>

#include "HexBoard.hpp"
//#include "HexGame.hpp"

// Container of a players game data
class HexPlayer {
public:
	HexPlayer(HexBoard& board, HexBoard::Direction direction, char avatar) :direction_(direction), avatar_(avatar), board_(board) {
	}

	// Mark the spot as if the player put a game piece in it.
	inline char Avatar() {
		return avatar_;
	}

	// Mark the spot as if the player put a game piece in it.
	inline void MarkSpot(unsigned spot_id) {
		moves_.insert(spot_id);
	}

	// Returns true if the player has put a pgame piece in the spot
	inline bool HasTileInSpot(unsigned spot_id) {
		return (moves_.find(spot_id) != moves_.end());
	}

	// Returns the direction in which the player should build connections
	inline HexBoard::Direction Direction() {
		return direction_;
	}

	inline static void Swap(HexPlayer& p1, HexPlayer& p2) {
		auto d = p1.direction_;
		auto a = p1.avatar_;
		p1.direction_ = p2.direction_;
		p1.avatar_ = p2.avatar_;
		p2.direction_ = d;
		p2.avatar_ = a;
		p1.moves_.swap(p2.moves_);
	}

	bool Done();
	virtual bool InputMove();

protected:
	bool CheckIfBordersConnected(unsigned spot_id, std::set<unsigned>& visited);

	HexBoard::Direction direction_; // The direction which this player should build connection with
	std::set<unsigned> moves_; // Container of the positions (spots) the player has put tiles in
	char avatar_; // A character used in printouts to distinguish this player from another
	HexBoard& board_;
};


class AIHexPlayer : public HexPlayer {
public:
	AIHexPlayer(HexBoard& game, HexBoard::Direction direction, char avatar, const HexPlayer& other) 
		:HexPlayer(game, direction, avatar),game_(game),other_(other) {
//		std::cout << "AI player is " << Direction() << std::endl;
	}

	virtual bool InputMove();

protected:
	HexBoard& game_;
	const HexPlayer& other_;
};

#endif // HEXPLAYER_HPP