#ifndef Qsurface_DATA_H
#define Qsurface_DATA_H 1
#include "Qdataset.h"
#include "pick_draw.h"
#include "pick_new.h"
#include "surface_data.h"
#define FUNKY_VAL -123456
namespace SEP {

class Qsurface_data : public Qdataset {
 public:
  Qsurface_data(std::shared_ptr<SEP::hypercube> g, const std::string &nm,
                const std::string &typ, std::shared_ptr<Qdataset> dat,
                std::shared_ptr<SEP::paramObj> p,
                std::shared_ptr<SEP::pick_draw> picks, const std::string &col,
                int in) {
    std::shared_ptr<surface_data> surf(new surface_data());
    surf->surfaceInit(g, nm, typ, dat, p, picks, col, in);
    _data = surf;
  }
  // virtual void form_histo(std::shared_ptr<SEP::orient_cube> pos);
};
}  // namespace SEP

#endif
