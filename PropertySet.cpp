//
// Created by mfbut on 1/27/2018.
//

#include "PropertySet.h"

Monopoly::PropertySet::PropertySet(int setId) : setId(setId), numPropertiesInSet(1) {}

/*
Monopoly::PropertySet::PropertySet(const Monopoly::Property& property) :
    setId(property.getSetId()), numPropertiesInSetOwned(0){
  properties.push_back(&property);
}
*/

void Monopoly::PropertySet::incNumPropertiesInSet() {
  numPropertiesInSet++;
}

/**
 * Does a sorted insert of the property into the set based on the intraset id
 * @param property
 */
void Monopoly::PropertySet::addProperty(Monopoly::Property& property) {

  // not a part of the set so don't add it in
  if (property.getSetId() != setId) {
    return;
  }

  auto propItr = properties.cbegin();

  //locate insertion position
  for (; propItr != properties.cend(); ++propItr) {
    if (property.getIntraSetId() < (*propItr)->getIntraSetId()) {
      break;
    }
  }
  //add it in
  properties.insert(propItr, &property);
}

void Monopoly::PropertySet::removeProperty(const Monopoly::Property& property) {
  // not a part of the set so don't can't remove it
  if (property.getSetId() != setId) {
    return;
  }

  auto propItr = properties.cbegin();

  //locate insertion position
  for (; propItr != properties.cend(); ++propItr) {
    if (property.getIntraSetId() == (*propItr)->getIntraSetId()) {
      properties.erase(propItr);
      return;
    }
  }
}

void Monopoly::PropertySet::clear() {
  properties.clear();
}

bool Monopoly::PropertySet::ownsAll() const {
  return static_cast<int>(properties.size()) == numPropertiesInSet;
}

const std::vector<Monopoly::Property*>& Monopoly::PropertySet::getProperties() const {
  return properties;
}

void Monopoly::PropertySet::updateOwner(Monopoly::Player& newOwner) {
  for (auto& propertyPtr : properties) {
    propertyPtr->setOwner(&newOwner);
  }
}

Monopoly::PropertySet::~PropertySet() {
  /*
   * Since property sets
   */
  for (auto& property : properties) {
    if (property) {
      property->setOwner(nullptr);
      property->setNumHotelsOn(0);
      property->setNumHousesOn(0);
    }
  }
}

int Monopoly::PropertySet::getValue() const {
  int value = 0;
  for (const auto& property : properties) {
    value += property->getValue();
  }
  return value;
}

std::vector<Monopoly::Property*> Monopoly::PropertySet::getUpgradeableProperties(const Rules rules,
                                                                                 const int available_cash) const {
  std::vector<Monopoly::Property*> upgradeableProperties;
  if (ownsAll()) {
    const int minUpgradesOn = getMinUpgradesOn();

    for (const auto& property : properties) {
      if (property->isFullyUpgraded()) { // fully upgraded
        continue; // can't upgrade it anymore
      } else if (available_cash < property->getUpgradeCost()) { //can't afford upgrade
        continue; // can't buy upgrade
      } else if (rules.Must_build_evenly()) {
        if (property->getNumUpgrades() == minUpgradesOn) {
          upgradeableProperties.push_back(property);
        }
      } else {
        upgradeableProperties.push_back(property);
      }
    }
  }
  return upgradeableProperties;
}

int Monopoly::PropertySet::getMinUpgradesOn() const {
  if(properties.size() == 0){
    return 0;
  }else {

    int minUpgrades = properties.front()->getNumUpgrades();
    for (const auto& property : properties) {
      if (property->getNumUpgrades() < minUpgrades) {
        minUpgrades = property->getNumUpgrades();
      }
    }
    return minUpgrades;
  }
}

int Monopoly::PropertySet::getMaxUpgradesOn() const {
  int maxUpgrades = 0;
  for (const auto& property : properties) {
    if (property->getNumUpgrades() > maxUpgrades) {
      maxUpgrades = property->getNumUpgrades();
    }
  }
  return maxUpgrades;
}


std::vector<Monopoly::Property*> Monopoly::PropertySet::getDowngradeableProperties(const Monopoly::Rules rules) const {
  std::vector<Monopoly::Property*> downGradeableProperties;
  if (ownsAll()) {
    const int maxUpgradesOn = getMaxUpgradesOn();

    for (const auto& property : properties) {
      if (property->getNumUpgrades() > 0) {
        if (rules.Must_build_evenly()) {
          if (property->getNumUpgrades() == maxUpgradesOn) {
            downGradeableProperties.push_back(property);
          }
        } else {
          downGradeableProperties.push_back(property);
        }
      }
    }
  }
  return downGradeableProperties;
}