#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int findKey(int id, int* idList, int hashSpace){
	if(idList[id] == 1)
		return id;
	int i = id;
	while(true){
		if(idList[i] != 1){
			i = (i + 1) % (hashSpace + 1);
			continue;
		}
		else
			return i;
	}
}

int main(){

	string inputFile, outputFile;
	cout << "Please enter the input file address:" << endl;
	cin >> inputFile;
	cout << "Please enter the output file address:" << endl;
	cin >> outputFile;

	ifstream inf;
	inf.open(inputFile,ios::in);

	string line;
	int hashSpace, nodeCount, keyCount;

	getline(inf,line).good();
	hashSpace = stoi(line);

	getline(inf,line).good();
	nodeCount = stoi(line);

	getline(inf,line).good();
	keyCount = stoi(line);

	const char * split = ",";
	int* nodeID = new int[nodeCount];
	int* online = new int[hashSpace + 1];
	for(int i = 0; i < hashSpace; i++)
		online[i] = 0;

	getline(inf,line).good();
	char* input = (char*)line.c_str();
	char *p = strtok(input, split);
	int numTemp;
	for(int i = 0; i < nodeCount; i++){
		sscanf(p, "%d", &numTemp);
		nodeID[i] = numTemp;
		p = strtok(NULL, split);
		online[numTemp] = 1;
	}

	int* keyID = new int[keyCount];
	getline(inf,line).good();
	input = (char*)line.c_str();
	p = strtok(input, split);
	for(int i = 0; i < keyCount; i++){
		sscanf(p, "%d", &numTemp);
		keyID[i] = numTemp;
		p = strtok(NULL, split);
	}
	inf.close();

	ofstream ouf;
	ouf.open(outputFile);

	int row = int(log(double(hashSpace + 1)) / log(2.0));

	for(int i = 0; i < keyCount; i++){
		int target = findKey(keyID[i], online, hashSpace);
		ouf << target << endl;
		for(int j = 0; j < row; j++){
			ouf << j << " " ;
			int next = int((target + pow(2.0, j)));
			next = next % (hashSpace + 1);
			ouf << next << " " ;
			if(online[next] == 1)
				ouf << next << " " << endl;
			else{
				int temp = findKey(next, online, hashSpace);
				ouf << temp << " " << endl;
			}
		}
		ouf << endl;
	}
	ouf.close();

	delete [] nodeID;
	delete [] online;
	delete [] keyID;

	system("pause");
	return 0;
}