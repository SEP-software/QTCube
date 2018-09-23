#include "byte_buffer_buffer.h"
#include <stdlib.h>
#include <iostream>
#include "buffersRegFile.h"
#include "byte2DReg.h"
#include "fileIO.h"
#include "simpleMemoryLimit.h"
using namespace SEP;
// Initialize and read in buffer
byte_buffer_buffer::byte_buffer_buffer(std::shared_ptr<paramObj> p,
                                       std::shared_ptr<hypercube> h,
                                       std::shared_ptr<io_func> i, int in,
                                       std::vector<int> &nwbuf,
                                       std::vector<int> &fwbuf, const int mem) {
  set_basics(p, h, i, in);

  std::shared_ptr<fileIO> fIO = std::dynamic_pointer_cast<fileIO>(i);
  if (!fIO) {
    std::cerr << "Can only specify buffered IO with a buffered file"
              << std::endl;
    assert(fIO);
  }
  std::shared_ptr<genericRegFile> f = fIO->getFile();
  _file = std::dynamic_pointer_cast<buffersRegFile>(f);
  if (!_file) {
    std::cerr << "Can only specify buffered IO with a buffered file"
              << std::endl;
    assert(_file);
  }
  std::shared_ptr<IO::simpleMemoryLimit> memS(
      new IO::simpleMemoryLimit(mem * 1024));
  _file->setMemoryUsage(memS);
  _ndim = _file->getHyper()->getNdim();

  _minV = _file->getFloat("minval", 0.);
  _maxV = _file->getFloat("minval", 255.);
  _delta = (_maxV - _minV) / 255;
}

unsigned char *byte_buffer_buffer::get_char_data(int n, long long *index) {
  assert(1 == 2);
}

unsigned char *byte_buffer_buffer::get_char_data(
    std::shared_ptr<orient_cube> pos, int iax1, int f1, int e1, int iax2,
    int f2, int e2) {
  if (!hold[iax1] || !hold[iax2])
    _par->error("Internal error don't hold axes requested");
  std::vector<int> jw(_ndim, 1);
  std::vector<int> nw(_ndim, 1);
  std::vector<int> fw(_ndim, 1);
  pos->set_no_rotate();

  for (int idim = 0; idim < _ndim; idim++) {
    if (idim == iax1) {
      if (f1 > e1) {
        fw[idim] = f1;
        nw[idim] = e1 - f1;
      } else {
        fw[idim] = e1;
        nw[idim] = f1 - e1;
      }

    } else if (idim == iax2) {
      if (f2 > e2) {
        fw[idim] = f2;
        nw[idim] = e2 - f2;
      } else {
        fw[idim] = e2;
        nw[idim] = f2 - e2;
      }
    } else {
      fw[idim] = pos->loc[idim];
    }
  }
  int n1 = abs(e1 - f1), n2 = abs(e2 - f2);
  std::shared_ptr<byte2DReg> flt(new byte2DReg(n1, n2));
  _file->readUCharWindow(nw, fw, jw, (unsigned char *)flt->getVoidPtr());
  _minV = std::min((float)flt->min(), _minV);
  _maxV = std::max((float)flt->max(), _maxV);
  float j = (_maxV - _minV) / 255.;
  unsigned char *out = new unsigned char[n1 * n1];
  int i = 0;

  if (e2 > f2) {
    if (e1 > f1) {
      for (int i2 = 0; i2 < n2; i2++) {
        for (int i1 = 0; i1 < n1; i1++, i++) {
          out[i] = (*flt->_mat)[i2][i1] * _delta + _minV;
        }
      }
    } else {
      for (int i2 = 0; i2 < n2; i2++) {
        for (int i1 = 0; i1 < n1; i1++, i++) {
          out[i] = (*flt->_mat)[i2][n1 - 1 - i1] * _delta + _minV;
        }
      }
    }
  } else {
    if (e1 > f1) {
      for (int i2 = 0; i2 < n2; i2++) {
        for (int i1 = 0; i1 < n1; i1++, i++) {
          out[i] = (*flt->_mat)[n2 - 1 - i2][i1] * _delta + _minV;
          ;
        }
      }
    } else {
      for (int i2 = 0; i2 < n2; i2++) {
        for (int i1 = 0; i1 < n1; i1++, i++) {
          out[i] = (*flt->_mat)[n1 - 1 - i2][n1 - 1 - i1] * _delta + _minV;
        }
      }
    }
  }

  /*
    int n1 = abs(e1 - f1), n2 = abs(e2 - f2);
    if (pos->get_rotate() && (!hold[pos->rot_ax[0]] || !hold[pos->rot_ax[1]])) {
      fprintf(stderr, "Must hold rotated axes. Defaulting to no rotation.\n");
      pos->set_no_rotate();
    }

    long long *index = form_index_map(pos, iax1, iax2, f1, e1, f2, e2);

    unsigned char *out = get_char_data(n1 * n2, index);
    delete[] index;
    */
  return out;
}

