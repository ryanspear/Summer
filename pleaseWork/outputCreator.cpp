//
//  outputCreator.cpp
//  pleaseWork
//
//  Created by Ryan Spear on 12/8/17.
//  Copyright © 2017 Ryan Spear. All rights reserved.
//

#include "outputCreator.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <ctime>

class outputCreator{
    
    
    
    uchar randomPixelGrey(){
        srand(time(NULL));
        uchar gPixel = rand() % 256;
        return gPixel;
    }
    
    uchar seedPixelGrey(int seed){
        srand(seed);
        uchar gPixel = rand() % 256;
        return gPixel;
    }
    
    cv::Vec3b randomPixelColour(){
        srand(time(NULL));
        cv::Vec3b rPixel;
        int B = rand() % 256;
        int G = rand() % 256;
        int R = rand() % 256;
        
        rPixel = {static_cast<unsigned char>(B), static_cast<unsigned char>(G), static_cast<unsigned char>(R)};
        return rPixel;
    }
    
    cv::Vec3b seedPixelColour(int seed){
        srand(seed);
        cv::Vec3b rPixel;
        int B = rand() % 256;
        int G = rand() % 256;
        int R = rand() % 256;
        
        rPixel = {static_cast<unsigned char>(B), static_cast<unsigned char>(G), static_cast<unsigned char>(R)};
        return rPixel;
    }
    
    template <size_t N, size_t M>
    void colourOutput(int (&arr)[M][N], cv::Mat img){
        cv::Mat output = cv::Mat::zeros(img.size(), CV_8UC3);
        
        for(int rows = 0; rows < arr.size(); rows++){
            for(int cols = 0; cols < arr[rows].size(); cols++){
                if(arr[rows][cols] == 0){
                    output.at<cv::Vec3b>(rows,cols) = randomPixelColour();
                } else {
                    output.at<cv::Vec3b>(rows,cols) = seedPixelColour(arr[rows][cols]); // same seed gives same pixel.
                }
            }
        }
        cv::namedWindow("Output", CV_WINDOW_AUTOSIZE);
        cv::imshow("Output", output);
    }
    
    template <size_t N, size_t M>
    void greyOutput(int (&arr)[M][N], cv::Mat img){
        cv::Mat output = cv::Mat::zeros(img.size(), CV_8UC1);
        
        for(int rows = 0; rows < arr.size(); rows++){
            for(int cols = 0; cols < arr[rows].size(); cols++){
                if(arr[rows][cols] == 0){
                    output.at<uchar>(rows,cols) = randomPixelGrey();
                } else {
                    output.at<uchar>(rows,cols) = seedPixelGrey(arr[rows][cols]); // same seed gives same pixel.
                }
            }
        }
        cv::namedWindow("Output", CV_WINDOW_AUTOSIZE);
        cv::imshow("Output", output);
    }
};
