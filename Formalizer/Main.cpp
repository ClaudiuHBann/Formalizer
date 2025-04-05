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

/*

GYAFC > NUS English SMS corpus -> http://www.comp.nus.edu.sg/~nlp/sw/sm_norm_mt.tar.gz

2000 labeled data points in the dataset is too small so we augument the dataset using synonym
augmentation (so we will have 4000) and spelling augmentation (so we will reach 8000)

parsing the dataset in pandas DataFrame with two columns namely Informal text and Formal text

tokenization on chars will be better than words giving this small dataset

the encoder will have the sentence between <...>, de decoder input will start with < and it's output
will end with >

we analyze the dataset and see that most of the sentences don't go over 200 chars so we will discard
the sentences that go over 200 chars and split the dataset into 90% train, 5% validation and 5%
tests

we will tokenize the dataset which means that every word will have a GUID and then we will pad the
dataset so each sentence will have 200 chars (formal and informal separately)

*/
