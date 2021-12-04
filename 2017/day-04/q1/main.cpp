#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

int validateAndSumPassphrases(vector<vector<string>>* passphrases) {
  int totalValidPassphrases = 0;
  for (vector<string> passphrase : *passphrases) {
    map<string, bool> wordMap;
    bool foundInvalidPassphrase = false;
    for (int i = 0; i < passphrase.size(); i++) {
      auto search = wordMap.find(passphrase[i]);
      if (search != wordMap.end()) {
        // We found a match. Passphrase is invalid!
        foundInvalidPassphrase = true;
        break;
      } else {
        wordMap[passphrase[i]] = true;
      }
    }
    if (!foundInvalidPassphrase) {
      totalValidPassphrases = totalValidPassphrases + 1;
    }
  }
  return totalValidPassphrases;
}

int main() {
  // Read da file 'o text
  string filename;
  cout << "Please enter a file name: ";
  cin >> filename;
  ifstream fileStream(filename);
  if (!fileStream) {
    cerr << "Unable to open file " << filename << endl;
    exit(1);
  }

  // Split each passphrase and push into the words collection
  vector<vector<string>> passphrases;
  string buffer;
  while (getline(fileStream, buffer)) {
    vector<string> words = split(buffer, " ");
    passphrases.push_back(words);
  }

  // Close da file. Thank you file.
  fileStream.close();

  int validPassphrases = validateAndSumPassphrases(&passphrases);
  cout << "Valid phrases: " << validPassphrases << endl;

}
