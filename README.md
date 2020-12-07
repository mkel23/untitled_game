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

`make game`  
`./play`

## Notes
* It's been a while since I did any C++ development, and when I did, it was purely academic.
* I'm using [Lazy Foo' Productions Beginning Game Programming v2.0](https://lazyfoo.net/tutorials/SDL/index.php) to get started, given the above.
* This is a hobby project, but I'm open to learning, so call me out on my bullshit.

## TODO
What I've thought of so far, obviously going to change FREQUENTLY:

- [ ] Get a background and character movement
- [ ] Clean up Makefile
- [ ] Undecided Game Engine Parts
  - [ ] Extract classes out to their own files
  - [ ] Sound
  - [ ] Texture Loading/Rendering
  - [ ] Input/Controls
  - [ ] Menu System
  - [ ] Saving/Loading
  - [ ] Probably a Dialog System once I decide some story stuff
- [ ] Story
  - [ ] Come up with some basic themes/rules
  - [ ] Decide what "progress" means in the game
    - e.g., does progess mean levels? does progress mean completing the linear story? main story with side quests?
- [ ] Sprite sheet
  - [ ] Get a "guided" sprite sheet up first
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
