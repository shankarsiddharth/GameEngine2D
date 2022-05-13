#include "JSONParser.h"
#include <string>
#include <sstream>
#include <fstream>
#include <functional>

JSONParser::JSONParser()
{

}

JSONParser::~JSONParser()
{

}

rapidjson::Document JSONParser::GetJSONDocument(const std::string InJSONFilePath)
{
	std::ifstream inputJSONFile(InJSONFilePath);
	std::stringstream fileContentStringStream;
	fileContentStringStream << inputJSONFile.rdbuf();

	return GetJSONDocumentFromString(fileContentStringStream.str());
}

rapidjson::Document JSONParser::GetJSONDocumentFromString(const std::string InJSONString)
{
	rapidjson::Document doc;
	doc.Parse(InJSONString.c_str());
	return doc;
}

std::string JSONParser::GetFileContents(const std::string InJSONFilePath)
{
	std::ifstream inputJSONFile(InJSONFilePath);
	std::stringstream fileContentStringStream;
	fileContentStringStream << inputJSONFile.rdbuf();
	return fileContentStringStream.str();
}


void JSONParser::GetFileContentsAsync(const std::string InJSONFilePath, std::function<void(std::string)> InOnFileContentsReadCallback)
{
	std::ifstream inputJSONFile(InJSONFilePath);
	std::stringstream fileContentStringStream;
	fileContentStringStream << inputJSONFile.rdbuf();
	if (InOnFileContentsReadCallback != nullptr)
	{
		InOnFileContentsReadCallback(fileContentStringStream.str());
	}
}