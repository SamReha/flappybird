#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "AssetManager.hpp"

int main(int, char const**) {
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(288, 512), "SFML window");

  // Set the Icon
  sf::Image icon;
  if (!icon.loadFromFile(resourcePath() + "icon.png")) {
    return EXIT_FAILURE;
  }
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // Load some sprites and textures
  AssetManager assetManager;
  
  sf::Texture world_texture;
  if (!world_texture.loadFromFile(resourcePath() + "world_texture.png")) {
    return EXIT_FAILURE;
  }
  
  std::map<sf::String, sf::Sprite> spriteSet = assetManager.generateSpriteSet(&world_texture);
  spriteSet["day_background"].setPosition(0, 0);
  spriteSet["night_background"].setPosition(0, 0);
  spriteSet["floor"].setPosition(0, 400); // Floor actually moves, so this will need to be dynamic later

  // Create a graphical text to display
  sf::Font font;
  if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
    return EXIT_FAILURE;
  }
  sf::Text text("Hello SFML", font, 50);
  text.setColor(sf::Color::Black);

  // Load a music to play
  sf::Music music;
  if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
    return EXIT_FAILURE;
  }

  // Play the music
  //music.play();
  
  // Set a menu bg and game bg
  sf::Sprite menu_background;
  sf::Sprite game_background;
  
  // initialize random seed:
  srand(time(NULL));
  
  if (rand()%2) {
    menu_background = spriteSet["day_background"];
  } else {
    menu_background = spriteSet["day_background"];
  }
  
  if (rand()%2) {
    game_background = spriteSet["day_background"];
  } else {
    game_background = spriteSet["night_background"];
  }

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // Escape pressed: exit
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        window.close();
      }
    }

    // Update the screen! (perhaps I should make this a function finally)
    // Clear screen
    window.clear();
    
    window.draw(menu_background);
    window.draw(spriteSet["floor"]);
    window.draw(spriteSet["game_over"]);
    
    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}
