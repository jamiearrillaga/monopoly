#include "PayBank.h"
#include <iostream>
#include "Player.h"
#include "GameState.h"

Monopoly::PayBank::PayBank(CSVReader& boardFile, const int spaceNumber, GameState& gameState) :
    gameState(gameState) {
  name = boardFile.get_next_field();
  amount = boardFile.get_next_field_as_int();
  sn = spaceNumber;
}

int Monopoly::PayBank::getAmount() const {
  return amount;
}

const std::string& Monopoly::PayBank::getName() const {
  return name;
}

void Monopoly::PayBank::display() const {
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

const int Monopoly::PayBank::getSpaceNumber() const {
  return sn;
}

void Monopoly::PayBank::activate(Player &activatingPlayer) {
  if (activatingPlayer.getCash() > amount){
    activatingPlayer.payBank(amount);
    gameState.appendFreePark(amount);
    std::cout << activatingPlayer.getName() << " paid the bank $" << amount << " for landing on " << name << std::endl;
  } else {
    activatingPlayer.avoidBankruptcy(amount, gameState.rules);
    activatingPlayer.payBank(amount);
    if (activatingPlayer.getCash() >= amount) {
      std::cout << name << " paid the bank $" << amount << " for landing on " << name << std::endl;
    } else {
      std::cout << activatingPlayer.getName() << " went bankrupt by landing on " << name << std::endl;
    }
    gameState.appendFreePark(amount);
  }
}