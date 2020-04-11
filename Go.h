#ifndef HOARDINGCPPVERSION_GO_H
#define HOARDINGCPPVERSION_GO_H

#include <string>
#include "CSVReader.h"
#include "Player.h"
#include "Space.h"

namespace Monopoly {
class GameState;
class Go : public Space{
 public:
  explicit Go(CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  int getSalary() const;
 private:
  int salary;
  int landing_multiplier;
  std::string name;
  GameState& gameState;
 public:
  int getLanding_multiplier() const;
  void setLanding_multiplier(int landing_multiplier);
  const std::string& getName() const;
  const int getSpaceNumber() const;
 protected:
  virtual void activate(Player& activatingPlayer);
  virtual void display() const;
  int sn;
};
}

#endif //HOARDINGCPPVERSION_GO_H
