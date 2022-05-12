#pragma once
#include <string>
#include "../ThirdParty/rapidjson/rapidjson.h"
#include "../ThirdParty/rapidjson/document.h"
#include <functional>

class JSONParser
{
public:
	JSONParser();
	~JSONParser();

	rapidjson::Document GetJSONDocument(const std::string i_FilePath);
	std::string  GetFileContents(const std::string i_JSONFilePath);

	void GetFileContentsAsync(const std::string i_JSONFilePath, std::function<void(std::string)> OnFileContentsReadCallback);

};