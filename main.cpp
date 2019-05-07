#include "bits/stdc++.h"

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include "camera-controller.h"

using namespace std;
using namespace cv;

/*
  TODO:
  - look at how each keypoint moves frame to frame
  - find some way to map this distance to a depth vector
*/
int main(int argc, char const *argv[]) {

  auto camController = CamController(25000);
  camController.analyseVideo(argv[1]);
  
  // auto keypoints = camController.keypoints;
  // for (int i = 0; i < keypoints.size(); i++) {
  //   cout << keypoints[i].pt.x << ", " << keypoints[i].pt.y << endl;
  // }

  return 0;
}
