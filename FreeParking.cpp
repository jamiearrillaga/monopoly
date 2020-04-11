#include "FreeParking.h"
#include <iostream>
#include "Player.h"
#include "GameState.h"

Monopoly::FreeParking::FreeParking(CSVReader& boardFile, const int spaceNumber, GameState& gameState) :
    gameState(gameState) {
  name = boardFile.get_next_field();
  sn = spaceNumber;
}

const std::string& Monopoly::FreeParking::getName() const {
  return name;
}

const int Monopoly::FreeParking::getSpaceNumber() const{
  return sn;
}


void Monopoly::FreeParking::display() const {
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << name << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);
  const std::string temp = "None";
  std::cout << temp << " | ";
  std::cout << "         | ";

  std::cout.flags(frmt_flags);

  auto player = playersOnSpace.cbegin();
  for (; player != playersOnSpace.cend(); ++player) {
    if (player + 1 == playersOnSpace.cend()) {
      break;
    }
    (*player)->display();
    std::cout << ", ";
  }
  if (player != playersOnSpace.cend()) {
    (*player)->display();
  }
}

void Monopoly::FreeParking::activate(Player &activatingPlayer) {
  if(gameState.getFreePark() > 0) {
    std::cout << activatingPlayer.getName() << " got $ " << gameState.getFreePark() <<
              " for landing on " << name << std::endl;
    activatingPlayer.giveCash(gameState.getFreePark());
    gameState.resetFreePark();
  }
}