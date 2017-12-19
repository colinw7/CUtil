#ifndef CTrie_H
#define CTrie_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

class CTrie {
 public:
  class Node;

  using CharNode = std::map<char,Node *>;
  using String   = std::string;
  using Strings  = std::vector<String>;

  struct Node {
    CharNode nodes;
    int      count { 0 };
  };

 public:
  CTrie() { }

  void addWord(const std::string &str) {
    Node *node = root();

    for (const auto &c : str) {
      node = addNode(node, c);
    }

    node = addNode(node, '\0');

    ++node->count;
  }

 private:
  template<class VISITOR>
  void visit(VISITOR &v, Node *node, const std::string &str) {
    for (const auto &n : node->nodes) {
      if (! n.first)
        v.visit(str, n.second->count);
      else
        visit(v, n.second, str + n.first);
    }
  }

 public:
  template<class VISITOR>
  void visit(VISITOR &v) {
    Node *node = root();

    std::string str;

    visit(v, node, str);
  }

  void dump(std::ostream &os=std::cerr) {
    class Dumper {
     public:
      Dumper(std::ostream &os) :
       os_(os) {
      }

      void visit(const std::string &str, int n) {
        std::cerr << str << "(#" << n << ")" << std::endl;
      }

     private:
      std::ostream &os_;
    };

    Dumper dumper(os);

    visit(dumper);
  }

 private:
  struct MatchData {
    MatchData(const std::string &match) :
     str(match), pos(0), len(match.size()) {
    }

    std::string str;
    uint        pos;
    uint        len;
  };

 public:
  void complete(const std::string &match, Strings &strs) {
    MatchData matchData(match);

    Node *node = root();

    std::string str;

    complete(node, str, strs, matchData);
  }

 private:
  void complete(Node *node, const std::string &str, Strings &strs, MatchData &matchData) {
    for (const auto &n : node->nodes) {
      if (matchData.pos == matchData.len) {
        if (! n.first)
          strs.push_back(matchData.str + str);
        else
          complete(n.second, str + n.first, strs, matchData);
      }
      else {
        if (n.first && n.first == matchData.str[matchData.pos]) {
          ++matchData.pos;

          complete(n.second, str, strs, matchData);

          --matchData.pos;
        }
      }
    }
  }

  Node *root() {
    if (! root_)
      root_ = new Node;

    return root_;
  }

  Node *addNode(Node *parent, char c) {
    auto p = parent->nodes.find(c);

    if (p == parent->nodes.end())
      p = parent->nodes.insert(p, CharNode::value_type(c, new Node));

    return (*p).second;
  }

 private:
  Node *root_ { 0 };
};

#endif
