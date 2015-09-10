#include "pipe.hpp"
// Private
// Public
Pipe::Pipe(sf::Sprite topPipe, sf::Sprite bottPipe, double xPos, double yPos, double gp, double vel) {
  sprite = topPipe;
  bottomPipe = bottPipe;
  position.x = xPos;
  position.y = yPos;
  gap = gp;
  velocity = vel;
  active = true;
  
  sf::Rect<int> topPipeRect = sprite.getTextureRect();
  sf::Rect<int> bottomPipeRect = bottomPipe.getTextureRect();
  
  sprite.setPosition(position.x, position.y-((gap + topPipeRect.height)/2.0));
  bottomPipe.setPosition(position.x, position.y+((gap + bottomPipeRect.height)/2.0));
}

std::vector<sf::Sprite> Pipe::getSprites() {
  std::vector<sf::Sprite> retVal;
  retVal.push_back(sprite);
  retVal.push_back(bottomPipe);
  
  return retVal;
}

void Pipe::setPosition(double x, double y) {
  position.x = x;
  position.y = y;
  sf::Rect<int> topPipeRect = sprite.getTextureRect();
  
  sprite.setPosition(x, y-((gap + topPipeRect.height)/2.0));
  bottomPipe.setPosition(x, y+((gap + topPipeRect.height)/2.0));
}

void Pipe::setXPos(double x) {
  position.x = x;
  sprite.setPosition(x, sprite.getPosition().y);
  bottomPipe.setPosition(x, bottomPipe.getPosition().y);
}

void Pipe::setYPos(double y) {
  position.y = y;
  sf::Rect<int> topPipeRect = sprite.getTextureRect();
  
  sprite.setPosition(sprite.getPosition().x, y-((gap + topPipeRect.height)/2.0));
  bottomPipe.setPosition(bottomPipe.getPosition().x, y+((gap + topPipeRect.height)/2.0));
}

void Pipe::reactivate() {
  active = true;
}

bool Pipe::isTouchedBy(sf::Rect<int> otherCollisionBox) {
  sf::Vector2<double> size;
  size.x = sprite.getTextureRect().width;
  size.y = sprite.getTextureRect().height;
  collisionBox = *new sf::Rect<int>(sprite.getPosition().x, sprite.getPosition().y, size.x, size.y);
  
  sf::Vector2<double> lowerPipeSize;
  lowerPipeSize.x = bottomPipe.getTextureRect().width;
  lowerPipeSize.y = bottomPipe.getTextureRect().height;
  lowerCollisionBox = *new sf::Rect<int>(bottomPipe.getPosition().x, bottomPipe.getPosition().y, lowerPipeSize.x, lowerPipeSize.y);
  
  if (collisionBox.intersects(otherCollisionBox) || lowerCollisionBox.intersects(otherCollisionBox)) {
    return true;
  } else {
    return false;
  }
}

bool Pipe::hasBeenPassed(double birdPos) {
  if (active && birdPos > position.x) {
    active = false;
    return true;
  } else return false;
}

bool Pipe::isOffScreen() {
  sf::Rect<int> topPipeCol = sprite.getTextureRect();
  if (position.x + topPipeCol.width < 0) {
    return true;
  } else return false;
}

void Pipe::update() {
  sf::Vector2<float> oldSpritePosition = sprite.getPosition();
  sf::Vector2<float> oldBottomPipePosition = bottomPipe.getPosition();

  position.x -= velocity;
  sprite.setPosition(position.x, oldSpritePosition.y);
  bottomPipe.setPosition(position.x, oldBottomPipePosition.y);
}
