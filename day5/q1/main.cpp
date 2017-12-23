#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Steps taken.
// Index in instruction set.
// Pointer to the current instuction.
// If we go past the bounds of the vector, we're done.
int runMaze(vector<int>* maze) {
  int stepsTaken = 0;
  int idx = 0;
  bool escaped = false;
  while (!escaped) {
    cout << "idx: " << idx << endl;
    cout << "instruction: " << (*maze)[idx] << endl;
    int oldIdx = idx;
    // jump
    idx = idx + (*maze)[idx];
    // increment previous instruction
    (*maze)[oldIdx] = (*maze)[oldIdx] + 1;
    stepsTaken++;
    if (idx < 0 || idx > (*maze).size() - 1) {
      escaped = true;
      break;
    }
  }
  return stepsTaken;
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
  vector<int> maze;
  string buffer;
  while (getline(fileStream, buffer)) {
    maze.push_back(stoi(buffer));
  }

  // Close da file. Thank you file.
  fileStream.close();

  cout << runMaze(&maze) << endl;

}
