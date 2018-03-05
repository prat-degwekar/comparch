#include <iostream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

/* Converts a port range given in CLI to a portPrefix */

/* ushort is the central datatype as we are only dealing with 16 bit things (ports) */
typedef unsigned short ushort;

typedef struct{
	ushort port;
	ushort dcbits;

	void print() {
		bitset <16> bits(port);
		for (int i = 15; i >= dcbits; i--)
			cout << bits[i];
		for (int i = 0; i < dcbits; i++)
			cout << '*';
		cout << endl;
	}
} portPrefix;

typedef pair <ushort, ushort> portRange; // Both inclusive
#define lower first
#define higher second

/* Global variables where all the magic happens */
portRange range;
vector <portPrefix> prefixes;

// Returns True if the portPrefix can be merged at the nth bit by introducing a wildcard
bool canMerge(portPrefix a, portPrefix b) {
	/* Check if all bits until nth bit are the same */
	/* 	1. XOR */
	/* 	2. Right shift by n positions */
	/* 	3. Subtract 1 */
	/* 	4. Check if 0 */
	/* If 0 then cannot be merged */
	if (a.dcbits == b.dcbits) {
		ushort mask = (a.port ^ b.port) >> a.dcbits;
		if (mask - 1)
			return false;
		else
			return true;
	}
	return false;
}

void merge(portPrefix a) {
	/* Merge can only be called when it is mergeable */
	/* So increase the dcbits (Replace last bit with wildcard) */
	a.dcbits += 1;
	/* Replace the last element with the new element */
	prefixes.back() = a;

	for (int i = prefixes.size()-2 ; i >= 0; i--) {
		if (canMerge(prefixes.at(i), prefixes.at(i+1))) {
			prefixes.pop_back();
			prefixes.at(i).dcbits++;
		}
	}
}

void convertRangeToPrefixes() {
	/* Just push the first port to avoid a comparison in each iteration */
	portPrefix a = { .port = ushort(range.lower), .dcbits = 0 };
	prefixes.push_back(a);

	/* Now add each port one by one, after checking if a merge is possible */
	for (int i = range.lower + 1; i <= range.higher ; i++) {
		a.port = ushort(i);
		a.dcbits = 0;
		/* If a merge is possible once it might be possible more times */
		if (canMerge(a, prefixes.back()))
			merge(a);
		else
		/* If it isn't just add it to the vec */
			prefixes.push_back(a);
	}
}

int main(int argc, char const* argv[]) {
	if (argc != 3) {
		cout << "Expected usage: " << argv[0]
			<< "<Lower port> <Higher port>"
			<<endl;
	}
	else {
		range.lower  = stoi(argv[1]);
		range.higher = stoi(argv[2]);
		convertRangeToPrefixes();
		for (auto&& i : prefixes) {
			i.print();
		}
	}
}
