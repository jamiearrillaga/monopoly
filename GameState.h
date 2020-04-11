#ifndef HOARDINGCPPVERSION_GAMESTATE_H
#define HOARDINGCPPVERSION_GAMESTATE_H
#include <vector>
#include <string>
#include <fstream>
#include <memory>

#include "Rules.h"
#include "Move.h"
#include "Board.h"
#include "DiceRoller.h"
#include "Player.h"


namespace Monopoly {
class GameState {
  //friend Space;
 public:
  static std::vector<std::string> get_player_names();
  GameState(const std::string& RulesFileName,
            const std::string& BoardFileName,
            const std::string& RandomFileName,
            const std::vector<std::string>& playerNames);

  void playGame();
  bool isGameOver() const;
  Player& getCurrentPlayer();
  void make_move(Player& player, Move& move);
  void declareWinner();
  void changeTurn();
  void removeFromGame(Player& player);
  void auction(Property& property);
  void jail_roll(Player& player);

  void display() const;
  Rules rules;
  Board board;
  void appendFreePark(int num);
  int getFreePark() const;
  void resetFreePark();
  void buyUpgrade();
  void sellUpgrade();
  void rollDice(Monopoly::Player& player);

 private:
  DiceRoller diceRoller;
  int turn_count;
  unsigned long player_turn;
  std::vector<std::unique_ptr<Player> > players;
  int freeParkPool=0;
};
}

#endif //HOARDINGCPPVERSION_GAMESTATE_H
