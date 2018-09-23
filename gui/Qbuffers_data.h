#ifndef QCREATED_DATA_H
#define QCREATED_DATA_H 1
#include "Qdataset.h"
#include "buffers_data.h"

namespace SEP {

class Qbuffers_data_float : public Qdataset {
 public:
  Qbuffers_data_float(const std::string& title, const std::string& nm,
                      std::shared_ptr<SEP::hypercube> g,
                      std::shared_ptr<SEP::io_func> i,
                      std::shared_ptr<SEP::paramObj> p, const int inum,
                      const int mem) {
    _data.reset(new buffers_data_float(title, nm, g, i, p, inum, mem));
  }
};

class Qbuffers_data_byte : public Qdataset {
 public:
  Qbuffers_data_byte(const std::string& title, const std::string& nm,
                     std::shared_ptr<SEP::hypercube> g,
                     std::shared_ptr<SEP::io_func> i,
                     std::shared_ptr<SEP::paramObj> p, const int inum,
                     const int mem) {
    _data.reset(new buffers_data_byte(title, nm, g, i, p, inum, mem));
  }
};
}  // namespace SEP

#endif
