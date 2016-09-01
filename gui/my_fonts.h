#ifndef MY_FONTS
#define MY_FONTS 1

#include <qcolor.h>
#include <qstring.h>
#include  <map>
#include<stdio.h>
#include <vector>
#include <QFont>
#include<qfontmetrics.h>
class my_font{
  public:
     my_font(){ fm=0;myf=0;}
     my_font(QString xx);
     QFontMetrics *return_font_metric(){return fm;}
     QFont *return_font(){ return myf;}
     ~my_font(){ 
     fprintf(stderr,"im de;te \n");
       if(fm!=0) delete fm; 
       fprintf(stderr,"mmm \n");
       if(myf!=0) delete myf;
       fprintf(stderr,"EREER \n");
       }
  private:
     QFontMetrics *fm;
	 QFont *myf;
};

class my_fonts{
  public:
    my_fonts();
	std::vector<QString> font_list; 
    QFontMetrics *return_font_metric(QString nm){ return fonts[nm]->return_font_metric();}
    QFont *return_font(QString nm){ return fonts[nm]->return_font();}
    ~my_fonts(){
       delete_it();
 
    }
    void delete_it();
  private:
    std::map<QString,my_font*> fonts;
   

};


#endif
