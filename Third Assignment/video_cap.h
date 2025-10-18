#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void optionsHeader();
int operations(Mat src, Mat cpy, int operation, int size);
// void on_trackbar(int pos, void* userdata);