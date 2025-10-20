#include <iostream>
#include <string>
#include "video_cap.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void optionsHeader(){
    cout << "B or b : Blurring (Gaussian)" << endl;
    cout << "C or c : Edge Detection (Canny)" << endl;
    cout << "Backspace : Back to Source Image" << endl;
}

int operations(Mat src, Mat cpy, vector<int> operations, int size){

    for(auto operation : operations){

        switch(operation){

            case 'b':
            case 'B': 
                GaussianBlur(cpy, cpy, Size(size,size),0);
                break;
            case 'c':
            case 'C': {
                Mat canny_edges;
                Mat gray_cpy;     
                cvtColor(cpy, gray_cpy, COLOR_BGR2GRAY);         
                Canny(cpy, canny_edges, 50, 150); 
                cvtColor(canny_edges, cpy, COLOR_GRAY2BGR); 
                break;
            }
            case 27: 
                return 1;
            case 8:
                src.copyTo(cpy);
        }
    }

    return 0;
}
