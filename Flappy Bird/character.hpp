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

  int score;

  sf::Vector2<double> velocity;
  sf::Vector2<double> accelerationDueToGravity;
public:
  Character(double xPos, double yPos, double frmeRte, double accelDueToGravity);
  void setSpriteVector(std::vector<sf::Sprite>, int vecLeng);
  void setVelocity(sf::Vector2<double> newVelocity);
  void setXVel(double newX);
  void setYVel(double newY);
  void setState(sf::String state);
  void setScore(int newScore);
  void incrementScore();
  void decrementScore();
  
  sf::Vector2<double> getVelocity();
  double getXVel();
  double getYVel();
  int getScore();
  
  bool touchingFloor();
  
  void kill();
  void revive();
  void bounce(double bounceFactor);
  
  void update();
};