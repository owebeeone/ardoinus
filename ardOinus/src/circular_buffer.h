
#ifndef CIRCULAR_BUFFER__H
#define CIRCULAR_BUFFER__H

#include "setl_cyclic_int.h"
#include "setl_system.h"

#include "setlx_array.h"
#include "setlx_type_traits.h"
#include "setlx_cstdint.h"
#include "setlx_cassert.h"

namespace setl {
#pragma warning( push )
#pragma warning( disable : 4101 )

/**
 * Provides interrupt safe circular buffer where all elements of the buffer
 * can be used.
 *
 * The tradeoff is slightly slower speed and code size but smaller RAM
 * utilization. Only really useful when the bufferred elements are large.
 * See: https://goo.gl/CHpTNa for a design description.
 * Use the template parameter full_use = true to use this version.
 */
template <typename T, std::uint32_t w_size, bool w_is_full_use = false, typename S = System>
class CircularBuffer {
public:
  static const bool value_type_is_volatile = std::is_volatile<T>::value;
  static const std::uint32_t size = w_size;
  static_assert(w_is_full_use, "Wrong template used");
  enum { is_full_use = true };

  using memory_barrier = typename std::conditional<value_type_is_volatile, 
    typename S::MemoryBarrier, NopMemoryBarrier>::type;
  using index_type = CyclicInt<size * 2, value_type_is_volatile>;
  using nv_index_type = CyclicInt<size * 2, false>;
  using index_int_type = typename nv_index_type::nv_type;

  using value_type = T;
  using nv_value_type = typename std::remove_volatile<value_type>::type;

  static const index_int_type BIT_SET = index_int_type(1u);
  static const index_int_type BIT_CLEAR = ~BIT_SET;

  /** 
   * Writes a value if there is space in the buffer and returns true on success. 
   * In asynchronous use, must be called only be called by only one writer.
   */
  bool write(const nv_value_type& value) {
    memory_barrier barrier;

    if (has_overrun) {
      return false;
    }

    nv_index_type to_copy = to;
    nv_index_type from_copy = from;

    // By design, diff by 1 means full when lower number has lsb set.
    auto from_sub_to = from_copy - to_copy;
    bool to_partial = to_copy.get() & BIT_SET;
    if (to_partial && from_sub_to.get() == 1) {
      has_overrun = true;
      return false;
    }

    // Check other side of full condition.
    auto to_sub_from = to_copy - from_copy;
    bool from_partial = from_copy.get() & BIT_SET;
    if (from_partial && to_sub_from.get() == 1) {
      has_overrun = true;
      return false;
    }

    // 0 means empty and 4 or more means we have plenty of room.
    if (from_sub_to.get() == 0 || from_sub_to.get() > 3) {
      ++to_copy;
      // Order here is important.
      values[to_copy.get() >> 1] = value;
      ++to_copy;
      to = to_copy;
      return true;
    }

    // Turn the 4 cases into 2.
    if (from_partial) {
      from_partial = false;
      --from_sub_to;
      ++to_copy;
    }

    // Writes the last empty slot.
    values[to_copy.get() >> 1] = value;

    // Handle making to and from different.
    to_copy += 3u - from_sub_to.get();

    to = to_copy;
    return true;
  }

  /**
  * Reads a value if there is data to be read.
  * In asynchronous use, must be called only be called by only one reader.
  * Returns true if data was written to result.
  */
  bool read(nv_value_type& result) {
    memory_barrier barrier;

    nv_index_type to_copy = to;
    nv_index_type from_copy = from;

    // Equal index means empty.
    if (to_copy == from_copy) {
      return false;
    }

    ++from_copy;
    // Reading result.
    result = values[from_copy.get() >> 1u];

    if (to_copy == from_copy) {
      if (from_copy.get() & BIT_SET) {
        from = to_copy;  // indicate empty.
      } else {
        from = from_copy + 2u; // was a full state.
      }
      return true;
    }

    ++from_copy;
    if (from_copy.get() & BIT_SET) {
      if ((to_copy - from_copy).get() == 1u) {
        from = to_copy;
      } else {
        from_copy.unsetLsb();
        from = from_copy;
      }
    } else {
      from = from_copy;
    }

    return true;
  }

