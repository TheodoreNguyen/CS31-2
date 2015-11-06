
//==========================================================================================================================================
//============NOTE IMPORTANT: each noncode question region is surrounded by a pair of /**/, the coded answers ==============================
//============are also surrounded by /**/ so the viewer can run each program separately upon deletion of the /**/===========================
//==========================================================================================================================================






/*
There are eight problems in this assignment.If you are seriously interested in mastering the course materials, you will do every homework problem,
even though not every problem of this homework will be graded.You will submit your solution electronically.

1.	Briefly explain the functions below with an example for each.You must provide your own examples and exclude the ones presented in the
lecture / textbook.

.length(), .size(), .find(), .substr(), .erase(), .replace()
*/

/*
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str = "hello world.";
	cerr << str.length() << endl;
	cerr << str.size() << endl;
		cerr << str.find("world") << endl;
		cerr << str.substr(2, 5) << endl;
		cerr << str.substr(2) << endl;
		cerr << str.erase(2, 5) << endl;
		cerr << str << endl;
		str = "hello world.";
		cerr << str.replace(2, 5, "cs31") << endl; 
		cout << str << endl;
} 
*/




/*
2.	Write a function(mirror()) that takes in a string parameter of any length and returns its mirror reverse.

Example:
input : ABCDEFGH
	return : HGFEDCBA

*/


	#include <iostream>
	#include <string>
	using namespace std;

	string mirror(string str);

	int main()
	{
		string str = "ABCDEFGH";
		string inverse = mirror(str);
		cout << inverse << endl;		//outputs HGFEDCBA
	}

	string mirror(string str)
	{
		string old = str;
		string nuevo = old;

		nuevo.replace(1, 1, "a");
			
		return nuevo;
	}








/*
	3.	Write function(truncate()) which shortens a string to n characters.If the string is already shorter than n, the function should
	not change the string.
*/

/*
#include <iostream>
#include <string>
using namespace std;

void truncate(string& MyStr, int n);

int main()
{
	string str = "ABCDE";
	truncate(str, 6);
	cout << str << endl;
}
void truncate(string& MyStr, int n)
{
	if (MyStr.size() < size_t(n))
		return;
	else
	{
		MyStr.erase(n, MyStr.size() - 1);
		return;
	}
}
*/





/*
		4.	Explain concisely what the following program does :
*/

/*
#include <iostream>
#include <string>
		using namespace std;
		int main()
		{
			string MyStr = " The future depends on what you do today. – Mahatma Gandhi";
			cout << "MyStr is: " << MyStr << endl;

			int i = MyStr.find("depends");

			string str = MyStr.substr(i);
			cout << "str   is: " << str << endl;

			str = MyStr.substr(i, 24);
			cout << "str   is: " << str << endl;

			return 0;
		}
*/




/*
		5.	Write function(count) which takes in two parameters(a string and a single character).Your function should count the occurrences
			of the single character in the string.


		Prototype: 	int count(string MyStr, char c);

	Example:count("Supercalifragilisticexpialidocious", 'i');
		would return 7
*/

/*
#include <iostream>
#include <string>
using namespace std;

int count(string MyStr, char c);

int main()
{
	string str = "Supercalifragilisticexpialidocious";			//this does not satisfy the requirements because it uses []
	int number = count(str, 'i');
	cout << number << endl;
}

int count(string MyStr, char c)
{
	int number = 0;
	for (size_t i = 0; i != MyStr.size(); i++)
		if (MyStr[i] == c)
			number++;
	return number;
}
*/


/*
#include <iostream>
#include <string>
using namespace std;

int count(string MyStr, char c);

int main()
{
	string str = "Supercalifragilisticexpialidocious";
	int number = count(str, 'i');
	cout << number << endl;
}

int count(string MyStr, char c)
{
	int number = 0;
	do
	{
		if (-1 != MyStr.find(c))
		{
			number++;
			MyStr.erase(MyStr.find(c), 1);
		}
		else
			break;
	} while (true);
	return number;
}
*/



/*	
6.	Complete the following code in order to print out the sample given output :
	OUTPUT :

sssssssssss
 sssssssss
  sssssss
   sssss
    sss
     s

*/

/*
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string MyStr = "sssssssssss";
	cout << MyStr << endl;
	for (int i = 0; i != (MyStr.size() - 1); i++)
	{
		MyStr.erase(MyStr.size() - 2, MyStr.size() - 1);
		MyStr = " " + MyStr;
		cout << MyStr << endl;
	}
	return 0;
}*/
		   
		  // Important note that you are not allowed to use character ‘s’ or any string containing ‘s’ such as “sss” other than MyStr.You are supposed
			 //  to use string library functions and process MyStr to print out the intended content.Note that hard - coding the exact output will result losing the entire credit for this question.






		   
			 /*  7.	Please explain in “one” sentence what does the following program do: */
/*
#include <iostream>
		   using namespace std;

		   int main()
		   {
			   bool found = false;
			   string str = "A day without sunshine is like, you know, night.";

			   for (int i = 0; i != str.size(); i++)
			   {
				   if (str[i] == 'i')
					   found = true;
			   }

			   if (found)
				   cout << "I found an i!?!!" << endl;
		   }
*/

		   


/*
		   8.	Complete the following code using only .find() and.replace() functions, in order to replace :
		   a.‘pizza’ with ‘pasta’
			   b.‘Dad’ with ‘I’
			   c.‘made’ with ‘helped to make’

			   Note that hard - coding the replacements instead of using the string library functions will result losing the entire credit for this
			   question.
*/

/*
		#include <iostream>
		#include <string>
			   using namespace std;

		   int main()
		   {
			   string MyStr = "Dad made pizza last night!";
			   string str1 = "helped to make";
			   string str2 = "pasta";
			   string str3 = "I";

			   MyStr.replace(MyStr.find("Dad"), 3, str3);
			   MyStr.replace(MyStr.find("pizza"), 5, str2);
			   MyStr.replace(MyStr.find("made"), 4, str1);


			   cout << "MyStr is: " << MyStr << endl;
			   return 0;
		   }
*/