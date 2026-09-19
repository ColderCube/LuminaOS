#include "lib/string.h"

#include <cstddef>
#include <cstdint>

void *memcpy(void *dest, const void *src, std::size_t n) {
  std::uint8_t *pdest = static_cast<std::uint8_t *>(dest);
  const std::uint8_t *psrc = static_cast<const std::uint8_t *>(src);

  for (std::size_t i = 0; i < n; i++) {
    pdest[i] = psrc[i];
  }

  return dest;
}

void *memset(void *s, int c, std::size_t n) {
  std::uint8_t *p = static_cast<std::uint8_t *>(s);

  for (std::size_t i = 0; i < n; i++) {
    p[i] = static_cast<uint8_t>(c);
  }

  return s;
}

void *memmove(void *dest, const void *src, std::size_t n) {
  std::uint8_t *pdest = static_cast<std::uint8_t *>(dest);
  const std::uint8_t *psrc = static_cast<const std::uint8_t *>(src);

  if (src > dest) {
    for (std::size_t i = 0; i < n; i++) {
      pdest[i] = psrc[i];
    }
  } else if (src < dest) {
    for (std::size_t i = n; i > 0; i--) {
      pdest[i - 1] = psrc[i - 1];
    }
  }

  return dest;
}

int memcmp(const void *s1, const void *s2, std::size_t n) {
  const std::uint8_t *p1 = static_cast<const std::uint8_t *>(s1);
  const std::uint8_t *p2 = static_cast<const std::uint8_t *>(s2);

  for (std::size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return p1[i] < p2[i] ? -1 : 1;
    }
  }

  return 0;
}

bool checkStringEndsWith(const char *str, const char *end) {
  const char *_str = str;
  const char *_end = end;

  while (*str != 0)
    str++;
  str--;

  while (*end != 0)
    end++;
  end--;

  while (true) {
    if (*str != *end)
      return false;

    str--;
    end--;

    if (end == _end || (str == _str && end == _end))
      return true;

    if (str == _str)
      return false;
  }

  return true;
}
