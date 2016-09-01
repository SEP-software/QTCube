#ifndef WINDOW_PANEL_H
#define WINDOW_PANEL_H 1
#include "qcubewidgetbasics.h"
#include "qcubetabbasics.h"

#include "widget_tools.h"

#include <vector>
class window_panel: public qcubeTabBasic{
  Q_OBJECT
  public: 
  window_panel(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c,maps *my_m);

       void set_current_index(int ind){ setCurrentIndex(ind);}
     void update_menu(std::vector<QString>);
       signals:
       void actionDetected(std::vector<QString> text);
  private slots:
    void actionRespond(std::vector<QString> text){
       emit actionDetected(text);
    }
};
class sub_window_panel: public qcubeWidgetBasic{
  Q_OBJECT
  public: 
    sub_window_panel(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c,maps *m,QString w);
  
     void actionRespond(std::vector<QString>){;}
     ~sub_window_panel(){ delete_sub_window_panel();}
     void update_menu(std::vector<QString>);
       signals:
       void actionDetected(std::vector<QString> text);
   private:
     void delete_sub_window_panel();
     basicComboBox *splitXBox,*splitYBox,*boundaryBox;
     QHBoxLayout *mainLay,*saveLay;
     QGroupBox *saveBox;
     QComboBox  *boundary;
     QPushButton *saveHigh,*saveLow,*closeButton,*splitButton;
     QString myw;     
 private slots:
   void save_big();
   void save_small();
   void split_x(const QString com);
   void split_y(const QString com);
   void boundary_change(const QString com);
   void close_window();


 
};



#endif
