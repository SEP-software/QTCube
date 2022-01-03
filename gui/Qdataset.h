#ifndef Qdataset_H
#define Qdataset_H 1
#include "dataset.h"
#include <QTreeWidgetItem>
#include <assert.h>
#include <qobject.h>

namespace SEP {
class Qdataset : public QObject {
  Q_OBJECT
public:
  int check_load_buffer(std::shared_ptr<orient_cube> pos, const int iax1,
                        const int iax2);
  void build_conv();
signals:
  void actionDetected(std::vector<QString> text);

public:
  Qdataset();

  inline void clean_bufs() { _data->clean_bufs(); }

  virtual std::shared_ptr<SEP::hypercube> return_io_hyper() {
    return _data->return_io_hyper();
  }
  virtual std::shared_ptr<byteTensor2D>
  getCharData(std::shared_ptr<orient_cube> pos, int iax1, int f1, int e1,
              int iax2, int f2, int e2) {
    return _data->getCharData(pos, iax1, f1, e1, iax2, f2, e2);
  }
  virtual std::shared_ptr<byteTensor2D>
  getCharData(std::shared_ptr<orient_cube> pos, int iax1, int iax2, int n,
              long long *index) {
    return _data->getCharData(pos, iax1, iax2, n, index);
  }
  virtual std::shared_ptr<floatTensor2D>
  getFloatData(std::shared_ptr<orient_cube> pos, int iax1, int f1, int e1,
               int iax2, int f2, int e2) {
    return _data->getFloatData(pos, iax1, f1, e1, iax2, f2, e2);
  }
  virtual float get_value(std::shared_ptr<orient_cube> pos) {
    return _data->get_value(pos);
  }
  //}
  virtual std::vector<std::string> return_header_keys() {
    return _data->return_header_keys();
  }
  std::vector<std::string> virtual get_header_vals(
      std::shared_ptr<orient_cube> pos) {
    return _data->get_header_vals(pos);
  }
  std::string return_axis_name(int iax) { return _data->return_axis_name(iax); }
  long long get_trace_num(std::shared_ptr<orient_cube> pos) {
    return _data->get_trace_num(pos);
  }
  void snap_location(float *floc, int single, const std::string &stype) {
    _data->snap_location(floc, single, stype);
  }
  int find_buffer(std::shared_ptr<orient_cube> pos) {
    return _data->find_buffer(pos);
  }
  virtual void afterInitialization() { _data->afterInitialization(); }
  virtual std::shared_ptr<buffer>
  create_buffer(std::shared_ptr<orient_cube> pos, int iax1, int iax2) {
    return _data->create_buffer(pos, iax1, iax2);
  }
  std::string validate_view(const std::string &name,
                            std::shared_ptr<orient_cube> pos) {
    return _data->validate_view(name, pos);
  }
  SEP::axis get_grid_axis(int iax) { return _data->get_grid_axis(iax); }
  SEP::axis get_io_axis(int iax) { return _data->get_io_axis(iax); }
  std::string get_bcolor() { return _data->get_bcolor(); }
  std::string get_type() { return _data->get_type(); }
  std::string get_ecolor() { return _data->get_ecolor(); }
  std::string getRestrict() { return _data->restrict; }
  void set_bcolor(const std::string &col) { _data->set_bcolor(col); }
  void set_ecolor(const std::string &col) { _data->set_ecolor(col); }
  void set_display_axis(int iax, const std::string &x) {
    _data->set_display_axis(iax, x);
  }

  int return_axes_display(int iax) { return _data->return_axes_display(iax); }
  std::vector<float> return_axis_value(int iax,
                                       std::vector<long long> positions) {
    return _data->return_axis_value(iax, positions);
  }
  std::shared_ptr<io_func> getIO() { return _data->io; }
  std::string return_histogram() { return _data->return_histogram(); }
  int add_pt(float pct, float clp) { return _data->add_pt(pct, clp); }
  void del_pt(int ipt) { _data->del_pt(ipt); }
  std::string return_clip() { return _data->return_clip(); }
  std::string data_updated() { return _data->data_updated(); }
  std::string get_name() { return _data->get_name(); }
  std::shared_ptr<SEP::hypercube> return_grid() { return _data->return_grid(); }
  virtual float get_minval() { return _data->get_minval(); }
  virtual float get_maxval() { return _data->get_maxval(); }
  std::string get_values() { return _data->get_values(); }
  std::string get_title_short() { return _data->get_title_short(); }
  virtual void delete_dataset(std::shared_ptr<orient_cube> pos, const int iax1,
                              const int iax2) {
    _data->delete_dataset(pos, iax1, iax2);
  }
  bool valid_display(int iax, int *order, std::vector<int> ns) {
    return valid_display(iax, order, ns);
  }
  virtual bool match_grid() { return _data->match_grid(); }
  virtual void set_contains() { _data->set_contains(); }

  void get_pt(int ipt, float *pct, float *clp) { _data->get_pt(ipt, pct, clp); }
  bool get_data_contain(int iax) { return _data->get_data_contain(iax); }
  virtual void add_pt_action(int *iloc) { _data->add_pt_action(iloc); }
  virtual void del_pt_action(int *iloc) { _data->del_pt_action(iloc); }
  virtual void get_io_loc(int *iloc) { _data->get_io_loc(iloc); }
  virtual bool am_region() { return _data->am_region(); }
  std::string set_pts(float *pcts) { return _data->set_pts(pcts); }
  void clear_pts() { _data->clear_pts(); }

  std::shared_ptr<dataset> _data;
  virtual ~Qdataset() { clean_bufs(); }
}; // namespace SEP

} // namespace SEP

#endif
