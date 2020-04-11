//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_RULES_H
#define HOARDINGCPPVERSION_RULES_H
#include <string>
namespace Monopoly {

class Rules {

 public:
  explicit Rules(const std::string& rulesFileName);

 private:
  int starting_cash;

  int num_dice_rolled;
  int max_dice_value;

  int num_houses_before_hotel;
  bool must_build_evenly;

  int turn_limit;

  int num_players_left_to_end_game;

  int property_set_multiplier;
  bool put_money_in_free_parking;
  bool auction_properties;
  int salary_multiplier_for_landing_on_go;
  int maxDoubleReRolls;
 public:
  int getMaxDoubleReRolls() const;
 private:

  bool is_turn_limit() const;
 public:
  int getStarting_cash() const;
  int getNum_dice_rolled() const;
  int getMax_dice_value() const;
  int getNum_houses_before_hotel() const;
  int getMaxHotels() const;
  bool Must_build_evenly() const;
  int getTurn_limit() const;
  int getNum_players_left_to_end_game() const;
  int getProperty_set_multiplier() const;
  bool isPut_money_in_free_parking() const;
  bool isAuction_properties() const;
  int getSalary_multiplier_for_landing_on_go() const;
  bool isTurnLimit() const;
};
}

#endif //HOARDINGCPPVERSION_RULES_H