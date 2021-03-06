#include <iostream>

#include "character.hpp"

// Private
double clamp(double value, double min, double max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else return value;
}

// Public
Character::Character(double xPos, double yPos, double frmeRte, double accelDueToGravity) {
  position.x = xPos;
  position.y = yPos;
  frameRate = frmeRte;
  
  velocity.x = 0.0;
  velocity.y = 0.0;
  
  dead = false;
  inMenu = true;
  
  activeVectorIndex = 0;
  timeOfLastSpriteChange = -1.0;
  sprite.setPosition(xPos, yPos);
  score = 0;
  
  accelerationDueToGravity = *new sf::Vector2<double>(0.0, accelDueToGravity);
}

void Character::setSpriteVector(std::vector<sf::Sprite> vector, int vecLeng) {
  activeSpriteVector = vector;
  vectorLength = vecLeng;
  sprite = vector[0];
  
  sf::Vector2<double> size;
  size.x = sprite.getTextureRect().width;
  size.y = sprite.getTextureRect().height;
  collisionBox = *new sf::Rect<int>(position.x, position.y, size.x, size.y);
}

void Character::setVelocity(sf::Vector2<double> newVelocity) {
  velocity = newVelocity;
}

sf::Vector2<double> Character::getVelocity() {
  return velocity;
}

double Character::getXVel() {
  return velocity.x;
}

double Character::getYVel() {
  return velocity.y;
}

int Character::getScore() {
  return score;
}

bool Character::touchingFloor() {
  if (position.y > 368) {
    return true;
  } else return false;
}

void Character::setState(sf::String state) {
  if (state == "menu") {
    inMenu = true;
  } else {
    inMenu = false;
  }
}

void Character::setScore(int newScore) {
  score = newScore;
}

void Character::incrementScore() {
  score += 1;
}

void Character::decrementScore() {
  score -= 1;
}

void Character::kill() {
  velocity.x = 0.0;
  velocity.y = 0.0;
  dead = true;
}

void Character::revive() {
  dead = false;
}

void Character::bounce(double bounceFactor) {
  velocity.y = -bounceFactor;
}

void Character::update() {
  if (!dead) {
    // Update the active sprite
    double secondsSinceLastSpriteChange = ((double) clock()/CLOCKS_PER_SEC) - timeOfLastSpriteChange;
    if (secondsSinceLastSpriteChange > 1.0/frameRate) {
      if (!inMenu && velocity.y > 0) {  // If we're actively playing, make sure to only animate when flapping upwards
        sprite = activeSpriteVector[1];
      } else {
        activeVectorIndex = (activeVectorIndex+1)%vectorLength;
        sprite = activeSpriteVector[activeVectorIndex];
      }
      
      timeOfLastSpriteChange = (double) clock()/CLOCKS_PER_SEC;
    }
    
    // If we aren't in a menu, then update our velocity based on gravity
    if (!inMenu) {
      velocity.y += accelerationDueToGravity.y;
      position.x += velocity.x;
      position.y += velocity.y;
      position.y = clamp(position.y + velocity.y, -50, 1000);
    }
    
    sprite.setPosition(position.x, position.y); // Make sure the sprite knows where we are
    sf::Vector2<double> size;
    size.x = sprite.getTextureRect().width;
    size.y = sprite.getTextureRect().height;
    collisionBox = *new sf::Rect<int>(position.x, position.y, size.x, size.y);
  }
}