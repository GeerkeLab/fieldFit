#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <vector>
#include <string>

class Tokenizer
{
public:
	
	void Tokenize( const std::string &line, const std::string &delimiters );
	void Empty();
	
	bool IsEnd();
	
	size_t Size();
	
	const std::vector< std::string > & GetBuffer();
	
private:
		
	std::vector< std::string > mBuffer;
};

#endif