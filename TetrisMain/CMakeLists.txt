cmake_minimum_required(VERSION 2.6)

project(myOwnFramework)
enable_testing()

###  Settings  ###{{{
set(CMAKE_CXX_FLAGS "-std=c++11 -DGL_GLEXT_PROTOTYPES -I/opt/X11/include") # Don't forget to define GL_GLEXT_PROTOTYPES to ensure that the glCreateShader and other prototypes are declared. Note we could do it in the main file via "#define GL_GLEXT_PROTOTYPES" before "#include <GL/glext.h>"
## setting build type to debug
add_compile_options(-DUSE_FRAMEWORK__HAKUREI)
set(CMAKE_CXX_FLAGS_DEBUG "-O3")
set(CMAKE_BUILD_TYPE DEBUG)
LINK_DIRECTORIES("~/local_install/lib")
LINK_DIRECTORIES("/usr/local/lib")
INCLUDE_DIRECTORIES("/usr/local/include")
INCLUDE_DIRECTORIES("~/local_install/include")
INCLUDE_DIRECTORIES("./lib/include")
###  Settings  ###}}}

###  OpenGL  ###{{{
find_package(OpenGL)
if (OPENGL_FOUND)
   include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
    message("OpenGL environment missing")
endif (OPENGL_FOUND)
set(GL_LIBRARIES ${OPENGL_LIBRARIES} GLEW)
if(APPLE)
 set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
 SET(APPLE_FRAMEWORKS "-framework Cocoa -framework IOkit -framework CoreVideo")
endif(APPLE)
###  OpenGL  ###}}}

###  GLFW3  ###{{{
set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:$ENV{HOME}/local_install/lib/pkgconfig")
FIND_PACKAGE( PkgConfig REQUIRED )
PKG_SEARCH_MODULE( GLFW3 REQUIRED glfw3 ) # sets GLFW3 as prefix for glfw vars
# now ${GLFW3_INCLUDE_DIR}, ${GLFW3_LIBRARIES} and ${GLFW3_STATIC_LIBRARIES} 
# are set
INCLUDE_DIRECTORIES( ${GLFW3_INCLUDE_DIR} )
###  GLFW3  ###}}}

###  ASSIMP  ###{{{
PKG_SEARCH_MODULE( ASSIMP REQUIRED assimp ) 
include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})
###  ASSIMP  ###}}}

### Framework ###
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(FRAMEWORK_SRC lib/Hakurei_ShaderProgram.cpp  lib/Hakurei_ShaderProgram.h  lib/Hakurei_Material.cpp  lib/Hakurei_Material.h  lib/Hakurei_Texture.cpp  lib/Hakurei_Texture.h  lib/Hakurei_Mesh.cpp  lib/Hakurei_Mesh.h  lib/Hakurei_KeyHandler.cpp  lib/Hakurei_KeyHandler.h  lib/Hakurei_OpenCamera.cpp lib/Hakurei_OpenCamera.h  lib/Hakurei_OpenScene.cpp  lib/Hakurei_OpenScene.h  lib/Hakurei_Utils.cpp  lib/Hakurei_Utils.h  lib/all.h)
add_library(FrameworkHakurei ${FRAMEWORK_SRC})
### --------- ###


### Source files ###
set(GAME_PHYSIC  GamePhysic/Tetris_GamePhysic.cpp  GamePhysic/Tetris_GamePhysic.h  GamePhysic/Tetris_Shape.cpp  GamePhysic/Tetris_Shape.h  GamePhysic/Tetris_3DBloc.cpp  GamePhysic/Tetris_3DBloc.h)
set(GAME_LOGIC  GameLogic/Tetris_Matrix.cpp  GameLogic/Tetris_Matrix.h GameLogic/Tetris_Player.cpp GameLogic/Tetris_Player.h)
### ------------ ###


### Creating an executable
add_executable(LookAroundTetris main.cpp ${GAME_PHYSIC} ${GAME_LOGIC})
target_link_libraries(FrameworkHakurei ${GL_LIBRARIES} ${APPLE_FRAMEWORKS} ${GLFW3_STATIC_LIBRARIES} ${ASSIMP_LIBRARIES})
if(APPLE)
	target_link_libraries(LookAroundTetris FrameworkHakurei "${CMAKE_CURRENT_SOURCE_DIR}/lib/libIrrKlang.dylib")
else(APPLE)
	target_link_libraries(LookAroundTetris FrameworkHakurei "${CMAKE_CURRENT_SOURCE_DIR}/lib/libIrrKlang.so")
endif(APPLE)

