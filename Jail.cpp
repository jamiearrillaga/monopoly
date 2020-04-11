#include "Jail.h"
#include <iostream>
#include "Player.h"
#include "GameState.h"

Monopoly::Jail::Jail(CSVReader& boardFile, const int spaceNumber, GameState& gameState) :
    gameState(gameState) {
  name = boardFile.get_next_field();
  turnsInJail = boardFile.get_next_field_as_int();
  cost = boardFile.get_next_field_as_int();
  sn = spaceNumber;
}

int Monopoly::Jail::getTurnsInJail() const {
  return turnsInJail;
}

int Monopoly::Jail::getCost() const {
  return cost;
}

const std::string& Monopoly::Jail::getName() const {
  return name;
}

void Monopoly::Jail::display() const {
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

const int Monopoly::Jail::getSpaceNumber() const {
  return sn;
}

void Monopoly::Jail::activate(Player &activatingPlayer) {
  if(!activatingPlayer.getInJail() && activatingPlayer.getTimeLeftInJail()==-1)
    return;
  if (!activatingPlayer.getInJail()) {
    activatingPlayer.setInJail(true);
    return;
  }
  if (activatingPlayer.getTimeLeftInJail() == 0) {
    pay(activatingPlayer);
    return;
  } else {
    std::cout << activatingPlayer.getName() << " you are in jail for " << activatingPlayer.getTimeLeftInJail()
              << " turns." << std::endl;
    if (activatingPlayer.getCash() >= cost) {
      if (leave(activatingPlayer)) {
        move(activatingPlayer);
        return;
      } else {
        move(activatingPlayer);
      }
    }
    else {
      std::cout << activatingPlayer.getName() << " please enter your move " << std::endl;
      move(activatingPlayer);
    }
  }
}

void Monopoly::Jail::move(Player &activatingPlayer){
  int move=-1;
  while(move==2 || move==3 || move==-1) {
    move = getMove(activatingPlayer);
    if (move == 1){
      if (activatingPlayer.getInJail())
        gameState.jail_roll(activatingPlayer);
      else
        gameState.rollDice(activatingPlayer);
    } else if (move == 2)
      gameState.buyUpgrade();
    else if (move == 3)
      gameState.sellUpgrade();
    else if (move == 4)
      gameState.removeFromGame(activatingPlayer);
  }
}

bool Monopoly::Jail::leave(Player &activatingPlayer){
  char choice;
  std::cout << "Would you like to pay $" << cost << " to leave jail early?" << std::endl;
  std::cout << "y for yes and n for no: " << activatingPlayer.getName() << " please enter your move" << std::endl;
  std::cin >> choice;
  choice = static_cast<char>(tolower(choice));
  if (choice == 'y') {
    activatingPlayer.payBank(cost);
    gameState.appendFreePark(cost);
    activatingPlayer.setInJail(false);
    activatingPlayer.setTimeInJail(-1);
    return true;
  }
  return false;
}

int Monopoly::Jail::getMove(Player &activatingPlayer){
  int move_number;
  std::cout << Move::MoveActionToInt(MoveAction::rollDice) << " to roll dice" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::buyUpgrade)
            << " to upgrade a property with a house or hotel" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::sellUpgrade)
            << " to sell a house or hotel" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::leaveGame) << " to leave the game" << std::endl;
  std::cout << "Your move: ";
  std::cin >> move_number;
  return move_number;
}

void Monopoly::Jail::pay(Player &activatingPlayer){
  activatingPlayer.avoidBankruptcy(cost, gameState.rules);
  if(activatingPlayer.getCash() >= cost) {
    std::cout << activatingPlayer.getName() << ", you had to pay $" << cost << " to get out of jail" << std::endl;
    gameState.appendFreePark(cost);
    activatingPlayer.giveCash(-cost);
    activatingPlayer.setInJail(false);
    activatingPlayer.setTimeInJail(-1);
    std::cout << activatingPlayer.getName() << " please enter your move ";
    move(activatingPlayer);
  } else {
    activatingPlayer.giveCash(-cost);
    std::cout << activatingPlayer.getName() << " went bankrupt when paying to leave jail" << std::endl;
    gameState.removeFromGame(activatingPlayer);
    activatingPlayer.setInJail(false);
    activatingPlayer.setTimeInJail(-1);
  }
}