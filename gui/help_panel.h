#ifndef help_panel_H
#define help_panel_H 1
#include "qcubetabbasics.h"
#include "widget_tools.h"
#include <QTextEdit>
class help_panel: public qcubeTabBasic{
  public:
    help_panel(std::shared_ptr<position>p,std::shared_ptr<windows>my_w, std::shared_ptr<panels>my_p, std::shared_ptr<datasets>my_d, std::shared_ptr<pick_draw>pk, std::shared_ptr<slice_types>c,std::shared_ptr<maps>mym);
    void createit();
    void layout();
  private:
    QTextEdit *ModesWidget, *MouseWidget, *CommandWidget, *KeysWidget, *HistWidget, *ClipWidget, *LoadWidget;

        std::vector<QTextEdit *> edits;
};
#endif
