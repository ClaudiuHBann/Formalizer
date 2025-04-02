#pragma once

// Denotes a semantic relation between one synset/word to another.
struct pointer : public hbann::IStreamable
{
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(pointer, symbol, synset, source, target);
  STREAMABLE_DEFINE(pointer, symbol, synset, source, target);

  // relation between the 2 words. Target is <symbol> to source. See their
  // meanings here:
  // https://pkg.go.dev/github.com/fluhus/gostuff/nlp/wordnet#pkg-constants
  std::string symbol;

  // target synset ID.
  std::string synset;

  // index of word in source synset, -1 for entire synset.
  int source;

  // index of word in target synset, -1 for entire synset.
  int target;
};
