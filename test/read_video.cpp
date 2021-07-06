#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;

int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  string filename = "filesrc location=video.mp4 ! qtdemux ! queue ! h264parse ! omxh264dec ! nvvidconv ! video/x-raw,format=BGRx ! queue ! videoconvert ! queue ! video/x-raw, format=BGR ! appsink";
  cv::VideoCapture cap(filename, cv::CAP_GSTREAMER); 
   
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
	
  while(1){

    cv::Mat frame;
    // Capture frame-by-frame
    cap >> frame;
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Display the resulting frame
    cv::imshow( "Frame", frame );

    // Press  ESC on keyboard to exit
    char c=(char) cv::waitKey(25);
    if(c==27)
      break;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  cv::destroyAllWindows();
	
  return 0;
}


