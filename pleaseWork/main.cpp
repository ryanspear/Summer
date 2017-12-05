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

/* creates an output image comparing pixels in the right image to the left image.
 if any the pixels in a row the size of eye width from the left image are the same(ish),
 that colour will be used in those positions in the output image.
 */
int main(int argv, char** argc) {
    int count = 0; // tracks how many times a pixel in the right is the same as the left.
    double eyeWidth = 4.5*37.795276; // how many pixels the typical eyes are apart
    Mat left = imread("houseLeft.jpg" , CV_LOAD_IMAGE_UNCHANGED);
    Mat right = imread("houseRight.jpg" , CV_LOAD_IMAGE_UNCHANGED);
    Mat output = Mat::zeros(left.size(), CV_8UC3); // fills an empty output with black pixels
    
    if (left.empty() || right.empty()){
        cout << "image(s) failed to load"; // if images aren't in the folder or named wrong
    }
    
    /* for loops iterating though ever pixel and getting the RGB values. */
    for(int rows = 0; rows < left.rows; rows++){
        for(int cols = 0; cols < left.cols; cols++){
            Vec3b leftIntensity = left.at<Vec3b>(rows,cols);
            float B = leftIntensity.val[0]/10; // blue, green & red values
            float G = leftIntensity.val[1]/10; // divided by 10 so colour doesn't have to be exactly the same
            float R = leftIntensity.val[2]/10; // just close enough
            int i = cols;
            
            /* goes along the row until eye width apart comparing each pixel in the right image to the original pixel in the left image */
            while(i < cols + eyeWidth){
                Vec3b rightIntensity = right.at<Vec3b>(rows,i);
                float Bcompare = (rightIntensity.val[0])/10;
                float Gcompare = (rightIntensity.val[1])/10;
                float Rcompare = (rightIntensity.val[2])/10;
                
                if(B == Bcompare && G == Gcompare && R == Rcompare){ // if they're close enough (divided by 10)
                    count++;
                    output.at<Vec3b>(rows,i) = leftIntensity; // output pixel same colour as left pixel
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

