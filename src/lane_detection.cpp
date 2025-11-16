//
// Created by Majd Khalife on 2025-11-15.
//
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include "lane_detection.h"

LineEquation compute_lane_equation(const std::vector<cv::Vec4i>& segments, bool is_left) {
    std::vector<double> slopes;
    std::vector<double> intercepts;
    std::vector<double> weights;

    for (const auto& seg : segments) {
        int x1 = seg[0], y1 = seg[1], x2 = seg[2], y2 = seg[3];
        if (x1 == x2) {
            continue;
        }

        double slope = static_cast<double>(y2 - y1) / static_cast<double>(x2 - x1);
        if (is_left && slope >= 0) continue;
        if (!is_left && slope <= 0) continue;

        double intercept = y1 - slope * x1;
        double length = std::hypot(static_cast<double>(x2 - x1), static_cast<double>(y2 - y1));

        slopes.push_back(slope);
        intercepts.push_back(intercept);
        weights.push_back(length);
    }

    LineEquation result;
    if (!weights.empty()) {
        double weight_sum = 0.0;
        double slope_sum = 0.0;
        double intercept_sum = 0.0;

        for (size_t i = 0; i < weights.size(); ++i) {
            weight_sum += weights[i];
            slope_sum += weights[i] * slopes[i];
            intercept_sum += weights[i] * intercepts[i];
        }

        result.slope = slope_sum / weight_sum;
        result.intercept = intercept_sum / weight_sum;
        result.valid = true;
    }

    return result;
}

std::pair<LineEquation, LineEquation>
average_slope_intercept(const std::vector<cv::Vec4i>& lines) {
    LineEquation left_lane  = compute_lane_equation(lines, true);   // slope < 0
    LineEquation right_lane = compute_lane_equation(lines, false);  // slope > 0
    return {left_lane, right_lane};
}

bool pixel_points(double y1, double y2,
                  const LineEquation& line,
                  cv::Point& p1, cv::Point& p2) {
    if (!line.valid) {
        return false;
    }

    double slope = line.slope;
    double intercept = line.intercept;

    double x1 = (y1 - intercept) / slope;
    double x2 = (y2 - intercept) / slope;

    p1 = cv::Point(static_cast<int>(x1), static_cast<int>(y1));
    p2 = cv::Point(static_cast<int>(x2), static_cast<int>(y2));
    return true;
}

LanePoints lane_lines(const cv::Mat& image, const std::vector<cv::Vec4i>& lines) {
    LanePoints result;

    auto [left_lane, right_lane] = average_slope_intercept(lines);

    double y1 = static_cast<double>(image.rows);
    double y2 = y1 * 0.6;

    if (pixel_points(y1, y2, left_lane, result.left_p1, result.left_p2)) {
        result.has_left = true;
    }

    if (pixel_points(y1, y2, right_lane, result.right_p1, result.right_p2)) {
        result.has_right = true;
    }

    return result;
}

cv::Mat draw_lane_lines(const cv::Mat& image,
                        const LanePoints& lanes,
                        const cv::Scalar& color,
                        int thickness) {
    cv::Mat line_image = cv::Mat::zeros(image.size(), image.type());

    if (lanes.has_left) {
        cv::line(line_image, lanes.left_p1, lanes.left_p2, color, thickness);
    }
    if (lanes.has_right) {
        cv::line(line_image, lanes.right_p1, lanes.right_p2, color, thickness);
    }

    cv::Mat output;
    cv::addWeighted(image, 1.0, line_image, 1.0, 0.0, output);
    return output;
}
