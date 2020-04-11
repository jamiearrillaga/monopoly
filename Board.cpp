//
// Created by mfbut on 1/20/2018.
//

#include "Board.h"
#include <iostream>
#include "MonopolyUtility.h"
#include "Player.h"
#include "GameState.h"
#include "Go.h"
#include "GoToJail.h"
#include "FreeParking.h"
#include "PayBank.h"
#include "Jail.h"

Monopoly::Board::Board(const std::string& boardFileName, GameState& gameState) {
  CSVReader boardFile(boardFileName);
  constexpr int num_lines_to_skip = 4;

  if (boardFile.good()) {
    boardFile.skip_field();
    const int numSpaces = boardFile.get_next_field_as_int();

    for (int i = 0; i < num_lines_to_skip; ++i) {
      boardFile.skip_line();
    }

    for (int i = 0; i < numSpaces; ++i) {
      std::string space_type_string = boardFile.get_next_field();
      if (space_type_string == "Go") {
        //spaceType = SpaceType::goSpace;
        spaces.push_back(std::make_unique<Monopoly::Go>(boardFile, i, gameState));
        boardFile.skip_line(); // skip the remainder of the line in the file
      } else if (space_type_string == "Property") {
        //spaceType = SpaceType::propertySpace;
        spaces.push_back(std::make_unique<Monopoly::Property>(boardFile, i, gameState));
      } else if (space_type_string == "FreeParking") {
        //spaceType = SpaceType::freeParkingSpace;
        spaces.push_back(std::make_unique<Monopoly::FreeParking>(boardFile, i, gameState));
        boardFile.skip_line(); // skip the remainder of the line in the file
      } else if (space_type_string == "Pay") {
        //spaceType = SpaceType::payBankSpace;
        spaces.push_back(std::make_unique<Monopoly::PayBank>(boardFile, i, gameState));
        boardFile.skip_line(); // skip the remainder of the line in the file
      }else if (space_type_string == "Jail") {
        //spaceType = SpaceType::jailSpace;
        spaces.push_back(std::make_unique<Monopoly::Jail>(boardFile, i, gameState));
        boardFile.skip_line(); // skip the remainder of the line in the file
      } else if (space_type_string == "GoToJail") {
        //spaceType = SpaceType::goToJailSpace;
        spaces.push_back(std::make_unique<Monopoly::GoToJail>(boardFile, i, gameState));
        boardFile.skip_line(); // skip the remainder of the line in the file
      } else
        std::cout << "Unrecognized Space type: " << space_type_string << std::endl;
    }

    Monopoly::Space::length_of_longest_space_name = calc_length_of_longest_space_name();
    Monopoly::Space::length_of_longest_space_name =
        Utility::max(Monopoly::Space::length_of_longest_space_name, std::string("Space Name").size());

  } else {
    std::cout << "Failed to open board file: " << boardFileName << std::endl;
  }
}



/*
std::unique_ptr<Monopoly::Space> factory(CSVReader &boardFile) {
  //if (spaceType == SpaceType::goSpace)
    return std::make_unique<Go>(boardFile);
  else if (spaceType == SpaceType::propertySpace)
    return std::make_unique<Property>(boardFile, gameState.rules);
  else if (spaceType == SpaceType::freeParkingSpace)
    return std::make_unique<FreeParking>(boardFile);
  else if (spaceType == SpaceType::payBankSpace)
    return std::make_unique<PayBank>(boardFile);
  else if (spaceType == SpaceType::jailSpace)
    return std::make_unique<Jail>(boardFile);
  else
    return std::make_unique<GoToJail>(boardFile);

}*/

void Monopoly::Board::display() const {

  //const std::string header("Space Number | Space Name | Owner | Upgrades | Players");
  //std::cout << header << std::endl;
  const std::string spaceNumber("Space Number");
  const std::string spaceName("Space Name");
  const std::string owner("Owner");
  const std::string Upgrades("Upgrades");
  const std::string playersString("Players");
  const auto frmt_flags = std::cout.flags();
  std::cout.setf(std::ios::left);

  std::cout << spaceNumber; std::cout << " | ";
  std::cout << spaceName; std::cout << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << owner; std::cout << " | ";

  std::cout.width(Upgrades.size());
  std::cout << Upgrades << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << playersString; std::cout << std::endl;

  int i = 0;
  for (const auto& space : spaces) {
    std::cout.width(spaceNumber.size());
    std::cout << i << " | ";
    space->display();
    std::cout << std::endl;
    ++i;
  }
  std::cout.flags(frmt_flags);
}

Monopoly::Space& Monopoly::Board::getSpace(int spaceNum) {
  return *spaces[spaceNum];
}

Monopoly::Space& Monopoly::Board::getGoSpace() {
  Go* go;
  for (auto& space : spaces) {
    go = dynamic_cast<Go*>(space.get());
      return *go;
    }
  //this line should never execute
  return *spaces[0];
}

int Monopoly::Board::getNumSpaces() const {
  return static_cast<int>(spaces.size());
}

const std::vector<std::unique_ptr<Monopoly::Space>>& Monopoly::Board::getSpaces() const {
  return spaces;
}

unsigned long Monopoly::Board::calc_length_of_longest_space_name() const {
  std::vector<std::string> space_names;
  //for (const auto& space : spaces) {
    //space_names.emplace_back(space.getName());
  //}
  return Utility::get_max_string_length(space_names);
}

void Monopoly::Board::removeAllPlayers() {
  for (auto& space : spaces) {
    space->removeAllPlayers();
  }
}