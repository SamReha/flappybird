#include <iostream>

#include "floor.hpp"
// Private
// Public
Floor::Floor(sf::Sprite floor_main, sf::Sprite floor_cpy, double xPos, double yPos, double vel) {
  sprite = floor_main;
  floor_copy = floor_cpy;
  velocity = vel;
  
  sf::Rect<int> topFloorRect = sprite.getTextureRect();
  sf::Rect<int> bottomFloorRect = floor_copy.getTextureRect();
  
  sprite.setPosition(xPos, yPos);
  floor_copy.setPosition(xPos + bottomFloorRect.width, yPos);
  
  sf::Vector2<double> size;
  size.x = sprite.getTextureRect().width;
  size.y = sprite.getTextureRect().height;
  collisionBox = *new sf::Rect<int>(xPos, yPos, size.x, size.y);
}

std::vector<sf::Sprite> Floor::getSprites() {
  std::vector<sf::Sprite> retVal;
  retVal.push_back(sprite);
  retVal.push_back(floor_copy);
  
  return retVal;
}

void Floor::setPosition(double x, double y) {
  sf::Rect<int> topFloorRect = sprite.getTextureRect();
  
  sprite.setPosition(x, y);
  floor_copy.setPosition(x + topFloorRect.width, y);
}

void Floor::setXPos(double x) {
  sf::Rect<int> topFloorRect = sprite.getTextureRect();
  
  sprite.setPosition(x, sprite.getPosition().y);
  floor_copy.setPosition(x + topFloorRect.width, floor_copy.getPosition().y);
}

void Floor::setYPos(double y) {
  sf::Rect<int> topFloorRect = sprite.getTextureRect();
  
  sprite.setPosition(sprite.getPosition().x, y);
  floor_copy.setPosition(floor_copy.getPosition().x, y);
}

bool Floor::isTouchedBy(sf::Rect<int> otherCollisionBox) {
  if (collisionBox.intersects(otherCollisionBox)) {
    return true;
  } else {
    return false;
  }
}

void Floor::update() {
  sf::Vector2<float> oldSpritePosition = sprite.getPosition();
  sf::Vector2<float> floorCopyPosition = floor_copy.getPosition();
  
  sf::Rect<int> topFloorCol = sprite.getTextureRect();
  sf::Rect<int> floorCopyCol = floor_copy.getTextureRect();
  if (oldSpritePosition.x + topFloorCol.width < 0) {
    oldSpritePosition.x = floorCopyPosition.x + floorCopyCol.width;
  }
  if (floorCopyPosition.x + floorCopyCol.width < 0) {
    floorCopyPosition.x = oldSpritePosition.x + topFloorCol.width;
  }
  
  sprite.setPosition(oldSpritePosition.x - velocity, oldSpritePosition.y);
  floor_copy.setPosition(floorCopyPosition.x - velocity, floorCopyPosition.y);
}
