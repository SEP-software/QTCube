#ifndef QCUBE_PANEL_H
#define QCUBE_PANEL_H 1
#include "position.h"
#include "panels.h"
#include "windows.h"
#include "datasets.h"
#include "pick_draw.h"
#include "slice_types.h"
#include "my_fonts.h"
#include "my_colors.h"
#include "view_types.h"
#include "maps.h"
#include <QWidget>
#include <QHBoxLayout>
#include<QGroupBox>
#include<QComboBox>
#include <QPushButton>
#include <vector>

class qcube_panel{
 public:
   qcube_panel(){;}
   void set_basics(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c, maps *m);
   ~qcube_panel(){ delete_qcube_panel();}
    virtual void actionRespond(std::vector<QString>){;}


     position *pos,*my_pos;
     windows *my_wind;
     panels *my_pan;
     datasets *my_dat;
     pick_draw *my_pick;
     slice_types *my_slices;
     my_colors *my_c;
     my_fonts *my_f;
     maps *my_maps;
     view_types *my_v;


  private:
    void delete_qcube_panel();


};
#endif

