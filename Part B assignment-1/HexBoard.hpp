#ifndef HEXBOARD_HPP
#define HEXBOARD_HPP

#include <map>
#include <set>
#include <string>

#include "Graph.hpp"

class HexBoard : public Graph {
public:
	static const unsigned kStandardSize = 11; // Default number of squares on a side of the board
	enum class Direction { SN, EW }; // Player directions South-North and East-West


	// Default constructor
	HexBoard() : HexBoard(kStandardSize) {
	}

	// Main Constructor
	HexBoard(unsigned side_size); 
	

	// Returns the number of spots of one side of the game board
	inline unsigned SideLen() const {
		return (side_size_);
	}

	// Returns if the row and col coordinates identifies a valid spot on the board
	inline virtual bool IsValidSpot(const unsigned row, const unsigned col) {
		if ((row < side_size_) && (col < side_size_)) {
			return true;
		}

		return false;
	}

	// Returns a reference to the spot on the game board
	inline Node& FindSpot(unsigned row_no, unsigned col_no) {
		return Graph::FindNode(SpotId(row_no, col_no));
	}

	// Converts the row and col coordinates to an id that idenifies a spot on the board
	inline std::size_t SpotId(unsigned row_no, unsigned col_no) {
		return (row_no * side_size_) + col_no;
	}

	friend std::ostream& operator<< (std::ostream& os,  HexBoard& g) {
		g.print(os);
		return os;
	}

	friend std::ostream& operator<< (std::ostream& os, HexBoard::Direction d) {
		os << (d == Direction::EW ?  "EW" : "SN");	
		return os;
	}

	virtual void print(std::ostream& os);

protected:
	const unsigned side_size_; // The number of spots of the game board sides
};

#endif // HEXBOARD_HPP

