// spam_filter-vs_prj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>    // std::ifstream
#include <string>     // std::string
#include <sstream>    // std::istringstream
#include <iostream>   // std::cout
#include <vector>     // std::vector
#include <algorithm>  // std::find_if
#include <cctype>     // std::isalpha

int main()
{
  std::ifstream ifs("00004.68819fc91d34c82433074d7bd3127dcc", std::ifstream::in);

  ////
  // get line w/ subject

  std::string line;
  while (std::getline(ifs, line))
  {
    std::istringstream iss(line);

    // skip non-subject lines
    if (not line.compare(0, 9, "Subject: ")) break;
  }

  ////
  // get words from subject line

  // substr w/o "Subject: "
  line = line.substr(9);
  // iss
  std::istringstream iss(line);
  // words from line
  std::string word;
  // res
  std::vector<std::string> words;

  struct non_alpha {
    bool operator()(char c) {
      return !std::isalpha(c);
    }
  };

  while (iss >> word)
  {
    bool contains_non_alpha
      = std::find_if(word.begin(), word.end(), non_alpha()) != word.end();
    // if not only letters
    if (contains_non_alpha)
    {
      // get only letters
      std::string letterWord;
      for (auto& c : word)
      {
        if (not std::isalpha(c)) break;

        letterWord += c;
      }

      word = letterWord;
    }

    // skip empty word
    if (word.empty()) continue;

    // get lower-case word
    std::string lowerWord;
    for (auto& c : word)
    {
      lowerWord += std::tolower(c);
    }

    std::cout << lowerWord << std::endl;
    words.push_back(lowerWord);
  }


  return 0;
}
