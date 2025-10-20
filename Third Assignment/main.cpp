#include <opencv2/opencv.hpp>
#include "video_cap.h"
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int brightness_level = 0;
int max_brightness_level = 150;
float contrast_level = 0;
float max_contrast_level = 20;
int trackbar_value = 0;
int trackbar_max_value = 100;

void on_blur_trackbar(int pos, void* userdata) {
    trackbar_value = pos;
}

void on_bright_trackbar(int pos, void* userdata) {
    brightness_level = pos;
}

void on_contrast_trackbar(int pos, void* userdata) {
    contrast_level = pos;
}   


int main(int argc, char** argv)
{

    int camera = 0, pressed_key;
    vector<int> operations_array; //oerations array to cumulative operations;
    unordered_set <char> possible_operations = {'C','c','B','b','S','s','R','r','E','e','T','t','N','n','G','g',27,8}; //the set of possible operations

    VideoCapture src_cap;
    VideoCapture cpy_cap;

    namedWindow("Source Capture");
    namedWindow("Copy Capture");

    createTrackbar("Blur Level", "Copy Capture" , NULL, trackbar_max_value, on_blur_trackbar);
    setTrackbarPos("Blur Level", "Copy Capture", 0);

    createTrackbar("Brightness Level", "Copy Capture" , NULL, trackbar_max_value, on_bright_trackbar);
    setTrackbarPos("Brightness Level", "Copy Capture", 0);

    createTrackbar("Contrast Level", "Copy Capture" , NULL, trackbar_max_value, on_contrast_trackbar);
    setTrackbarPos("Contrast Level", "Copy Capture", 0);

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
        int brightness = brightness_level - 50;
        float contrast = (contrast_level + 1)/10;

        if(operations(src_frame, cpy_frame, operations_array, kernel_size, brightness, contrast)) break; // do operation, an ESC returns 1, so the videos end.
        
        imshow("Source Capture", src_frame);
        imshow("Copy Capture", cpy_frame);
  
    }

    src_cap.release();
    cpy_cap.release(); 
    return 0;
}