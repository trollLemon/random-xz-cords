#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define MIN_DISTANCE 2500 // each point will be at least this many units away from each other
#define MAP_WIDTH 25     // output size
typedef std::vector<std::pair<long, long>> t_data; // typedef to make typing easier




/* *
 * Verifies the new random point is at least MIN_DISTANCE for every other point.
 * 
 * Arguments:
 *  points: a t_data with points in it
 *  point: a point with an x and a z coord
 *
 * If the point adheres to this restriction, this function returns true; false if not.
 *
 * If the points vector is empty, the function returns true.   
 *
 * */
bool verifyPoints(t_data points, std::pair<long, long> point) {

  if (points.empty()){
    return true;
  }

    //compare point to every other point in the list
    //we can do this in linear time
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


/* *
 * Generates random points. Returns the points as a t_data. 
 *
 * Arguments:
 * 
 *  size: amount of points to generate
 *  upperXBound: The max x coordinate the random number generator should generate
 *  lowerXBound: The min x coordinate the random number generator should generate
 *  upperZBound: The max z coordinate the random number generator should generate
 *  lowerZBound: The min z coordinate the random number generator should generate
 * 
 * The points generated by this function are guaranteed to be at least MIN_DISTANCE from each other.
 * 
 *
 * */
t_data generatePoints(int size, long upperXBound, long lowerXBound,
                     long upperZBound, long lowerZBound) {

  std::random_device r; // a seed source for the random number engine
  std::seed_seq seed{r(), r(), r(), r(), r(), r(),
                     r(), r(), r(), r(), r()}; // seeding stuff

  std::mt19937_64 gen(seed);

  std::uniform_int_distribution<> xdistrib(lowerXBound, upperXBound);
  std::uniform_int_distribution<> zdistrib(lowerZBound, upperZBound);

  int i = 0; // point counter

  t_data randPoints;
  
  // while we need to generate points
  while (i < size) {    

    // generate coordinates
    long x = xdistrib(gen);
    long z = zdistrib(gen);

    // make the x and z coord into a point
    std::pair<long, long> point = std::make_pair(x, z);

    // if this point is far enough away from every other point, add it to the
    // list of points and increment the point counter.
    if (verifyPoints(randPoints, point)) {
      randPoints.push_back(point);
      i++;
    }
  }

  return randPoints;
}



/* *
 * Prints a ascii representation of the positions of the chests within the boundaries
 *
 * Arguments:
 *  points: random points
 *  x: width of the map
 *  z: height of the map
 *  offsetX: offset to make all x positive*
 *  offsetZ: offset to make all z positive* 
 *
 *  *since we can have negative coordinates, we need to add an offset to the coordinates
 *   so we can access the positions in a 2D array. 
 *   A bound from -10000 to 10000 is the same as a bound from 0 to 20000 relative to the
 *   position and distance of the points; the distances will still be the same
 *
 *
 *
 * */
void printMap(t_data points, long x, long z, long offsetX, long offsetZ) {

  std::vector<char> width(z, '.');

  std::vector<std::vector<char>> map(x, width);

  map[x / 2][z / 2] = 'O'; // this marks the spawn point at 0,0,0. 


  // divisors to scale down point values to fit on the map
  long divisorX = offsetX / MAP_WIDTH * 2; 
  long divisorZ = offsetZ / MAP_WIDTH * 2;
  
  std::cout << "X and Z Coordinates::::::" << std::endl;
  for (auto coord : points) {
    std::cout << coord.first << ", " << coord.second << std::endl;
    
    //scale points 
    long currX = (coord.first + offsetX) / divisorX;
    long currZ = (coord.second + offsetZ) / divisorZ;

    map[currX][currZ] = 'X'; //mark this point with a chest marker
  }
    
// print the map
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
  long relativeX =  MAP_WIDTH;
  long relativeZ = MAP_WIDTH;


  t_data points = generatePoints(size, upX, loX, upZ, loZ);
  printMap(points, relativeX, relativeZ, offsetX, offsetZ);

  return 0;
}
