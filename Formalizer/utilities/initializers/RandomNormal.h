#pragma once

#include "RandomInitializer.h"

class RandomNormal : public RandomInitializer
{
public:
  explicit RandomNormal(const float aMean, const float aSigma);
  explicit RandomNormal(const float aMean, const float aSigma, const uint32_t aSeed);

  float NextFloat() override;

private:
  std::default_random_engine      mGenerator;
  std::normal_distribution<float> mDistribution;
};