  /** Returns true if there was an overrun. */
  bool overrun() const {
    return has_overrun;
  }

  /** Clears all data and error states. Should only be called by reader. */
  void clear() {
    memory_barrier barrier;

    // Reset pointers first.
    from = to;  // Only change the reader side variable.

    // Then clear overrun state, this allows writer to write again.
    has_overrun = false;
  }

private:
  std::array<value_type, size> values;

  // Last read location. An extra bit is needed to indicate having read the position.
  // Initialize to 1 indicating the zero element has been read.
  index_type from{ 0 }; // only reader can modify.

  using bool_type = typename std::conditional<value_type_is_volatile, volatile bool, bool>::type;

  bool_type has_overrun = false;  // Writer writes true, reader writes false.

  // Last written location.
  index_type to{ 0 };  // only writer (usually isr) can modify.
};

/**
 * Provides interrupt safe circular buffer.
 *
 * This version does not make full use of the elements allocated and hence
 * may use more memory. One element more than the requested size is allocated but
 * this algorithm is simpler and faster.
 */
template <typename T, std::uint32_t w_size, typename S>
class CircularBuffer<T, w_size, /*is_full_use=*/ false, S> {
public:
  static const bool value_type_is_volatile = std::is_volatile<T>::value;
  static const std::uint32_t size = w_size;
  enum { is_full_use = false };

  using memory_barrier = typename std::conditional<value_type_is_volatile,
    System::MemoryBarrier, NopMemoryBarrier>::type;
  using index_type = CyclicInt<size + 1, value_type_is_volatile>;
  using nv_index_type = CyclicInt<size + 1, false>;
  using index_int_type = typename nv_index_type::nv_type;

  using value_type = T;
  using nv_value_type = typename std::remove_volatile<value_type>::type;


  /**
   * Writes a value if there is space in the buffer and returns true on success.
   * In asynchronous use, must be called only be called by only one writer.
   */
  bool write(const nv_value_type& value) {
    memory_barrier barrier;

    if (has_overrun) {
      return false;
    }

    nv_index_type to_copy = to;
    nv_index_type from_copy = from;

    if (to_copy == from_copy) {
      has_overrun = true;
      return false;
    }
    // Order is important.
    values[to_copy.get()] = value;

    ++to_copy;
    to = to_copy;
    return true;
  }

  /**
   * Reads a value if there is data to be read.
   * In asynchronous use, must be called only be called by only one reader.
   * Returns true if data was written to result.
   */
  bool read(nv_value_type& result) {
    memory_barrier barrier;

    nv_index_type to_copy = to;
    nv_index_type from_copy = from;

    ++from_copy;
    if (from_copy == to_copy) {
      return false;
    }

    // Order is important.
    result = values[from_copy.get()];
    from = from_copy;

    return true;
  }

  /** Returns true if there was an overrun. */
  bool overrun() const {
    return has_overrun;
  }

  /** Clears all data and error states. Should only be called by reader. */
  void clear() {
    memory_barrier barrier;

    // Reset pointers first.
    auto to_copy = to;
    from = --to_copy;  // Indicate data is clear by only setting the reader side value.

    // Then clear overrun state, this allows writer to write again.
    has_overrun = false;
  }

private:
  std::array<value_type, size + 1> values;

  // Last read location. An extra bit is needed to indicate having read the position.
  // Initialize to 1 indicating the zero element has been read.
  index_type from{ 0 }; // only reader can modify.

  using bool_type = typename std::conditional<value_type_is_volatile, volatile bool, bool>::type;

  bool_type has_overrun = false;  // Writer writes true, reader writes false.

                                  // Last written location.
  index_type to{ 1 };  // only writer (usually isr) can modify.
};
#pragma warning( pop )

} // namespace
#endif