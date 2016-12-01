#include "moved_out.h"
#ifndef NMOED_H
#define NMOED_H 1
#include<string>
#include "datasets.h"
#include "pick_draw.h"
class nmoed: public moved_out{

  public:
     nmoed(){};
     nmoed(std::shared_ptr<hypercube>grid, std::shared_ptr<dataset>dat, int it,int ioff, int imes,
       std::shared_ptr<paramObj>pars, std::shared_ptr<pick_draw>pk,QString col1, QString col2);
     virtual void move_it(std::vector<int>&f,float *nmo);

     virtual void afterInitialization();
     float smute;
     bool done;
    
   private:
     
   std::shared_ptr<hypercube >_grid;
   std::shared_ptr<dataset>_dat;
  int _it,_ioff,_imes;
   std::shared_ptr<paramObj>_pars; 
 std::shared_ptr<pick_draw>_pk;
 QString _col1,_col2;
 
 };
#endif
