#include "qcubetabbasics.h"

void qcubeTabBasic::clean_basic(){

  for(std::map<QString,QWidget*>::iterator i=my_tabs.begin(); i!=my_tabs.end();
    i++) delete i->second;
}

  
