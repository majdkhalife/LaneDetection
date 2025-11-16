#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

struct LineEquation {
    double slope;
    double intercept;
    bool valid;
    LineEquation() : slope(0.0), intercept(0.0), valid(false) {}
};

struct LanePoints {
    bool has_left;
    bool has_right;
    cv::Point left_p1, left_p2;
    cv::Point right_p1, right_p2;
    LanePoints() : has_left(false), has_right(false) {}
};

LanePoints lane_lines(const cv::Mat& image, const std::vector<cv::Vec4i>& lines);

cv::Mat draw_lane_lines(const cv::Mat& image, const LanePoints& lanes, const cv::Scalar& color = cv::Scalar(0, 0, 255), int thickness = 12);
