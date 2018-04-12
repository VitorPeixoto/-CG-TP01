#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <SOIL/SOIL.h>
#include <GL/freeglut.h>
#include <stdio.h>

void inicializaMenu();
void resizeMenu();
void drawMenu();

void drawText(char* s, float x, float y);

double getStringBitmapLength(char* str);
void drawRestartingConfirmation();
void drawExitingConfirmation(double x, double y);
void drawExitingConfirmation();
void drawPaused();
void drawLandedOn();
void drawLandedOff();
void drawExploded();
void drawFlewOutOfBounds();

#endif // SCREENCONTROLLER_H
