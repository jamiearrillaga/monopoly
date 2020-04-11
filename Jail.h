#ifndef HOARDINGCPPVERSION_JAIL_H
#define HOARDINGCPPVERSION_JAIL_H
#include <string>
#include "CSVReader.h"
#include "Space.h"
namespace Monopoly {
class GameState;
class Jail : public Space {
 public:
  explicit Jail(CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  int getTurnsInJail() const;
  int getCost() const;
  const std::string& getName() const;
  virtual void activate(Player &activatingPlayer);
  GameState& gameState;
  bool leave(Player &activatingPlayer);
  int getMove(Player &activatingPlayer);
  const int getSpaceNumber() const;
    protected:
  virtual void display() const;
 private:
  int turnsInJail;
  int cost;
  std::string name;
  int sn;
  void pay(Player &activatingPlayer);
  void move(Player &activatingPlayer);
};
}

#endif //HOARDINGCPPVERSION_FREEPARKING_H
