#include <SFML/Graphics.hpp>
#include "game_obj.hpp"

class Button: public Game_obj{
private:
  sf::Vector2<double> size, position;
  sf::Rect<double> collisionBox;
public:
  Button(sf::Vector2<double> size, sf::Vector2<double> pos, sf::Sprite spr, sf::Rect<double> collBox);
  
  void setPosition(sf::Vector2<double>);  // Sets the button to a specific position (x, y)
  bool isClicked(sf::Vector2<double>);    // returns true if the given (x, y) is within the button
};