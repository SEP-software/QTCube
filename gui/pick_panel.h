#ifndef pick_panel_H
#define pick_panel_H 1
#include <QVBoxLayout>
#include "qcubewidgetbasics.h"
#include "widget_tools.h"

#include <vector>
class pick_panel: public qcubeWidgetBasic{
  Q_OBJECT
  public: 
    pick_panel(std::shared_ptr<position>p,std::shared_ptr<windows>my_w, std::shared_ptr<panels>my_p, std::shared_ptr<datasets>my_d, std::shared_ptr<pick_draw>pk, std::shared_ptr<slice_types>c,std::shared_ptr<maps>mym);

     virtual void actionRespond(std::vector<QString>){;}
     ~pick_panel(){ delete_row_1();delete_row_2(); delete_row_3(); delete layMain;}
          void update_menu(std::vector<QString>);
   signals:
     void actionDetected(std::vector<QString> coms);
     
   private:
     void delete_row_1();
     void delete_row_2();
     void delete_row_3();
          void delete_row_4();

     QWidget *build_row_1();
     QWidget * build_row_2();
     QWidget * build_row_3();
          QWidget * build_row_4();

     basicComboBox *group,*view,*single;
     basicRadioBox *display;
     basicButtonBox *loadsave;
     basicSliderBox *distance;
     basicComboBox *extra;
     basicButtonBox *pksize;
     basicLineEditBox *pkText;
     basicButtonBox *auto2d;
     basicComboBox *method,*direction;
     basicComboBox *autoType,*autoLen,*autoMax,*autoError;
     QVBoxLayout *layMain;
     QHBoxLayout *lay1,*lay2,*lay3,*lay4;
     QWidget *row1,*row2,*row3,*row4;
     
     private slots:
     
     void group_change(const QString txt);
     void view_change(const QString txt);
     void display_points();
     void display_line();
     void display_text();
     void single_change(const QString txt);
     void load_picks();
     void save_picks();
     void distance_change(int change);
     void extra_change(const QString txt);
     void increase_size();
     void decrease_size();
     void change_text(const QString txt);
      void auto_do();
      void auto_accept();
      void auto_decline();
      void auto_extend();
      void auto_method(const QString& txt);
      void auto_type(const QString& txt);
      void auto_len(const QString& txt);
      void auto_maxd(const QString& txt);
      void auto_error(const QString& txt);
      void auto_direction(const QString& txt);
      

     
};



#endif
