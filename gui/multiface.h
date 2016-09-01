#include<slice.h>
#include<dataset.h>
#include<vector>
#include<view.h>
#include<qfontmetrics.h>
#ifndef multi_face_H
#define multi_face_H 1
class multi_face: public view
{

public:
  multi_face(){}
  multi_face(QString view,QFontMetrics *f_m,pick_draw *_pks,draw_other *dr,int g1,int g2, int j);
  void viewit(QPainter *pm,QPen *pen, slice *fact,dataset *dat,orient_cube *pos,
  int bx, int ex, int by, int ey,draw_what *drawit,bool overlay);

  ~multi_face(){  }
  
   private:
    int grid1,grid2;
    int j3;
    int bsmall;


};
#endif
