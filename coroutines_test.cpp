#include <expected>

#include <gmock/gmock.h>

using namespace ::testing;

enum class parse_error {
  invalid_input,
  overflow,
};

auto parse_number(std::string_view str) -> std::expected<double, parse_error> {
  const auto begin = str.data();
  char *readto = nullptr;
  const auto ret = std::strtod(begin, &readto);

  if (begin == readto) {
    return std::unexpected(parse_error::invalid_input);
  } else if (std::isinf(ret)) {
    return std::unexpected(parse_error::overflow);
  } else {
    return ret;
  }
}

TEST(parse_number, parse_number_test) {
  using namespace std::string_view_literals;
  EXPECT_THAT(parse_number("10.0"sv), Eq(10.0));
  EXPECT_THAT(parse_number("hello"sv),
              Eq(std::unexpected(parse_error::invalid_input)));

  const auto thousand = "1000"sv;
  const auto ten_substr = thousand.substr(0, 2);
  EXPECT_THAT(ten_substr, StrEq("10"));
  EXPECT_THAT(parse_number(ten_substr), Eq(1000));
}
