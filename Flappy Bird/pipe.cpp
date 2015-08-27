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
  
  sf::Rect<int> topPipeRect = sprite.getTextureRect();
  sf::Rect<int> bottomPipeRect = bottomPipe.getTextureRect();
  
  sprite.setPosition(position.x, position.y-((gap+ topPipeRect.height)/2.0));
  bottomPipe.setPosition(position.x, position.y+((gap+ bottomPipeRect.height)/2.0));
}

std::vector<sf::Sprite> Pipe::getSprites() {
  std::vector<sf::Sprite> retVal;
  retVal.push_back(sprite);
  retVal.push_back(bottomPipe);
  
  return retVal;
}

bool Pipe::isTouchedBy(sf::Rect<int> collisionBox) {
  sf::Rect<int> topPipeCol = sprite.getTextureRect();
  sf::Rect<int> bottomPipeCol = bottomPipe.getTextureRect();
  
  if (topPipeCol.intersects(collisionBox) || bottomPipeCol.intersects(collisionBox)) {
    return true;
  } else {
    return false;
  }
}

bool Pipe::hasBeenPassed(double prevPos, double currentPos) {
  if (prevPos < position.x && currentPos >= position.x) {
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
