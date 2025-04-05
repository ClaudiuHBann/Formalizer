#pragma once

#include "models/wordnet/wordnet.h"

class WordNetHelper final
{
public:
  [[nodiscard]] static wordnet Load(const std::filesystem::path & aFilePath);
  static void                  Save(const std::filesystem::path & aFilePath, wordnet & aWordNet);

private:
  [[nodiscard]] static wordnet LoadFromJSON(const std::filesystem::path & aFilePath);
  [[nodiscard]] static wordnet LoadFromStreamable(const std::filesystem::path & aFilePath);

  static void SaveToStreamable(const std::filesystem::path & aFilePath, wordnet & aWordNet);
};
