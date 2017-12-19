#include <CQTrie.h>
#include <CFile.h>
#include <CStrUtil.h>
#include <COSProfile.h>
#include <QApplication>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQTrie *trie = new CQTrie;

  trie->show();

  for (int i = 1; i < argc; ++i)
    trie->addFile(argv[i]);

  app.exec();

  return 0;
}

CQTrie::
CQTrie(QWidget *parent) :
 QFrame(parent)
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  edit_  = new QLineEdit;
  list_  = new QListWidget;
  label_ = new QLabel;

  connect(edit_, SIGNAL(textChanged(const QString &)), this, SLOT(complete()));

  layout->addWidget(edit_);
  layout->addWidget(list_);
  layout->addWidget(label_);
}

void
CQTrie::
addFile(const std::string &filename)
{
  CFile file(filename);

  std::vector<std::string> lines;

  file.toLines(lines);

  for (const auto &l : lines) {
    std::vector<std::string> words;

    CStrUtil::addWords(l, words);

    for (const auto &w : words) {
      trie_.addWord(w);

      words_.insert(w.c_str());
    }
  }
}

void
CQTrie::
complete()
{
  QString str = edit_->text();

  int    n1 = 0, n2 = 0;
  double t1 = 0, t2 = 0;

  CTrie::Strings strs;

  {
  COSProfile p1("trie");

  trie_.complete(str.toStdString(), strs);

  t1 = p1.elapsed().getSecs();
  n1 = strs.size();
  }

  QStringList matches;

  {
  COSProfile p2("strs");

  QRegExp regexp(str + "*", Qt::CaseSensitive, QRegExp::Wildcard);

  for (const auto &w : words_) {
    if (matchPattern(regexp, str, w))
      matches.push_back(w);
  }

  t2 = p2.elapsed().getSecs();
  n2 = matches.length();
  }

  label_->setText(QString("Trie %1 Matches in %2, Strings %3 Matches in %4").
                   arg(n1).arg(t1).arg(n2).arg(t2));

  list_->clear();

  for (const auto &s : strs) {
    list_->addItem(s.c_str());

    if (list_->count() > 20)
      break;
  }
}

bool
CQTrie::
matchPattern(const QRegExp &regexp, const QString &pattern, const QString &str)
{
  return (str == pattern || regexp.indexIn(str) == 0);
}
