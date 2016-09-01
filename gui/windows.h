#ifndef WINDOWS_H
#define WINDOWS_H 1
#include "drawwindow.h"
#include "panels.h"
#include <map>
#include <QObject>
class windows:public QObject{
  Q_OBJECT
  public:
    windows(panels  *m){ my_pan=m; active_num=0;}
         signals:
    void actionDetected(std::vector<QString> text);
    public:
    void add_window(DrawWindow *um);
    void delete_window(DrawWindow *wind);
    void update_displays(bool tr=false);
    int size(){return (int)my_winds.size();}
    void set_active_panel(int iw, int ip){ my_winds[iw]->set_active_panel(ip);}
    void windows_respond(std::vector<QString> coms);
        void annotate_respond(std::vector<QString> coms);

    ~windows(){delete_windows();}
    int nwind(){ return my_winds.size();}
    DrawWindow *return_window(int i){return my_winds[i];}
        void connect_all();
    void connect_it(int i);
    void disconnect_it(int i);
    void update_grid(DrawWindow *active,int ioldx,int ioldy, int inewx, int inewy);
       void set_active(int ia){ 
       active_num=ia;}
    int get_active_num(){ return active_num;}
   std::vector<DrawWindow*> my_winds;

  private:
   void delete_windows();
   panels *my_pan;
   int active_num;
     private slots:
    void actionRespond(std::vector< QString> text);
    void update_all();

};
  
   
    
  
#endif
