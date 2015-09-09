#include "game_obj.hpp"

class Pipe: public Game_obj{
protected:
  sf::Sprite bottomPipe;
  double velocity;
  double gap;
  bool active;
  sf::Rect<int> lowerCollisionBox;
public:
  Pipe(sf::Sprite topPipe, sf::Sprite bottPipe, double xPos, double yPos, double gap, double vel);
  std::vector<sf::Sprite> getSprites();
  
  void setPosition(double, double);
  void setXPos(double);
  void setYPos(double);
  void reactivate();
  
  bool isTouchedBy(sf::Rect<int> collisionBox);
  bool hasBeenPassed(double birdPos);
  bool isOffScreen();
  void update();
};