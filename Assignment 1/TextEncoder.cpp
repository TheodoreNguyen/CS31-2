#include <iostream>
#include <string>
using namespace std;

//  GLOBAL CONSTANT DECLARATIONS
const int CHARACTER_OFFSET = 33;	// Character offset
const int CHARACTER_RANGE = 93;	// Character range
const int CHARACTER_MODULUS = 94;	// Character modulus
const int CHECKSUM_MODULUS = 10000;// Checksum  modulus
const char SPECIAL_LIMIT = ' ';	// Special character limit		
const char UPPER_LIMIT = '~';	// Upper   character limit
const char CARET = '^';	// Caret character

string	code(char key, char in);	// Encode a character			
string	sum(string	in);			// Generate a string checksum		

int main()
{
	bool	done;						// Done indicator
	char	key;						// Key character
	int		pos;						// Input line position
	string	iline;						// Input  line
	string	oline;						// Output line
	cout << "Input: String to be encoded " << endl;
	cout << "Output: Encoded string " << endl << endl;
	cout << "Empty string exits the program." << endl;
	cout << endl;
	done = false;
	while (!done)
	{
		cout << "Input: ";
		getline(cin, iline);
		if (iline == "")				//If line is empty, set done to true
		{
			done = true;
		}
		else
		{
			key = iline[0];				// Extract the key character
			oline = "";					// Initilalize the output line
			for (pos = 1;				// Append each coded character string
				(pos < iline.length() &&
				(iline[pos] != 0) &&
				(iline[pos] <= UPPER_LIMIT));
			pos++)
			{
				oline += code(key, iline[pos]); // Append the coded string for one character
			}
			oline += sum(oline);				// Append the output string checksum
			oline = key + oline;				// Prepend the output with the key character
			cout << "Output:" << oline << endl;	// Display the output line
			cout << endl;						// Display a blank line
		}
	}
	cout << endl;
	cout << "Done." << endl;
	return 0;
}

string code(char key, char	in)
{
	string	out = "";
	if (int(in) == 0 || int(in) > UPPER_LIMIT)				//if character code == 0 || code > 126, terminate encoding
		return out;
	else if (int(in) > 0 && int(in) <= SPECIAL_LIMIT)		//if character code is in range 1 to 32, 
	{
		unsigned char second = 0;
		out += CARET;										//output caret 
		second = key + in;									//followed by second character
		if (second > UPPER_LIMIT)							//if result is > 126
		{
			second = second - UPPER_LIMIT;					//32 is added modulo 126 to initial value of code for 2nd char
			second = second + SPECIAL_LIMIT;
		}
		out += second;
	}
	else
	{
		unsigned char store = in;							// if char code is anything else, 
		store = store - CHARACTER_OFFSET;					//subtract 33 from character
		store = store + key;								//add code of the key character
	
		if (store > CHARACTER_RANGE)
		{													//modulo 94, reflected in range 0 through 93
			store = store % CHARACTER_MODULUS;
			store = CHARACTER_RANGE - store;
		}
		else
		{
			store = CHARACTER_RANGE - store;
		}

		store += CHARACTER_OFFSET;							//add 33 to character code
		out += store;
		if (store == CARET)									//if result is caret char, also output the key char
			out += key;
	}
	return out;
}


string sum(string in)
{
	string out = "";
	string input = in;
	int add = 0;							//add is the integer sum of the coded characters
	int one;								//one, ten, hundred, and thousand are integer multiples of their respective names
	int ten;									//used to calculate the integer from 0-9 to be stored as a char in their character counterparts
	int hundred;
	int thousand;
	unsigned char ones;						// ones, tens, hundreds, and thousands are the respective digit in the checksum to be added onto the string out
	unsigned char tens;
	unsigned char hundreds;
	unsigned char thousands;
	for (int i = 0; i != input.size(); i++)			//the integer sum of the coded, outputted characters is stored into add through this loop
	{
		add += int(input[i]);
	}
	if (add >= 10000)								//accounts for when the integer sum is greater than 10000
		add = add % 10000;

	for (int k = 0; k < 10; k++)					//ones
	{
		if ((add - k) % 10 == 0)					//each decimal digit of the checksum is calculated by finding the number by which, when the sum is
		{												//subtracted by, will be divisible by 10, 100, 1000, 10000 - depending on which decimal digit
			ones = char(k + '0');						//is being calculated at the time. 
			one = k;
			break;
		}
	}

	for (int k = 0; k < 100; k = k + 10)			//tens
	{
		if ((add - (k + one)) % 100 == 0)
		{
			tens = char((k / 10) + '0');
			ten = k;
			break;
		}
	}

	for (int k = 0; k < 1000; k = k + 100)			//hundreds
	{
		if ((add - (k + one + ten)) % 1000 == 0)
		{
			hundreds = char((k / 100) + '0');
			hundred = k;
			break;
		}
	}

	for (int k = 0; k < CHECKSUM_MODULUS; k = k + 1000)					//thousands
	{
		if ((add - (k + one + ten + hundred)) % CHECKSUM_MODULUS == 0)
		{
			thousands = char((k / 1000) + '0');
			thousand = k;
			break;
		}
	}

	out += thousands;			//each decimal digit char is appended onto the out string to be used in the main function
	out += hundreds;
	out += tens;
	out += ones;
	return out;
}
