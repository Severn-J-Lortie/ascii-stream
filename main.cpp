#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <string>

int main() {
    
    cv::VideoCapture webCam(0);

    cv::Mat image;
    cv::Mat imageDownScaled;
    cv::Mat imageGrayScale;
    cv::Mat imageBlackAndWhite;
    
    
    int pixelColour;
    std::string character;
    
    cv::Size size(1000, 512);
    cv::Scalar colour(0, 0, 0);
    
    int spacing = 10;
    
    
    cv::Point textLocation;
    cv::Scalar textColour;
    
    
    while (true) {
        cv::Mat ASCIIImage(size, CV_8UC3, colour);
        
        webCam.read(image);
        cv::resize(image, imageDownScaled, cv::Size(89, 40), cv::INTER_LINEAR);
        cv::cvtColor(imageDownScaled, imageGrayScale, cv::COLOR_BGR2GRAY);
        
        for (int i = 0; i < imageGrayScale.rows; i++) {
            
            for (int j = 0; j < imageGrayScale.cols; j++) {
                
                pixelColour = imageGrayScale.at<uchar>(i,j);
             
                if (pixelColour < 64) {
                    
                    character = ".";
                    
                } else if (pixelColour >= 64 && pixelColour < 128) {
                    
                    character = "*";
                    
                } else if (pixelColour >= 128 && pixelColour < 192) {
                    
                    character = "x";
                    
                } else if (pixelColour >= 192 && pixelColour < 256) {
                    character = "#";
                }
                
                
                textLocation.x = j * spacing;
                textLocation.y = i * spacing * 1.5;
                
                textColour[0] = 255;
                textColour[1] = 255;
                textColour[2] = 255;
                
                cv::putText(ASCIIImage, character, textLocation, cv::FONT_HERSHEY_PLAIN, 1, textColour, 1);
                
            }
        }
        cv::imshow("ASCII feed", ASCIIImage);
        cv::waitKey(1);
    }

    //cv::imshow("Image", imageGrayScale);

    
    
    return 0;
}
