#include "pch.h"
#include "WordNetHelper.h"

namespace
{
constexpr auto kWordNetFilePathJSON =
  R"(C:\Users\Claudiu HBann\Desktop\Projects\C++\Formalizer\data\wordnet.json)"sv;
constexpr auto kWordNetFilePathStreamable =
  R"(C:\Users\Claudiu HBann\Desktop\Projects\C++\Formalizer\data\wordnet.streamable)"sv;
}  // namespace

int main()
{
  const auto wordnet = WordNetHelper::Load(kWordNetFilePathStreamable);
  wordnet;

  return 0;
}
