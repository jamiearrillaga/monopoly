//
// Created by mfbut on 1/23/2018.
//

#include "DiceRoller.h"
#include "MonopolyUtility.h"

Monopoly::DiceRoller::DiceRoller(const std::string& file_name,
                                 const int num_dice_rolled,
                                 const int min_die_value,
                                 const int max_die_value)
    : file(file_name),
      num_dice_rolled(num_dice_rolled),
      min_die_value(min_die_value),
      max_die_value(max_die_value),
      numConsecutiveMultiplesRolled(0) {}

/**
 * Roll the specified number of dice and return their sum
 * @param numDiceToRoll
 * @return
 */
int Monopoly::DiceRoller::getDiceRoll(int numDiceToRoll) {
  int num = 0;
  prev_die_rolls.clear();
  for (int i = 0; i < numDiceToRoll; ++i) {
    file >> num;
    num = min_die_value + (num % (max_die_value - min_die_value + 1));
    prev_die_rolls.push_back(num);
  }
  if(multiplesRolled()){
    numConsecutiveMultiplesRolled++;
  } else{
    numConsecutiveMultiplesRolled = 0;
  }

  return Utility::vector_sum(prev_die_rolls);
}

int Monopoly::DiceRoller::getDiceRoll() {
  return getDiceRoll(num_dice_rolled);
}

/**
 * Check if any multiples were rolled in the previous roll
 * @return
 */
bool Monopoly::DiceRoller::multiplesRolled() const {
  for (auto die1 = prev_die_rolls.cbegin(); die1 != prev_die_rolls.cend(); ++die1) {
    for (auto die2 = die1 + 1; die2 != prev_die_rolls.cend(); ++die2) {
      if (*die1 == *die2) {
        return true;
      }
    }
  }
  return false;
}

int Monopoly::DiceRoller::getNumConsecutiveMultiplesRolled() const {
  return numConsecutiveMultiplesRolled;
}

void Monopoly::DiceRoller::setNumConsecutiveMultiplesRolled(int numConsecutiveMultiplesRolled) {
  DiceRoller::numConsecutiveMultiplesRolled = numConsecutiveMultiplesRolled;
}


