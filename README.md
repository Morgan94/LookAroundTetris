# OpenGL Project LookAroundTetris


**Dev team :** Braem Quentin, Lacherez Sylvain, Lemiere Morgan and Binet Benjamin

**Team leader :** Lacherez Sylvain

### Folder contents
* **OwnFromScratch :** FromScratch demo
* **TetrisMain** :
    * **GameLogic**   
    * **GamePhysic** 
    * **lib** : Hakurei library (copyright LookAroundTetris Team), IrrKlang (audio library). 
    * **resources** : audio files, shaders, textures and objects.
    
### Ongoing modifications
High Score and Time currently displayed in console will be displayed in game window.  

### Execution
    You need OpenGL and GLFW to play this game.
    Compile and launch in a folder "build" created in the TetrisMain folder (to access properly the resources). 
    
    shell instructions:
        cd yourpath/TetrisMain 
        mkdir build
        cd build
        cmake ..
        make
        ./LookAroundTetris


## Overview
 *  **Title :** LookAroundTetris
 *  **Goal :**  Try to do the best score before the end of the game.
            The game will end when blocks touch the upper point of the cylinder.
            
 *  **Feature :**   
    * Manual and intuitive control
    * Preview of the next tetromino
    * Possibility of speed up the tetromino
    * Pause mode

#### **Controls :**

| Key | Action  |
|---|---|
|Key left| Rotate to the left  | 
|Key right| Rotate to the right  |
|Key down| Speed up the tetromino  |  
|Space| Rotate the tetromino  |   
|Esc| Quit Game  |   
|P| Pause  |

## GamePlay :

LookAroundTetris is a single player game.
The goal is to complete rows with tetrominos that drop from the top of the screen. When a row is full, it disappears, and after 5 rows destroyed, the player level up and the difficulty increase.
The score of the player increase when he destroy rows and when he speed up tetrominos with key down

## Tetrominos :

There is 7 different tetriminos in LookAroundTetris : 

![tetrominos Image](http://gitlab.ecole.ensicaen.fr/lacherez/LookAroundTetris/blob/master/TetrisMain/resources/TetrisSS.png)

These tetrominos will pop randomly during the game. The player is able to see the next tetromino in a small preview at the upper left corner of the screen.


## Technical details (Viewport configuration) : 

The viewport is composed of a single area with the cylinder at the center. Tetrominos continuously fall down from the top of the cylinder.
At the upper left corner, the next falling shape is displayed.

## Technical details (Rendering) :

* "Title" screen and main music.
* One positional light source, placed at eye-level.
* Fading of blocks upon completion of a row.
* Rotation of the falling block and the camera are synchronized.
* Blocks are falling down when the game is over. 
* "Game over" screen and music.
* Current score and final score is displayed in console.

