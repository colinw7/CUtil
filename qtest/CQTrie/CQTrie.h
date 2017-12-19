#ifndef CQTrie_H
#define CQTrie_H

#include <QFrame>
#include <QRegExp>
#include <CTrie.h>
#include <set>

class QLineEdit;
class QListWidget;
class QLabel;

class CQTrie : public QFrame {
  Q_OBJECT

 public:
  CQTrie(QWidget *parent=0);

  void addFile(const std::string &str);

 private slots:
  void complete();

 private:
  bool matchPattern(const QRegExp &regexp, const QString &pattern, const QString &str);

 private:
  typedef std::set<QString> Words;

  CTrie        trie_;
  QLineEdit   *edit_  { nullptr };
  QListWidget *list_  { nullptr };
  QLabel      *label_ { nullptr };
  Words        words_;
};

#endif
