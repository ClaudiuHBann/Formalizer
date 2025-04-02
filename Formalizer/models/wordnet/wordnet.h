#pragma once

#include "models/wordnet/synset.h"

// An entire WordNet database.
struct wordnet : public hbann::IStreamable
{
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(wordnet, synset, lemma, lemmaRanked, exception, example);
  STREAMABLE_DEFINE(wordnet, synset, lemma, lemmaRanked, exception, example);

  // from synset ID to synset object
  std::unordered_map<std::string, synset> synset;

  // from pos.lemma to synset IDs that contain it
  std::unordered_map<std::string, std::vector<std::string>> lemma;

  // like Lemma but synsets are ordered from the most frequently used to the
  // least. Only a subset of the synsets are ranked, so LemmaRanked has less
  // synsets
  std::unordered_map<std::string, std::vector<std::string>> lemmaRanked;

  // from example ID to sentence template
  std::unordered_map<std::string, std::vector<std::string>> exception;

  // from example ID to sentence template
  std::unordered_map<std::string, std::string> example;
};
