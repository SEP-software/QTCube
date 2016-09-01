#include <qlayout.h>
#include <qlabel.h>
#include <qapplication.h>
#include <qsplitter.h>
#include <qsettings.h>
#include <qstatusbar.h>

#include <QCloseEvent>
#include <QKeyEvent>


#include "centerwindow.h"
#include "drawwindow.h"
#include "param_func.h"
#include "slice_types.h"
#include<iostream>
#include <qregexp.h>
#include "util.h"
#include "mouse_orient.h"
#include "mouse_anno.h"
#include "mouse_zoom.h"
#include "mouse_pick.h"
#include "mouse_region.h"
#include "mouse_overlay.h"
#include "windows.h"
#include "panels.h"




void MainWindow::create_panels(){

  int nviews=pars->get_int("nviews",1);
  int inum=0;
  for(int i=0; i < nviews; i++){
     QString par=tr("npanelx")+QString::number(i+1);
     int npanx=pars->get_int(par.toAscii().constData(),1);
     par=tr("npanely")+QString::number(i+1);
     int npany=pars->get_int(par.toAscii().constData(),1);
     int npan=npanx*npany;
     for(int ipan=0; ipan<npan; ipan++,inum++){
       my_pan->add_panel(new panel(my_pan->get_next_panel_num(), pars,pos,pk,datas,0,colort,cur_func,serv,my_or,my_maps));

     }
  }
  stat_view="mouse";
}
void MainWindow::create_windows(){
   int nviews=pars->get_int("nviews",1);
   int ipan=0;
   for(int iv=0; iv < nviews; iv++){     

        QString par=tr("npanelx")+QString::number(iv+1);
        int npanx=pars->get_int(par.toAscii().constData(),1);
        par=tr("npanely")+QString::number(iv+1);
        int npany=pars->get_int(par.toAscii().constData(),1);
        int npan=npanx*npany;
        std::vector<panel*> pp;
        for(int i=0; i < npan; i++){
          pp.push_back(my_pan->get_panel(i+ipan));
          my_pan->set_window(i+ipan,i);
        }
        ipan+=npan;
        my_wind->add_window(new DrawWindow(npanx,npany,&pp,iv));

   }
}
void MainWindow::create_mouse_funcs(){
   funcs["pick"]=new mouse_pick();
    funcs["navigate"]=new mouse_orient();
    funcs["zoom"]=new mouse_zoom();
    funcs["region"]=new mouse_region();
    funcs["overlay"]=new mouse_overlay();
    funcs["annotate"]=new mouse_anno();

	cur_func=funcs["zoom"];

}
MainWindow::MainWindow(param_func *par,datasets *d,pick_draw *_pks, slice_types *col,  util *p){

 pp=p;
    datas=d;
      my_or=new orients();

    connect(datas, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));

