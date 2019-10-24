#include <iostream>
#include <fstream>
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

int main()
{
  ifstream in("file.txt");

  if(!in) {
    cout << "Cannot open input file.\n";
    return 1;
  }

  char str[255];

  while(in) {
    in.getline(str, 255);  // delim defaults to '\n'
    if(in) cout << str << endl;

  }

  in.close();

  return 0;
}