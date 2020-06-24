#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
//#include "function.h"

class Codec {
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual ~Codec() { } // Do nothing
    virtual void show(std::ostream& os) const = 0;
    virtual bool is_encoded() const = 0;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): encoded{false}, code_str{s} { }

    void encode() {
        encoded = true;
    }

    void decode() {
        encoded = false;
    }

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }

private:
    bool encoded;
    std::string code_str;
};

class RleCodec: public Codec
{
public:
    RleCodec(std::string s): encoded{false}, code_str{s} { }

    void encode();

    void decode();

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }


private:
    bool encoded;
    std::string code_str;
};

std::ostream& operator<<(std::ostream& os, Codec& data)
{
    data.show(os);
    return os;
}

void encode_decode(Codec & data)
{
    if (!data.is_encoded())
        data.encode();
    else
        data.decode();
}


void RleCodec::encode()
{
	int cnt = 0;
	char prev = '\0';
	std::stringstream ss;
	for (auto c : code_str) {
		if (c!=prev) {
			if (cnt>0) {
				if (cnt==1)
					ss << prev;
				else if (cnt==2)
					ss << prev << prev;
				else
					ss << cnt << prev;
			}
			prev = c;
			cnt = 1;
		} 
        else {
			++cnt;
		}
	}
	if (cnt>0) {
		if (cnt==1)
			ss << prev;
		else if (cnt==2)
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
    // range base for loop
    // make sure that the "c" is within code_str
    // auto, auto check the type of "c"
	for (auto c : code_str) {
		if (std::isdigit(c)) {
            // push_back is default function of string
			int_str.push_back(c);
		} 
        else {
            // now 'c' is a char
			int cnt = 0;
			std::stringstream is{int_str}; // put "int_str" into "is"
            // is == cin
            // os == cout
			is >> cnt;  // put the number  "is" into "cnt"
            
            // if no number before a char, just print it once
			if (cnt==0) {
				os << c;
			} 
            // print it by its times
            else {
				for (int i=0; i<cnt; ++i)
					os << c;
			}
            // clear out the number
			int_str.clear();
		}
	}

	code_str = os.str(); //replace code_str with os
	encoded = false;
}

int main()
{
    std::string input_string;
    std::cin >> input_string;

    DummyCodec dummy{input_string};
    encode_decode(dummy);
    std::cout << "Dummy encoding: ";
    std::cout << dummy << std::endl;
    encode_decode(dummy);
    std::cout << "Dummy decoding: ";
    std::cout << dummy << std::endl;

    RleCodec rle{input_string};
    encode_decode(rle);
    std::cout << "RLE encoding: ";
    std::cout << rle << std::endl;
    encode_decode(rle);
    std::cout << "RLE decoding: ";
    std::cout << rle << std::endl;
}