//setStyleSheet("border-radius 0px; font: bold 14px; padding: 0px; border-style: inset; spacing: 0px");
//setStyleSheet("QGroupBox { spacing: 40px }");
setStyleSheet("margin: 3px");
setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 3px; }");
setStyleSheet("QGroupBox::title { background-color: transparent; subcontrol-position: top left; padding:9 13px;}");
    pk=_pks;
    stat_view="mouse";
    pars=par;
	this->colort=col;
    QFont font("Arial", 12, QFont::Normal);
	QApplication::setFont(font);
	    my_maps=new maps();

	my_pan=new panels(pk,my_maps,my_or);
	datas->set_orients(my_or);
		my_wind=new windows(my_pan);

	int beg[8],end[8],init[8];
    for(int i=0; i< 8; i++){
       beg[i]=0; end[i]=datas->return_dat(0)->get_grid_axis(i+1).n; init[i]=end[i]/2;
    }
     modeLabel = new QLabel(mouse_lab, this);
  	statusBar()->addWidget(modeLabel);
   create_mouse_funcs();
    pos=new position((hypercube*)datas->return_dat(0)->return_grid(),init,beg,end,2);
 	serv=new orientation_server(pos);
        pk->set_server(serv);
  pk->set_position(pos);
 	create_panels();
 	create_windows();


     QWidget *widget = new QWidget;
     setCentralWidget(widget);

     my_window_panel = new window_panel(pos,my_wind,my_pan,datas,pk,colort,my_maps);
     my_window_panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     my_window_panel->setMaximumHeight(75);


     my_panel_panel = new panel_panel(pos,my_wind,my_pan,datas,pk,colort,my_maps);
     my_panel_panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

     QVBoxLayout *layout = new QVBoxLayout;
     layout->setMargin(5);
     layout->addWidget(my_window_panel);
     layout->addWidget(my_panel_panel);
   //  layout->addWidget(bottomFiller);
     widget->setLayout(layout);
     my_data_panel=new data_panel(pos,my_wind,my_pan,datas,pk,colort,my_maps);

     createActions();
     createMenus();

     my_color_panel=new color_panel(pos,my_wind,my_pan,datas,pk,colort,my_maps);
     my_help_panel=new help_panel(pos,my_wind,my_pan,datas,pk,colort,my_maps);
     my_help_panel->setMinimumSize(200,200);
     my_ano_panel=new ano_panel(pos,my_wind,my_pan,datas,pk,colort,my_maps);
     my_pick_panel=new pick_panel(pos,my_wind,my_pan,datas,pk,colort,my_maps);
     my_hist=new history();

     mouse_lab=funcs["zoom"]->status;     
     
     setWindowTitle(tr("qt_cube"));
     setMinimumSize(160, 160);
     resize(630,650);
     

     for(int i=0; i < my_wind->nwind(); i++)  {
        my_wind->return_window(i)->resize(600,400);
        my_wind->return_window(i)->update_panel_map();
        my_wind->return_window(i)->show();
      }
      connect_it();
     my_pan->update_all();
    update_status_bar();
  std::vector<QString> coms; coms.push_back("-1"); coms.push_back("redraw");coms.push_back("all"); actionRespond(coms);
   coms[1]="view"; coms[2]="data";
   coms.push_back("");
   for(int ipan=1; ipan < my_pan->size(); ipan++){
    coms[0]=QString::number(ipan);
    
    coms[3]=QString::number(std::min(ipan,datas->return_ndat()-1));
    actionRespond(coms);
   }
 my_pan->update_all();
 my_pan->set_active(0);
 coms[0]="-1";
 coms[1]="redraw";
 coms[2]="all";
 actionRespond(coms);
 }
 void MainWindow::connect_it(){

 
   connect(my_pan, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));
   connect(my_panel_panel, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));
   connect(my_pan, SIGNAL(windows_update()), my_wind, SLOT(update_all()));
   connect(my_window_panel, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));
   connect(my_wind, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));
   connect(my_hist, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));
    connect(my_ano_panel, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));
    connect(my_color_panel, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));
     connect(my_pick_panel, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));
     connect(my_data_panel, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));

 }
  void MainWindow::secondaryRespond(std::vector<QString> coms){
 
    
 
 
 }
 void MainWindow::actionRespond(std::vector<QString> coms){
 
// for(int i=0; i < coms.size(); i++)  fprintf(stderr,"%s ",coms[i].toAscii().constData());
 // fprintf(stderr,"\n");
  //fflush(stderr);
   if(coms[1].contains("none")) return;
   if(coms[0].contains("annotate")) coms.insert(coms.begin(),QString::number(my_wind->get_active_num()));
      if(coms[0].contains("auto")) coms.insert(coms.begin(),QString::number(my_wind->get_active_num()));
   if(!coms[1].contains("clip")) my_hist->addEvent(coms);
   
   

   
   
   if(coms[1].contains("navigate")) my_pan->perform_navigate(coms);
    else if(coms[1].contains("pick")) my_pan->perform_pick(coms);
    else if(coms[1].contains("auto")) my_pan->perform_auto(coms);
    else if(coms[1].contains("display")) {
        my_pan->perform_display(coms);
        }
        else if(coms[1].contains("navigate")) my_pan->perform_navigate(coms);
        else if(coms[1].contains("orient")) my_pan->perform_orient(coms);
        else if(coms[1].contains("windows")) my_wind->windows_respond(coms);
        else if(coms[1].contains("annotate")) my_wind->annotate_respond(coms);

    else if(coms[1].contains("view")) my_pan->perform_view(coms);
   else if(coms[1].contains("ctable")) colort->update_colortable(coms);
      else if(coms[1].contains("data")) {
         datas->update_data(coms);
            my_wind->update_displays(true);
   }
   else if(coms[1].contains("redraw")){

      if(coms[2].contains("only")) my_pan->update_only(coms[0].toInt());
      else if(coms[2].contains("all")) my_pan->update_all();
      else if(coms[2].contains("limited")) my_pan->update_it(coms[0].toInt());
   }
   if(!coms[1].contains("panels") && !coms[1].contains("windows") && !coms[1].contains("menu") && 
    !coms[1].contains("clip")){
     if(coms[1].contains("ctable"))      my_wind->update_displays(true);
      else my_wind->update_displays();
   }
   my_panel_panel->update_menu(coms);

   my_data_panel->update_menu(coms);

   my_ano_panel->update_menu(coms);

   my_color_panel->update_menu(coms);

   my_pick_panel->update_menu(coms);

   my_window_panel->update_menu(coms);

   bool v; int i=coms[0].toInt(&v);

   if(v){
     if(i!=-1 && !coms[1].contains("menu") &&!coms[1].contains("clip") ){
       if(coms[1].contains("windows") ||coms[1].contains("annotate")||coms[1].contains("data") ){
          my_window_panel->set_current_index(i);        
          my_wind->set_active(i);
       }
       else{
         int iwind=my_pan->get_window(i);
         my_wind->set_active_panel(iwind,i);
          my_window_panel->set_current_index(iwind);
          my_panel_panel->set_current_index(i);
          my_wind->set_active(iwind);
          my_pan->set_active(i);

       }
     }
    }
    update_status_bar();
    coms[0]="none"; coms[1]=="none";
 }
 void MainWindow::update_status_bar(){
 
  if(stat_view.contains("mouse") >0) {
    modeLabel->setText(mouse_lab);
  }
  else if(stat_view.contains("position") >0) {
      modeLabel->setText(my_pan->get_panel(0)->get_orient()->return_pos_label());

  }  
  else if(stat_view.contains("overlay")>0){
      mouse_overlay *x=(mouse_overlay*) funcs["overlay"];
      modeLabel->setText(x->get_info());
  }
    else if(stat_view.contains("pick") >0) {
      QString color="Active:"+pk->get_active_name();
      QString drawing="Drawing:"+pk->get_draw_what();
      QString dis;
      int what=pk->get_display();
      if(what==DISPLAY_EXTRA) dis="Display: Extra";
      else if(what==DISPLAY_POINTS) dis="Display: Points";
      else if(what==DISPLAY_LINE) dis="Display: Line";
      QString ex="Extra:"+QString::number(pk->get_extra());
      QString dist="Distance:"+QString::number(pk->get_dist());
      QString move="Move:Single";
    //  if(pk->get_move()==1) move="Move:Multi";
      
      modeLabel->setText(color+" "+drawing+" "+ex+" "+dist+" "+dis+" "+move);

  } 
  else if(stat_view.contains("value") >0) {
    //  modeLabel->setText(statwindow->return_val_lab());
  }

  }
