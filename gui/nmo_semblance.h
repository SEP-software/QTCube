#include "move_semblance.h"
#ifndef NMO_SEMBLANCE_H
#define NMO_SEMBLANCE_H 1
#include <string>
#include "datasets.h"
#include "pick_draw.h"
namespace SEP {
class nmo_semblance : public move_semblance {
 public:
  nmo_semblance(){};
  nmo_semblance(std::shared_ptr<SEP::hypercube> grid,
                std::shared_ptr<SEP::Qdataset> dat, int it, int ioff, int imes,
                std::shared_ptr<SEP::paramObj> pars,
                std::shared_ptr<SEP::pick_draw> pk, const std::string &col1,
                const std::string &col2);

  virtual void semblance_it(int *f, float *semb);

  int no_sem;
  float smute;
  int nsmooth;
  void add_pt_action(int *iloc) { update_vel(iloc); }
  void del_pt_action(int *iloc) { update_vel(iloc); }
  void update_vel(int *iloc);
};

}  // namespace SEP
#endif
