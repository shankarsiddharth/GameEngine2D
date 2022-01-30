#include "String.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String::String()
	: m_string_data(NULL),
	m_length(0)
{
	//Initialize();
}

String::~String()
{
	FreeMemory();
}

char* String::ReadUserInput()
{
	//FreeMemory();

	m_string_data = NULL;
	
	m_length = 0;
	char* buffer_data = NULL;
	size_t current_position = 0;
	int current_input_character = EOF;

	while (current_input_character) 
	{
		current_input_character = getc(stdin);

		if (current_input_character == EOF || current_input_character == STRING_DELIMITER)
		{
			current_input_character = '\0';
			fseek(stdin, 0, SEEK_END);
		}		

		if (m_length <= current_position) 
		{
			m_length += sizeof(char);
			buffer_data = (char*)realloc(m_string_data, m_length);
			if (!buffer_data) 
			{
				free(m_string_data);
				m_string_data = NULL;
				break;
			}
			m_string_data = buffer_data;
		}

		m_string_data[current_position++] = current_input_character;
	}
	m_length--;
	
	/*if (m_length == 0)
	{
		Initialize();
	}*/

	/*size_t source_string_length = 0;
	for (size_t i = 0; m_string_data[i] != '\0'; i++)
	{
		source_string_length = i + 1;
	}
	source_string_length += sizeof(char);
	char* temp_buffer = new char[source_string_length];
	for (size_t i = 0; m_string_data[i] != '\0'; i++)
	{
		temp_buffer[i] = m_string_data[i];
	}
	temp_buffer[source_string_length - 1] = '\0';

	CopyString(temp_buffer);
	if (temp_buffer)
	{
		delete temp_buffer;			
	}
	temp_buffer = NULL;*/

	return m_string_data;
}

char* String::GetString() const
{
	return m_string_data;
}

void String::CopyString(const char* InSourceString)
{	
	//FreeMemory();
	m_length = 0;
	if (InSourceString == NULL)
	{
		m_string_data = NULL;		
	}
	else
	{
		char* buffer_data = NULL;
		size_t index = 0;
		int current_character = EOF;
		while(current_character)
		{
			current_character = InSourceString[index];
			if (current_character == EOF || current_character == STRING_DELIMITER)
			{
				current_character = '\0';
			}
			if (m_length <= index)
			{
				m_length += sizeof(char);
				buffer_data = (char*)realloc(m_string_data, m_length);
				if (!buffer_data)
				{
					free(m_string_data);
					m_string_data = NULL;
					break;
				}
				m_string_data = buffer_data;
			}

			m_string_data[index++] = InSourceString[index];			
		}
		m_length--;
	}
}

/*
void String::CopyString(const char* InSourceString)
{
	m_length = 0;
	if (InSourceString == NULL)
	{
		m_string_data = NULL;
	}
	else
	{
		size_t source_string_length = 0;
		for (size_t i = 0; InSourceString[i] != '\0'; i++)
		{
			source_string_length = i+1;
		}
		source_string_length += sizeof(char);
		m_string_data = new char[source_string_length];
		for (size_t i = 0; InSourceString[i] != '\0'; i++)
		{
			m_string_data[i] = InSourceString[i];
		}
		m_string_data[source_string_length-1] = '\0';
		m_length = source_string_length;
	}
}
*/

size_t String::GetLength() const
{
	return m_length;
}

void String::Initialize()
{
	m_string_data = (char*)malloc(sizeof(char));
	if (m_string_data)
	{
		*m_string_data = '\0';
	}
}

void String::FreeMemory()
{
	if (m_string_data)
	{
		free(m_string_data);
	}
	m_string_data = nullptr;
	m_length = 0;
}

bool String::IsStringValid() const
{
	return (m_string_data != NULL || m_length != 0);
}

