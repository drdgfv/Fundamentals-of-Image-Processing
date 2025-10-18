#include <iostream>
#include <string>
#include "video_cap.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void optionsHeader(){
    cout << "B or b : Blurring (Gaussian)" << endl;
    cout << "Any other : Back to Color Image" << endl;
}

int operations(Mat src, Mat cpy, int operation, int size){

    switch(operation){

        case 66:
        case 98: 
            GaussianBlur(src, cpy, Size(size,size),0);
            return 0;
        case 27: 
            return 1;
    }

    return 0;
}
