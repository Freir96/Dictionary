#include <iostream>
#include <fstream>
#include <locale>
#include <stdio.h>
#include <ctype.h>
#include <vector>
using namespace std;

void get_word(char* dest, FILE* pFile) {
	char c = fgetc(pFile);
	int index = 0;
	while (isalpha(c)) {
		dest[index] = c;
		c = fgetc(pFile);
		index++;
	}
}

std::string first_letter_toupper(std::string s) {
	std::string buf = "";
	std::string::iterator it = s.begin();
	buf += toupper(*it);
	++it;
	for (; it != s.end(); ++it) {
		buf += *it;
	}

	return buf;
}

class element {
public: 
	std::string pol;
	std::string eng;
};

std::string find_translation(std::string to_translate, std::vector<element> dict ) {
	for (element n : dict) {
		if (n.pol == to_translate) {
			return n.eng;
		}
	}
	return to_translate;
}

std::string replace_word(std::string in, std::string to_replace, std::string new_word) {
	std::locale loc;
	std::string result = "";
	std::string word = "";
	std::string capital_word1 = first_letter_toupper(to_replace);
	std::string capital_word2 = first_letter_toupper(new_word);
	for (std::string::iterator it = in.begin(); it != in.end(); ++it)
	{
		if (std::isalpha(*it, loc))
			word += *it;
		else {
			if (word == to_replace) {
				//std::cout << word << " " << result << std::endl;
				result += new_word;
				word = "";
			}			
			else {
				//std::cout << word << "-" << result << std::endl;
				if (word == capital_word1) {
					result += capital_word2;
					word = "";
				}
				else {
					result += word;
					word = "";
				}
				
				//std::cout << word << "---" << result << std::endl;
			}
			result += *it;
		}
			
				
	}
	return result;
}

std::string translate(std::string in, std::vector<element> dict) {
	std::locale loc;
	std::string result = "";
	std::string word = "";
	//std::string capital_word1 = first_letter_toupper(to_replace);
	//std::string capital_word2 = first_letter_toupper(new_word);
	bool upper = false;
	for (std::string::iterator it = in.begin(); it != in.end(); ++it)
	{
		if (std::isalpha(*it, loc)) {
			if (std::isupper(*it, loc)) {
				word += tolower(*it);
				upper = true;
			}
			else {
				word += *it;
			}
		}
			
		else {
			if (upper) {
				result += first_letter_toupper(find_translation(word, dict));
			}
			else {
				std::cout << " :" << word << std::endl;
				result += find_translation(word, dict);
			}
				
			word = "";
			upper = false;
			result += *it;
		}


	}
	return result;
}

int main()
{
 /* ifstream in("file.txt");

  if(!in) {
    cout << "Cannot open input file.\n";
    return 1;
  }

  char str[255];

  while(in) {
    in.getline(str, 255);  // delim defaults to '\n'
    if(in) cout << str << endl;

  }

  in.close();*/
	std::string s = "This is my cat Mark. My cats are Tim and Rick. Cat is an animal.";
	std::string s2 = "To jest moj kot. Kot to nie pies.";
	std::string to_replace = "cat";
	std::string new_word = "dog";
	//std::cout << replace_word(s, to_replace, new_word) << std::endl;
	//std::cout << first_letter_toupper("cat\n");
	element e1;
	e1.eng = "dog";
	e1.pol = "pies";
	element e2;
	e2.eng = "cat";
	e2.pol = "kot";
	std:vector <element> dict = { e1, e2 };
	std::cout << translate(s2, dict) << std::endl;


  return 0;
}