// This is essentially a simpler case of Pipe, and could probably just be a Game Obj if Game Obj
// were better abstracted. For now, though, this is quick and dirty and gets the job done.
#include "game_obj.hpp"

class Floor: public Game_obj{
protected:
  sf::Sprite floor_copy;
  double velocity;
public:
  Floor(sf::Sprite topPipe, sf::Sprite floor_cpy, double xPos, double yPos, double vel);
  std::vector<sf::Sprite> getSprites();
  
  void setPosition(double, double);
  void setXPos(double);
  void setYPos(double);
  
  //bool isTouchedBy(sf::Rect<int> collisionBox);
  bool isTouchedBy(sf::Rect<int> otherCollisionBox);
  void update();
};