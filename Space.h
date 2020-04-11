#ifndef HOARDINGCPPVERSION_SPACE_H
#define HOARDINGCPPVERSION_SPACE_H

#include <memory>
#include <vector>

#include "CSVReader.h"
#include "Rules.h"

namespace Monopoly {
class Player;
//class GameState;
enum class SpaceType { goSpace, propertySpace, freeParkingSpace,
  payBankSpace, jailSpace, goToJailSpace };

class Space {
 public:
  static unsigned long length_of_longest_space_name;
  //Space(CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  Space();
  //int getSpaceNumber() const;
  virtual void display() const;
  virtual const std::string& getName() const = 0;
  virtual void activate(Player& activatingPlayer) = 0;
  virtual const int getSpaceNumber() const = 0;
  void addPlayer(Player& player);
  void removePlayer(const Player& player);
  void removeAllPlayers();
  SpaceType getSpaceType() const;
  //GameState& gameState;
 protected:
  std::vector<Player*> playersOnSpace;
 private:
  SpaceType spaceType;
  //int spaceNumber;
};
}

#endif //HOARDINGCPPVERSION_SPACE_H
