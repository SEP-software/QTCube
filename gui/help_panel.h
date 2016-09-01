#ifndef help_panel_H
#define help_panel_H 1
#include "qcubetabbasics.h"
#include "widget_tools.h"
#include <QTextEdit>
class help_panel: public qcubeTabBasic{
  public:
    help_panel(position *p,windows *my_w, panels *my_p, datasets *my_d, pick_draw *pk, slice_types *c,maps *mym);
    void createit();
    void layout();
  private:
    QTextEdit *ModesWidget, *MouseWidget, *CommandWidget, *KeysWidget, *HistWidget, *ClipWidget, *LoadWidget;

        std::vector<QTextEdit *> edits;
};
#endif
