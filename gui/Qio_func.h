#ifndef IO_FUNC_H
#define IO_FUNC_H 1
#include <qobject.h>
#include <QTreeWidgetItem>
#include <memory>
#include "hypercube.h"
#include "util.h"

namespace SEP {
class Qio_func : public QObject, io_func {
  Q_OBJECT

 signals:
  void actionDetected(std::vector<QString> text);

 public:
  Qio_func(){};
  virtual std::vector<QStringList> get_header(long long inum) {
    if (inum == 0) {
      ;
    };
    std::vector<QStringList> send;
    return send;
  }
};
}  // namespace SEP
#endif
