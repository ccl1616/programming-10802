#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "function.h"
using namespace std;
void RleCodec::encode()
{
	int cnt = 0;
	char prev = '\0';
	std::stringstream ss;
	for (auto c : code_str) {
		if(c != prev){
			if(cnt > 0){
				if(cnt == 1)
					ss << prev;
				else if(cnt == 2)
					ss << prev << prev;
				else
					ss << cnt << prev; //put cnt and prev into ss
			}
			prev = c;
			cnt = 1;
		}
		else cnt++;
	}
	//for last consecutive chars'
	if(cnt > 0){
		if(cnt == 1)
			ss << prev;
		else if(cnt == 2)
			ss << prev << prev;
		else
			ss << cnt << prev;
	}

	code_str = ss.str();
	encoded = true;
}

void RleCodec::decode()
{
	std::stringstream os;
	std::string int_str;
	for (auto c : code_str) {
		if(isdigit(c)){
			int_str.push_back(c);
		}
		else{
			int cnt = 0;
			std::stringstream is{int_str};
			is >> cnt;
			//for those who has only one char
			// eg 3a"b"2c
			if(cnt == 0)
				os << c;
			else{
				for(int i = 0 ; i < cnt; i ++)
					os << c;
			}
			//clear the string everytime after printed out
			int_str.clear();
		}
	}
	code_str = os.str();
	encoded = false;
}
