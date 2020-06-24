#ifndef FUNCTION_H
#define FUNCTION_H
#include<cstddef>
#include<map>
#include<string>

namespace oj
{
	struct String
	{
		std::string str;
		String(const std::string &); //ok
		String(const String &); //ok
		String& operator=(const String &); //ok
	};

	std::ostream& operator<<(std::ostream &,const String &); //ok

	// do all the down below

	void insert(std::map<int,String> &ma,int key,const std::string &str);
	void output(const std::map<int,String> &ma,int begin,int end);
	void erase(std::map<int,String> &ma,int begin,int end);

	std::ostream& operator<<(std::ostream &,const std::map<int,String> &);
}

#endif