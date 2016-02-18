#ifndef CTrie_H
#define CTrie_H

#include <map>
#include <string>
#include <iostream>

class CTrie {
 public:
  class Node;

  typedef std::map<char,Node *> CharNode;

  struct Node {
    CharNode nodes;
  };

 public:
  CTrie() { }

  void addWord(const std::string &str) {
    Node *node = root();

    for (const auto &c : str) {
      node = addNode(node, c);
    }

    node = addNode(node, '\0');
  }

 private:
  template<class VISITOR>
  void visit(VISITOR &v, Node *node, const std::string &str) {
    for (const auto &n : node->nodes) {
      if (! n.first)
        v.visit(str);
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

      void visit(const std::string &str) {
        std::cerr << str << std::endl;
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
  void complete(const std::string &match) {
    MatchData matchData(match);

    Node *node = root();

    std::string str;

    complete(node, str, matchData);
  }

 private:
  void complete(Node *node, const std::string &str, MatchData &matchData) {
    for (const auto &n : node->nodes) {
      if (matchData.pos == matchData.len) {
        if (! n.first)
          std::cerr << matchData.str + str << std::endl;
        else
          complete(n.second, str + n.first, matchData);
      }
      else {
        if (n.first && n.first == matchData.str[matchData.pos]) {
          ++matchData.pos;

          complete(n.second, str, matchData);

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
