#include "trigonometrie.h"
#include "math.h"

double cos_degre(double angle) { return cos(angle*M_PI/180.0); }
double sin_degre(double angle) { return sin(angle*M_PI/180.0); }
double tan_degre(double angle) { return tan(angle*M_PI/180.0); }
double acos_degre(double dist)  { return acos(dist)*180.0/M_PI; }
double asin_degre(double dist)  { return asin(dist)*180.0/M_PI; }
double atan_degre(double dist)  { return atan(dist)*180.0/M_PI; }
