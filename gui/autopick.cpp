#include "autopick.h"
#include "auto_brown.h"
#include "auto_viteribi.h"
#include "lloyd_1d.h"
using namespace SEP;
autopick::autopick(std::shared_ptr<pick_draw> _pks) {
  ncor = 20;
  nsearch = 20;
  correlate = true;
  nail = 1000.;
  cur_auto = 2;
  accept = 1;
  pks = _pks;
  pen_o = -3.;
  pen_e = 3;
  error = 0.;
  dip = 0;
  auto_2d = 0;
  method = "viterbi";
  plane = "left";
}
void autopick::create_viteribi() {
  if (auto_2d) auto_2d.reset();
  std::shared_ptr<auto_viteribi> x(new auto_viteribi(pen_o, pen_e, nail));
  auto_2d = x;
}
void autopick::create_brown() {
  if (auto_2d) auto_2d.reset();
  std::shared_ptr<auto_brown> x(new auto_brown(pen_o, pen_e, nail));
  auto_2d = x;
}
void autopick::init_method() {
  if (method.contains("iter")) create_viteribi();
  if (method.contains("Brown")) create_brown();
}
int autopick::extend_picks(std::shared_ptr<view> myv,
                           std::shared_ptr<orient_cube> pos) {
  cur_auto += 1;
  init_method();
  int iax1, iax2, iax3;
  int order[8];
  int isingle = pks->get_single();
  if (pos->get_rotate()) return 0;

  pos->get_orders(order);
  if (plane.contains("top")) {
    iax1 = order[1];
    iax2 = order[2];
    iax3 = order[0];
  } else if (plane.contains("left")) {
    iax1 = order[0];
    iax2 = order[2];
    iax3 = order[1];
  } else {
    iax1 = order[0];
    iax2 = order[1];
    iax3 = order[2];
  }

  if (iax1 != isingle && iax2 != isingle) return 0;
  int isort = 0;
  if (iax1 == isingle) {
    isort = iax2;
  } else if (iax2 == isingle) {
    isort = iax1;
  }
  float fpos[8], os[8], ds[8];
  for (int i = 0; i < 8; i++) {
    fpos[i] = pos->get_pos(i);
  }
  int ibeg = pos->get_beg(iax3);
  int iend = pos->get_end(iax3);
  pos->get_os(os);
  pos->get_ds(ds);
  int iloc[8];
  pos->get_locs(iloc);
  for (int i3 = ibeg; i3 < iend; i3++) {
    fpos[iax3] = os[iax3] + ds[iax3] * i3;
    iloc[iax3] = i3;

    QString col = pks->get_active_col();

    std::shared_ptr<pairs_new> myp(
        pks->get_pts_sort_le(pos, iax1, iax2, accept, isort, col));

    pick_line(myv, fpos, pos, iax1, iax2, isort, isingle, myp, iax3);
  }
  cur_auto += 1;
  return 0;
}
int autopick::pick_2d(std::shared_ptr<view> myv,
                      std::shared_ptr<orient_cube> pos) {
  init_method();

  QString col = pks->get_active_col();

  for (int islc = 0; islc < (int)myv->slices.size(); islc++) {
    int iax1 = myv->slices[islc]->get_iax1();
    int iax2 = myv->slices[islc]->get_iax2();
    int isingle = pks->get_single();

    if (iax1 == isingle || iax2 == isingle) {
      int isort = 0;
      if (iax1 == isingle) {
        isort = iax2;
      } else if (iax2 == isingle) {
        isort = iax1;
      }
      float fpos[8];
      for (int i = 0; i < 8; i++) {
        fpos[i] = pos->get_pos(i);
      }

      std::shared_ptr<pairs_new> myp = pks->get_pts_sort_le(
          pos, myv->slices[islc]->get_iax1(), myv->slices[islc]->get_iax2(),
          accept, isort, col);

      pick_line(myv, fpos, pos, iax1, iax2, isort, isingle, myp, -1);
    }
  }
  cur_auto += 1;
  return cur_auto;
}
// WORK ON THIS
void autopick::decline_picks() {
  cur_auto--;
  QString col = pks->get_active_col();

  pks->delete_pick_vals(cur_auto, col);
}
void autopick::pick_line(std::shared_ptr<view> myv, float *fpos,
                         std::shared_ptr<orient_cube> pos, int iax1, int iax2,
                         int isort, int isingle, std::shared_ptr<pairs_new> myp,
                         int iax3) {
  QString col = pks->get_active_col();
  if (fpos == 0 && iax3 == 0) {
    ;
  };
  if (myp->size() > 1) {
    int il[8];
    pos->get_locs(il);
    il[iax1] = il[iax2] = -1;
    pks->clear_picks(pos, il, col);
    axis a = pos->get_orient_axis(isort), b = pos->get_orient_axis(isingle);
    float osort = a.o, dsort = a.d;
    float osingle = b.o, dsingle = b.d;
    osort += pos->get_beg(isort) * dsort;
    osingle += pos->get_beg(isingle) * dsingle;
    std::vector<int> loc_p;
    for (int i = 0; i < (int)myp->size(); i++) {
      loc_p.push_back(myp->vals[i].y);
    }

    int f = loc_p[0], n = loc_p[loc_p.size() - 1] - f + 1;
    std::shared_ptr<float1DReg> line(new float1DReg(n));
    myp->build_int_line(f, n, (float *)line->getVoidPtr());
    std::shared_ptr<float2DReg> sim;

    if (correlate) {
      std::shared_ptr<float2DReg> ar = extract_dat(
          pos, myv->cur_dat, isingle, isort, line, nsearch + ncor, f);

      std::vector<int> close;
      for (int i = 0; i < (int)myp->size(); i++) {
        close.push_back(myp->vals[i].y - f);
      }

      sim = correlate_it(ar, ncor, close);

    } else {
      sim = extract_dat(pos, myv->cur_dat, isingle, isort, line, nsearch, f);
    }
    // Normalize it to max 1
    double mx = sim->absMax();
    sim->scale(1. / mx);
    std::vector<int> locs;
    for (int i = 0; i < (int)myp->size(); i++) {
      locs.push_back(myp->vals[i].y - f);
    }
    std::vector<path> mypath = auto_2d->return_path(locs, sim);
    locs.clear();

    std::vector<float> tr;
    std::vector<int> iloc;
    if (error > .01) {
      for (int i = 0; i < (int)mypath.size(); i++)
        tr.push_back(mypath[i].ix * 1.);
      int nlenc = mypath.size() / 3;
      if (nlenc > 40) nlenc = 40;
      lloyd_1d_fit *fit = new lloyd_1d_fit(tr, nlenc, error / 100.);
      for (int iter = 0; iter < 35; iter++) {
        fit->do_iter(iter);
      }
      for (int i = 0; i < (int)fit->center.size(); i++)
        iloc.push_back((int)fit->center[i]);
      delete fit;
    } else {
      for (int i = 0; i < (int)mypath.size(); i++) iloc.push_back(i);
    }

    int oc = pos->get_orient_num();
    for (int i = 0; i < (int)iloc.size(); i++) {
      bool newp = true;
      for (int j = 0; j < (int)loc_p.size(); j++)
        if (loc_p[j] == f + iloc[i]) newp = false;

      il[isingle] = mypath[iloc[i]].ix - nsearch + (*line->_mat)[iloc[i]];
      il[isort] = f + iloc[i];
      if (newp) pks->add_rotated_pt(oc, il, cur_auto);
      //   else pks->add_rotated_pt(oc,il,1);
      //  }
    }
  }
}
int autopick::flat_view(std::shared_ptr<view> myv,
                        std::shared_ptr<orient_cube> pos) {
  cur_auto += 1;
  if (!myv || !pos) {
    ;
  };

  return 0;
}