void MainWindow::newFile(){

  int in=my_pan->get_next_panel_num();

  panel *x=my_pan->get_panel(0)->clone(in);

  my_pan->add_panel(x);

  std::vector<QString> coms;
  coms.push_back("-1");
  coms.push_back("panels");
  coms.push_back("add");
  coms.push_back(QString::number(in));
     my_panel_panel->update_menu(coms);

     std::vector<panel*> pp; pp.push_back(x);


     my_wind->add_window(new DrawWindow(1,1,&pp,my_wind->size()));
               my_pan->set_window(in,my_wind->size()-1);


     coms[1]="windows";
     my_window_panel->update_menu(coms);
 
     my_wind->my_winds[my_wind->size()-1]->show();
      my_wind->return_window(my_wind->size()-1)->resize(600,400);
        my_wind->return_window(my_wind->size()-1)->update_panel_map();
        my_wind->return_window(my_wind->size()-1)->show();
 my_wind->update_displays(true);


 }
void MainWindow::lockViews(){
    my_pan->set_locked(true);
 }
void MainWindow::unlockViews(){
    my_pan->set_locked(false);
 }
void MainWindow::open(){
 QString filename = QFileDialog::getOpenFileName(this );
       if ( !filename.isNull() ){
   my_hist->load_history(filename); }
   
   }
void MainWindow::save(){
 QString filename = QFileDialog::getSaveFileName(this );
       if ( !filename.isNull() ){
   my_hist->write_history(filename);
  }

 }
void MainWindow::mouseAnnotate(){\

	cur_func=funcs["annotate"];
	     my_pan->update_mouse(cur_func);
	          mouse_lab=funcs["annotate"]->status;     


}
void MainWindow::mouseZoom(){
	cur_func=funcs["zoom"];
     my_pan->update_mouse(cur_func);
          mouse_lab=funcs["zoom"]->status;     

}
void MainWindow::statusOverlay(){
 stat_view="overlay";
   update_status_bar();

 }