float *byte_buffer_buffer::get_float_data(std::shared_ptr<orient_cube> pos,
                                          int iax1, int f1, int e1, int iax2,
                                          int f2, int e2) {
  if (!hold[iax1] || !hold[iax2])
    _par->error("Internal error don't hold axes requested");
  std::vector<int> jw(_ndim, 1);
  std::vector<int> nw(_ndim, 1);
  std::vector<int> fw(_ndim, 1);
  pos->set_no_rotate();

  for (int idim = 0; idim < _ndim; idim++) {
    if (idim == iax1) {
      if (f1 > e1) {
        fw[idim] = f1;
        nw[idim] = e1 - f1;
      } else {
        fw[idim] = e1;
        nw[idim] = f1 - e1;
      }

    } else if (idim == iax2) {
      if (f2 > e2) {
        fw[idim] = f2;
        nw[idim] = e2 - f2;
      } else {
        fw[idim] = e2;
        nw[idim] = f2 - e2;
      }
    } else {
      fw[idim] = pos->loc[idim];
    }
  }
  int n1 = abs(e1 - f1), n2 = abs(e2 - f2);
  std::shared_ptr<byte2DReg> flt(new byte2DReg(n1, n2));
  _file->readUCharWindow(nw, fw, jw, (unsigned char *)flt->getVoidPtr());
  _minV = std::min((float)flt->min(), _minV);
  _maxV = std::max((float)flt->max(), _maxV);
  float *out = new float[n1 * n1];
  int i = 0;

  if (e2 > f2) {
    if (e1 > f1) {
      for (int i2 = 0; i2 < n2; i2++) {
        for (int i1 = 0; i1 < n1; i1++, i++) {
          out[i] = (*flt->_mat)[i2][i1];
        }
      }
    } else {
      for (int i2 = 0; i2 < n2; i2++) {
        for (int i1 = 0; i1 < n1; i1++, i++) {
          out[i] = (*flt->_mat)[i2][n1 - 1 - i1];
        }
      }
    }
  } else {
    if (e1 > f1) {
      for (int i2 = 0; i2 < n2; i2++) {
        for (int i1 = 0; i1 < n1; i1++, i++) {
          out[i] = (*flt->_mat)[n2 - 1 - i2][i1];
          ;
        }
      }
    } else {
      for (int i2 = 0; i2 < n2; i2++) {
        for (int i1 = 0; i1 < n1; i1++, i++) {
          out[i] = (*flt->_mat)[n1 - 1 - i2][n1 - 1 - i1];
        }
      }
    }
  }

  /*
    int n1 = abs(e1 - f1), n2 = abs(e2 - f2);
    if (pos->get_rotate() && (!hold[pos->rot_ax[0]] || !hold[pos->rot_ax[1]]))
    { fprintf(stderr, "Must hold rotated axes. Defaulting to no rotation.\n");
      pos->set_no_rotate();
    }

    long long *index = form_index_map(pos, iax1, iax2, f1, e1, f2, e2);

    unsigned char *out = get_char_data(n1 * n2, index);
    delete[] index;
    */
  return out;
}

void byte_buffer_buffer::calc_histo() {
  for (int i = 0; i < 256; i++) histo[i] = 0;

  /*
  long long count[256];
  for (int i = 0; i < 256; i++) count[i] = 0;
  io->return_clips(&bclip, &eclip);
  float j = eclip - bclip;
  int b;
  for (long long i = 0; i < n123_view; i++) {
    b = (int)(255 * (fbuf[i] - bclip) / j + .5);
    if (b < 0)
      b = 0;
    else if (b > 255)
      b = 255;
    count[b]++;
  }
  long long mym = 0;
  for (int i = 0; i < 256; i++) {
    if (count[i] > mym) mym = count[i];
  }
  for (int i = 0; i < 256; i++) {
    histo[i] = (float)count[i] / (float)mym;
  }
  */
}

float byte_buffer_buffer::get_value(std::shared_ptr<orient_cube> pos) {
  std::vector<int> nw(_ndim, 1), fw(_ndim), jw(_ndim, 1);

  for (int idim = 0; idim < _ndim; idim++) {
    fw[idim] = pos->loc[idim];
  }
  float pt;
  _file->readFloatWindow(nw, fw, jw, &pt);

  return pt;
}
