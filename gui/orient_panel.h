#ifndef orient_panel_H
#define orient_panel_H 1
#include <QVBoxLayout>
#include "qcubewidgetbasics.h"
#include "widget_tools.h"

#include <vector>
class orient_panel: public qcubeWidgetBasic{
  Q_OBJECT
  public: 
    orient_panel(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c,maps *mym);
     void update_menu(std::vector<QString>);
     virtual void actionRespond(std::vector<QString>){;}
     ~orient_panel(){ delete_row_1();delete_row_2(); delete_row_3(); delete layMain;}
     signals:
       void actionDetected(std::vector<QString> text);
   private:
     void delete_row_1();
     void delete_row_2();
     void delete_row_3();
     QWidget *build_row_1();
     QWidget * build_row_2();
     QWidget * build_row_3();
     basicButtonBox *flipAxes,*frameOrient,*rotation;
     basicRadioBox *proportions;
     std::vector<basicLineEditBox*> axes;
     basicComboBox *transpAxes,*rotateAxes;
     basicSliderBox *angle2;
     basicLineEditBox *angle1;
          QVBoxLayout *layMain;
     QHBoxLayout *lay1,*lay2,*lay3;
     QWidget *row1,*row2,*row3;

     bool validax[8];
         
    private slots:
      void flip_1();
            void reset_orientation();

      void flip_2();
      void flip_3();
      void center();
      void edge();
      void transpose(const QString com);
      void angle_int(int ang);
      void angle_str(const QString com);
      void rotate_axes(const QString com);
      void reset_rotation();
      void set_rotation_pt();
      void true_prop();
      void false_prop();
      
};



#endif
