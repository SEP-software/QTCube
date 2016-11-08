#include<three_view.h>
#include<slice.h>
#include<dataset.h>
#include<vector>
#include<qfontmetrics.h>
#ifndef THREE_FACE_H
#define THREE_FACE_H 1
class three_face: public three_view
{

public:
  three_face(){}
  three_face(QString view,std::shared_ptr<QFontMetrics >f_m,std::shared_ptr<pick_draw>_pks,
  std::shared_ptr<draw_other>dr,std::vector<float >proportions);
  void viewit(QPainter *pm,QPen *pen, std::shared_ptr<slice>fact,std::shared_ptr<dataset>dat,std::shared_ptr<orient_cube>pos,
  int bx, int ex, int by, int ey,std::shared_ptr<draw_what>drawit,bool overlay);

  ~three_face(){  }
  
   private:



};
#endif
