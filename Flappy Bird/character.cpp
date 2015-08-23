#include <iostream>

#include "character.hpp"

// Private

// Public
Character::Character(double xPos, double yPos, double frmeRte) {
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
}

void Character::setSpriteVector(std::vector<sf::Sprite> vector, int vecLeng) {
  activeSpriteVector = vector;
  vectorLength = vecLeng;
  sprite = vector[0];
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

void Character::setState(sf::String state) {
  if (state == "menu") {
    inMenu = true;
  } else {
    inMenu = false;
  }
}

void Character::kill() {
  velocity.x = 0.0;
  velocity.y = 0.0;
  dead = true;
}

void Character::bounce(double bounceFactor) {
  velocity.y = -bounceFactor;
}

void Character::update() {
  sf::Vector2<double> accelerationDueToGravity(0.0, 4.9);
  if (!dead) {
    // Update the active sprite
    double secondsSinceLastSpriteChange = ((double) clock()/CLOCKS_PER_SEC) - timeOfLastSpriteChange;
    if (secondsSinceLastSpriteChange > 1.0/frameRate) {
      activeVectorIndex = (activeVectorIndex+1)%vectorLength;
      sprite = activeSpriteVector[activeVectorIndex];
      
      // If we aren't in a menu, then update our velocity based on gravity
      if (!inMenu) {
        velocity.y += accelerationDueToGravity.y;
        position.x += velocity.x;
        position.y += velocity.y;
      }
      
      timeOfLastSpriteChange = (double) clock()/CLOCKS_PER_SEC;
    }
    
    sprite.setPosition(position.x, position.y); // Make sure the sprite knows where we are
  }
}