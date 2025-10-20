#include <iostream>
#include <string>
#include "video_cap.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void optionsHeader(){
    cout << "B or b : Blurring (Gaussian)" << endl;
    cout << "E or e : Edge Detection (Canny)" << endl;
    cout << "S or s : Gradient Estimation (SobelX)" << endl;
    cout << "R or r : Brightness Enhancement" << endl;
    cout << "T or t : Contrast Enhancement" << endl;
    cout << "N or n : Negative" << endl;
    cout << "G or g : Gay Scale" << endl;
    cout << "Z or z : Resize in 1/4 both dimensions" << endl;
    cout << "L or l : Resize in 1/4 both dimensions" << endl;
    cout << "H or h : Flip horizontal" << endl;
    cout << "C or c : Clear all operations" << endl;
    cout << "Backspace : Undo the last operation" << endl;
}

int operations(Mat& src, Mat& cpy, vector<int>& operations, int size, int brightness, float contrast){

    for(auto operation : operations){

        switch(operation){

            case 'b':
            case 'B': 
                GaussianBlur(cpy, cpy, Size(size,size),0);
                break;
            case 'e':
            case 'E':
                edges(cpy);
                break;
            case 's':
            case 'S':
                gradient(cpy);
                break;
            case 'r':
            case 'R':
                cpy.convertTo(cpy, -1, 1, brightness); 
                break;
            case 't':
            case 'T':
                cpy.convertTo(cpy, -1, contrast, 0);
                break;
            case 'n':
            case 'N':
                cpy.convertTo(cpy, -1, -1, 255);
                break;
            case 'g':
            case 'G':
                grayScale(cpy);
                break;
            case 'z':
            case 'Z':
                resize(cpy, cpy, Size(0,0), 0.5, 0.5, INTER_AREA);
                break;
            case 'l':
            case 'L':
                rotate(cpy, cpy, ROTATE_90_CLOCKWISE);
                break;
            case 'h':
            case 'H':
                flip(cpy,cpy,1);
                break;
            case 'c':
            case 'C':
                src.copyTo(cpy);
                break;
            case 27: 
                return 1;
            case 8:
                if(operations.size() > 1){
                    operations.pop_back();
                    operations.pop_back();
                }
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

void grayScale(Mat cpy){
    Mat gray_cpy;     
    cvtColor(cpy, gray_cpy, COLOR_BGR2GRAY);  
    cvtColor(gray_cpy, cpy, COLOR_GRAY2BGR);
}
