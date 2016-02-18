#include <CTrie.h>
#include <CFile.h>

int
main(int argc, char **argv)
{
  std::string filename;
  std::string complete;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (argv[i][1] == 'f') {
        ++i;

        if (i < argc)
          filename = argv[i];
      }
      else if (argv[i][1] == 'c') {
        ++i;

        if (i < argc)
          complete = argv[i];
      }
      else
        std::cerr << "Invalid option " << argv[i] << std::endl;
    }
    else
      std::cerr << "Invalid arg " << argv[i] << std::endl;
  }

  CTrie trie;

  if (filename != "") {
    CFile file(filename);

    std::vector<std::string> lines;

    file.toLines(lines);

    for (const auto &l : lines)
      trie.addWord(l);
  }
  else {
    trie.addWord("One");
    trie.addWord("Two");
    trie.addWord("Three");
    trie.addWord("Four");
    trie.addWord("Five");
    trie.addWord("Six");
    trie.addWord("Seven");
    trie.addWord("Eight");
    trie.addWord("Nine");
    trie.addWord("Ten");
  }

  if (complete != "")
    trie.complete(complete);
  else
    trie.dump();
}
