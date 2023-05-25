#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define MIN_DISTANCE 3000
#define MAP_WIDTH 25
typedef std::vector<std::pair<long, long>> t_data;

bool verifyPoints(t_data points, std::pair<long, long> point) {

  if (points.empty()){
    return true;
  }

    for (int j = 0; j < points.size(); j++) {
      long x1 = point.first;
      long x2 = points[j].first;

      long y1 = point.second;
      long y2 = points[j].second;

      long dX = x2 - x1;
      long dY = y2 - y1;

      if (sqrt(dY * dY + dX * dX) <= MIN_DISTANCE) {
        return false;
      }
    }
  return true;
}

t_data generatePoints(int size, long upperXBound, long lowerXBound,
                     long upperZBound, long lowerZBound) {

  std::random_device r; // a seed source for the random number engine
  std::seed_seq seed{r(), r(), r(), r(), r(), r(),
                     r(), r(), r(), r(), r()}; // seeding stuff

  std::mt19937_64 gen(seed);

  std::uniform_int_distribution<> xdistrib(lowerXBound, upperXBound);
  std::uniform_int_distribution<> zdistrib(lowerZBound, upperZBound);

  int i = 0;
  t_data randPoints;
  while (i < size) {

    long x = xdistrib(gen);
    long z = zdistrib(gen);

    std::pair<long, long> point = std::make_pair(x, z);
    if (verifyPoints(randPoints, point)) {
      randPoints.push_back(point);
      i++;
    }
  }

  return randPoints;
}

void printMap(t_data points, long x, long z, long offsetX, long offsetZ) {

  std::vector<char> width(z, '.');

  std::vector<std::vector<char>> map(x, width);

  map[x / 2][z / 2] = 'O';

  long divisorX = offsetX / MAP_WIDTH * 2;
  long divisorZ = offsetZ / MAP_WIDTH * 2;
  
  std::cout << "X and Z Coordinates::::::" << std::endl;
  for (auto coord : points) {
    std::cout << coord.first << ", " << coord.second << std::endl;
    long currX = (coord.first + offsetX) / divisorX;
    long currZ = (coord.second + offsetZ) / divisorZ;

    map[currX][currZ] = 'X';
  }
    

  std::cout << "Relative positions:::::::::" << std::endl;
  for (auto line : map) {

    for (char c : line) {
      std::cout << c << " ";
    }

    std::cout << std::endl;
  }
}

int main() {
  int size = 23;
  long upX = 10000;
  long loX = -10000;
  long upZ = 10000;
  long loZ = -10000;
  long offsetX = 10000;
  long offsetZ = 10000;
  long relativeX = 25;
  long relativeZ = 25;


  t_data points = generatePoints(size, upX, loX, upZ, loZ);
  printMap(points, relativeX, relativeZ, offsetX, offsetZ);

  return 0;
}
