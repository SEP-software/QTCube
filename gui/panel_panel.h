#ifndef panel_panel_H
#define panel_panel_H 1
#include "qcubetabbasics.h"
#include "widget_tools.h"

#include <vector>
class panel_panel: public qcubeTabBasic{
  Q_OBJECT
  public: 
    panel_panel(std::shared_ptr<position>p,std::shared_ptr<windows>my_w, 
    std::shared_ptr<panels> my_p, std::shared_ptr<datasets>my_d, std::shared_ptr<pick_draw>pk, 
    std::shared_ptr<slice_types>c,std::shared_ptr<maps>mym);
    
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
    sub_panel_panel(std::shared_ptr<position>p,std::shared_ptr<windows>my_w, 
     std::shared_ptr<panels>my_p, std::shared_ptr<datasets>my_d, 
     std::shared_ptr<pick_draw> pk, std::shared_ptr<slice_types>c,std::shared_ptr<maps> mym,QString v);
    
    
          void update_menu(std::vector<QString>);
  
   signals:
       void actionDetected(std::vector<QString> text);
  
  private slots:
    void actionRespond(std::vector< QString> text);
    
  private:
    QString vnum;
 
};


#endif
