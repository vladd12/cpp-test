#include <concepts>
#include <cstdint>
#include <cstring>
//#include <format> not implemented in libc++14, lmao
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// just use that as converter
union buffer_converter
{
  static constexpr std::size_t kSize = sizeof(std::uint64_t);
  std::byte m_buffer[kSize];
  std::uint64_t m_value;
};

// shared sized buffer
struct sized_buffer
{
private:
  std::shared_ptr<std::byte[]> m_buffer;
  std::size_t m_size;

public:
  sized_buffer() = delete;
  inline sized_buffer(const std::size_t size) : m_buffer(std::make_shared<std::byte[]>(size)), m_size(size)
  {
  }

  inline std::byte *get() noexcept
  {
    return m_buffer.get();
  }

  inline const std::byte *get() const noexcept
  {
    return m_buffer.get();
  }

  inline std::size_t size() const noexcept
  {
    return m_size;
  }
};

template <std::integral T>
inline sized_buffer generate_random_buffer(const std::size_t elements)
{
  constexpr auto value_size = sizeof(T);
  sized_buffer result { elements * value_size };
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  constexpr auto min = std::numeric_limits<T>::min();
  constexpr auto max = std::numeric_limits<T>::max();
  std::uniform_int_distribution<T> distribution(min, max);
  for (std::size_t idx = 0; idx < elements; ++idx)
  {
    T random_value = distribution(gen);
    std::memcpy(result.get() + idx, &random_value, value_size);
  }
  return result;
}

inline std::uint64_t get_from_buffer(sized_buffer &buffer, const std::size_t idx)
{
  buffer_converter converter;
  std::memcpy(&(converter.m_buffer[0]), buffer.get() + (idx * buffer_converter::kSize), buffer_converter::kSize);
  return converter.m_value;
}

int main()
{
  constexpr std::size_t elements = 10;
  std::uint64_t accumulator = 0;
  sized_buffer buffer = generate_random_buffer<std::uint64_t>(elements);
  for (std::size_t idx = 0; idx < elements; ++idx)
  {
    accumulator += get_from_buffer(buffer, idx);
  }
  // std::cout << std::format("value: {}\n", accumulator); // not implemented in libc++14
  std::cout << "value: " << accumulator << '\n';
  return 0;
}
