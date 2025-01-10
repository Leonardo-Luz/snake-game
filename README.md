# Snake Game

**Author:** Leonardo Luz

[**Repository**](https://github.com/leonardo-luz/snake-game)

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

<details><summary> Preview </summary>

  ![Gameplay](./images/preview.gif)

  <details><summary> Menus </summary>

  1. Main Menu

  ![Main Menu](./images/mainMenu.png)

  2. Pause Menu

  ![Pause Menu](./images/pauseMenu.png)

  3. Game Over Menu

  ![Game Over Menu](./images/gameOverMenu.png)

  4. Controls Menu

  ![Controls Menu](./images/controlsMenu.png)

  5. Scores Menu

  ![Scores Menu](./images/scoresMenu.png)

  6. New Score Menu

  ![New Score Menu](./images/newScoreMenu.png)

  </details>

  <details><summary> Assets </summary>

  1. Head

  ![Snake Head](./assets/head.png)

  2. Body

  ![Snake Body](./assets/body.png)

  3. Tail

  ![Snake Tail](./assets/tail.png)

  4. Apple

  ![Snake Head](./assets/apple.png)

  5. Banana

  ![Snake Head](./assets/banana.png)

  6. Berry

  ![Berry](./assets/berry.png)

  </details>
</details>

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
