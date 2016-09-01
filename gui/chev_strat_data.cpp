#include "chev_strat_data.h"
#include "sregf.h"
#include "float_1d.h"
chev_strat_data::chev_strat_data(hypercube *g, QString nm, 
  pick_draw *picks, QString col,int in){

  data_type="FLATTEN";

  grid=g;
  n1=grid->get_axis(1).n;
  pick_col=col;
  pickable=false;
  name=nm;
  title_short=nm;
  inum=in;
  pk=picks;
  moveable=true;
  restrict="NONE";
  moveable=true;
  bcolor="none";
  ecolor="none";
  display="single";
  show_picks=false;
  update_pick=true;
  nslices=9;
  layers.clear();  
   histo=new float [256];
   set_contains();   
    for(int i=0; i<8; i++) axes_display.push_back(-1);

}

unsigned char *chev_strat_data::get_char_data(orient_cube *pos,int iax1, int iax2,int n, long long *bb){

     std::vector<int> strat=form_strat_col(pos,true);
     unsigned char *buf=new unsigned char[n];
     int *one_shift=pos->return_one_shift();
     if(one_shift==0){
     for(int i=0; i < n; i++){
        if(bb[i]<0) buf[i]=-1;
        else buf[i]=(unsigned char)strat[(int)(bb[i]%n1)];
    }
    }
    else{
   int ifast=0;
      int iold=0;
         for(int i=0; i < n; i++){
           if(bb[i]==-1){
             buf[i]=0;
           }
           else{
           int ilook=bb[i]%n1;
           long long ib=bb[i]-(long long)ilook;
           bool found=false;
           int icheck=std::max(0,iold-3);
           while(!found && icheck < std::min(iold+3,n1-1)){
              if(one_shift[ib+icheck]<= ilook && one_shift[ib+icheck+1]>=ilook){
                found=true;
                 buf[i]=(unsigned char) strat[icheck];
                 iold=icheck;
                 ifast++;
              }
              icheck++;
           }
           if(!found){
             int is=0;
             while(is< n1-1 && !found){
             
               
               if(one_shift[ib]<= ilook && one_shift[ib+1] >=ilook){
                 found=true;
                 int iuse;
                 if(ilook-one_shift[ib] < one_shift[ib+1] - ilook) iuse=is;
                 else iuse=is+1;
                 buf[i]=(unsigned char) strat[iuse];
                  iold=iuse;
              }
              is++; ib++;
         }
       }
    }}
 }
      strat.clear();
     return buf;
   
  }
