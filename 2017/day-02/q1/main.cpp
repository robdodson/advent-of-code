#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Split string at delimeter.
// Returns vector<string>.
vector<string> split(string source, string delimiter) {
  size_t idx = 0;
  string token;
  vector<string> output;

  while ((idx = source.find(delimiter)) != string::npos) {
    token = source.substr(0, idx);
    output.push_back(token);
    source.erase(0, idx + delimiter.length());
  }

  // Adds the remainder of the string after all of the dilimeted
  // sections have been removed.
  output.push_back(source);

  return output;
}

// Each column contains a number as a string.
// For the collection of columns, find the difference between the largest and
// smallest numbers.
int findDifference(const vector<string>* columns) {
  int largest;
  int smallest;
  for (int i = 0; i < (*columns).size(); i++) {
    int num = stoi((*columns)[i]);
    if (i == 0) {
      largest = num;
      smallest = num;
      continue;
    }
    if (num < smallest) {
      smallest = num;
      continue;
    }
    if (num > largest) {
      largest = num;
      continue;
    }
  }
  cout << largest << " - " << smallest << " = " << largest - smallest << endl;
  return largest - smallest;
}

int main() {
  // Read da file 'o text
  string filename = "input.txt";
  ifstream fileStream(filename);
  if (!fileStream) {
    cerr << "Unable to open file " << filename << endl;
    exit(1);
  }

  // Split each column and push into the rows collection
  vector<vector<string>> rows;
  string buffer;
  while (getline(fileStream, buffer)) {
    vector<string> columns = split(buffer, "\t");
    rows.push_back(columns);
  }

  // Close da file. Thank you file.
  fileStream.close();

  // Find the difference between each row and add to the checksum.
  int checksum = 0;
  for (vector<string> row : rows) {
    int difference = findDifference(&row);
    checksum = checksum + difference;
  }
  cout << "Checksum: " << checksum << endl;
}
