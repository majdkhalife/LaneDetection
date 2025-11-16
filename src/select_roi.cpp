#include <opencv2/opencv.hpp>
#include <vector>
#include "select_region_of_interest.h"

cv::Mat select_region_of_interest(const cv::Mat& image) {
    cv::Mat mask = cv::Mat::zeros(image.size(), image.type());
    cv::Scalar ignore_mask_color = cv::Scalar::all(255);

    int rows = image.rows;
    int cols = image.cols;

    cv::Point bottom_left(cols * 0.1, rows * 0.9);
    cv::Point top_left(cols * 0.4, rows * 0.6);
    cv::Point bottom_right(cols * 0.9, rows * 0.95);
    cv::Point top_right(cols * 0.6, rows * 0.5);

    std::vector<cv::Point> vertices = { bottom_left, top_left, bottom_right, top_right };
    std::vector<std::vector<cv::Point>> pts = { vertices };

    cv::fillPoly(mask, pts, ignore_mask_color);

    cv::Mat masked_image;
    cv::bitwise_and(image, mask, masked_image);

    return masked_image;
}
