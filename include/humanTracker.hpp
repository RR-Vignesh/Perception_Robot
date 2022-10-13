#ifndef INCLUDE_HUMANTRACKER_HPP_
#define INCLUDE_HUMANTRACKER_HPP_

#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"

class HumanTracker: public Detector, public Tracker{
private:
  void getcameraframe();
  void transform_robotcoordinates();
  void exit();

public:
  void calibratecamera();

};

#endif