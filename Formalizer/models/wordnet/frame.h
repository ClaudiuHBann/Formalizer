#pragma once

// Links a synset word to a generic phrase that illustrates how to use it.
// Applies to verbs only.
struct frame : public hbann::IStreamable
{
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(frame, wordNumber, frameNumber);
  STREAMABLE_DEFINE(frame, wordNumber, frameNumber);

public:
  // index of word in the containing synset, -1 for entire synset.
  int wordNumber;

  // frame number on the WordNet site.
  int frameNumber;
};
