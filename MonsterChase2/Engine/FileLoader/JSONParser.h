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

	rapidjson::Document GetJSONDocument(const std::string InFilePath);
	rapidjson::Document GetJSONDocumentFromString(const std::string InJSONString);
	
	std::string  GetFileContents(const std::string InJSONFilePath);

	void GetFileContentsAsync(const std::string InJSONFilePath, std::function<void(std::string)> InOnFileContentsReadCallback);
	
private:
	
};