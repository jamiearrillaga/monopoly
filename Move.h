#ifndef HOARDINGCPPVERSION_MOVE_H
#define HOARDINGCPPVERSION_MOVE_H

#include "DiceRoller.h"
#include "Rules.h"

namespace Monopoly {
enum class MoveAction { rollDice = 1, buyUpgrade = 2, sellUpgrade = 3, leaveGame = 4, stayInJail, ERROR };
class Move {
 public:
  static int MoveActionToInt(MoveAction action);
  Move();
  MoveAction getAction() const;
  Move(const int moveNumber);
  bool endsTurn(const DiceRoller& diceRoller, const Rules& rules);
 private:
  MoveAction action;
};
}

#endif //HOARDINGCPPVERSION_MOVE_H
