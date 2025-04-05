#include "pch.h"
#include "RandomNormal.h"

RandomNormal::RandomNormal(const float aMean, const float aSigma, const uint32_t aSeed)
  : RandomNormal(aMean, aSigma)
{
  mGenerator.seed(aSeed);
}

RandomNormal::RandomNormal(const float aMean, const float aSigma)
  : mDistribution(aMean, aSigma)
{
}

float RandomNormal::NextFloat()
{
  return mDistribution(mGenerator);
}
