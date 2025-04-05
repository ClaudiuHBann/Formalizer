#include "pch.h"
#include "WordNetHelper.h"

namespace
{
constexpr auto kFileExtensionJSON       = L".json"sv;
constexpr auto kFileExtensionStreamable = L".streamable"sv;
}  // namespace

/* [[nodiscard]] static */ wordnet WordNetHelper::Load(const std::filesystem::path & aFilePath)
{
  if (aFilePath.native().ends_with(kFileExtensionJSON))
  {
    return LoadFromJSON(aFilePath);
  }
  else if (aFilePath.native().ends_with(kFileExtensionStreamable))
  {
    return LoadFromStreamable(aFilePath);
  }
  else
  {
    throw std::invalid_argument("Invalid file extension!");
  }
}

/* [[nodiscard]] static */ wordnet WordNetHelper::LoadFromJSON(
  const std::filesystem::path & aFilePath)
{
  std::ifstream fileStream(aFilePath);
  if (!fileStream)
  {
    throw std::runtime_error(std::format("Failed to open file: {}", aFilePath.string()));
  }

  nlohmann::json j;
  fileStream >> j;

  wordnet wn{};
  nlohmann::from_json(j, wn);
  return wn;
}

/* [[nodiscard]] static */ wordnet WordNetHelper::LoadFromStreamable(
  const std::filesystem::path & aFilePath)
{
  std::ifstream fileStream(aFilePath, std::ios_base::binary);
  if (!fileStream)
  {
    throw std::runtime_error(std::format("Failed to open file: {}", aFilePath.string()));
  }

  std::vector<uint8_t> fileData(std::filesystem::file_size(aFilePath));
  fileStream.read(reinterpret_cast<char *>(fileData.data()), fileData.size());

  wordnet       wn{};
  hbann::Stream stream;
  stream.Write(fileData);
  wn.Deserialize(std::move(stream), false);
  return wn;
}

/* static */ void WordNetHelper::Save(const std::filesystem::path & aFilePath, wordnet & aWordNet)
{
  if (aFilePath.native().ends_with(kFileExtensionStreamable))
  {
    SaveToStreamable(aFilePath, aWordNet);
  }
  else
  {
    throw std::invalid_argument("Invalid file extension!");
  }
}

/* static */ void WordNetHelper::SaveToStreamable(const std::filesystem::path & aFilePath,
                                                  wordnet &                     aWordNet)
{
  std::ofstream fileStream(aFilePath, std::ios_base::binary);
  if (!fileStream)
  {
    throw std::runtime_error(std::format("Failed to open file: {}", aFilePath.string()));
  }

  const auto wnStream(aWordNet.Serialize().Release());
  fileStream.write(reinterpret_cast<const char *>(wnStream.data()), wnStream.size());
}
