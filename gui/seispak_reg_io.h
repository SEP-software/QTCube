#ifndef SEISPAK_REG_IO_H
#define SEISPAK_REG_IO_H 1
#include "trace_io.h"


class seispak_reg_io: public trace_io{


  public:
 
   seispak_reg_io(){ }
   ~seispak_reg_io(){  }
  virtual std::vector<QStringList> get_header(long long inum);
    virtual std::vector<QString> get_header_val(long long inum);
   virtual std::vector<QString> return_header_keys();
    virtual int return_header_index(QString x);
   virtual float get_header_num(long long inum, int index);
  virtual QString return_key_name(int index){
     return headers[index];
  }

};

class seispak_reg_io_float: public seispak_reg_io{
  public:
    seispak_reg_io_float(QString file, hypercube *d, bool sw, int in, util *pars);

};
class seispak_reg_io_short: public seispak_reg_io{
  public:
    seispak_reg_io_short(QString file, hypercube *d, bool sw, int in, util *pars);
   void read_block_float(int *nw, int *fw, float *buf);
   void read_block_byte(int *nw, int *fw, unsigned char *buf);
};


#endif
