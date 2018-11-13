#ifndef HEADER_H_
#define HEADER_H_

typedef unsigned char byte;

void printData(byte **values);
double getX0(int x);
double getY0(int y);
byte isInMandel(double x0, double y0);
byte **allocMat(int x, int y);
void freeMat(byte **mat, int x);

#endif