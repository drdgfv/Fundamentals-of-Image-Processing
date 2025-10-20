#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void optionsHeader();
int operations(Mat src, Mat cpy, vector<int>& operations, int size, int brightness, float contrast);
void edges(Mat cpy);
void gradient(Mat cpy);
void grayScale(Mat cpy);