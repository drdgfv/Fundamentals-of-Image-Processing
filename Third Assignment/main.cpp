#include <opencv2/opencv.hpp>
#include "video_cap.h"
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int trackbar_value = 0;
int trackbar_max_value = 100;

void on_trackbar(int pos, void* userdata) {
    trackbar_value = pos;
}

int main(int argc, char** argv)
{

    int camera = 0, pressed_key;
    vector<int> operations_array; //oerations array to cumulative operations;
    unordered_set <char> possible_operations = {'C','c','B','b',27,8}; //the set of possible operations

    VideoCapture src_cap;
    VideoCapture cpy_cap;

    namedWindow("Source Capture");
    namedWindow("Copy Capture");

    createTrackbar("Blur Level", "Copy Capture" , NULL, trackbar_max_value, on_trackbar);
    setTrackbarPos("Blur Level", "Copy Capture", 0);

    optionsHeader();

    if(!src_cap.open(camera)) return 0;
    for(;;)
    {
        Mat src_frame;
        Mat cpy_frame;
        
        cpy_cap = src_cap;
        src_cap >> src_frame;
        cpy_cap >> cpy_frame;
        
        if( src_frame.empty() ) break;
        
        pressed_key = waitKey(1);

        // update operations_array if the key pressed is one of the possible operations
        if (possible_operations.find(pressed_key) != possible_operations.end()) operations_array.push_back(pressed_key);

        int kernel_size = (trackbar_value * 2) + 1;

        if(operations(src_frame, cpy_frame, operations_array, kernel_size)) break; // do operation, an ESC returns 1, so the videos end.
        
        imshow("Source Capture", src_frame);
        imshow("Copy Capture", cpy_frame);
  
    }

    src_cap.release();
    cpy_cap.release(); 
    return 0;
}