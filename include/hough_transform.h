#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

std::vector<cv::Vec4i> hough_transform(const cv::Mat& image);
