#ifndef HOARDINGCPPVERSION_GOTOJAIL_H
#define HOARDINGCPPVERSION_GOTOJAIL_H
#include <string>
#include "CSVReader.h"
#include "Space.h"
namespace Monopoly {
class GameState;
class GoToJail : public Space {
 public:
  explicit GoToJail(CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  int getIndex() const;
  const int getSpaceNumber() const;
    protected:
  virtual const std::string& getName() const;
  virtual void display() const ;
  virtual void activate(Player &activatingPlayer);
 private:
  int index;
  std::string name;
  GameState& gameState;
  int sn;
};
}

#endif //HOARDINGCPPVERSION_FREEPARKING_H