#ifndef INTERVAL_PICK_H
#define INTERVAL_PICK_H 1
#include <string>
#include "orient_cube.h"
#include "pick_draw.h"
namespace SEP {
class interval_pick {
 public:
  static bool form_interval_vel(std::shared_ptr<SEP::orient_cube> pos,
                                std::shared_ptr<SEP::hypercube> grid, float *ds,
                                std::shared_ptr<SEP::pick_draw> pks,
                                const std::string &col1,
                                const std::string &col2, int i_t, int i_off,
                                int i_mes);
};
}  // namespace SEP
#endif
