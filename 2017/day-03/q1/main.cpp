#include <tuple>
#include <vector>
#include <iostream>
using namespace std;

int findTaxiDistance(int p1, int p2, int q1, int q2) {
  // |p1 - q1| + |p2 - q2|
  return (abs(p1 - q1)) + (abs(p2 - q2));
}

// Returns the Cartesian x, y coordinates for the given number
tuple<int, int> plotCoordinates(int target) {
  /**
    17  16  15  14  13
    18   5   4   3  12
    19   6   1   2  11
    20   7   8   9  10
    21  22  23---> ...
  **/

  vector<tuple<int, int>> headings = {
    make_tuple(1, 0),
    make_tuple(0, 1),
    make_tuple(-1, 0),
    make_tuple(0, -1)
  };
  int headingIdx = 0;
  tuple<int, int> heading = headings[headingIdx];
  
  tuple<int, int> position = make_tuple(0, 0);

  bool plotting = true;
  int iterations = target;
  int rounds = 2;
  int stepsThisRound = 1;

  // Move one space by applying the heading to our position.
  // Decrement steps.
  // Subtract one from iterations.
  // If there are no more iterations, break.
  // If we are out of steps, move to the next heading, decrement the round, start the next round.
  // If there are no more rounds, increment the number of steps and reset rounds to 2.
  while (plotting) {
    int steps = stepsThisRound;
    while (steps > 0) {
      int headingX = get<0>(heading);
      int headingY = get<1>(heading);
      int* posX = &get<0>(position);
      int* posY = &get<1>(position);
      *posX = *posX + headingX;
      *posY = *posY + headingY;
      steps = steps - 1;
      if (steps == 0) {
        headingIdx = headingIdx + 1;
        if (headingIdx == headings.size()) {
          headingIdx = 0;
        }
        heading = headings[headingIdx];
      }
      iterations = iterations - 1;
      if (iterations == 1) { // remember, 1 is located at 0, 0
        plotting = false;
        break;
      }
    }
    rounds = rounds - 1;
    if (rounds == 0) {
      rounds = 2;
      stepsThisRound = stepsThisRound + 1;
    }
  }

  return position;
}

int main() {
  auto coordinates = plotCoordinates(368078);
  cout << "coordinates: " << get<0>(coordinates) << ", " << get<1>(coordinates) << endl;
  cout << "distance: " << findTaxiDistance(0, 0, get<0>(coordinates), get<1>(coordinates)) << endl;
}
