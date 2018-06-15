// Example how to do "nocase" search for containers in cpp
// analog "strcasecmp" in C

#include <cstring>
#include <string>
#include <set>
#include <iostream>

using namespace std;


// OR a simpler (and probably faster) version (by dave):
struct ci_less
{
  bool operator() (const string & s1, const string & s2) const
  {
	return strcasecmp(s1.c_str(), s2.c_str()) < 0;
  }
};






typedef set<std::string, ci_less> age_set;

int main()
{
	// make a map of people
	age_set people;

	// add items to list
	people.insert ("Nick") ;
	people.insert ("John") ;
	people.insert ("Mary") ;

	// find someone by key
	cout << "Finding person 'nick' ..." << endl;

	age_set::const_iterator i = people.find ("nick");

	if (i == people.end ())
		cout << "Not found." << endl;
	else
		cout << "Found NAME : " << (*i) << endl;

	return 0;
} // end of main


