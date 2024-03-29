/**
 *  - OpenCV Project 1
 *      - The aim of this project is to detect edges from real time video or camera
 *      - The project is based on skills I learned from Chapter 1 and 2
 *      - Chapter 1 topics
 *          - Reading images
 *          - Reading Videos
 *          - Reading Webcams
 *
 *      - Chapter 2 topics
 *          - Basic functions
 *              - Converting RGB images to Grayscale images
 *              - Blurring images
 *              - Detecting images edges
 *              - Dilating images [ increasing image edge thickness ]
 *              - Eroding images [ decreasing image edge thickness ]
*/

#include<opencv2/opencv.hpp>
#include<string>
#include<iostream>

const unsigned int ESC_ASCII_CODE{27};

int main(int argc, char* argv[]) {
    // camera id
    const unsigned int DEFAULT_CAMERA_ID{0};
    // read real time video from the default camera
    cv::VideoCapture camera{DEFAULT_CAMERA_ID};

    // check if the camera with the given ID has been opened successfully
    if (!camera.isOpened()) {
        std::cout << "**** Could not open the camera with the given ID {" << DEFAULT_CAMERA_ID << "} ****"
            << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat frame;
    // read the real time video frame by frame
    while (cv::waitKey(1) != ESC_ASCII_CODE) {
        camera.read(frame);

        if (frame.empty()) {
            std::cout << "*** End of real time video has been reach ***" << std::endl;
            break;
        }

        // convert the current frame to gray scale image
        cv::Mat gray_scale_frame;
        cv::cvtColor(frame, gray_scale_frame, cv::COLOR_BGR2GRAY);
        // blur the current frame
        cv::Mat blurred_frame;
        cv::GaussianBlur(gray_scale_frame, blurred_frame, cv::Size{3, 3}, 3, 0);
        // detect image edges
        cv::Mat canny_frame;
        cv::Canny(blurred_frame, canny_frame, 25, 75);

        // dilate an image [ increase the thickness of the edge of an image ]
        cv::Mat dilated_frame;
        cv::Mat dilating_kernel{cv::getStructuringElement(cv::MORPH_RECT, cv::Size{3, 3})};
        cv::dilate(canny_frame, dilated_frame, dilating_kernel);

        cv::imshow("Realtime video", dilated_frame);
    }
    return EXIT_SUCCESS;
}