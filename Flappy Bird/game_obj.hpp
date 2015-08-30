// Heads up, you should probably never instantiate a maze_obj!
#include <SFML/Graphics.hpp>

#pragma once

class Game_obj {
protected:
  sf::Sprite sprite;
  sf::Vector2<double> position;
  sf::Rect<int> collisionBox;
public:
  sf::Sprite getSprite();
  sf::Vector2<double> getPosition();
  double getXPos();
  double getYPos();
  sf::Rect<int> getCollisionBox();
  
  void setPosition(double, double);
  void setXPos(double);
  void setYPos(double);
  void setSprite(sf::Sprite spr);
};