// C++ For C Programmers Part B
// assignment 1 -  Implemenation of the Hex Game. 
// Not Complete. Implementaion of computer acting as a player still remains to be done.

#include <algorithm>
#include <iostream>

#include "HexGame.hpp"
#include "HexPlayer.hpp"


int main() {
	HexGame().Run();
}

void HexGame::Run() {
	// Let the player choose direction
	std::string direction = "";
	while ((direction.compare("EW") != 0) && (direction.compare("SN") != 0)) {
		std::cout << "Choose direction SN (south-north) or EW (east-west): ";
		std::cin >> direction;
		transform(direction.begin(), direction.end(), direction.begin(), ::toupper);
	}

	HexPlayer player = HexPlayer(*this, HexBoard::Direction::SN, 'X');
	AIHexPlayer aiPlayer = AIHexPlayer(*this, HexBoard::Direction::EW, 'O', player);
	if (direction.compare("EW") == 0) {
		HexPlayer::Swap(player, aiPlayer);
	}
	players_.insert(std::make_pair(player.Direction(), &player));
	players_.insert(std::make_pair(aiPlayer.Direction(), &aiPlayer));

	HexPlayer *current_player = players_.find(player.Direction())->second;
	bool game_Over = false;
	while (!game_Over) {
		bool terminate_game = current_player->InputMove();
		if (terminate_game)
			return;
		std::cout << *this << std::endl;

		game_Over = current_player->Done();
		if (game_Over) {
			std::cout << "Player " << current_player->Direction () << " wins" << std::endl;
		}

		// Switch current player
		if (current_player->Direction() == HexBoard::Direction::EW)
			current_player = players_.find(HexBoard::Direction::SN)->second;
		else
			current_player = players_.find(HexBoard::Direction::EW)->second;
	}
}


// Checks if the spot is available to be used by one of the players
bool HexGame::IsValidSpot(const unsigned row, const unsigned col) {
	auto spot_id = SpotId(row, col);

	if (!HexBoard::IsValidSpot(row, col))
		return false;
	else if (Player(HexBoard::Direction::SN).HasTileInSpot(spot_id))
		return false;
	else if (Player(HexBoard::Direction::EW).HasTileInSpot(spot_id))
		return false;

	return (true);
}

void HexGame::print(std::ostream& os) {
	const unsigned side_len = SideLen();

	os << "HexBoard" << std::endl;

	std::string indent = " ";
	for (unsigned row = 0; row < side_len; row++) {
		os << indent;

		for (unsigned col = 0; col < side_len; col++) {
			unsigned board_pos = SpotId(row, col);
			char pos = '.';
			if (Player(HexBoard::Direction::SN).HasTileInSpot(board_pos)) {
				pos = Player(HexBoard::Direction::SN).Avatar();
			} else if (Player(HexBoard::Direction::EW).HasTileInSpot(board_pos)) {
				pos = Player(HexBoard::Direction::EW).Avatar();
			}

			os << pos << (col != (side_len - 1) ? "-" : "");
		}
		os << std::endl;
		indent.append(1, ' ');

		/*
		if (row != (side_len - 1)) {
			os << indent;
			for (unsigned col = 0; col < side_len; col++) {
				os << (col != (side_len - 1) ? "\\/" : "\\");
			}
			os << std::endl;
			indent.append(1, ' ');
		}
		*/
	}
}
