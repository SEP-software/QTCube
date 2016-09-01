#ifndef panel_panel_H
#define panel_panel_H 1
#include "qcubetabbasics.h"
#include "widget_tools.h"

#include <vector>
class panel_panel: public qcubeTabBasic{
  Q_OBJECT
  public: 
    panel_panel(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c,maps *mym);
    
    void update_menu(std::vector<QString>);
    void set_current_index(int ind);
    signals:
       void actionDetected(std::vector<QString> text);
  private slots:
    void actionRespond(std::vector< QString> text);
 private:
   std::vector<int> tab_order;

};

class sub_panel_panel: public qcubeTabBasic{
  Q_OBJECT
  public: 
    sub_panel_panel(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c,maps *mym,QString v);
    
    
          void update_menu(std::vector<QString>);
  
   signals:
       void actionDetected(std::vector<QString> text);
  
  private slots:
    void actionRespond(std::vector< QString> text);
    
  private:
    QString vnum;
 
};


#endif
