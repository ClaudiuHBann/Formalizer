#pragma once

#include "models/wordnet/example.h"
#include "models/wordnet/frame.h"
#include "models/wordnet/pointer.h"

// A set of synonymous words.
struct synset {
  enum class PosType : char {
    Adjective = 'a',
    Noun = 'n',
    Adverb = 'r',
    Satellite = 's',
    Verb = 'v',
  };

  // synset offset in the raw data file, also used as an identifier.
  int offset;

  // part of speech
  PosType pos;

  // words in this synset.
  std::vector<std::string> word;

  // pointers to other synsets.
  std::vector<pointer> pointer;

  // sentence frames for verbs.
  std::vector<frame> frame;

  // lexical definition.
  std::string gloss;

  // usage examples for words in this synset. Verbs only.
  std::vector<example> example;
};
