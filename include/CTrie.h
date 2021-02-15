#ifndef CTrie_H
#define CTrie_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

class CTrie {
 public:
  class Node;

  using CharNodeMap = std::map<unsigned char,Node *>;
  using CharSet     = std::set<unsigned char>;
  using String      = std::string;
  using Strings     = std::vector<String>;
  using Patterns    = Strings;

  class Node {
   public:
    Node(Node *parent=nullptr, unsigned char c='\0') :
     parent_(parent), c_(c) {
    }

    Node *parent() const { return parent_; }

    unsigned char c() const { return c_; }

    const CharNodeMap &children() const { return nodes_; }

    int numChildren() const { return nodes_.size(); }

    int count() const { return count_; }

    void incCount() { ++count_; }

    Node *addChar(unsigned char c) {
      auto p = nodes_.find(c);

      if (p == nodes_.end())
        p = nodes_.insert(p, CharNodeMap::value_type(c, new Node(this, c)));

      return (*p).second;
    }

    String str() const {
      if (! parent_)
        return "";

      return parent_->str() + char(c_);
    }

    void patterns(int depth, Patterns &patterns) const {
      String prefix;

      subPatterns(prefix, depth, patterns);
    }

    void subPatterns(const String &prefix, int depth, Patterns &patterns) const {
      if (depth == 0)
        return;

      if (nodes_.empty()) {
        patterns.push_back(prefix);

        return;
      }

      if (nodes_.size() == 1) {
        String prefix1 = prefix;

        auto p = nodes_.begin();

        char c = char((*p).first);

        if (c)
          prefix1 += c;

        return (*p).second->subPatterns(prefix1, depth, patterns);
      }

      if (depth == 1) {
        for (const auto &node : nodes_) {
          String prefix1 = prefix;

          char c = char(node.first);

          String pattern = prefix1;

          if (c) {
            pattern += escapeChar(c);
            pattern += "*";
          }

          patterns.push_back(pattern);
        }
      }
      else {
        for (const auto &node : nodes_) {
          String prefix1 = prefix;

          char c = char(node.first);

          if (c)
            prefix1 += escapeChar(c);

          Patterns patterns1;

          node.second->subPatterns(prefix1, depth - 1, patterns1);

          for (const auto &pattern1 : patterns1)
            patterns.push_back(pattern1);
        }
      }
    }

#if 0
    String pattern() const {
      String childStr  = childPattern ();
      String parentStr = parentPattern();

      return parentStr + childStr;
    }

    String parentPattern() const {
      Node *pnode = parent();

      if (! pnode) // root
        return "";

      return pnode->parentPattern() + pnode->nodesPattern();
    }

    String childPattern() const {
      String pattern = nodesPattern();

      using NodeSet = std::set<Node *>;

      NodeSet nodeSet;

      for (const auto &node : nodes_)
        nodeSet.insert(node.second);

      if (nodeSet.empty())
        return pattern;

      if (nodeSet.size() == 1)
        return (*nodeSet.begin())->childPattern();

      return pattern + "*";
    }

    String nodesPattern() const {
      if (nodes_.empty())
        return "";

      if (nodes_.size() == 1) {
        auto p = nodes_.begin();

        char c = char((*p).first);

        if (! c)
          return "";

        return String(&c, 1);
      }

      CharSet charSet;

      nodeChars(charSet);

      //---

      String pattern = "[";

      unsigned char firstChar = 0;
      unsigned char lastChar  = 0;

      for (const auto &c : charSet) {
        if (c > 0 && lastChar + 1 == c) {
          lastChar = c;
        }
        else {
          if (firstChar != 0) {
            char c1 = char(firstChar);
            char c2 = char(lastChar);

            pattern += c1;

            if (c1 != c2) {
              pattern += "-";
              pattern += c2;
            }
          }

          firstChar = c;
          lastChar  = c;
        }
      }

      if (firstChar != 0) {
        char c1 = char(firstChar);
        char c2 = char(lastChar);

        pattern += c1;

        if (c1 != c2) {
          pattern += "-";
          pattern += c2;
        }
      }

      pattern += "]";

      return pattern;
    }

    void nodeChars(CharSet &charSet) const {
      for (const auto &node : nodes_) {
        charSet.insert(node.first);
      }
    }
#endif

    int numWords() const {
      int n = 0;

      for (const auto &node : nodes_) {
        if (node.first == '\0')
          ++n;

        n += node.second->numWords();
      }

      return n;
    }

    String escapeChar(char c) const {
      if      (c == '*' ) return "\\*";
      else if (c == '?' ) return "\\?";
      else if (c == '\\') return "\\\\";

      return String(&c, 1);
    }

   private:
    Node*         parent_ { nullptr };
    unsigned char c_      { '\0' };
    CharNodeMap   nodes_;
    int           count_  { 0 };
  };

 public:
  CTrie() { }

  void addWord(const String &str) {
    Node *node = root();

    for (const auto &c : str) {
      node = addNode(node, c);
    }

    node = addNode(node, '\0');

    node->incCount();
  }

 private:
  template<class VISITOR>
  void visit(VISITOR &v, Node *node, const String &str) {
    for (const auto &n : node->children()) {
      if (! n.first)
        v.visit(str, n.second->count());
      else
        visit(v, n.second, str + char(n.first));
    }
  }

 public:
  Node *root() const {
    if (! root_) {
      CTrie *th = const_cast<CTrie *>(this);

      th->root_ = new Node;
    }

    return root_;
  }

  int numWords() const {
    Node *node = root();

    return node->numWords();
  }

 public:
  template<class VISITOR>
  void visit(VISITOR &v) {
    Node *node = root();

    String str;

    visit(v, node, str);
  }

  void dump(std::ostream &os=std::cerr) {
    class Dumper {
     public:
      Dumper(std::ostream &os) :
       os_(os) {
      }

      const std::ostream &os() const { return os_; }

      void visit(const String &str, int n) {
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
    MatchData(const String &match) :
     str(match), len(match.size()) {
    }

    String str;
    uint   pos { 0 };
    uint   len;
  };

 public:
  void complete(const String &match, Strings &strs) {
    MatchData matchData(match);

    Node *node = root();

    String str;

    complete(node, str, strs, matchData);
  }

  void patterns(int depth, Patterns &patterns) const {
    Node *root = this->root();

    return root->patterns(depth, patterns);
  }

 private:
  void complete(Node *node, const String &str, Strings &strs, MatchData &matchData) {
    for (const auto &n : node->children()) {
      if (matchData.pos == matchData.len) {
        if (! n.first)
          strs.push_back(matchData.str + str);
        else
          complete(n.second, str + char(n.first), strs, matchData);
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

  Node *addNode(Node *parent, unsigned char c) {
    return parent->addChar(c);
  }

 private:
  Node *root_ { nullptr };
};

#endif
