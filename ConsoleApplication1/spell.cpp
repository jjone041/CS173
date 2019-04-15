#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>


typedef
std::set <std::string,
	std::less<std::string>, std::allocator<std::string> > stringset;
typedef
std::ostream_iterator<std::string,
	char, std::char_traits<char> >            ostrm_iter;
typedef
std::istream_iterator<std::string,
	char, std::char_traits<char>,
	std::ptrdiff_t>  istrm_iter;


void spellCheck(std::istream& dictionary, std::istream& text) {

	stringset   words, misspellings;
	std::string word;
	istrm_iter  eof, dstream(dictionary);

	// First read the dictionary.
	std::copy(dstream, eof, std::inserter(words, words.begin()));

	// Next read the text.
	while (text >> word)
		if (!words.count(word))
			misspellings.insert(word);

	// Finally, output all misspellings.
	std::cout << std::endl << "Misspelled words:" << std::endl;

	std::copy(misspellings.begin(), misspellings.end(),
		ostrm_iter(std::cout, "\n"));
}

int main()
{
	std::cout << "Enter text:";
	std::ifstream words("words");
	spellCheck(words, std::cin);
	std::cout << "End of spell check program" << std::endl;
	return 0;
}