#pragma once

class RandomInitializer
{
public:
  virtual ~RandomInitializer() = default;

  virtual float NextFloat();

protected:
  explicit RandomInitializer() = default;
};
