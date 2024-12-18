# Snake Game

**Author:** Leonardo Luz <br/>
_Fullstack Developer_ <br/>
[**Repository**](https://github.com/leonardo-luz/snake-game) <br/>

[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-blue?style=flat-square)](LICENSE.md)
[![DOCUMENTATION](https://img.shields.io/badge/DOCUMENTATION-GITHUB-blue?style=flat-square)](README.md)

## Summary
1. [Description](#Description)
2. [Preview](#Preview)
3. [Requirements](#Requirements)
4. [Installation](#Installation)
5. [License](#License)

## Description

This project is a recreation of the classic Snake game, where the player controls a snake that grows longer with each food consumed. The game ends if the snake collides with the wall or itself. Special foods trigger specific effects, and the game tracks score and highscore, providing a competitive edge for players. The game includes multiple menus like Start, Pause, and Game Over, with a rich visual interface featuring images for foods and the snake.

## Preview

![Gameplay](./images/preview.gif)

### Menus

1. Main Menu <br/>
![Main Menu](./images/mainMenu.png)
2. Pause Menu <br/>
![Pause Menu](./images/pauseMenu.png)
3. Game Over Menu <br/>
![Game Over Menu](./images/gameOverMenu.png)
4. Controls Menu <br/>
![Controls Menu](./images/controlsMenu.png)
5. Scores Menu <br/>
![Scores Menu](./images/scoresMenu.png)
6. New Score Menu <br/>
![New Score Menu](./images/newScoreMenu.png)

### Assets

1. Head <br/>
![Snake Head](./assets/head.png)

2. Body <br/>
![Snake Body](./assets/body.png)

3. Tail <br/>
![Snake Tail](./assets/tail.png)

4. Apple <br/>
![Snake Head](./assets/apple.png)

5. Banana <br/>
![Snake Head](./assets/banana.png)

6. Berry <br/>
![Berry](./assets/berry.png)

## Requirements

- **OS**: Ubuntu
- **Dependencies**:
  - Raylib (for game development)
  - GCC (GNU Compiler Collection)
  - Make (for build automation)

### Installation

To install the necessary dependencies, run the following commands:

```
sudo apt install make gcc

```
After installing make and gcc, you will also need to install the Raylib library. <br/>
You can follow the official installation instructions for Raylib [here](https://www.raylib.com/).

#### Clone Repository
```
git clone https://github.com/leonardo-luz/snake-game
cd snake-game
```

#### Build & Run
```
make
./game
```

### License
This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.
