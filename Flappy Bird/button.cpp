#include "button.hpp"

Button::Button(sf::Vector2<double> sze, sf::Vector2<double> pos, sf::Sprite spr, sf::Rect<double> collBox) {
  position = pos;
  size = sze;
  sprite = spr;
  sprite.setPosition(pos.x, pos.y);
  collisionBox = collBox;
}

// Private

// Public
void Button::setPosition(sf::Vector2<double> newPosition) {
  sprite.setPosition(newPosition.x, newPosition.y);
  collisionBox.left = newPosition.x;
  collisionBox.top = newPosition.y;
}

bool Button::isClicked(sf::Vector2<double> clickPosition) {
  return collisionBox.contains(clickPosition);
}
