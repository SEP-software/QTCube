#include "qcube_panel.h"

void qcube_panel:: set_basics(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c,maps *mym){

  pos=p;
  my_wind=my_w;
  my_pan=my_p;
  my_dat=my_d;
  my_maps=mym;
  my_pick=pk;
  my_slices=c;
  my_f=new my_fonts();
  my_v= new view_types();
  my_c = new my_colors();
  my_pos=p;
}
void qcube_panel::delete_qcube_panel(){
  delete my_f;
  delete my_v;
  delete my_c;
}
