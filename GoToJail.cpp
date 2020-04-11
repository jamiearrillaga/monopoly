#include "GoToJail.h"
#include <iostream>
#include "GameState.h"
#include "Player.h"
#include "Jail.h"

Monopoly::GoToJail::GoToJail(CSVReader& boardFile, const int spaceNumber, GameState& gameState) :
    gameState(gameState) {
  name = boardFile.get_next_field();
  index = boardFile.get_next_field_as_int();
  sn = spaceNumber;
}

int Monopoly::GoToJail::getIndex() const {
  return index;
}

const std::string& Monopoly::GoToJail::getName() const {
  return name;
}

void Monopoly::GoToJail::display() const {
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

const int Monopoly::GoToJail::getSpaceNumber() const {
    return sn;
}

void Monopoly::GoToJail::activate(Player &activatingPlayer) {
  Jail* jail = dynamic_cast<Jail*>(&gameState.board.getSpace(index));
  std::cout << activatingPlayer.getName() << ", you were sent to " << (*jail).getName() << " for 2 turns" << std::endl;
  activatingPlayer.setTimeInJail(jail->getTurnsInJail());
  activatingPlayer.moveTo(gameState.board.getSpace(index));
}