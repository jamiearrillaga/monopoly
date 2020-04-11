#include "Go.h"
#include "GameState.h"
#include <iostream>

Monopoly::Go::Go(Monopoly::CSVReader& boardFile, const int spaceNumber, Monopoly::GameState& gameState) :
    gameState(gameState) {
  sn = spaceNumber;
  salary = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();
}

int Monopoly::Go::getSalary() const {
  return salary;
}

const std::string& Monopoly::Go::getName() const {
  return name;
}

int Monopoly::Go::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Go::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}

const int Monopoly::Go::getSpaceNumber() const {
  return sn;
}

void Monopoly::Go::display() const {
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

void Monopoly::Go::activate(Player& activatingPlayer){
  activatingPlayer.giveCash(salary * (gameState.rules.getSalary_multiplier_for_landing_on_go() - 1));
}