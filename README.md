# Untitled Game

## Idea
So I've always wanted to dabble in game dev, but never got past choosing a language/framework. It's untitled for now and the ideas are still rolling in, but here's the gist:

* I loved playing Runescape growing up, and my favorite part was the skill progression through the game. I want to bring most of these into my game and maybe a few new ones.
* I don't want to overwhelm myself dev-wise, so I'm sticking with 2D and turn based combat. Really, I'm going to be basing this off of another pinnacle childhood game for me: Pokemon.
* Everything after that is undecided. I have no story, I have no art style, I have no time period. This will all come later, for now I just want to get something that runs.

Some part of me would love to:
* make the code myself (this repo)
* make the music/sound effects myself
* make the graphics myself
* put this game on hardware that I build myself
* put that hardware in a case the I design/3D print myself

but...I gotta start with the first one, which is a lot, based on my ideas and TODO list below.

## Makefile
Yeah...I know. It's not the greatest right now, but will update to (hopefully) be portable. Right now, I'm on macOS Catalina 10.15.1 and using Homebrew to install these SDL packages.

I've decided to just keep using Make for now, and revisit CMake or SCons later, instead of wasting my time on portability, but not actually getting anything done.

`make game`  
`./play`

## Notes
* It's been a while since I did any C++ development, and when I did, it was purely academic.
* I'm using [Lazy Foo' Productions Beginning Game Programming v2.0](https://lazyfoo.net/tutorials/SDL/index.php) to get started, given the above.
* This is a hobby project, but I'm open to learning, so call me out on my bullshit.

* Current assets found here (this will most likely change, just wanted to get something going for once): [https://opengameart.org/content/16xx16-tileset-pokemonzelda-styled](https://opengameart.org/content/16xx16-tileset-pokemonzelda-styled)
* Font found here: [https://www.dafont.com/early-gameboy.font](https://www.dafont.com/early-gameboy.font)

## TODO
What I've thought of so far, obviously going to change FREQUENTLY:

- [X] Get a background and character movement
- [ ] Add `using namespace std` to files to clean some of that up
- [ ] Some sort of entity dictionary? (json or yml)
- [ ] Some sort of level/door dictionary to map level files and coordinates
- [ ] Might be nice to get the texture name strings out to a constant (can't do inline because that's C++17, but maybe something cleaner than extern)
- [X] Clean up Makefile
  - [ ] Look into CMake/SCons
  - [ ] Find a better (read: more portable) way to deal with SDL dependencies (Conan?)
- [X] Separate globals/functions in `main.cpp` to Game class
- [X] Start using vectors, idk why I haven't been doing that before :shrug:
- [X] Grid Based Movement (a la Pokemon)
  - [X] Figure nice way to hold down key to keep moving, but stop during next tile when released
- [ ] Undecided Game Engine Parts
  - [X] Extract classes out to their own files
  - [X] Game State
  - [ ] Sound
    - [ ] Menu Button sounds
  - [X] Texture Loading/Rendering
    - [ ] Change map data to allow for "doors"
    - [X] Level/Map class to deal with loading up tiles/maps
    - [ ] Level Editor to help with making new environments
    - [ ] Deal w/ doors and other levels/maps...can we learn how to do some sort of transition?
  - [X] Input/Controls
    - [X] Movement
    - [X] Decide if we want mouse support, or everything keyboard? Leaning keyboard only
  - [ ] Menu System
    - [X] Main Menu
    - [X] Pause Menu
    - [ ] Controls Menu (just display and esc for back)
    - [X] Extract Menu component out
      - [X] Function to add buttons (say, text and font only). Handles spacing and everything
      - [X] Add hover effects to buttons
      - [ ] Display menu title
  - [X] Saving/Loading (can only save when not in combat)
    - [X] X and Y position
    - [X] Player Direction
    - [ ] Map/Level state
    - [X] Hook up menu buttons
  - [X] NotificationManager
    - [X] Game saved successfully
    - [ ] Maybe useful when adding something to inventory? Like +1 and the item pic?
    - [ ] Also for quest completion/etc.
  - [X] Potentially a TextureManager? Could "register" textures by name, then call the texture by name and have it render in a coord? Useful for when things are getting duped a lot/moved around between classes
  - [ ] Probably a Dialog System once I decide some story stuff
- [ ] Story
  - [ ] Come up with some basic themes/rules
  - [ ] Decide what "progress" means in the game
    - e.g., does progess mean levels? does progress mean completing the linear story? main story with side quests?
- [ ] Sprite sheet
  - [X] Get a simple sprite sheet up first
  - [X] Directional Idle sprites
  - [ ] Actually get my own sprites going
- [ ] Combat
  - [ ] Combat skill/style based on RS vs turn based combat a la pokemon
- [ ] Inventory/Items
  - [ ] Build an inventory system
  - [ ] Build a character equipment system
  - [ ] Create item types
- [ ] Currency System
- [ ] Skills
  - [ ] Crafting
  - [ ] Mining
  - [ ] Smithing
  - [ ] Fishing
  - [ ] Cooking
  - [ ] Firemaking
  - [ ] Woodcutting
  - [ ] Magic
  - [ ] Farming
  - [ ] Construction
  - [ ] Herblore
  - [ ] Thieving
  - [ ] Fletching
  - [ ] Agility/Hunter/Slayer?
  - [ ] Decide on new skills (maybe get some cyberpunk inspired stuff?)
  - [ ] Combat sklls depending on combat system
  - [ ] Linear skills like RS or skill trees/point system like Elder Scrolls/Witcher/Horizon Zero Dawn, etc.
- [ ] Controller Support
  - I would love to eventually try to put this on some hardware that I would build myself
