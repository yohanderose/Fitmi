#ifndef B74DADE3_E134_1527_105E_DE2DD79B9B81
#define B74DADE3_E134_1527_105E_DE2DD79B9B81

#include "bits/stdc++.h"

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

using namespace std;
using namespace cv;

class CamController {
 public:
  int MAX_FEATURES = 1500;
  vector<KeyPoint> keypoints;
  Mat descriptor;

 public:
  CamController(int max) : MAX_FEATURES(max) {}

  void analyseVideo(char const *fileName) {
    
    VideoCapture cam(fileName);
    Mat frame;

    auto orb = ORB::create(MAX_FEATURES);

    while (cam.isOpened()) {
      for (;;) {
        cam >> frame;
        if (frame.empty()) { break; }
        orb->detectAndCompute(frame, Mat(), keypoints, descriptor);
        drawKeypoints(frame, keypoints, frame);
        imshow("preview", frame);
        if (waitKey(1) == 27) {  // esc twice to quit
          break;
        }
        waitKey(10);
      }
      cam.release();
      destroyAllWindows();
    }
  }

  void recordVideo(string outputName) {
    VideoCapture cam(2);
    Mat frame;

    while (cam.isOpened()) {
      int w = cam.get(CAP_PROP_FRAME_WIDTH);
      int h = cam.get(CAP_PROP_FRAME_HEIGHT);
      VideoWriter writer(outputName+".avi", CV_FOURCC('M', 'J', 'P', 'G'), 10,
                         Size(w, h), true);

      vector<KeyPoint> keypoints;
      Mat descriptor;
      auto orb = ORB::create(MAX_FEATURES);

      for (;;) {
        cam >> frame;
        cvtColor(frame, frame, COLOR_RGB2BGR);
        writer.write(frame);

        orb->detectAndCompute(frame, Mat(), keypoints, descriptor);
        drawKeypoints(frame, keypoints, frame);
        imshow("preview", frame);
        if (waitKey(1) == 27) {  // esc twice to quit
          break;
        }
        waitKey(1);
      }
      writer.release();
      cam.release();
    }
    destroyAllWindows();
  }
};

#endif /* B74DADE3_E134_1527_105E_DE2DD79B9B81 */