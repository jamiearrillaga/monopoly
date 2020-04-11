#ifndef HOARDINGCPPVERSION_DICEROLLER_H
#define HOARDINGCPPVERSION_DICEROLLER_H
#include <fstream>
#include <string>
#include <vector>
namespace Monopoly {
class DiceRoller {
 public:
  explicit DiceRoller(const std::string& file_name,
                      const int num_dice_rolled = 2,
                      const int min_die_value = 1,
                      const int max_die_value = 6);
  int getDiceRoll(int numDiceToRoll);
  int getDiceRoll();
  bool multiplesRolled() const;
 private:
  std::ifstream file;
  int num_dice_rolled;
  int min_die_value;
  int max_die_value;
  std::vector<int> prev_die_rolls;
  int numConsecutiveMultiplesRolled;
 public:
  int getNumConsecutiveMultiplesRolled() const;
  void setNumConsecutiveMultiplesRolled(int numConsecutiveMultiplesRolled);

};
}

#endif //HOARDINGCPPVERSION_DICEROLLER_H
