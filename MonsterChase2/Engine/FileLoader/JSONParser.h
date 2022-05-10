#pragma once
#include <string>
#include "../ThirdParty/rapidjson/rapidjson.h"
#include "../ThirdParty/rapidjson/document.h"

class JSONParser
{
public:
	JSONParser();
	~JSONParser();

	rapidjson::Document GetJSONDocument(const std::string i_FilePath);

};