void MainWindow::statusMouse(){
stat_view="mouse";
  update_status_bar();

}
void MainWindow::statusPosition(){
stat_view="position";
  update_status_bar();

}
void MainWindow::statusPick(){
stat_view="pick";
  update_status_bar();

}
void MainWindow::mouseOverlay(){
	cur_func=funcs["overlay"];
     my_pan->update_mouse(cur_func);
     mouse_lab=funcs["overlay"]->status;     


}
void MainWindow::mousePick(){
	cur_func=funcs["pick"];
     my_pan->update_mouse(cur_func);
     mouse_lab=funcs["pick"]->status;     

}
void MainWindow::mouseRegion(){
	cur_func=funcs["region"];
     my_pan->update_mouse(cur_func);
     mouse_lab=funcs["region"]->status;     

}
void MainWindow::mouseNavigate(){
	cur_func=funcs["navigate"];
     my_pan->update_mouse(cur_func);
     mouse_lab=funcs["navigate"]->status;     

}
 void MainWindow::closeAnno(){

}
void MainWindow::openAnno(){
   my_ano_panel->show();

}
void MainWindow::closeData(){

}
void MainWindow::openData(){
  my_data_panel->show();
}
void MainWindow::closeColor(){

}
void MainWindow::openColor(){
   my_color_panel->show();
}
void MainWindow::closePick(){

}
void MainWindow::openPick(){
   my_pick_panel->show();

}
void MainWindow::closeHelp(){

}
void MainWindow::openHelp(){
   my_help_panel->show();

}
 void MainWindow::about(){
     QMessageBox::about(this, tr("About Sep_cube"),
             tr("<b>Sep_cube</b>  is a multi-dimensional viewer of regularly sampled cube.  "
                "If you find bugs please email the author bob@sep.stanford.edu"));
 }
 void MainWindow::aboutQt(){
 }
