//
// Created by mfbut on 1/20/2018.
//
#include <iostream>
#include "Space.h"
#include "MonopolyUtility.h"
#include "Player.h"
#include "GameState.h"

unsigned long Monopoly::Space::length_of_longest_space_name;
/*Monopoly::Space::Space(CSVReader& boardFile, const int spaceNumber, GameState& gameState):
    gameState(gameState), spaceNumber(spaceNumber){}
*/

Monopoly::Space::Space(){}

void Monopoly::Space::display() const {

  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << /*getName() << */" | ";

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
/*
const std::string& Monopoly::Space::getName() const {
  return this->getName();
}
*/
void Monopoly::Space::addPlayer(Monopoly::Player& player) {
  auto playerIt = playersOnSpace.cbegin();
  for (; playerIt != playersOnSpace.cend(); ++playerIt) {
    if (player.getId() < (*playerIt)->getId()) {
      break;
    }
  }
  playersOnSpace.insert(playerIt, &player);
}

void Monopoly::Space::removePlayer(const Monopoly::Player& player) {
  for (auto playerIt = playersOnSpace.cbegin(); playerIt != playersOnSpace.cend(); ++playerIt) {
    if ((*playerIt)->getId() == player.getId()) {
      playersOnSpace.erase(playerIt);
      return;
    }
  }
}

void Monopoly::Space::removeAllPlayers() {
  playersOnSpace.clear();
}

Monopoly::SpaceType Monopoly::Space::getSpaceType() const {
  return spaceType;
}


void Monopoly::Space::activate(Monopoly::Player& activatingPlayer) {

}