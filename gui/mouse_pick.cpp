#include "mouse_pick.h"

mouse_pick::mouse_pick(){

status="Pick: L-add pick M-delete pick R-move pick";
ivalid_down=-1;

}
void mouse_pick::l_mouse_r(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o){
  add_pt(slices,islice,ix,iy,pos,com,draw_o);
}



void  mouse_pick::m_mouse_r(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o){
  del_pt(slices,islice,ix,iy,pos,com,draw_o);
}
 void  mouse_pick::r_mouse_d(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o){
  del_pt(slices,islice,ix,iy,pos,com,draw_o,true);
} 

void  mouse_pick::r_mouse_m(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o){
  move_pt(slices,islice,ix,iy,pos,com,draw_o);
}

  void  mouse_pick::r_mouse_r(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o){
  add_pt(slices,islice,ix,iy,pos,com,draw_o);
}
   