std::shared_ptr<float2DReg> autopick::correlate_it(
    std::shared_ptr<float2DReg> ar, int ncor, std::vector<int> close) {
  axis ax[2], ain1, ain2;
  ;
  ain1 = ar->getHyper()->getAxis(1);
  ax[1] = ain2 = ar->getHyper()->getAxis(2);
  ax[0] = ain1;
  ax[0].n = ax[0].n - 2 * ncor;
  std::shared_ptr<float2DReg> out(new float2DReg(ax[0], ax[1]));

  // int center=ax[0].n/2;
  float master[ain1.n];

  int iout = 0, cold = ain1.n / 2, imaster, ishift;
  float f;
  int iless = 0, iloc = 0;
  for (int i2 = 0; i2 < ain2.n; i2++) {
    // construct master
    for (int i = 0; i < (int)close.size(); i++) {
      if (close[i] <= i2) {
        iless = close[i];
        iloc = i;
      }
    }
    if (i2 == iless || iloc == (int)close.size() - 1) {  // Right on pick
      for (int i = 0; i < ain1.n; i++) master[i] = (*ar->_mat)[close[iloc]][i];

    } else {
      f = ((float)(i2 - iless) / ((float)(close[iloc + 1] - close[iloc])));
      for (int i = 0; i < ain1.n; i++) {
        master[i] = (*ar->_mat)[close[iloc]][i] * (1. - f) +
                    (*ar->_mat)[close[iloc + 1]][i] * f;
      }
    }
    out->scale(0.);
    for (int i1 = 0; i1 < ax[0].n; i1++) {
      imaster = cold - ncor;
      ishift = i1 + i2 * ain1.n;
      for (int i = 0; i < ncor; i++) {
        (*out->_mat)[i2][i1] += master[i + imaster] * (*ar->_mat)[i2][i1 + i];
      }
    }
  }
  return out;
}

