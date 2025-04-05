#include "pch.h"
#include "Embedding.h"
#include "utilities/Math.h"

Embedding::Embedding(const uint64_t      aDimensionInput,
                     const uint64_t      aDimensionOutput,
                     RandomInitializer & aInitializer,
                     const bool          aMaskZero)
  : Layer(aMaskZero)
  , mDimensionInput(aDimensionInput)
  , mDimensionOutput(aDimensionOutput)
  , mInitializer(aInitializer)
{
}

void Embedding::Build()
{
  if (IsBuilt())
  {
    return;
  }

  mEmbeddings.resize(mDimensionInput, std::vector<float>(mDimensionOutput));
  for (size_t i = 0; i < mDimensionInput; i++)
  {
    for (size_t j = 0; j < mDimensionOutput; j++)
    {
      mEmbeddings[i][j] = mInitializer.NextFloat();
    }
  }

  SetBuilt(true);
}

std::vector<float> Embedding::operator()(const std::vector<size_t> & aIndices)
{
  return Math::TakeRowsFromMatrix(mEmbeddings, aIndices);
}
