OpenGL Project LookAroundTetris

New tree :
Files are now in TetrisMain :
- GameLogic (old, don't use it)
- GamePhysic
- lib (framework up to date, please use it instead of fromScratch's)
- new CMakeLists (use it to compile main.cpp)
- main.cpp (provisional, can be used for testing)


/!\ Update 24/03/2016 /!\
~~~ Flemme d'écrire en anglais ~~~

Mise à jour du framework:
- Fonctions de Callback reliées à la caméra pour les entrées clavier
- Quelques modifications mineures
Mise à jour de la game physic:
- Tetris_3DBloc décrit un bloc dans l'environnement 3D
- Tetris_Shape est la classe manipulant des formes construites à partir de blocs (2 formes disponibles pour le moment)
- /!\ Aucun lien avec la game logic pour l'instant
- Nouveau CMakeLists (ajout de Tetris_3DBloc dans GAME_PHYSIC)
- quelques tests dans le main.cpp


