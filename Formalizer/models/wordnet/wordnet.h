#pragma once

#include "models/wordnet/synset.h"

// https://github.com/fluhus/wordnet-to-json
struct wordnet {
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
