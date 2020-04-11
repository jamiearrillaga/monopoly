#include "Player.h"
#include <iostream>
#include <cctype>
#include "Jail.h"
#include "GameState.h"

unsigned long Monopoly::Player::length_of_longest_player_name;

Monopoly::Player::Player(int id,
                         const std::string& name,
                         int cash,
                         Space* spaceOn,
                         const PropertyManager& propertyManager)
    : id(id), name(name), cash(cash), spaceOn(spaceOn), propertyManager(propertyManager) {
}

const std::string& Monopoly::Player::getName() const {
  return name;
}

int Monopoly::Player::getCash() const {
  return cash;
}

void Monopoly::Player::setCash(int cash) {
  Player::cash = cash;
}

void Monopoly::Player::giveCash(const int amount) {
  cash += amount;
}

Monopoly::Move Monopoly::Player::getMove() {
  if(inJail){
    current_move = Move(Move::MoveActionToInt(MoveAction::stayInJail));
    return current_move;
  }
  int move_number;
  std::cout << name << " please enter your move" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::rollDice) << " to roll dice" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::buyUpgrade)
            << " to upgrade a property with a house or hotel" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::sellUpgrade)
            << " to sell a house or hotel" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::leaveGame) << " to leave the game" << std::endl;
  std::cout << "Your move: ";
  std::cin >> move_number;
  current_move = Move(move_number);
  return current_move;
}

void Monopoly::Player::display() {
  std::cout << '[' << name << " : $" << cash << ']';
}

int Monopoly::Player::getId() const {
  return id;
}
bool Monopoly::Player::getInJail() {
  return inJail;
}
void Monopoly::Player::setInJail(bool set) {
  inJail = set;
}
void Monopoly::Player::setTimeInJail(int num){
  timeLeftInJail = num;
}
int Monopoly::Player::getTimeLeftInJail() const {
  return timeLeftInJail;
}
void Monopoly::Player::offerLeaveJail(){
  Jail* jail = dynamic_cast<Jail*>(spaceOn);
  char choice;
  std::cout << name << " you are in jail for " << getTimeLeftInJail() << " turns." << std::endl;
  if (getCash() >= jail->getCost()) {
    std::cout << "Would you like to pay $50 to leave jail early?" << std::endl;
    std::cout << "y for yes and n for no: " << name << " please enter your move" << std::endl;
    std::cin >> choice;
    choice = static_cast<char>(tolower(choice));
    if (choice == 'y') {
      payBank(jail->getCost());
      jail->gameState.appendFreePark(jail->getCost());
      setInJail(false);
    }
  }
}

Monopoly::Space& Monopoly::Player::getSpaceOn() {
  return *spaceOn;
}

void Monopoly::Player::setOn(Space& space, bool activateSpace) {
  this->spaceOn = &space;
  space.addPlayer(*this);

  if (activateSpace) {
    space.activate(*this);
  }
}

void Monopoly::Player::moveTo(Monopoly::Space& space, bool activateSpace) {
  spaceOn->removePlayer(*this);
  setOn(space);
}

bool Monopoly::Player::getBuyDecision(const Monopoly::Property& property) const {
  char choice;
  std::cout << "Would you like to buy " << property.getName() << " for $" << property.getCost() << '?' << std::endl;
  std::cout << "Rent on " <<property.getName() << " is $" << property.getRent() << std::endl;
  std::cout << "Enter y for yes or n for no: ";
  std::cin >> choice;
  choice = static_cast<char>(tolower(choice));
  if (!(choice == 'y' || choice == 'n')) {
    std::cout << "Unknown choice of " << choice << " received for buy decision" << std::endl;
    return false;
  }
  return choice == 'y';
}

void Monopoly::Player::purchase(Property& property, const int amount) {
  cash -= amount;
  property.setOwner(this);
  propertyManager.takeOwnershipOf(property);
}

void Monopoly::Player::payPlayer(int amount, Monopoly::Player& owner, const Property& propertyOn, const Rules& rules) {
  avoidBankruptcy(amount, rules);
  if (cash >= amount) {
    cash -= amount;
    owner.cash += amount;

    std::cout << name << " paid " << owner.name << " $" << amount << " for landing on " << propertyOn.getName()
              << std::endl;
  } else {
    owner.cash += cash;
    cash -= amount;
    propertyManager.givePropertiesTo(owner.propertyManager); // give all of our properties to the player we owe
    owner.propertyManager.updateOwner(owner); // the player we are paying to now owns all those properties
    std::cout << name << " went bankrupt to " << owner.name << " for landing on " << propertyOn.getName() << std::endl;;
  }
}

void Monopoly::Player::decreaseTimeInJail(){
  timeLeftInJail--;
}

void Monopoly::Player::avoidBankruptcy(const int amount, const Rules& rules){
  unsigned long sell_num;
  std::vector<Property*> downgradeableProperties = getDowngradeableProperties(rules);
  while(cash< amount && downgradeableProperties.size() > 0){
    std::cout << "You have $" << cash << " but you owe $" << amount << std::endl;
    std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
    for (unsigned long i = 0; i < downgradeableProperties.size(); ++i) {
      std::cout << i << ". " << downgradeableProperties.at(i)->getName() << " [$"
                << downgradeableProperties.at(i)->getUpgradeCost()  / 2<< "]" << std::endl;
    }
    std::cout << "Your choice: ";
    std::cin >> sell_num;
    downgradeableProperties.at(sell_num)->downgrade();
    downgradeableProperties = getDowngradeableProperties(rules);
  }
}

void Monopoly::Player::payBank(const int amount) {
  cash -= amount;
}

bool Monopoly::Player::ownsAllPropertiesInSet(const int setId) const {
  return propertyManager.ownsEntireSet(setId);
}

/**
 * Update all the references to this player so that they actually point to this player
 */
void Monopoly::Player::refreshReferencesTo() {
  propertyManager.updateOwner(*this);
  spaceOn->addPlayer(*this);
}

Monopoly::Player::~Player() {
  //spaceOn->removePlayer(*this);
}

int Monopoly::Player::getNetWorth() const {
  return cash + propertyManager.getValue();
}

std::vector<Monopoly::Property*> Monopoly::Player::getUpgradeableProperties(const Rules& rules) const {
  return propertyManager.getUpgradeableProperties(rules, cash);
}

std::vector<Monopoly::Property*> Monopoly::Player::getDowngradeableProperties(const Monopoly::Rules& rules) const {
  return propertyManager.getDowngradeableProperties(rules);
}