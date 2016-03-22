#ifndef __PROG_TEST_H__
#define __PROG_TEST_H__

#include "lib/myOwnFramework.h"

#define SEG_TOP     0
#define SEG_1       1
#define SEG_2       2
#define SEG_BOT     3

void createDiamonds(Hakurei::Mesh* mesh, Uint32 nbDiamonds, Uint32 nbFaces, float dFromCenter, float diameter);
Vec2f computeUV(char segment, Uint32 index, Uint32 nbEm, double phi);
void createDiamond(Hakurei::Mesh* mesh, Uint32 index, Uint32 nbDia, Uint32 nbFaces, float dFromCenter, float diameter);
void linkDiamonds(Hakurei::Mesh* mesh, Uint32 nbDiamonds, Uint32 nbFaces);

void make_resources(void);
void mainLoop();
void drawScene();

#endif
