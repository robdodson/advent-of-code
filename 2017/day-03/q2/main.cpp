#include <exception>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
using namespace std;

int MAX = 368078;

int findTaxiDistance(int p1, int p2, int q1, int q2) {
  // |p1 - q1| + |p2 - q2|
  return (abs(p1 - q1)) + (abs(p2 - q2));
}

// For each x, y point, check for values in the 8 adjacent positions.
// Sum all found values and return.
int getAdjacentValueForPoint(map<int, map<int, int>>* plane,
                             int pointX,
                             int pointY) {
  vector<tuple<int, int>> adjacentHeadings = {
      make_tuple(1, 0),  make_tuple(1, 1),  make_tuple(0, 1),
      make_tuple(-1, 1), make_tuple(-1, 0), make_tuple(-1, -1),
      make_tuple(0, -1), make_tuple(1, -1)};
  int sum = 0;
  for (int i = 0; i < adjacentHeadings.size(); i++) {
    tuple<int, int> adjacentHeading = adjacentHeadings[i];
    int adjacentX = pointX + get<0>(adjacentHeading);
    int adjacentY = pointY + get<1>(adjacentHeading);
    int value;
    try {
      value = (*plane).at(adjacentX).at(adjacentY);
    } catch (exception& err) {
      value = 0;
    }
    sum = sum + value;
  }
  return sum;
}

// Returns the Cartesian x, y coordinates for the given number
void plotCoordinates(int target) {
  /**
    17  16  15  14  13
    18   5   4   3  12
    19   6   1   2  11
    20   7   8   9  10
    21  22  23---> ...
  **/

  vector<tuple<int, int>> headings = {make_tuple(1, 0), make_tuple(0, 1),
                                      make_tuple(-1, 0), make_tuple(0, -1)};
  int headingIdx = 0;
  tuple<int, int> heading = headings[headingIdx];

  map<int, map<int, int>> plane;
  plane[0][0] = 1;
  tuple<int, int> position = make_tuple(0, 0);

  bool plotting = true;
  int iterations = target;
  int rounds = 2;
  int stepsThisRound = 1;

  // Move one space by applying the heading to our position.
  // Decrement steps.
  // Subtract one from iterations.
  // If there are no more iterations, break.
  // If we are out of steps, move to the next heading, decrement the round,
  // start the next round. If there are no more rounds, increment the number of
  // steps and reset rounds to 2.
  while (plotting) {
    int steps = stepsThisRound;
    while (steps > 0) {
      int headingX = get<0>(heading);
      int headingY = get<1>(heading);
      int* posX = &get<0>(position);
      int* posY = &get<1>(position);
      *posX = *posX + headingX;
      *posY = *posY + headingY;
      int pointValue = getAdjacentValueForPoint(&plane, get<0>(position), get<1>(position));
      plane[*posX][*posY] = pointValue;
      steps = steps - 1;
      if (steps == 0) {
        headingIdx = headingIdx + 1;
        if (headingIdx == headings.size()) {
          headingIdx = 0;
        }
        heading = headings[headingIdx];
      }
      iterations = iterations - 1;
      if (iterations == 1) {  // remember, 1 is located at 0, 0
        plotting = false;
        break;
      }
      // If we find a number bigger than the MAX, break out and log it.
      if (pointValue > MAX) {
        plotting = false;
        cout << "New max: " << pointValue << endl;
        break;
      }
    }
    rounds = rounds - 1;
    if (rounds == 0) {
      rounds = 2;
      stepsThisRound = stepsThisRound + 1;
    }
  }
}

int main() {
  plotCoordinates(MAX);
}
