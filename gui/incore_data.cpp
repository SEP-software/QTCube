#include "incore_data.h"
#include "float_buffer.h"
#include "float_mmap_buffer.h"
#include "byte_buffer.h"
#include "sregf.h"
incore_data_float::incore_data_float(std::string title,QString nm,hypercube *g,io_func *i, param_func *p, int in,int
mmap,int im){
    mmap_it=mmap;

  set_basics(title,nm,g,i,p,in,im);

    datas=io->return_hyper();
 
}

buffer *incore_data_float::create_buffer(orient_cube *pos, int iax1, int iax2){

   int nw[8],fw[8];
   std::vector<axis> axes=grid->return_axes(8);
   for(int i=0; i< 8; i++){
     nw[i]=axes[i].n;
     fw[i]=0;
   }

   if(iax1==0 && iax2==0 && pos==0);
   if(mmap_it==1){
      float_mmap_buffer *b=new float_mmap_buffer(par,grid,io,inum,nw,fw);
      return b;
   }
    float_buffer *b=new float_buffer(par,grid,io,inum,nw,fw);
     return b;
}

incore_data_byte::incore_data_byte(std::string title,QString nm, hypercube *g,io_func *i, param_func *p, int in,int im){
  set_basics(title,nm,g,i,p,in,im);
  datas=io->return_hyper();

}
buffer *incore_data_byte::create_buffer(orient_cube *pos, int iax1, int iax2){
 
 
   int nw[8],fw[8];
   std::vector<axis> axes=grid->return_axes(8);
   for(int i=0; i< 8; i++){
     nw[i]=axes[i].n;
     fw[i]=0;
   }

  
   
   if(iax1==0 && iax2==0 && pos==0);
    byte_buffer *b=new byte_buffer(par,grid,io,inum,nw,fw);
   return b;
}
