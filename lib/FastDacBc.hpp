#ifndef CDA_TRIES_FAST_DAC_BC_HPP
#define CDA_TRIES_FAST_DAC_BC_HPP

#include "Bc.hpp"
#include "BitArray.hpp"
#include "SmallArray.hpp"

namespace cda_tries {

class FastDacBc : public Bc {
public:
  FastDacBc();
  ~FastDacBc();

  void build(const std::vector<bc_t> &bc);

  uint32_t base(uint32_t pos) const {
    return access_(pos * 2) ^ pos;
  }
  uint32_t link(uint32_t pos) const {
    return values_1st_[pos * 2] | (extras_[leaf_flags_.rank(pos)] << 8);
  }
  uint32_t check(uint32_t pos) const {
    return access_(pos * 2 + 1) ^ pos;
  }
  bool is_leaf(uint32_t pos) const {
    return leaf_flags_[pos];
  }
  bool is_fixed(uint32_t pos) const {
    return check(pos) != pos;
  }

  size_t size() const;
  size_t size_in_bytes() const;
  size_t num_emps() const;
  double bytes_per_elem() const;
  void stat(std::ostream &os) const;

  void write(std::ostream &os) const;
  void read(std::istream &is);

  void clear();

  FastDacBc(const FastDacBc &) = delete;
  FastDacBc &operator=(const FastDacBc &) = delete;

private:
  Array<uint8_t>  values_1st_;
  Array<uint16_t> values_2nd_;
  Array<uint32_t> values_3rd_;
  Array<uint32_t> ranks_[2];
  BitArray leaf_flags_;
  SmallArray extras_;
  size_t num_emps_ = 0;

  uint32_t access_(uint32_t pos) const;
  size_t dac_size_in_bytes_() const;
};

} // cda_tries

#endif // CDA_TRIES_FAST_DAC_BC_HPP
