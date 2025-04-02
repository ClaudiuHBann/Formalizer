#pragma once

// Links a synset word to an example sentence. Applies to verbs only.
struct example {
  // index of word in the containing synset, -1 for entire synset.
  int wordNumber;

  // tumber of template in the WordNet. Example field.
  int templateNumber;
};
