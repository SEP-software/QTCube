#ifndef MAPS_H
#define MAPS_H 1 
#include <vector>
#include "hypercube.h"
#include <QString>

class map_1{
  public:
    map_1(){;}
    map_1(QString nm, hypercube *h, float oversamp);
    int *return_index(){return ind;}
    QString return_name(){ return name;}
    float return_oversamp(){ return oversamp;}
  private:
    int *ind;
    QString name;
    float oversamp;

};

class maps{
  public:
  maps(){;}
  void add_map(map_1 *x){ my_maps.push_back(x);}
  map_1 *return_map(int inum);
  map_1 *return_map(QString nm);
  std::vector<QString> return_names();
  int size(){ return (int)my_maps.size();}
  int return_num(QString nm);
  
  private:

  std::vector<map_1*> my_maps;

};


#endif
