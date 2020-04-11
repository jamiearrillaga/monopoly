#ifndef HOARDINGCPPVERSION_PROPERTYSET_H
#define HOARDINGCPPVERSION_PROPERTYSET_H
#include <vector>
#include <map>
#include "Rules.h"
#include "Property.h"


namespace Monopoly {
class Player;
class PropertySet {
 public:
  explicit PropertySet(int setId = -99);
  //explicit PropertySet(const Property& property);
  PropertySet(const PropertySet& orig) = default;
  void incNumPropertiesInSet();
  void addProperty(Property& property);
  void removeProperty(const Property& property);
  void clear();
  bool ownsAll() const;
  const std::vector<Property*>& getProperties() const;
  void updateOwner(Player& newOwner);
  int getValue() const;
  std::vector<Monopoly::Property*> getUpgradeableProperties(const Rules rules, const int available_cash) const ;
  std::vector<Monopoly::Property*> getDowngradeableProperties(const Rules rules) const ;
  virtual ~PropertySet();
 private:
  int setId;
  int numPropertiesInSet;

  int getMinUpgradesOn() const;
  int getMaxUpgradesOn() const;

  std::vector<Property*> properties;
};

}

#endif //HOARDINGCPPVERSION_PROPERTYSET_H