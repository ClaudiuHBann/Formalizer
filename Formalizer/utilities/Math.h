#pragma once

class Math final
{
public:
  // TODO: make me more generic
  template <typename Type>
  static inline std::vector<Type> TakeRowsFromMatrix(const std::vector<std::vector<Type>> & aTensor,
                                                     const std::vector<size_t> & aIndices)
  {
    std::vector<Type> output;
    for (const auto index : aIndices)
    {
      output.push_range(tensor[index]);
    }
    return output;
  }
};
