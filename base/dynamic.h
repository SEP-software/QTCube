#ifndef DYNAMIC_H
#define DYNAMIC_H 1
#include<float_2d.h>
#include <path.h>
#include<memory>
class dynamic{

  public:
    dynamic(){sim=0; score=0;};
    dynamic(float_2d *buf, float jump_pen);
    void add_to_sim(float_2d *s);
    virtual void calc_score();
    virtual std::vector<path> return_path();
 
    virtual ~dynamic(){delete_ar();}

    void delete_ar(){
    
    }
   std::shared_ptr<float_2d>sim,score;
   float jump;
   int maxloc[2];
  
};

#endif
