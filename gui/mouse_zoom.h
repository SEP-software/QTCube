#ifndef MOUSE_ZOOM
#define MOUSE_ZOOM 1
#include "mouse_func.h"

class mouse_zoom: public mouse_func{

 public:
 mouse_zoom();
 virtual void  l_mouse_d(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o);
 virtual void  l_mouse_m(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o);
 virtual void l_mouse_r(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o);
 virtual void m_mouse_r(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o);
 virtual void r_mouse_r(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o);
 virtual void l_mouse_double(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o);
 virtual void m_mouse_d(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o);
 virtual void m_mouse_m(std::vector<std::shared_ptr<slice>> slices, int islice, int ix, int iy, std::shared_ptr<orient_cube>pos, std::vector<QString> *com, std::shared_ptr<draw_other>draw_o);


};
#endif
