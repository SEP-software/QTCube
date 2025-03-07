#ifndef PICK_NEW_H
#define PICK_NEW_H 1
#define TYPE_DEFAULT -10
#define EXTRA_DEFAULT -9999
#include <memory>
#include <vector>
#include "position.h"
namespace SEP {
class pick_new {
 public:
  pick_new() {}
  pick_new(int *iloc, long long p, int te, const std::string &col, int ex,
           const std::string &t);
  inline int *return_loc() { return iloc; }
  inline long long return_pos() { return pos; }
  void print();
  ~pick_new() { pick_delete(); }
  void pick_delete();
  std::shared_ptr<SEP::pick_new> clone() {
    std::shared_ptr<SEP::pick_new> y(
        new pick_new(iloc, pos, type, col, extra, txt));
    return y;
  }
  long long pos;
  int type;
  std::string col;
  std::string txt;
  int extra;
  int iloc[8];
  int info;
};
class picks_vec {
 public:
  picks_vec() {}
  void add_pick(std::shared_ptr<SEP::pick_new> p) { picks.push_back(p); }
  std::shared_ptr<SEP::pick_new> return_pick(int i) { return picks[i]; }
  int return_size() { return picks.size(); }
  std::vector<std::shared_ptr<SEP::pick_new>> picks;
};
class picks_new {
 public:
  picks_new() { setit = -1; }
  std::shared_ptr<pick_new> get_pick(long long p, const std::string &col);
  picks_new(std::shared_ptr<position> pos);
  std::shared_ptr<pick_new> add_pick(int *iloc, long long p, int te,
                                     const std::string &col, int ex,
                                     const std::string &t);
  void del_pick(long long p, const std::string &col);
  std::shared_ptr<picks_vec> get_parse_picks(const std::string col = "None",
                                             int type = TYPE_DEFAULT,
                                             int extra = EXTRA_DEFAULT,
                                             const std::string txt = "None");
  void get_parse_picks(std::shared_ptr<SEP::picks_vec> picks,
                       const std::string col = "None", int type = TYPE_DEFAULT,
                       int extra = EXTRA_DEFAULT,
                       const std::string txt = "None");
  void delete_pick_type(int typ);
  std::shared_ptr<pick_new> return_pick(int i) { return bucket[i]; }
  int return_size() { return bucket.size(); }
  void delete_picks();
  void print(int i);
  ~picks_new() { delete_picks(); }

 private:
  std::shared_ptr<position> myp;
  int setit;
  std::vector<std::shared_ptr<SEP::pick_new>> bucket;
};

}  // namespace SEP

#endif
