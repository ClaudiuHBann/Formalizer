#pragma once

#include "networks/Layer.h"
#include "utilities/initializers/RandomInitializer.h"

class Embedding : public Layer
{
public:
  Embedding(const uint64_t      aDimensionInput,
            const uint64_t      aDimensionOutput,
            RandomInitializer & aInitializer,
            const bool          aMaskZero);

  void Build();

  std::vector<float> operator()(const std::vector<size_t> & aIndices);

private:
  const uint64_t      mDimensionInput;
  const uint64_t      mDimensionOutput;
  RandomInitializer & mInitializer;

  std::vector<std::vector<float>> mEmbeddings;
};
