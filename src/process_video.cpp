#include "process_video.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int process_video(const std::string& video_path) {
    cv::VideoCapture cap(video_path);
    if (!cap.isOpened()) {
        std::cerr << "Unable to open camera\n";
        return -1;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()){}
        cv::imshow("Video", frame);
        if (cv::waitKey(30) == 27) {
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}