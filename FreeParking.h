#ifndef HOARDINGCPPVERSION_FREEPARKING_H
#define HOARDINGCPPVERSION_FREEPARKING_H
#include <string>
#include "CSVReader.h"
#include "Space.h"

namespace Monopoly {
class GameState;
  class FreeParking : public Space{
   public:
    explicit FreeParking(CSVReader& boardFile, const int spaceNumber, GameState& gameState);
    const std::string& getName() const;
    const int getSpaceNumber() const;
   protected:
    virtual void display() const;
    virtual void activate(Player& activatingPlayer);
   private:
    std::string name;
    GameState& gameState;
    int sn;
  };
}

#endif //HOARDINGCPPVERSION_FREEPARKING_H
