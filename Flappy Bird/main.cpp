#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "AssetManager.hpp"
#include "character.hpp"
#include "button.hpp"

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
  spriteSet["floor"].setPosition(0, 400); // Floor actually moves, so this will need to be dynamic later
  spriteSet["title"].setPosition(55, 150);
  
  // Load unincorporated sprites
  // Loading sprites off a single texture is tedious and difficult - so I broke some off into seperate
  // files to make loading easier. If I have time, I'll incorporate these sprites into the asset manager
  // but for now, they'll clutter up my code like this.
  sf::Texture blue_one_texture;
  if (!blue_one_texture.loadFromFile(resourcePath() + "other_textures/blue_one_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite blue_one(blue_one_texture);
  
  sf::Texture blue_two_texture;
  if (!blue_two_texture.loadFromFile(resourcePath() + "other_textures/blue_two_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite blue_two(blue_two_texture);
  
  sf::Texture blue_three_texture;
  if (!blue_three_texture.loadFromFile(resourcePath() + "other_textures/blue_three_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite blue_three(blue_three_texture);
  
  sf::Texture red_one_texture;
  if (!red_one_texture.loadFromFile(resourcePath() + "other_textures/red_one_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite red_one(red_one_texture);
  
  sf::Texture red_two_texture;
  if (!red_two_texture.loadFromFile(resourcePath() + "other_textures/red_two_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite red_two(red_two_texture);
  
  sf::Texture red_three_texture;
  if (!red_three_texture.loadFromFile(resourcePath() + "other_textures/red_three_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite red_three(red_three_texture);
  
  sf::Texture yellow_one_texture;
  if (!yellow_one_texture.loadFromFile(resourcePath() + "other_textures/yellow_one_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite yellow_one(yellow_one_texture);
  
  sf::Texture yellow_two_texture;
  if (!yellow_two_texture.loadFromFile(resourcePath() + "other_textures/yellow_two_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite yellow_two(yellow_two_texture);
  
  sf::Texture yellow_three_texture;
  if (!yellow_three_texture.loadFromFile(resourcePath() + "other_textures/yellow_three_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite yellow_three(yellow_three_texture);
  
  sf::Texture start_texture;
  if (!start_texture.loadFromFile(resourcePath() + "other_textures/start_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite start_spr(start_texture);
  
  sf::Texture instruction_texture;
  if (!instruction_texture.loadFromFile(resourcePath() + "other_textures/instruction_texture.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite instruction(instruction_texture);
  instruction.setPosition(87, 207);

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
  
  // initialize random seed (this is used for chosing assets that change randomly):
  srand(time(NULL));
  
  // Set a menu bg and game bg
  sf::Sprite menu_background;
  sf::Sprite game_background;
  std::vector<sf::Sprite> birdSpriteVector;
  
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
  
  if (rand()%3 == 0) {
    birdSpriteVector.push_back(blue_one);
    birdSpriteVector.push_back(blue_two);
    birdSpriteVector.push_back(blue_three);
    birdSpriteVector.push_back(blue_two);
  } else if (rand()%3 == 1) {
    birdSpriteVector.push_back(yellow_one);
    birdSpriteVector.push_back(yellow_two);
    birdSpriteVector.push_back(yellow_three);
    birdSpriteVector.push_back(yellow_two);
  } else {
    birdSpriteVector.push_back(red_one);
    birdSpriteVector.push_back(red_two);
    birdSpriteVector.push_back(red_three);
    birdSpriteVector.push_back(red_two);
  }
  
  // Let's create some objects that will be of great use during the game
  char gameState = 'm';
  bool showInstructions = true;
  Character bird(127, 250, 24);
  bird.setSpriteVector(birdSpriteVector, 4);
  
  sf::Vector2<double> startButtonPosition(86, 343);
  sf::Vector2<double> startButtonSize(116, 68);
  Button startButton(startButtonSize, startButtonPosition, start_spr, sf::Rect<double>(startButtonPosition, startButtonSize));
  
  sf::Mouse mouse;
  sf::Vector2<int> mousePos;

  // Start the game loop
  double secondsSinceLastFrame;
  double timeOfLastFrame = 1;
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }
    }
    
    // Hard lock the game at 60 FPS!
    secondsSinceLastFrame = ((double) clock()/CLOCKS_PER_SEC) - timeOfLastFrame;
    if (secondsSinceLastFrame > 1.0/60.0) {
      switch (gameState) {
        // Case M: The menu state
        case 'm':
          // Update logic!
          bird.update();
          if (mouse.isButtonPressed(sf::Mouse::Button::Left)) {
            mousePos = mouse.getPosition(window);
            if (startButton.isClicked(sf::Vector2<double>(mousePos.x, mousePos.y))) {
              gameState = 'g';
              bird.setPosition(85, 230);
            }
          }

          // Update the screen!
          // Clear screen
          window.clear();
    
          window.draw(menu_background);
          window.draw(spriteSet["floor"]);
          window.draw(spriteSet["title"]);
    
          window.draw(bird.getSprite());
          window.draw(startButton.getSprite());
    
          // Update the window
          window.display();
          break;
        // Case G: The gameplay state
        case 'g':
          // Update logic!
          // Check for keyboard events
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            showInstructions = false;
            bird.setState("game");
            bird.bounce(20.0);
          }
          bird.update();
          // Update the screen!
          // Clear screen
          window.clear();
          
          window.draw(menu_background);
          window.draw(spriteSet["floor"]);
          
          window.draw(bird.getSprite());
          
          if (showInstructions) {
            window.draw(instruction);
          }
          
          // Update the window
          window.display();
          break;
        default:
          break;
      }
      
      timeOfLastFrame = (double) clock()/CLOCKS_PER_SEC;
    }
  }

  return EXIT_SUCCESS;
}
