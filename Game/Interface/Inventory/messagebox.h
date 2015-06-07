#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QPainter>
#include "Enums.h"
#include "Colision/rectangle.h"
#include "Mouse/mouse.h"

//Caio, isso aqui era para o cara selecionar
//Não sabia da classe Comands, utiliza ela aqui se precisar
class MessageBox: public Mouse{
public:

  MessageBox();
  ~MessageBox();
  void setCursor(int x, int y);

private:
  QPixmap *back, *button[2];
  Rectangle *del, *add, *all;

};

#endif // MESSAGEBOX_H
