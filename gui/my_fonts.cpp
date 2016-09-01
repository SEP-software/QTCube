#include "my_fonts.h"


my_font::my_font(QString name){
    QString nm=name.section("-",0,0);
    int sz=name.section("-",1,1).toInt();
    QString typ=name.section("-",2,2);
    if(typ.contains("Normal")){
      myf=new QFont(nm,sz,QFont::Normal);
    }
    else if (typ.contains("Bold")){
      myf=new QFont(nm,sz,QFont::Bold);
    }
    fm=new QFontMetrics(*myf);
}

my_fonts::my_fonts(){

  font_list.push_back("Arial-12-Normal");

  font_list.push_back("Arial-12-Bold");
  font_list.push_back("Arial-14-Bold");
  font_list.push_back("Arial-16-Bold");
  font_list.push_back("Arial-17-Bold");
  for(int i=0; i < (int)font_list.size(); i++) fonts[font_list[i]]=new my_font(font_list[i]);
}
void my_fonts::delete_it(){
fprintf(stderr,"BBB  %d\n",(int)fonts.size());
  std::map<QString,my_font*>::iterator i;
  for(i=fonts.begin(); i !=fonts.end(); i++){
    fprintf(stderr,"before delete %s \n",i->first.toAscii().constData());
    delete i->second;
    
    }
fprintf(stderr,"jdfsjikfsdji \n");


}

