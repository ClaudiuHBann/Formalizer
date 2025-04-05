#pragma once

class Layer
{
public:
  virtual ~Layer() = default;

protected:
  explicit Layer(const bool aMaskZeros);

  bool IsBuilt() const;
  void SetBuilt(const bool aIsBuilt);

  bool AreZerosMasked() const;

private:
  const bool mMaskZero;
  bool       mIsBuilt{};
};