unsigned char *chev_strat_data::get_char_data(orient_cube *pos, int iax1, int f1, int e1, int iax2,  int f2, int e2){
               
        int nfast=abs(e1-f1);
     bool fast=false; 
     int n=abs(e1-f1)*abs(e2-f2);
     if(iax1==0 && e1 >f1) fast=true;
     std::vector<int> strat=form_strat_col(pos,true);
     long long *bb=pos->get_index_map_ptr(iax1,iax2,f1,e1,f2,e2,0);
     unsigned char *buf=new unsigned char[n];
     int *one_shift=pos->return_one_shift();
     if(one_shift==0){
     for(int i=0; i < n; i++){
   
        buf[i]=(unsigned char)strat[(int)(bb[i]%n1)];
    }
    }
    else{
       int n2=n/n1;
       int i=0;
      int iold=0;
         for(int i=0; i < n; i++){
           int ilook=bb[i]%n1;
           if(i%nfast==0) iold=0;
           long long ib=bb[i]-(long long)ilook;
           bool found=false;
           int is=0;
           buf[i]=(unsigned char) strat[0];
           if(fast) {is=iold; ib+=iold;}
           
           while(is< n1-1 && !found){
             if(one_shift[ib]<= ilook && one_shift[ib+1] >=ilook){
               found=true;
               int iuse;
               if(ilook-one_shift[ib] < one_shift[ib+1] - ilook) iuse=is;
               else iuse=is+1;
               buf[i]=(unsigned char) strat[iuse];
       //        fprintf(stderr,"IUSE IS %d %d %d \n",i,(int)buf[i],iuse);
               iold=iuse-2;
            }
            
            is++; ib++;
          
          }
     //     if(!found) fprintf(stderr,"FAILED axes=%d,%d  %d %d  \n",iax1,iax2,iold,one_shift[bb[i]-ilook+iold]);
       }
       
    
    }
       //  delete [] bb;
     strat.clear();
     return buf;
      
}
void chev_strat_data::save_file(QString fle){
 
 orient_cube *pos=0;
 const char *nm=fle.toAscii().constData();
 std::vector<int> b=form_strat_col(pos,false);
 float_1d a=float_1d((int)b.size());
 int val=-1;
 for(int i=0; i < (int)b.size(); i++) {
   if(b[i]==-1){ b[i]=val; val--;}
     a.vals[i]=b[i];
  }   
 std::vector<axis> ax;
 for(int i=0; i< grid->get_ndim(); i++) ax.push_back(grid->get_axis(i+1));
 sregf fl=sregf(ax);
 
 fl.write_description(nm);
 srite(nm,a.vals,4);
 sseek(nm,0,0);
 for(long long i=0; i< grid->get_n123()/n1; i++) srite(nm,a.vals,b.size()*4);

}
float *chev_strat_data::get_float_data(orient_cube *pos, int iax1, int f1, int e1, int iax2,  int f2, int e2){
      if(pos==0 && iax1==0 && f1==0 && e1==0 &&f2==0 && e2==0 && iax2==0);
     assert(1==2);
     //return  check_load_slice(pos,iax1,f1,e1,iax2,f2,e2);
    return 0;
}
void chev_strat_data::set_layer(orient_cube *pos , int ival){
  int i1=pos->get_loc(0);
  if(layers.size()>0){
    std::vector<int> col=form_strat_col(pos,false);
    int imid=i1,ibeg,iend;
    int i=imid;
    while(i>0 &&  col[i]!=-1) i--;
    ibeg=i;
    i=imid;
    while(i <n1-1 && col[i]!=-1) i++;
    iend=i;
    std::vector<int> erlist;
    for(std::map<int,int>::iterator v=layers.begin(); v!=layers.end(); v++){
      if(v->first>ibeg && v->first<iend) {
         erlist.push_back(v->first);
         }
    }
    for(int i=0; i < (int) erlist.size(); i++) layers.erase(erlist[i]);
  }
  
  layers[i1]=ival;
 // form_histo(pos);
}
std::vector<int> chev_strat_data::form_strat_col(orient_cube *pos,bool delete_bound){


  picks_vec *vec;
  std::vector<int> col;
  
  if(pos==0){
     vec=pk->return_all_picks(pos,pick_col);
   }
  else vec=pk->return_all_picks(pos,pick_col);

  int base=126;
  if(layers.size()==1){
      std::map<int,int> :: iterator v=layers.begin();
      base=v->second;
  }
  for(int i=0; i < n1; i++) col.push_back(base);
  for(int i=0; i<vec->return_size();i++){
        pick_new *pk=vec->return_pick(i);
        col[pk->iloc[0]]=-1;
  }
  if(layers.size()>1){
  

    for(std::map<int,int> :: iterator v=layers.begin(); v!=layers.end(); v++){
       int imid=v->first; int val=v->second;
       int i=imid;
       while(i >=0 && col[i] !=-1){
         col[i]=val;
         i--;
       }
       i=imid+1;
       while(i<n1 && col[i]!=-1){

         col[i]=val;
         i++;
       }

    }
  }

  int ilast=0;
         if(delete_bound){
       for(int i=0; i< n1; i++){
         if(col[i]==-1) {
            col[i]=ilast;

            }
         else ilast=col[i];
       }
    }
      delete vec;

  return col;  
}
float chev_strat_data::get_value(orient_cube *pos){
  std::vector<int> col=form_strat_col(pos,true);
  return col[pos->get_loc(0)];
}
QString chev_strat_data::return_histogram(){
 QString b;

 b=QString::number(histo[0]);
 for(int i=1; i< 256;i++){
   b=b+":"+QString::number(histo[i]);
 }
 return b;
}
void chev_strat_data::set_color(QString d){
   display=d; 
}
void chev_strat_data::form_histo(orient_cube *lc){
   std::vector<int> col=form_strat_col(lc,true);

   float mys=0,dv=(maxv-minv)/254;
   for(int i=0; i< 256; i++) histo[i]=0;
   for(int i=0; i < (int)col.size(); i++){
     histo[col[i]]++;
   }
   mys=0;
   for(int i=0; i < 256; i++){
     if(mys<histo[i]) mys=histo[i];
   }
   for(int i=0; i < 256; i++){
     histo[i]=histo[i]/mys;
   }
   col.clear();

 std::vector<QString> com2; com2.push_back(QString::number(inum)); com2.push_back("menu");
    com2.push_back("Clip");
 com2.push_back("set_histo");
 QString b=QString::number(histo[0]);
 for(int i=1; i< 256;i++){
   b=b+":"+QString::number(histo[i]);
 }
 com2.push_back(b);
 //emit actionDetected(com2);
}

