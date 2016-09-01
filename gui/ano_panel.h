#ifndef ano_panel_H
#define ano_panel_H 1
#include "qcubewidgetbasics.h"
#include "widget_tools.h"
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QObject>


class ano_panel: public qcubeWidgetBasic{
  Q_OBJECT
  public:
    ano_panel(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c,maps *mym);

    ~ano_panel(){delete_ano_panel();}
         void update_menu(std::vector<QString>);
  signals:
    void actionDetected(std::vector<QString> coms);
  private slots:
    void sbox_change();
    void stext_change();
    void sarrow_change();
    void sline_change();
    void selipse_change();
    void color_change(const QString txt);
    void thick_change(const QString txt);
    void text_change(const QString txt);
        void font_change(const QString txt);

  private:
    void delete_ano_panel();
    basicRadioBox *shape;
    QHBoxLayout *layBot,*layTop;
    QVBoxLayout *layMain;
    QGroupBox *gbox,*gbox2;
    basicComboBox *thick,*colorB,*font;
    basicLineEditBox *txt;    
};
#endif
