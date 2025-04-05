#include "pch.h"
#include "Layer.h"

Layer::Layer(const bool aMaskZeros)
  : mMaskZero(aMaskZeros)
{
}

bool Layer::IsBuilt() const
{
  return mIsBuilt;
}

void Layer::SetBuilt(const bool aIsBuilt)
{
  mIsBuilt = aIsBuilt;
}

bool Layer::AreZerosMasked() const
{
  return mMaskZero;
}

void Layer::MaskZeros(const bool aMaskZeros)
{
  mMaskZero = aMaskZeros;
}
