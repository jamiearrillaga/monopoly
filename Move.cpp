#include "Move.h"
#include <iostream>

Monopoly::Move::Move() : action(MoveAction::ERROR) {}

Monopoly::Move::Move(const int moveNumber) {
  if (moveNumber == static_cast<int>(MoveAction::rollDice)) {
    action = MoveAction::rollDice;
  } else if (moveNumber == static_cast<int>(MoveAction::buyUpgrade)) {
    action = MoveAction::buyUpgrade;
  } else if (moveNumber == static_cast<int>(MoveAction::sellUpgrade)) {
    action = MoveAction::sellUpgrade;
  } else if (moveNumber == static_cast<int>(MoveAction::leaveGame)) {
    action = MoveAction::leaveGame;
  } else if (moveNumber == static_cast<int>(MoveAction::stayInJail)) {
    action = MoveAction::stayInJail;
  } else {
    action = MoveAction::ERROR;
    std::cout << "Unrecognized move number " << moveNumber << " in Move constructor" << std::endl;
  }
}

bool Monopoly::Move::endsTurn(const DiceRoller& diceRoller, const Rules& rules) {
  if (action == MoveAction::leaveGame || action == MoveAction::stayInJail) {
    return true;
  } else if (action == MoveAction::rollDice) {
    return !(diceRoller.multiplesRolled()
        && diceRoller.getNumConsecutiveMultiplesRolled() <= rules.getMaxDoubleReRolls());
  } else {
    return false;
  }
}

Monopoly::MoveAction Monopoly::Move::getAction() const {
  return action;
}

int Monopoly::Move::MoveActionToInt(Monopoly::MoveAction action) {
  return static_cast<int>(action);
}

