#include "opencv2/opencv.hpp"
#include <unistd.h>

using namespace cv;
unsigned int microseconds;

int main(int argc, char** argv)
{
    VideoCapture cap;

    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(2))
        return 0;

    cap.set(CV_CAP_PROP_FRAME_WIDTH, 176);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 144);
	
    for(;;)
    {

          Mat frame;
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          
          //resize(frame, frame, Size(130, 103), 0, 0, INTER_NEAREST);

          vector<int> compression_params;
		  compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		  compression_params.push_back(85);

          //imshow("this is you, smile! :)", frame);
          imwrite("/var/www/html/robot/html5/images/camera.jpg", frame, compression_params);

          usleep(1 * 1000 * 40);
    }

    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}
