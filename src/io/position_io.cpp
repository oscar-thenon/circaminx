#include <cctype>
#include <fstream>
#include <string>

#include "position_io.hpp"
#include "util.hpp"

using namespace std;

bool import_position(const string &file_name, Position &position)
{
	ifstream file(file_name.c_str());
	string word;
	if (!(file >> word))
		return false;

	if (word.length() != 10)
		return false;

	bool seen[10] = {false, false, false, false, false, false, false, false, false, false};
	for (int k = 0; k < 10; k++)
	{
		char c = word[k];
		if (!isdigit(static_cast<unsigned char>(c)))
			return false;

		int value = char_to_int(c);
		if (value < 0 || value > 9 || seen[value])
			return false;

		seen[value] = true;
		position[k] = value;
	}

	return true;
}

bool export_position(const string &file_name, const Position &position)
{
	ofstream file(file_name.c_str());
	if (!file.is_open())
		return false;

	for (int k = 0; k < 10; k++)
		file << position[k];

	file.close();
	return true;
}
