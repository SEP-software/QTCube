#ifndef DATASETS_H 
#define DATASETS_H 1
#include "dataset.h"
#include "util.h"
#include "pick_draw.h"
#include "orient_cube.h"
#include <QObject>

class datasets: public QObject{
 Q_OBJECT
  public:
   datasets(param_func *p,pick_draw *pk);
   datasets(){}
   ~datasets(){ clean_dats();}
   void set_orients(orients *my){my_or=my;}
   void clean_dats();
   void update_data(std::vector<QString> coms);

   void add_dat(dataset *dat);
   dataset *return_dat(int i);
   dataset *return_dat(QString nm);
   int return_ndat(){ return (int)dats.size();}
   int dataNumFromName(QString name);
     signals:
    void actionDetected(std::vector<QString> text);
  private:
    std::vector<dataset*> dats;
    param_func *par;
    util *my_util;
    pick_draw *my_pk;
    orients *my_or;
    private slots:
    void actionRespond(std::vector< QString> text);
};
#endif
