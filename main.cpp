#include <vector>
#include <string>

#include "GameState.h"
int main(int argc, char** argv) {
  auto player_names = Monopoly::GameState::get_player_names();
  //Monopoly::GameState gameState(argv[1], argv[2], argv[3], player_names);
  Monopoly::GameState gameState("files/CampusRules.txt", "files/CampusBoard.csv", "files/RandomNums10000.txt", player_names);
  gameState.playGame();
  return 0;
}
