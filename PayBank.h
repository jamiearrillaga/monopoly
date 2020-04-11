#ifndef HOARDINGCPPVERSION_PAYBANK_H
#define HOARDINGCPPVERSION_PAYBANK_H
#include <string>
#include "CSVReader.h"
#include "Space.h"

namespace Monopoly {
class GameState;
class PayBank : public Space {
 public:
  explicit PayBank(CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  int getAmount() const;
  const std::string& getName() const;
  const int getSpaceNumber() const;
    protected:
  virtual void display() const;
  virtual void activate(Player& activatingPlayer);
 private:
  int amount;
  std::string name;
  GameState& gameState;
  int sn;
};
}

#endif //HOARDINGCPPVERSION_FREEPARKING_H
