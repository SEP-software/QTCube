#ifndef DATASETS_H
#define DATASETS_H 1
#include <QObject>
#include "Qdataset.h"
#include "orient_cube.h"
#include "pick_draw.h"
#include "util.h"
namespace SEP {
class datasets : public QObject {
  Q_OBJECT
 public:
  datasets(std::shared_ptr<SEP::paramObj> p, std::shared_ptr<pick_draw> pk);
  datasets() {}
  ~datasets() { clean_dats(); }
  void set_orients(std::shared_ptr<orients> my) { my_or = my; }
  void clean_dats();
  void update_data(std::vector<QString> coms);
  void afterInitialization();
  void add_dat(std::shared_ptr<Qdataset> dat);
  std::shared_ptr<Qdataset> return_dat(int i);
  std::shared_ptr<Qdataset> return_dat(QString nm);
  int return_ndat() { return (int)dats.size(); }
  int dataNumFromName(QString name);
 signals:
  void actionDetected(std::vector<QString> text);

 private:
  std::vector<std::shared_ptr<Qdataset>> dats;
  std::shared_ptr<SEP::paramObj> par;
  std::shared_ptr<util> my_util;
  std::shared_ptr<pick_draw> my_pk;
  std::shared_ptr<orients> my_or;
 private slots:
  void actionRespond(std::vector<QString> text);
};
}  // namespace SEP
#endif
