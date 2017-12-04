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


int main(int argv, char** argc) {
    double eyeWidth = 4.5*37.795276;
    Mat left = imread("left.jpg" , CV_LOAD_IMAGE_UNCHANGED);
    Mat right = imread("right.jpg" , CV_LOAD_IMAGE_UNCHANGED);
    Mat output = Mat::zeros(left.size(), CV_8UC1);
    if (left.empty() || right.empty()){
        cout << "image(s) failed to load";
    }
    
    
    /*for(int i = 0; i < 3; i++){
        cout << (left.at<Vec3b>(10,5)[i])/10;
        cout << "\n";
        
    }
    */
    
    for(int rows = 0; rows < left.rows; rows++){
        for(int cols = 0; cols < left.cols; cols++){
            Vec3b leftIntensity = left.at<Vec3b>(rows,cols);
            float B = leftIntensity.val[0];
            float G = leftIntensity.val[1];
            float R = leftIntensity.val[2];
            int i = cols;
            
            while(i < cols + eyeWidth){
                Vec3b rightIntensity = right.at<Vec3b>(rows,i);
                float Bcompare = rightIntensity.val[0];
                float Gcompare = rightIntensity.val[1];
                float Rcompare = rightIntensity.val[2];
                cout << Bcompare;
                cout << "\n";
                if((B/10) == Bcompare && (G/10) == Gcompare && (R/10) == Rcompare){
                    uchar pixel[3] = {B,G,R};
                    output.at<uchar>(rows,i) = pixel;
                    cout << output.at<Vec3b>(rows,i);
                }
                
                i++;
            }
            
            
        }
    }


namedWindow("output", WINDOW_AUTOSIZE);
imshow("output", output);
waitKey(0);


}