std::shared_ptr<float2DReg> autopick::extract_dat(
    std::shared_ptr<orient_cube> pos, std::shared_ptr<dataset> cur_dat,
    int isingle, int isort, std::shared_ptr<float1DReg> line, int ns, int f2) {
  int n1 = 1, n2 = 1;
  unsigned char *buf;

  n1 = cur_dat->get_grid_axis(isingle + 1).n;
  n2 = cur_dat->get_grid_axis(isort + 1).n;

  int b1 = 0, b2 = 0, e1 = n1, e2 = n2;
  if (e1 == e2) {
    ;
  };
  // b1=pos->get_beg(isingle); b2=pos->get_beg(isort);
  // e1=pos->get_end(isingle); e2=pos->get_end(isort);
  std::shared_ptr<byteTensor2D> bufA= cur_dat->getCharData(pos, isingle, 0, n1, isort, 0, n2);
  buf=bufA->getVals();
  axis axes[2];
  axes[0] = axis(ns * 2 + 1);
  axes[1] = axis(line->getHyper()->getAxis(1).n);
  std::shared_ptr<float2DReg> dat(new float2DReg(axes[0], axes[1]));
  int i;
  float f;
  int ishift;

  for (int i2 = 0; i2 < axes[1].n; i2++) {
    f = (*line->_mat)[i2] + b1;
    ishift = (int)f;
    f = f - ishift;
    for (int i1 = 0; i1 < ns * 2 + 1; i1++) {
      i = ishift - ns + i1;
      if (i < 0)
        (*dat->_mat)[i2][i1] = 0;
      else if (i > n1 - 2)
        (*dat->_mat)[i2][i1] = 0;
      else
        (*dat->_mat)[i2][i1] = (1. - f) * buf[i + (i2 + b2 + f2) * n1] +
                               f * buf[i + 1 + (i2 + b2 + f2) * n1] - 128;
    }
  }

  return dat;
}
