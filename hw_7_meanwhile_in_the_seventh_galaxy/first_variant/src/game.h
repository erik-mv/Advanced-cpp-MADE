#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H

#include "binary.h"
#include "xor_sum.h"

template <size_t last_bit, size_t last_index, size_t last_heap,
          size_t... remains>
struct get_heap {
  static constexpr bool bit = GetBit<last_bit, last_heap>::value;

  static constexpr size_t index =
      bit * last_index +
      !bit * get_heap<last_bit, last_index + 1, remains...>::index;

  static constexpr size_t heap =
      bit * last_heap +
      !bit * get_heap<last_bit, last_index + 1, remains...>::heap;
};

template <size_t last_bit, size_t last_index, size_t last_heap>
struct get_heap<last_bit, last_index, last_heap> {
  static constexpr bool bit = GetBit<last_bit, last_heap>::value;

  static constexpr size_t index = bit * last_index - !bit;

  static constexpr size_t heap = bit * last_heap - !bit;
};

template <size_t... Heaps>
struct Game {
  static constexpr bool first_player_wins = XorSum<Heaps...>::value;

  static constexpr size_t last_bit = Log2<XorSum<Heaps...>::value>::value;
  static constexpr ssize_t first_move_heap_index =
      first_player_wins * get_heap<last_bit, 0, Heaps...>::index -
      !first_player_wins;

  static constexpr size_t last_heap = get_heap<last_bit, 0, Heaps...>::heap;
  static constexpr ssize_t first_move_rocks_count =
      first_player_wins *
          (last_heap - XorSum<XorSum<Heaps...>::value, last_heap>::value) -
      !first_player_wins;
};

#endif  /// MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H.
