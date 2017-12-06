//
//  main.cpp
//  pleaseWork
//
//  Created by Ryan Spear on 12/3/17.
//  Copyright © 2017 Ryan Spear. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Vec3b randomPixel(){
    Vec3b rPixel;
    int B = rand() % 256;
    int G = rand() % 256;
    int R = rand() % 256;
    
    rPixel = {static_cast<unsigned char>(B), static_cast<unsigned char>(G), static_cast<unsigned char>(R)};
    return rPixel;
}

/* creates an output image comparing pixels in the right image to the left image.
 if any the pixels in a row the size of eye width from the left image are the same(ish),
 that colour will be used in those positions in the output image.
 */
int main(int argv, char** argc) {
    int count = 0; // tracks how many times a pixel in the right is the same as the left.
    double eyeWidth = 4.5*37.795276; // how many pixels the typical eyes are apart
    Vec3b defaultPix = {220, 100, 50};
    
    
    Mat left = imread("carLeft.jpg" , CV_LOAD_IMAGE_UNCHANGED);
    Mat right = imread("carRight.jpg" , CV_LOAD_IMAGE_UNCHANGED);
    Mat output = Mat::zeros(left.size(), CV_8UC3); // fills an empty output with black pixels
    
    if (left.empty() || right.empty()){
        cout << "image(s) failed to load"; // if images aren't in the folder or named wrong
    }
    
    /* for loops iterating though ever pixel and getting the RGB values. */
    for(int rows = 0; rows < left.rows; rows++){
        bool visited[left.cols];
        for(int y = 0; y < left.cols; y++){
            visited[y] = 0;
        }
        for(int cols = 0; cols < left.cols; cols++){
            Vec3b leftIntensity = left.at<Vec3b>(rows,cols);
            float B = leftIntensity.val[0]/10; // blue, green & red values
            float G = leftIntensity.val[1]/10; // divided by 10 so colour doesn't have to be exactly the same
            float R = leftIntensity.val[2]/10; // just close enough
            int i = cols;
            
            /* goes along the row until eye width apart comparing each pixel in the right image to the original pixel in the left image */
            while(i < cols + eyeWidth && i < left.cols){
                Vec3b rightIntensity = right.at<Vec3b>(rows,i);
                float Bcompare = (rightIntensity.val[0])/10;
                float Gcompare = (rightIntensity.val[1])/10;
                float Rcompare = (rightIntensity.val[2])/10;
                
                if(B == Bcompare && G == Gcompare && R == Rcompare && !visited[i]){ // if they're close enough (divided by 10)
                    Vec3b samePix = randomPixel();
                    count++;
                    output.at<Vec3b>(rows,i) = samePix;
                    output.at<Vec3b>(rows,cols) = samePix; // left and right eye positions the same random colour.
                    visited[i] = true;
                } else if(!visited[i]){
                    output.at<Vec3b>(rows,i) = randomPixel(); // if they're not the same make it a random colour
                }
                i++;
            }
        }
    }
    /* Deals with showing the images and their position on the monitor */
    cout << "Count: " << count;
    namedWindow("Output", WINDOW_AUTOSIZE);
    moveWindow("Output", 850, 100);
    namedWindow("Left", WINDOW_AUTOSIZE);
    moveWindow("Left", 50, 100);
    namedWindow("Right", WINDOW_AUTOSIZE);
    moveWindow("Right", 500, 500);
    imshow("Left", left);
    imshow("Right", right);
    imshow("Output", output);
    waitKey(0);
    
    
}