void MainWindow::createActions() {
     newAct = new QAction(tr("&New Window"), this);
     newAct->setShortcut(tr("Ctrl+W"));
     newAct->setStatusTip(tr("Create a new file"));
     connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

     lockAct = new QAction(tr("Lock views"), this);
     //lockAct->setShortcut(tr("Ctrl+L"));
     lockAct->setStatusTip(tr("Open an existing file"));
     connect(lockAct, SIGNAL(triggered()), this, SLOT(lockViews()));

     unlockAct = new QAction(tr("Unlock views"), this);
     //lockAct->setShortcut(tr("Ctrl+L"));
     unlockAct->setStatusTip(tr("Open an existing file"));
     connect(unlockAct, SIGNAL(triggered()), this, SLOT(unlockViews()));
     
     openAct = new QAction(tr("&Load..."), this);
     openAct->setShortcut(tr("Ctrl+L"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

     saveAct = new QAction(tr("&Save"), this);
     saveAct->setShortcut((tr("Ctrl+S")));
     connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));


     mNavAct = new QAction(tr("Navigate"), this);
     mNavAct->setShortcut((tr("Ctrl+N")));
     connect(mNavAct, SIGNAL(triggered()), this, SLOT(mouseNavigate()));

     mZoomAct = new QAction(tr("Zoom"), this);
     mZoomAct->setShortcut((tr("Ctrl+Z")));
     connect(mZoomAct, SIGNAL(triggered()), this, SLOT(mouseZoom()));

     mRegionAct = new QAction(tr("Region"), this);
     mRegionAct->setShortcut((tr("Ctrl+R")));
     connect(mRegionAct, SIGNAL(triggered()), this, SLOT(mouseRegion()));
     
     mAnnoAct = new QAction(tr("Annotate"), this);
      mAnnoAct->setShortcut((tr("Ctrl+A")));
     connect(mAnnoAct, SIGNAL(triggered()), this, SLOT(mouseAnnotate()));
     
     mPickAct = new QAction(tr("Pick"), this);
     mPickAct->setShortcut((tr("Ctrl+P")));
     connect(mPickAct, SIGNAL(triggered()), this, SLOT(mousePick()));

     mOverAct = new QAction(tr("Overlay"), this);
    mOverAct->setShortcut((tr("Ctrl+O")));
     connect(mOverAct, SIGNAL(triggered()), this, SLOT(mouseOverlay()));

     sMouseAct = new QAction(tr("Mouse"), this);
    // printAct->setShortcuts(QKeySequence::Print);
     connect(sMouseAct, SIGNAL(triggered()), this, SLOT(statusMouse()));

     sPositionAct = new QAction(tr("Position"), this);
    // printAct->setShortcuts(QKeySequence::Print);
     connect(sPositionAct, SIGNAL(triggered()), this, SLOT(statusPosition()));
     
     sOverlayAct = new QAction(tr("Overlay"), this);
    // printAct->setShortcuts(QKeySequence::Print);
     connect(sOverlayAct, SIGNAL(triggered()), this, SLOT(statusOverlay()));
     
     sPickAct = new QAction(tr("Picking"), this);
    // printAct->setShortcuts(QKeySequence::Print);
     connect(sPickAct, SIGNAL(triggered()), this, SLOT(statusPick()));


    yesAnnoAct = new QAction(tr("Annotate"), this);
     yesAnnoAct->setShortcut(tr("Ctrl+Shift+A"));
  //   yesDataAct->setStatusTip(tr("Show annotation menu"));
     connect(yesAnnoAct, SIGNAL(triggered()), this, SLOT(openAnno()));

        yesColorAct = new QAction(tr("Color"), this);
     yesColorAct->setShortcut(tr("Ctrl+Shift+C"));
  //   yesDataAct->setStatusTip(tr("Show annotation menu"));
     connect(yesColorAct, SIGNAL(triggered()), this, SLOT(openColor()));

        noColorAct = new QAction(tr("Hide"), this);
    // yesDataAct->setShortcuts(QKeySequence::Print);
  //   yesDataAct->setStatusTip(tr("Show annotation menu"));
     connect(noColorAct, SIGNAL(triggered()), this, SLOT(closeColor()));


     noAnnoAct = new QAction(tr("Hide"), this);
    // yesDataAct->setShortcuts(QKeySequence::Print);
     //noDataAct->setStatusTip(tr("Hide annotation menu"));
     connect(noAnnoAct, SIGNAL(triggered()), this, SLOT(closeAnno()));

     yesDataAct = new QAction(tr("Data"), this);
     yesDataAct->setShortcut(tr("Ctrl+Shift+D"));
     connect(yesDataAct, SIGNAL(triggered()), this, SLOT(openData()));

     noDataAct = new QAction(tr("&Hide"), this);
    // yesDataAct->setShortcuts(QKeySequence::Print);
     connect(noDataAct, SIGNAL(triggered()), this, SLOT(closeData()));

     yesPickAct = new QAction(tr("Pick"), this);
     yesPickAct->setShortcut(tr("Ctrl+Shift+P"));
     connect(yesPickAct, SIGNAL(triggered()), this, SLOT(openPick()));

     noPickAct = new QAction(tr("&Hide"), this);
    // yesDataAct->setShortcuts(QKeySequence::Print);
     connect(noPickAct, SIGNAL(triggered()), this, SLOT(closePick()));
     
     yesHelpAct = new QAction(tr("Help"), this);
      yesHelpAct->setShortcut(tr("Ctrl+Shift+H"));
     connect(yesHelpAct, SIGNAL(triggered()), this, SLOT(openHelp()));

     noHelpAct = new QAction(tr("&Hide"), this);
    // noHelpAct->setShortcuts(QKeySequence::Print);
     connect(noHelpAct, SIGNAL(triggered()), this, SLOT(closeHelp()));


     exitAct = new QAction(tr("E&xit"), this);
//     exitAct->setShortcuts(QKeySequence::Quit);
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

     

     aboutAct = new QAction(tr("&About"), this);
     aboutAct->setStatusTip(tr("Show the application's About box"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     aboutQtAct = new QAction(tr("About &Qt"), this);
     aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
     connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
     connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

 }
 void MainWindow::createMenus(){
     mainMenu = menuBar()->addMenu(tr("&Main"));
     mainMenu->addAction(newAct);
     mainMenu->addAction(exitAct);
     mainMenu->addAction(lockAct);
     mainMenu->addAction(unlockAct);
     
     
     mouseMenu=menuBar()->addMenu(tr("Mouse"));
     mouseMenu->addAction(mZoomAct);
     mouseMenu->addAction(mPickAct);
     mouseMenu->addAction(mNavAct);
     mouseMenu->addAction(mAnnoAct);
     mouseMenu->addAction(mOverAct);
     mouseMenu->addAction(mRegionAct);

     statusMenu=menuBar()->addMenu(tr("Status"));
     statusMenu->addAction(sMouseAct);
     statusMenu->addAction(sPositionAct);
     statusMenu->addAction(sOverlayAct);
     statusMenu->addAction(sPickAct);

     


     historyMenu = menuBar()->addMenu(tr("&History"));
     historyMenu->addAction(openAct);
     historyMenu->addAction(saveAct);
    
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
     helpMenu->addAction(aboutQtAct);
     
     panelMenu = menuBar()->addMenu(tr("&Panels"));
    panelMenu->addAction(yesColorAct);
    panelMenu->addAction(yesAnnoAct);
     panelMenu->addAction(yesDataAct);
     panelMenu->addAction(yesPickAct);
     panelMenu->addAction(yesHelpAct);

 }
