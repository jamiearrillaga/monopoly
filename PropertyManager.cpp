//
// Created by mfbut on 1/27/2018.
//

#include "PropertyManager.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

Monopoly::PropertyManager::PropertyManager(const Monopoly::Board& board) {
  Property* property;
  for (const auto& space : board.getSpaces()) {
    property = dynamic_cast<Property *>(space.get());
    if(property) {
      if (propertySets.count(property->getSetId()) == 0) {
        propertySets[property->getSetId()] = PropertySet(property->getSetId());
      } else {
        propertySets.at(property->getSetId()).incNumPropertiesInSet();
      }
    }
  }
}

void Monopoly::PropertyManager::takeOwnershipOf(Monopoly::Property& property) {
  propertySets.at(property.getSetId()).addProperty(property);
}

/**
 * Move all of the properties within the property set into this
 * property manager. Leaves the given propertySet empty
 * @param propertySet
 */
void Monopoly::PropertyManager::takeOwnershipOf(Monopoly::PropertySet& propertySet) {
  for (const auto& property : propertySet.getProperties()) {
    takeOwnershipOf(*property);
  }
  propertySet.clear();
}

bool Monopoly::PropertyManager::ownsEntireSet(const int setId) const {
  return propertySets.at(setId).ownsAll();
}

void Monopoly::PropertyManager::givePropertiesTo(Monopoly::PropertyManager& receiver) {
  for (auto& propertySet : propertySets) {
    receiver.takeOwnershipOf(propertySet.second); // second is the actual property. first is the property set id
  }
}

void Monopoly::PropertyManager::updateOwner(Monopoly::Player& newOwner) {
  for (auto& propertySet : propertySets) {
    propertySet.second.updateOwner(newOwner);
  }
}

int Monopoly::PropertyManager::getValue() const {
  int value = 0;

  for (const auto& propertySet : propertySets) {
    value += propertySet.second.getValue();
  }
  return value;
}

std::vector<Monopoly::Property*> Monopoly::PropertyManager::getUpgradeableProperties(const Rules& rules,
                                                                                     const int available_cash) const {
  std::vector<Property*> upgradeableProperties;
  for (const auto& propertySet: propertySets) {
    std::vector<Property*> addableProperties = propertySet.second.getUpgradeableProperties(rules, available_cash);
    upgradeableProperties.insert(upgradeableProperties.cend(), addableProperties.cbegin(), addableProperties.cend());
  }
  return upgradeableProperties;
}

std::vector<Monopoly::Property*> Monopoly::PropertyManager::getDowngradeableProperties(const Monopoly::Rules& rules) const {
  std::vector<Property*> downgradeableProperties;
  for (const auto& propertySet: propertySets) {
    std::vector<Property*> addableProperties = propertySet.second.getDowngradeableProperties(rules);
    downgradeableProperties.insert(downgradeableProperties.cend(), addableProperties.cbegin(), addableProperties.cend());
  }
  return downgradeableProperties;
}


