#ifndef HOARDINGCPPVERSION_BOARD_H
#define HOARDINGCPPVERSION_BOARD_H
#include <vector>
#include <string>
#include "Space.h"
#include "Rules.h"

namespace Monopoly {
class Space;
class GameState;
class Board {
 public:
  Board(const std::string& boardFileName, GameState& gameState);
  void display() const;
  Space& getSpace(int spaceNum);
  Space& getGoSpace();
  int getNumSpaces() const;
  const std::vector<std::unique_ptr<Space>>& getSpaces() const;
  void removeAllPlayers();
  std::unique_ptr<Space> factory(CSVReader &boardFile);
  void addSpace(std::unique_ptr<Monopoly::Space> space);
 private:
  std::vector<std::unique_ptr<Space>> spaces;
  unsigned long calc_length_of_longest_space_name() const;
};
}

#endif //HOARDINGCPPVERSION_BOARD_H
