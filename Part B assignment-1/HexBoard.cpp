#include <string>

#include "HexBoard.hpp"

// Constructor implementation. Creates the board and valid pathes between the spots (nodes).
HexBoard::HexBoard(unsigned side_size):Graph(side_size* side_size), side_size_(side_size) {
	//Create game board
	const unsigned path_cost = 1;
	const std::size_t side_idx_max = side_size - 1;
	unsigned row_idx = 0;

	// NorthWest corner
	Node& nw = FindSpot(0, 0);
	nw.name = "(0,0)";
	nw.AppendPath(SpotId(0, 1), path_cost);
	nw.AppendPath(SpotId(1, 0), path_cost);

	// NorthEast corner
    Node& ne = FindSpot(0, side_idx_max);
	ne.name = "(0," + std::to_string(side_idx_max) + ")";
	ne.AppendPath(SpotId(0, side_idx_max - 1), path_cost);
	ne.AppendPath(SpotId(1, side_idx_max), path_cost);

	// SouthWest corner
	Node& sw = FindSpot(side_idx_max, 0);
	sw.name = "(" + std::to_string(side_idx_max) + ",0)";
	sw.AppendPath(SpotId(side_idx_max - 1, 0), path_cost);
	sw.AppendPath(SpotId(side_idx_max, 1), path_cost);

	// SouthEast corner
	Node& se = FindSpot(side_idx_max, side_idx_max);
	se.name = "(" + std::to_string(side_idx_max) +"," + std::to_string(side_idx_max) + ")";
	se.AppendPath(SpotId(side_idx_max - 1, side_idx_max), path_cost);
	se.AppendPath(SpotId(side_idx_max, side_idx_max  - 1), path_cost);


		auto nodeitr = graph_.begin();
		while (nodeitr != graph_.end()) {
		for (unsigned col_idx = 0; col_idx < side_size; col_idx++) {
			Node& node = *nodeitr;
			node.name = "(" + std::to_string(row_idx) + "," + std::to_string(col_idx) + ")";

			if ((row_idx > 0) && (row_idx < side_idx_max) && (col_idx > 0) && (col_idx < side_idx_max)) {
				node.AppendPath(SpotId(row_idx - 1, col_idx), path_cost);
				node.AppendPath(SpotId(row_idx - 1, col_idx + 1), path_cost);
				node.AppendPath(SpotId(row_idx, col_idx - 1), path_cost);
				node.AppendPath(SpotId(row_idx, col_idx + 1), path_cost);
				node.AppendPath(SpotId(row_idx + 1, col_idx - 1), path_cost);
				node.AppendPath(SpotId(row_idx + 1, col_idx), path_cost);
			} else if (row_idx == 0) {
				if ((col_idx > 0) && (col_idx < side_idx_max)) {
					node.AppendPath(SpotId(row_idx, col_idx - 1), path_cost);
					node.AppendPath(SpotId(row_idx, col_idx + 1), path_cost);
					node.AppendPath(SpotId(row_idx + 1, col_idx - 1), path_cost);
					node.AppendPath(SpotId(row_idx + 1, col_idx), path_cost);
				}
			} else if (row_idx == side_idx_max) {
				if ((col_idx > 0) && (col_idx < side_idx_max)) {
					node.AppendPath(SpotId(row_idx - 1, col_idx - 1), path_cost);
					node.AppendPath(SpotId(row_idx - 1, col_idx + 1), path_cost);
					node.AppendPath(SpotId(row_idx, col_idx), path_cost);
					node.AppendPath(SpotId(row_idx, col_idx + 1), path_cost);
				}
			} else if (col_idx == 0) {
				if ((row_idx > 0) && (row_idx < side_idx_max)) {
					node.AppendPath(SpotId(row_idx - 1, col_idx), path_cost);
					node.AppendPath(SpotId(row_idx + 1, col_idx), path_cost);
					node.AppendPath(SpotId(row_idx - 1, col_idx + 1), path_cost);
					node.AppendPath(SpotId(row_idx, col_idx + 1), path_cost);
				}
			} else if (col_idx == side_idx_max) {
				if ((row_idx > 0) && (row_idx < side_idx_max)) {
					node.AppendPath(SpotId(row_idx - 1, col_idx), path_cost);
					node.AppendPath(SpotId(row_idx + 1, col_idx), path_cost);
					node.AppendPath(SpotId(row_idx, col_idx - 1), path_cost);
					node.AppendPath(SpotId(row_idx + 1, col_idx - 1), path_cost);
				}
			}

			nodeitr++;
		}

		row_idx++;
	}
}

// Prints the board on standard output
void HexBoard::print(std::ostream& os) {
	const unsigned side_len = SideLen();

	std::string indent = " ";
	for (unsigned row = 0; row < side_len; row++) {
		os << indent;

		for (unsigned col = 0; col < side_len; col++) {
			unsigned board_pos = SpotId(row, col);
			os << '.' << (col != (side_len - 1) ? "-" : "");
		}
		os << std::endl;
		indent.append(1, ' ');

		if (row != (side_len - 1)) {
			os << indent;
			for (unsigned col = 0; col < side_len; col++) {
				os << (col != (side_len - 1) ? "\\/" : "\\");
			}
			os << std::endl;
			indent.append(1, ' ');
		}
	}
}



