#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cctype>
using namespace std;

class SpellCheck {
public:
	SpellCheck(string filename) {
		ifstream in(filename.c_str());
		string temp;
		while (in) {
			getline(in, temp);
			string word;
			while (temp.length() > 0) {
				if (nextWord(temp, word)) {
					map<string, int>::iterator itr = nWords.find(word);
					if (itr == nWords.end()) {
						nWords.insert(pair<string, int>(word, 1));
					}
					else {
						(*itr).second++;
					}
				}
			}
		}
		in.close();
	}

	string correct(string word) {
		if (nWords.find(word) != nWords.end()) return word;
		vector<string> edit1 = edits(word);
		map<int, string> candidates;
		for (int i = 0; i < edit1.size(); i++) {
			map<string, int>::iterator itr = nWords.find(edit1[i]);
			if (itr != nWords.end()) {
				pair<string, int> myPair = *itr;
				candidates.insert(pair<int, string>(myPair.second, myPair.first));
			}
		}
		if (candidates.size() > 0) {
			map<int, string>::iterator itr = candidates.begin();
			pair<int, string> max = *itr;
			itr++;
			while (itr != candidates.end())
				if ((*itr).first > max.first) max = *itr;
			return max.second;
		}
		candidates.clear();
		for (int i = 0; i < edit1.size(); i++) {
			vector<string> edit2 = edits(edit1[i]);
			for (int i = 0; i < edit2.size(); i++) {
				map<string, int>::iterator itr = nWords.find(edit2[i]);
				if (itr != nWords.end()) {
					pair<string, int> myPair = *itr;
					candidates.insert(pair<int, string>(myPair.second, myPair.first));
				}
			}
		}
		if (candidates.size() > 0) {
			map<int, string>::iterator itr = candidates.begin();
			pair<int, string> max = *itr;
			itr++;
			while (itr != candidates.end())
				if ((*itr).first > max.first) max = *itr;
			return max.second;
		}
		return word;
	}

private:
	vector<string> edits(string word) {
		vector<string> result;
		string temp;
		for (int i = 0; i < word.length(); i++) {
			temp = word.substr(0, i) + word.substr(i + 1);
			result.push_back(temp);
		}
		for (int i = 0; i < word.length() - 1; i++) {
			temp = word.substr(0, i) + word[i + 1] + word[i] + word.substr(i + 2);
			result.push_back(temp);
		}
		for (int i = 0; i < word.length(); i++) {
			for (char c = 'a'; c <= 'z'; c++) {
				temp = word.substr(0, i) + c + word.substr(i + 1);
				result.push_back(temp);
			}
		}
		for (int i = 0; i < word.length() + 1; i++) {
			for (char c = 'a'; c <= 'z'; c++) {
				temp = word.substr(0, i) + c + word.substr(i);
				result.push_back(temp);
			}
		}
		return result;
	}

	bool nextWord(string & sentence, string & word) {
		while (true) {
			int pos = sentence.find(" ");

			if (pos != string::npos) {
				word = sentence.substr(0, pos);

				sentence = sentence.substr(pos);
				while (sentence.length() > 0 && !isalpha(sentence[0])) {
					sentence = sentence.substr(1);
				}
				bool isWord = true;
				for (int i = 0; i < word.length(); i++) {
					if (isalpha(word[i])) {
						word[i] = tolower(word[i]);
					}
					else if (ispunct(word[i])) {
						word = word.substr(0, i) + word.substr(i + 1);
					}
					else isWord = false;
				}
				if (!isWord) {
					continue;
				}
				return true;
			}
			else {
				word = sentence;
				sentence = "";
				bool isWord = true;
				for (int i = 0; i < word.length(); i++) {
					if (isalpha(word[i])) word[i] = tolower(word[i]);
					else isWord = false;
				}
				if (!isWord) {
					return false;
				}
				return true;
			}
		}
	}

	map<string, int> nWords;
};
