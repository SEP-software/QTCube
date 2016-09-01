#include "datasets.h"
#include "sep_reg_io.h"
#include "seispak_reg_io.h"
#include "surface_data.h"
#ifdef CHEVRON
#include "chev_strat_data.h"
#endif
#include "incore_data.h"
datasets::datasets(param_func *p,pick_draw *pk){
  par=p;
  my_util=new util(par);
  my_pk=pk;
}
void datasets::clean_dats(){

  for(int i=0; i < (int)dats.size(); i++){
    delete dats[i];
  }
  dats.clear();
}
dataset *datasets::return_dat(int idat){
  if(idat < 0 || idat >= (int)dats.size()){
//    par->error("Invalid dataset \n");
  }
  return dats[idat];

}
void datasets::update_data(std::vector<QString> command){
  int idat=command[0].toInt();

  if(command[2].contains("add")>0){
      int iret=dats[idat]->add_pt(command[3].section(":",0,0).toFloat(),
        command[3].section(":",1,1).toFloat());
  }
  else if(command[2].contains("axis")>0){
    int iax=command[3].toInt();
    dats[idat]->set_display_axis(iax-1,command[4]);
  }
  else if(command[2].contains("set")>0){
      float *pct=util::float_array_from_string(command[3]);
      QString tmp=dats[idat]->set_pts(pct);      
      int iret=dats[idat]->add_pt(command[3].section(":",0,0).toFloat(),
              command[3].section(":",1,1).toFloat());

      delete [] pct;

  }
  else if(command[2].contains("clear")>0){
       dats[idat]->clear_pts();
  }
  else if(command[2].contains("delete")>0){
     float pct,clp;
     dats[idat]->get_pt(command[3].toInt(),&pct,&clp);
     dats[idat]->del_pt(command[3].toInt());
  }
  else if(command[2].contains("beg_clip")>0){
    dats[idat]->set_bcolor(command[3]);
   
  }
  else if(command[2].contains("surface")>0){
    if(command[3].contains("update")>0){
      ( (surface_data*) dats[idat])->update_surface();
    }
}
  else if(command[2].contains("end_clip")>0){
    dats[idat]->set_ecolor(command[3]);
  }
  else if(command[2].contains("new")>0){
      io_func *io;

    if(command[3].contains("SEP")){
     sreg *d=new sreg(command[4].toAscii().constData());
    int esize=d->get_int("esize",4);
    if(esize==4) io=new sep_reg_io_float(command[4],my_util);
    else io=new sep_reg_io_byte(command[4],my_util);
    std::string title=d->get_string("title",command[4].toAscii().constData());
    if(command[5].contains("BYTE"))
     add_dat(new incore_data_byte(title,title.c_str(),dats[0]->return_grid(),io,par,0,1));
    else
          add_dat(new incore_data_float(title,title.c_str(),dats[0]->return_grid(),io,par,0,1));
 
    }
    else if(command[3].contains("SEISPAK")){
     char tt[20];
    sprintf(tt,"swap%d",idat); int s=par->get_int(tt,0);
      bool swap=false;
      if(s==1) swap=true;
    if(command[6].contains("SHORT")) io=new seispak_reg_io_short(command[4],dats[0]->return_grid(),
      swap,return_ndat(),my_util);
    else io=new seispak_reg_io_float(command[4],dats[0]->return_grid(),
      swap,return_ndat(),my_util);
    std::string title=command[4].toAscii().constData();
    if(command[5].contains("BYTE"))
     add_dat(new incore_data_byte(title,title.c_str(),dats[0]->return_grid(),io,par,0,1));
    else
          add_dat(new incore_data_float(title,title.c_str(),dats[0]->return_grid(),io,par,0,1));
 
    }
    else if(command[3].contains("surface")){
       hypercube *g=dats[0]->return_grid();
       QString nm="Surface"+QString::number(return_ndat());
       dataset *dat=return_dat(command[4].toInt());
       QString col=command[5];
       int nnum=return_ndat();
        add_dat(new surface_data(g,nm,command[6],dat,par,my_pk,col,nnum));
 
    }
#ifdef CHEVRON
        else if(command[3].contains("flatten")){
       hypercube *g=dats[0]->return_grid();
       QString nm="Surface"+QString::number(return_ndat());
       int nnum=return_ndat();
        add_dat(new chev_strat_data(g,nm,my_pk,command[4],nnum));

    }
#endif
  }
#ifdef CHEVRON
  else if(command[2].contains("strat")>0){
    if(command[3].contains("set")>0){
      ((chev_strat_data*)dats[idat])->set_layer(my_or->return_active(), command[4].toInt());
    
    }  
    else if(command[3].contains("save")>0){
      ((chev_strat_data*)dats[idat])->save_file(command[4]);
    
    }  
  
  }
#endif
}
dataset *datasets::return_dat(QString nm){
  for(int i=0; i < (int) dats.size(); i++){
    if(dats[i]->get_name()==nm) return dats[i];
  }
  //par->error("invalid dataset");
  return NULL;
}
void datasets::actionRespond(std::vector<QString> coms){

  emit actionDetected(coms);
}
void datasets::add_dat(dataset *d){
     connect(d, SIGNAL(actionDetected(std::vector<QString>)), this, SLOT(actionRespond(std::vector<QString>)));

  dats.push_back(d);
}
int datasets::dataNumFromName(QString name){
  for(int i=0; i < return_ndat(); i++){
    if(name==dats[i]->get_name()) return i;
  }
  return 0;

}

