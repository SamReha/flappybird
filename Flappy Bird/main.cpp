#include <random>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "AssetManager.hpp"
#include "character.hpp"
#include "button.hpp"
#include "pipe.hpp"
#include "floor.hpp"

const int PIPE_SPACING = 150;
const int PLAYFIELD_HEIGHT = 100;
const double BOUNCE_FACTOR = 6.0;
const double ACCEL_DUE_TO_GRAVITY = 0.4;
const double SPEED = 2.5;
const double GAP_WIDTH = 90;
const double STARTING_POSITION = 750;

int main(int, char const**) {
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(288, 512), "Flappy Bird");
  
  // Let's get at least something on the screen while the player waits for loading and setup to be over
  // Load some sprites and textures
  AssetManager assetManager;
  
  sf::Texture world_texture;
  if (!world_texture.loadFromFile(resourcePath() + "world_texture.png")) {
    return EXIT_FAILURE;
  }
  
  std::map<sf::String, sf::Sprite> spriteSet = assetManager.generateSpriteSet(&world_texture);
  spriteSet["floor"].setPosition(0, 400); // Floor actually moves, so this will need to be dynamic later
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
  
  window.draw(menu_background);
  window.draw(spriteSet["floor"]);
  window.display();

  // Set the Icon
  sf::Image icon;
  if (!icon.loadFromFile(resourcePath() + "icon.png")) {
    return EXIT_FAILURE;
  }
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  
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
  
  sf::Texture topPipe_texture;
  if (!topPipe_texture.loadFromFile(resourcePath() + "other_textures/green_pipe_up.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite topPipe(topPipe_texture);
  
  sf::Texture bottomPipe_texture;
  if (!bottomPipe_texture.loadFromFile(resourcePath() + "other_textures/green_pipe_down.png")) {
    return EXIT_FAILURE;
  }
  sf::Sprite bottomPipe(bottomPipe_texture);

  // Create a graphical text to display
  sf::Font font;
  if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
    return EXIT_FAILURE;
  }
  sf::Text text("Score: 0", font, 50);
  text.setColor(sf::Color::Black);
  
  // Load a music to play
  sf::Music music;
  if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
    return EXIT_FAILURE;
  }

  // Play the music
  //music.play();
  
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
  Character bird(127, 250, 24, ACCEL_DUE_TO_GRAVITY);
  bird.setSpriteVector(birdSpriteVector, 4);
  
  sf::Vector2<double> startButtonPosition(86, 343);
  sf::Vector2<double> startButtonSize(116, 68);
  Button startButton(startButtonSize, startButtonPosition, start_spr, sf::Rect<double>(startButtonPosition, startButtonSize));
  
  spriteSet["title"].setPosition(55, 150);
  spriteSet["game_over"].setPosition(50, 150);
  
  sf::Mouse mouse;
  sf::Vector2<int> mousePos;
  
  // Configure rand numbers for pipe positions
  srand(0);
  Pipe pipe1(topPipe, bottomPipe, STARTING_POSITION, rand()%PLAYFIELD_HEIGHT, GAP_WIDTH, SPEED);
  std::vector<sf::Sprite> pipe1Sprites;
  Pipe pipe2(topPipe, bottomPipe, STARTING_POSITION + PIPE_SPACING, rand()%PLAYFIELD_HEIGHT, GAP_WIDTH, SPEED);
  std::vector<sf::Sprite> pipe2Sprites;
  Pipe pipe3(topPipe, bottomPipe, STARTING_POSITION + 2*PIPE_SPACING, rand()%PLAYFIELD_HEIGHT, GAP_WIDTH, SPEED);
  std::vector<sf::Sprite> pipe3Sprites;
  
  Floor floor(spriteSet["floor"], spriteSet["floor_copy"], 0, 400, SPEED);
  std::vector<sf::Sprite> floorSprites;

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
    
    // Hard lock the game at 60 FPS! - there is a more patternistic way of doing this w/ SFML's time tools.
    secondsSinceLastFrame = ((double) clock()/CLOCKS_PER_SEC) - timeOfLastFrame;
    if (secondsSinceLastFrame > 1.0/60.0) {
      // You know what would work better than this switch case? A Scene object that bundles all non-global data together into a single chunk that
      // could be loaded or unloaded with a single function call. Scene objects would then have draw methods that accept a window object as a param
      // in order to encapsulate drawing and update logic. Saves the cycles spent figuring out which state we're in, plus it'll look cleaner.
      switch (gameState) {
        // Case M: The menu state
        case 'm':
          // Update logic!
          bird.update();
          if (mouse.isButtonPressed(sf::Mouse::Button::Left)) {
            mousePos = mouse.getPosition(window);
            if (startButton.isClicked(sf::Vector2<double>(mousePos.x, mousePos.y))) {
              gameState = 'g';
              bird.setPosition(79, 230);
            }
          }

          // Update the screen!
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
            bird.bounce(BOUNCE_FACTOR);
          }
          bird.update();
          
          if (!showInstructions) {
            pipe1.update();
            pipe2.update();
            pipe3.update();
            floor.update();
            
            if (pipe1.isOffScreen()) {
              pipe1.setXPos(pipe3.getXPos() + PIPE_SPACING);
              pipe1.setYPos(rand()%PLAYFIELD_HEIGHT);
              pipe1.reactivate();
            }
            if (pipe2.isOffScreen()) {
              pipe2.setXPos(pipe1.getXPos() + PIPE_SPACING);
              pipe2.setYPos(rand()%PLAYFIELD_HEIGHT);
              pipe2.reactivate();
            }
            if (pipe3.isOffScreen()) {
              pipe3.setXPos(pipe2.getXPos() + PIPE_SPACING);
              pipe3.setYPos(rand()%PLAYFIELD_HEIGHT);
              pipe3.reactivate();
            }

            if (pipe1.hasBeenPassed(bird.getXPos()) || pipe2.hasBeenPassed(bird.getXPos()) || pipe3.hasBeenPassed(bird.getXPos())) {
              bird.incrementScore();
              text.setString("Score: " + std::to_string(bird.getScore()));
            }
          }
              
          if (floor.isTouchedBy(bird.getCollisionBox()) ||
              pipe1.isTouchedBy(bird.getCollisionBox()) ||
              pipe2.isTouchedBy(bird.getCollisionBox()) ||
              pipe3.isTouchedBy(bird.getCollisionBox())) {
            bird.kill();
            bird.setState("menu");
            gameState = 'o';
          }
          
          pipe1Sprites = pipe1.getSprites();
          pipe2Sprites = pipe2.getSprites();
          pipe3Sprites = pipe3.getSprites();
          floorSprites = floor.getSprites();
          // Update the screen!
          window.clear();
          
          window.draw(game_background);
          
          window.draw(bird.getSprite());
          
          window.draw(pipe1Sprites[0]);
          window.draw(pipe1Sprites[1]);
          
          window.draw(pipe2Sprites[0]);
          window.draw(pipe2Sprites[1]);
          
          window.draw(pipe3Sprites[0]);
          window.draw(pipe3Sprites[1]);
          
          window.draw(floorSprites[0]);
          window.draw(floorSprites[1]);
          
          window.draw(text);
          
          if (showInstructions) {
            window.draw(instruction);
          }
          
          // Update the window
          window.display();
          break;
        // Cast O: the game-over state
        case 'o':
          // Update logic!
          if (mouse.isButtonPressed(sf::Mouse::Button::Left)) {
            mousePos = mouse.getPosition(window);
            if (startButton.isClicked(sf::Vector2<double>(mousePos.x, mousePos.y))) {
              gameState = 'g';
              bird.setPosition(79, 230);
              bird.setScore(0);
              bird.revive();
              text.setString("Score: " + std::to_string(bird.getScore()));
              showInstructions = true;
              
              // Reroll the game background
              if (rand()%2) {
                game_background = spriteSet["day_background"];
              } else {
                game_background = spriteSet["night_background"];
              }
              
              // Reset the pipes
              srand(0);
              pipe1.setPosition(STARTING_POSITION, rand()%PLAYFIELD_HEIGHT);
              pipe2.setPosition(STARTING_POSITION + PIPE_SPACING, rand()%PLAYFIELD_HEIGHT);
              pipe3.setPosition(STARTING_POSITION + 2*PIPE_SPACING, rand()%PLAYFIELD_HEIGHT);
            }
          }
          
          // Update the screen!
          window.clear();
          
          window.draw(game_background);
          window.draw(bird.getSprite());
          
          window.draw(pipe1Sprites[0]);
          window.draw(pipe1Sprites[1]);
          
          window.draw(pipe2Sprites[0]);
          window.draw(pipe2Sprites[1]);
          
          window.draw(pipe3Sprites[0]);
          window.draw(pipe3Sprites[1]);
          
          window.draw(spriteSet["floor"]);
          window.draw(startButton.getSprite());
          window.draw(spriteSet["game_over"]);
          
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
