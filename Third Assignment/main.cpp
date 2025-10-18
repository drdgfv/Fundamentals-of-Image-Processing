#include <opencv2/opencv.hpp>
#include "video_cap.h"
using namespace cv;

int trackbar_value = 0;
int trackbar_max_value = 50;

void on_trackbar(int pos, void* userdata) {
    trackbar_value = pos;
}

int main(int argc, char** argv)
{

    int camera = 0;
    int operation = 0, pressed_key;
    VideoCapture src_cap;
    VideoCapture cpy_cap;

    namedWindow("Source Capture");
    namedWindow("Copy Capture");

    createTrackbar("Blur Level", "Copy Capture" , NULL, trackbar_max_value, on_trackbar);
    setTrackbarPos("Blur Level", "Copy Capture", 0);

    optionsHeader();

    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!src_cap.open(camera)) return 0;
    for(;;)
    {
        Mat src_frame;
        Mat cpy_frame;
        
        cpy_cap = src_cap;
        src_cap >> src_frame;
        cpy_cap >> cpy_frame;
        
        if( src_frame.empty() ) break; // end of video stream
        
        pressed_key = waitKey(1);

        if (pressed_key != -1) operation = pressed_key; // update operation every key_pressed, and persist the last operation.

        int kernel_size = (trackbar_value * 2) + 1;

        if(operations(src_frame, cpy_frame, operation, kernel_size)) break; // do operation, if not a ESC.
        
        imshow("Source Capture", src_frame);
        imshow("Copy Capture", cpy_frame);

        
    }

    src_cap.release(); // release the VideoCapture object
    cpy_cap.release(); // release the VideoCapture object
    return 0;
}