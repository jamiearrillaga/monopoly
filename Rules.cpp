#include "Rules.h"
#include <fstream>

Monopoly::Rules::Rules(const std::string& rulesFileName) : num_dice_rolled(2), max_dice_value(6) {
  std::ifstream rulesFile(rulesFileName);
  std::string header, temp;

  std::getline(rulesFile, header, ':');
  rulesFile >> starting_cash;

  std::getline(rulesFile, header, ':');
  rulesFile >> turn_limit;

  std::getline(rulesFile, header, ':');
  rulesFile >> num_players_left_to_end_game;

  std::getline(rulesFile, header, ':');
  rulesFile >> property_set_multiplier;

  std::getline(rulesFile, header, ':');
  rulesFile >> num_houses_before_hotel;

  std::getline(rulesFile, header, ':');
  rulesFile >> temp;
  must_build_evenly = temp == "Yes";

  std::getline(rulesFile, header, ':');
  rulesFile >> temp;
  put_money_in_free_parking = temp == "Yes";

  std::getline(rulesFile, header, ':');
  rulesFile >> temp;
  auction_properties = temp == "Yes";

  std::getline(rulesFile, header, ':');
  rulesFile >> salary_multiplier_for_landing_on_go;

  std::getline(rulesFile, header, ':');
  rulesFile >> maxDoubleReRolls;

}

bool Monopoly::Rules::is_turn_limit() const {
  return turn_limit != -1;
}

int Monopoly::Rules::getStarting_cash() const {
  return starting_cash;
}

int Monopoly::Rules::getNum_dice_rolled() const {
  return num_dice_rolled;
}

int Monopoly::Rules::getMax_dice_value() const {
  return max_dice_value;
}

int Monopoly::Rules::getNum_houses_before_hotel() const {
  return num_houses_before_hotel;
}

int Monopoly::Rules::getMaxHotels() const {
  return 1;
}

bool Monopoly::Rules::Must_build_evenly() const {
  return must_build_evenly;
}

int Monopoly::Rules::getTurn_limit() const {
  return turn_limit;
}

int Monopoly::Rules::getNum_players_left_to_end_game() const {
  return num_players_left_to_end_game;
}

int Monopoly::Rules::getProperty_set_multiplier() const {
  return property_set_multiplier;
}

bool Monopoly::Rules::isPut_money_in_free_parking() const {
  return put_money_in_free_parking;
}

bool Monopoly::Rules::isAuction_properties() const {
  return auction_properties;
}

int Monopoly::Rules::getSalary_multiplier_for_landing_on_go() const {
  return salary_multiplier_for_landing_on_go;
}

bool Monopoly::Rules::isTurnLimit() const {
  return turn_limit != -1;
}

int Monopoly::Rules::getMaxDoubleReRolls() const {
  return maxDoubleReRolls;
}