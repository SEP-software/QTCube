#include "io_func.h"
#ifndef MOVED_OUT_H
#define MOVED_OUT_H 1
#include <string>
#include "datasets.h"
#include "pick_draw.h"
namespace SEP {
class moved_out : public io_func {
 public:
  moved_out(){};
  void set_moveout_basics(std::shared_ptr<hypercube> grid,
                          std::shared_ptr<SEP::Qdataset> dat, const int it,
                          const int ioff, const int imes,
                          std::shared_ptr<SEP::util> pars,
                          std::shared_ptr<SEP::pick_draw> _pk,
                          const std::string &col1, const std::string &col2);
  virtual void read_block_float(std::vector<int> &nw, std::vector<int> &fw,
                                float *buf);
  virtual void read_block_byte(std::vector<int> &nw, std::vector<int> &fw,
                               unsigned char *buf);
  virtual void move_it(std::vector<int> &f, float *nmo) {
    if (f[0] == 0 && nmo == 0) {
      ;
    }
  };
  void moveoutAfterInitialization();
  std::shared_ptr<Qdataset> data;
  int i_off, i_mes, i_t;
  std::shared_ptr<pick_draw> pks;
  std::string col1, col2;
  float os[8], ds[8];
  std::shared_ptr<util> par;
  std::shared_ptr<orient_cube> dumb;
  float *num, *den, *sum;
  std::shared_ptr<hypercube> grid;
};
}  // namespace SEP
#endif
