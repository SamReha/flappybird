#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>

class AssetManager {
private:
  std::map<sf::String, sf::Sprite> assetDict;
public:
  AssetManager();
  
  void setWidth(int newWidth);
  std::map<sf::String, sf::Sprite> generateSpriteSet(sf::Texture* tileset_texture);
};