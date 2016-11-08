
#ifndef VITERBI_H
#define VITERBI_H 1
#include "dynamic.h"
#include<my_score.h>
#include<memory>
class viterbi: public dynamic{

  public:
    viterbi();
    viterbi(std::shared_ptr<my_score> s,std::shared_ptr<float_2d> buf, int ns,int flac);
    virtual void calc_score();
    virtual std::vector<path> return_path();
    
    int nsearch,f;
    virtual  ~viterbi(){};
    std::shared_ptr<my_score> sc;
    
};

#endif
