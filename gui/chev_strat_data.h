#ifndef chev_strat_data_H
#define chev_strat_data_H 1
#include "pick_draw.h"
#include "dataset.h"
#define FUNKY_VAL -123456



class chev_strat_data: public dataset{
  
   public:
chev_strat_data(hypercube *g, QString nm, pick_draw *picks, QString col,int in);
 
   
     virtual unsigned char *get_char_data(orient_cube *pos, int iax1, int iax2,int n, long long *ind);
     virtual unsigned char *get_char_data(orient_cube *pos, int iax1, int f1, int e1, int iax2,
      int f2, int e2);
    virtual float *get_float_data(orient_cube *pos, int iax1, int f1, int e1, int iax2,
      int f2, int e2);
    
    virtual float get_value(orient_cube *pos);
    virtual float get_minval(){return 1;}
    virtual float get_maxval(){return 254;}
    std::vector<int> form_strat_col(orient_cube *pos,bool leave_barriers);    
    void save_file(QString fl);
     virtual std::vector<QStringList> get_header(orient_cube *pos){
       if(pos==0){;}
       std::vector<QStringList> send;
       return send;
     }
    std::vector<QString> virtual get_header_vals(orient_cube *pos){
  if(pos==0) {;}
  std::vector<QString> send;
  return send;
     }
       virtual std::vector<QString> return_header_keys(){
    std::vector<QString> x;
    return x;
  }
    void set_layer(orient_cube *pos, int ival);
    void form_histo(orient_cube *pos);

    QString get_dataset(){ return data_name;}
    QString return_histogram();
    QString get_color(){ return pick_col;}
    void set_color(QString col);
    
    
    virtual hypercube *return_io_hyper(){return grid;}
    virtual void get_io_loc(int *iloc){  if(iloc==0){;};}
     virtual bool am_region(){ return false;}
     pick_draw *pk;
     QString pick_col;
     float *histo;
     orient_cube *mypos;
     QString display;
     QString data_name;
     int nslices;
     std::map<int,int> layers;
     float minv, maxv;
     int n1;

};


#endif
