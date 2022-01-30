#pragma once
class String
{
public:
	String();
	~String();
		
	char* GetString() const;
	bool IsStringValid() const;

	char* ReadUserInput();
	void CopyString(const char* InString);

	size_t GetLength() const;
	
private:
	void Initialize();
	void FreeMemory();

	const char STRING_DELIMITER = '\n';
	char* m_string_data;
	size_t m_length;
};

