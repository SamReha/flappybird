#include "game_obj.hpp"

class Pipe: public Game_obj{
protected:
  sf::Sprite bottomPipe;
  double velocity;
  double gap;
public:
  Pipe(sf::Sprite topPipe, sf::Sprite bottPipe, double xPos, double yPos, double gap, double vel);
  std::vector<sf::Sprite> getSprites();
  bool isTouchedBy(sf::Rect<int> collisionBox);
  bool hasBeenPassed(double prevPos, double currentPos);
  void update();
};