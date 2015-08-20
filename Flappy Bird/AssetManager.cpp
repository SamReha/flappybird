#include "AssetManager.hpp"

// Private

// Public
AssetManager::AssetManager() {
}

std::map<sf::String, sf::Sprite> AssetManager::generateSpriteSet(sf::Texture* tileset_texture) {
  sf::Sprite day_background(*tileset_texture, sf::Rect<int>(0, 0, 288, 512));
  assetDict["day_background"] = day_background;
  
  sf::Sprite night_background(*tileset_texture, sf::Rect<int>(292, 0, 288, 512));
  assetDict["night_background"] = night_background;
  
  sf::Sprite floor(*tileset_texture, sf::Rect<int>(584, 0, 288, 112));
  assetDict["floor"] = floor;
  
  sf::Sprite title(*tileset_texture, sf::Rect<int>(702, 182, 178, 48));
  assetDict["title"] = title;
  
  sf::Sprite get_ready(*tileset_texture, sf::Rect<int>(584, 114, 196, 62));
  assetDict["get_ready"] = get_ready;
  
  sf::Sprite game_over(*tileset_texture, sf::Rect<int>(784, 114, 204, 62));
  assetDict["game_over"] = game_over;
  
  return assetDict;
}