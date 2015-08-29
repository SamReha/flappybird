#include "game_obj.hpp"

// Protected

// Public
sf::Sprite Game_obj::getSprite() {
  return sprite;
}

sf::Vector2<double> Game_obj::getPosition() {
  return position;
}

double Game_obj::getXPos() {
  return position.x;
}

double Game_obj::getYPos() {
  return position.y;
}

void Game_obj::setPosition(double x, double y) {
  position = sf::Vector2<double>(x, y);
  sprite.setPosition(x, y);
}

void Game_obj::setXPos(double x) {
  position.x = x;
  sprite.setPosition(position.x, position.y);
}
void Game_obj::setYPos(double y) {
  position.y = y;
  sprite.setPosition(position.x, position.y);
}

void Game_obj::setSprite(sf::Sprite spr) {
  sprite = spr;
}