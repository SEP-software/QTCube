#include "Qdataset.h"
#include <stdlib.h>
#include <QFileInfo>
#include "math.h"
using namespace SEP;

Qdataset::Qdataset() { _data.reset(new dataset()); }

int Qdataset::check_load_buffer(std::shared_ptr<orient_cube> pos,
                                const int iax1, const int iax2) {
  _data->check_load_buffer(pos, iax1, iax2);
  std::vector<QString> com2;
  com2.push_back(QString::number(_data->getInum()));
  com2.push_back("clip");
  com2.push_back("set_histo");
  com2.push_back(QString::fromStdString(return_histogram()));
  emit actionDetected(com2);
  return _data->getBufSize() - 1;
}

void Qdataset::build_conv() {
  _data->build_conv();

  std::vector<QString> com;
  com.push_back(QString::number(_data->getInum()));
  com.push_back("clip");
  com.push_back("set_pts");
  com.push_back(QString::fromStdString(return_clip()));
  emit actionDetected(com);
}
