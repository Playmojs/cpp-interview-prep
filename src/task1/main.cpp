#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <charconv>

/*
Task: Implement the CommandParser class such that the code below compiles and
runs without assertion errors.
*/

enum class ParseResult {
  OK,
  ERROR,
  // feel free to add specific error codes
};

std::vector<std::string> splitString(const std::string& str) {
    std::vector<std::string> tokens;
    std::istringstream iss(str.data());
    std::string token;

    while (std::getline(iss, token, ' ')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    return tokens;
}

class CommandParser {
  // your implementation
  public:
    CommandParser(const std::string& input)
    {
      _tokens = splitString(input);
    }
    void check_len()
    {
      if(_index >= _tokens.size()){_result = ParseResult::ERROR;}
    }
    CommandParser& require_name(std::string name)
    {
      if(name != _tokens[0]){_result = ParseResult::ERROR;}
      return *this;
    }

    CommandParser& parse_arg(std::string& val)
    {
      check_len();
      if(_result == ParseResult::ERROR){return *this;}
      val = _tokens[_index];
      ++_index;
      return *this;
    }
    CommandParser& parse_arg(float& val ) {
      check_len();
      if(_result == ParseResult::ERROR){return *this;}
      std::istringstream iss(_tokens[_index]);
      iss >> std::noskipws >> val;

      if (iss.fail() || !iss.eof()) {
          _result = ParseResult::ERROR;
      }
      ++_index;
      return *this;
    }

    CommandParser& parse_arg(int& val) 
    {
      check_len();
      if(_result == ParseResult::ERROR){return *this;}
      std::istringstream iss(_tokens[_index]);
      iss >> val;

      if (iss.fail() || !iss.eof()) {
        _result = ParseResult::ERROR;
      }
      ++_index;
      return *this;
    }
    
    ParseResult validate() 
    {
      if (_result == ParseResult::ERROR){return _result;}
      return ParseResult::OK;
    }

  private:
    std::vector<std::string> _tokens;
    ParseResult _result;
    size_t _index = 1;
};

// Do not change any code below this line

struct CommandA {
  int arg1{};
  std::string arg2;


  ParseResult parse(std::string input) {
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

  ParseResult parse(std::string input) {
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
  
  std::cout << "Epic Win! \n";
  return 0;
}