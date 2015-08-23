#include "game_obj.hpp"

#pragma once

class Character: public Game_obj {
protected:
  std::vector<sf::Sprite> activeSpriteVector;
  int vectorLength;
  int activeVectorIndex;
  double timeOfLastSpriteChange;
  double frameRate;
  
  bool dead;
  bool inMenu;
  
  sf::Vector2<double> velocity;
public:
  Character(double xPos, double yPos, double frmeRte);
  void setSpriteVector(std::vector<sf::Sprite>, int vecLeng);
  void setVelocity(sf::Vector2<double> newVelocity);
  void setXVel(double newX);
  void setYVel(double newY);
  
  sf::Vector2<double> getVelocity();
  double getXVel();
  double getYVel();
  sf::String getDirection();
  
  void setState(sf::String state);
  void kill();
  void bounce(double bounceFactor);
  
  void update();
};