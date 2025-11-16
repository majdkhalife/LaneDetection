//
// Created by Majd Khalife on 2025-11-15.
//
#include <opencv2/opencv.hpp>
#include <vector>
#include "hough_transform.h"


std::vector<cv::Vec4i> hough_transform(const cv::Mat& image) {
    double rho = 1.0;
    double theta = CV_PI / 180.0;
    int threshold  = 20;
    double minLineLength = 20.0;
    double maxLineGap    = 500.0;

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(image, lines, rho, theta, threshold,
                    minLineLength, maxLineGap);
    return lines;
}

