#include "JSONParser.h"
#include <string>
#include <sstream>
#include <fstream>

JSONParser::JSONParser()
{

}

JSONParser::~JSONParser()
{

}

rapidjson::Document JSONParser::GetJSONDocument(const std::string i_JSONFilePath)
{
	std::ifstream inputJSONFile(i_JSONFilePath);
	std::stringstream fileContentStringStream;
	fileContentStringStream << inputJSONFile.rdbuf();

	rapidjson::Document doc;
	doc.Parse(fileContentStringStream.str().c_str());
	return doc;
}


std::string JSONParser::GetFileContents(const std::string i_JSONFilePath)
{
	std::ifstream inputJSONFile(i_JSONFilePath);
	std::stringstream fileContentStringStream;
	fileContentStringStream << inputJSONFile.rdbuf();
	return fileContentStringStream.str();
}


void JSONParser::GetFileContentsAsync(const std::string i_JSONFilePath, std::function<void(std::string)> OnFileContentsReadCallback)
{
	std::ifstream inputJSONFile(i_JSONFilePath);
	std::stringstream fileContentStringStream;
	fileContentStringStream << inputJSONFile.rdbuf();
	OnFileContentsReadCallback(fileContentStringStream.str());
}
