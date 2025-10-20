#include <iostream>
#include <string>
#include "video_cap.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void optionsHeader(){
    cout << "B or b : Blurring (Gaussian)" << endl;
    cout << "C or c : Edge Detection (Canny)" << endl;
    cout << "S or s : Gradient Estimation (SobelX)" << endl;
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
            case 'C':
                edges(cpy);
                break;
            case 's':
            case 'S':
                gradient(cpy);
                break;
            case 27: 
                return 1;
            case 8:
                src.copyTo(cpy);
        }
    }

    return 0;
}

void edges(Mat cpy){

    Mat canny_edges;
    Mat gray_cpy;     
    cvtColor(cpy, gray_cpy, COLOR_BGR2GRAY);         
    Canny(gray_cpy, canny_edges, 50, 150); 
    cvtColor(canny_edges, cpy, COLOR_GRAY2BGR); 

}

void gradient(Mat cpy){

    Mat sobel_gradient;
    Mat gray_cpy;     
    cvtColor(cpy, gray_cpy, COLOR_BGR2GRAY);  
    cvtColor(gray_cpy, gray_cpy, COLOR_GRAY2BGR);                
    Sobel(gray_cpy, sobel_gradient, CV_16S, 1,0); 
    sobel_gradient.convertTo(cpy, CV_8U, 1, 127); 

}
