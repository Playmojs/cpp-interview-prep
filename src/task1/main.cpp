#include <cassert>
#include <string>
#include <string_view>

/*
Task: Implement the CommandParser class such that the code below compiles and
runs without assertion errors.
*/

enum class ParseResult {
  OK,
  ERROR,
  // feel free to add specific error codes
};

class CommandParser {
  // your implementation
};

// Do not change any code below this line

struct CommandA {
  int arg1{};
  std::string arg2;

  ParseResult parse(std::string_view input) {
    return CommandParser(input)
        .require_name("a")
        .parse_arg(arg1)
        .parse_arg(arg2)
        .validate();
  }
};

struct CommandB {
  int arg1{};
  int arg2{};
  float arg3{};

  ParseResult parse(std::string_view input) {
    return CommandParser(input)
        .require_name("b")
        .parse_arg(arg1)
        .parse_arg(arg2)
        .parse_arg(arg3)
        .validate();
  }
};

int main() {
  CommandA a;
  CommandB b;
  ParseResult result;

  result = a.parse("a 1 hello");
  assert(result == ParseResult::OK);
  assert(a.arg1 == 1);
  assert(a.arg2 == "hello");

  result = b.parse("b 42 1337 3.14");
  assert(result == ParseResult::OK);
  assert(b.arg1 == 42);
  assert(b.arg2 == 1337);
  assert(3.1f < b.arg3 && b.arg3 < 3.2f);

  result = a.parse("b 1 hello");
  assert(result != ParseResult::OK);

  result = b.parse("b");
  assert(result != ParseResult::OK);

  result = a.parse("a x y");
  assert(result != ParseResult::OK);
  return 0;
}