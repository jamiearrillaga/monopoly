//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_PROPERTY_H
#define HOARDINGCPPVERSION_PROPERTY_H
#include <string>
#include "CSVReader.h"
#include "Space.h"

namespace Monopoly {
class Player;
class GameState;
class Property : public Space {
 public:
  explicit Property(CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  void setOwner(Player* owner);
  int getSetId() const;
  int getIntraSetId() const;
  int getCost() const;
  int getHouse_cost() const;
  int getHotel_cost() const;
  int getRent() const;
  int getRent_with_house() const;
  int getRent_with_hotel() const;
  Player* getOwner() const;
  std::string getOwnerName() const;
  int calculateRent(const Rules& rules) const;
  int getNumHousesOn() const;
  int getNumHotelsOn() const;
  int getNumUpgrades() const;
  int getValue() const;
  int getLanding_multiplier() const;
  void setLanding_multiplier(int landing_multiplier);
  bool isFullyUpgraded() const;
  bool nextUpgradeIsHouse() const;
  bool nextUpgradeIsHotel() const;
  void upgrade();
  void downgrade();
  std::string getUpgradesString() const;
  int getUpgradeCost() const;
  void setNumHousesOn(int numHousesOn);
  void setNumHotelsOn(int numHotelsOn);
  const std::string& getName() const ;
  const int getSpaceNumber() const ;

    protected:
  virtual void activate(Player& activatingPlayer) ;
  virtual void display() const ;

 private:
  int setId;
  int intraSetId;
  std::string name;
  int cost;
  int house_cost;
  int hotel_cost;
  int rent;
  int rent_with_house;
  int rent_with_hotel;
  Player* owner;
  int landing_multiplier;
  int numHousesOn;
  int numHotelsOn;
  GameState& gameState;
  int sn;
};
}

#endif //HOARDINGCPPVERSION_PROPERTY_H
