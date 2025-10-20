#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void optionsHeader();
int operations(Mat src, Mat cpy,  vector<int> operation, int size);
void edges(Mat cpy);
void gradient(Mat cpy);