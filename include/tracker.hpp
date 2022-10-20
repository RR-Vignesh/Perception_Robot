#ifndef _INCLUDE_TRACKER_HPP_
#define _INCLUDE_TRACKER_HPP_
#include <vector>
#include <string>
// #include "../app/tracker.cpp"

using namespace std;
class Trackers{
public:
  vector<int> ids;
  string fileName;
private:
  void assigId();
  void saveTrajectory();
};
#endif