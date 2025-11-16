#include "process_video.h"
#include "hough_transform.h"
#include "lane_detection.h"
#include "select_region_of_interest.h"

#include <opencv2/opencv.hpp>
#include <iostream>

int process_video(const std::string& video_path) {
    cv::VideoCapture cap(video_path);
    if (!cap.isOpened()) {
        std::cerr << "Unable to open camera/video: " << video_path << "\n";
        return -1;
    }

    while (true) {
        cv::Mat frame;
        if (!cap.read(frame) || frame.empty()) {
            std::cout << "End of video or failed read.\n";
            break;
        }

        cv::Mat gray_frame;
        cv::Mat blurred_image;
        cv::Mat canny;

        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray_frame, blurred_image, cv::Size(5,5), 3,3);
        cv::Canny(blurred_image, canny, 50,150);

        cv::Mat canny_roi = select_region_of_interest(canny);

        std::vector<cv::Vec4i> lines = hough_transform(canny_roi);

        LanePoints lanes = lane_lines(frame, lines);

        cv::Mat lane_frame = draw_lane_lines(frame, lanes);

        cv::imshow("Video", frame);
        // cv::imshow("Gaussian Blur", blurred_image);
        // cv::imshow("Gray", gray_frame);
        // cv::imshow("Canny", canny);
        cv::imshow("Canny ROI", canny_roi);
        cv::imshow("Lane Detection", lane_frame);

        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
