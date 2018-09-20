#ifndef QPARTIAL_DATA_H
#define QPARTIAL_DATA_H 1
#include "Qdataset.h"
#include "partial_data.h"

namespace SEP {

class Qpartial_data_float : public Qdataset {
 public:
  Qpartial_data_float(const std::string& title, const std::string& nm,
                      std::shared_ptr<SEP::hypercube> g,
                      std::shared_ptr<SEP::io_func> i,
                      std::shared_ptr<SEP::paramObj> p, int in, int im = 1) {
    _data.reset(new partial_data_float(title, nm, g, i, p, in, im));
  }
};

class Qpartial_data_byte : public Qdataset {
 public:
  Qpartial_data_byte(const std::string& title, const std::string& nm,
                     std::shared_ptr<SEP::hypercube> g,
                     std::shared_ptr<SEP::io_func> i,
                     std::shared_ptr<SEP::paramObj> p, int in, int im = 1) {
    _data.reset(new partial_data_byte(title, nm, g, i, p, in, im));
  }
};
}  // namespace SEP

#endif
