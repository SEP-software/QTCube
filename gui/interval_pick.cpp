#include "interval_pick.h"
#include <math.h>
using namespace SEP;
bool interval_pick::form_interval_vel(std::shared_ptr<orient_cube> pos,
                                      std::shared_ptr<hypercube> grid,
                                      float *ds, std::shared_ptr<pick_draw> pks,
                                      const std::string &rms,
                                      const std::string &interval, int i_mes,
                                      int i_t, int i_off) {
  if (ds == 0) {
    ;
  }
  axis maxis = grid->getAxis(i_mes + 1);
  axis taxis = grid->getAxis(i_t + 1);
  float ot = taxis.o, dt = taxis.d, ov = maxis.o, dv = maxis.d;

  //  float scale[8];
  float floc[8];

  for (int i = 0; i < 8; i++) floc[i] = pos->get_pos(i);
  floc[i_off] = grid->getAxis(i_mes + 1).o;

  int iloc[8];
  pos->get_locs(iloc);
  iloc[i_off] = -1;  // Ignore the location in offset when finding slice
  iloc[i_t] = iloc[i_mes] = -1;  // Set what plane we are looking for
  //   pairs myp=pks->get_pts_sort(iloc,i_t,i_mes,i_t,1,rms);
  std::shared_ptr<pairs_new> myp(
      pks->get_pts_sort(pos, iloc, i_t, i_mes, QString::fromStdString(rms)));

  // rms->find_closest(floc,scale,&iclose,&dist,ds);

  if (myp->size() == 0) return false;

  pks->clear_picks(pos, iloc, QString::fromStdString(interval));
  axis ax = grid->getAxis(i_mes + 1);
  float vmin = ax.o, vmax = ax.o + ax.d * (ax.n - 1);
  float vmin2 = vmin * vmin, vmax2 = vmax * vmax;
  float vold = 0., told = 0., tmp;

  for (int i = 0; i < (int)myp->size(); i++) {
    float t = ot + dt * myp->vals[i].x;
    float v = ov + dv * myp->vals[i].y;
    tmp = (v * v * t - vold * vold * told) / (t - told);

    if (tmp < vmin2) tmp = vmin2;
    if (tmp > vmax2) tmp = vmax2;
    // pts[i].floc[i_mes]=sqrtf(tmp);
    vold = v;
    told = t;
    //  floc[i_t]=t;
    // floc[i_mes]=sqrtf(tmp);
    iloc[i_t] = myp->vals[i].x;
    iloc[i_mes] =
        std::max(0, std::min(maxis.n - 1, (int)(.5 + (sqrtf(tmp) - ov) / dv)));
    pks->add_pt(iloc, 0, QString::fromStdString(interval));
  }
  // emit actionDetected(com);
  return true;
}
