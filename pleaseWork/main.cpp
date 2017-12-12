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
#include <ctime>

using namespace cv;
using namespace std;

void seed()
{
    srand(time(0));
}

uchar randomPixelGrey(){
    uchar gPixel = rand() % 256;
    return gPixel;
}
/* returns a psudo-random pixel based on time */
Vec3b randomPixelColour(){
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
    /* timing the program */
    std::clock_t start;
    double duration;
    start = std::clock();
    
    int bucketSize = 3;
    int count = 0; // tracks how many times a pixel in the right is the same as the left.
    double eyeWidth = 241; // how many pixels the typical eyes are apart
    
    Mat left = imread("FountainLeft.jpg" , CV_LOAD_IMAGE_UNCHANGED);
    Mat right = imread("FountainRight.jpg" , CV_LOAD_IMAGE_UNCHANGED);
    Mat output = Mat::zeros(left.size(), CV_8UC1); // fills an empty output with black pixels
    int numberMatrix[output.rows][output.cols]; // holds number representation of pixels that should be same colour
    for(int i = 0; i < output.rows; i++){
        for(int j = 0; j < output.cols; j++){
            numberMatrix[i][j] = 0;
        }
    }
    int numMatIndex = 0; // gives a new number to pixels that are a new colour
    int numMatCurrent = numMatIndex; // current number value of the left pixel
    
    if (left.empty() || right.empty()){
        cout << "image(s) failed to load"; // if images aren't in the folder or named wrong
    }
    
    /* for loops iterating though every pixel and getting the RGB values. */
    for(int rows = 0; rows < output.rows; rows++){
        //numMatIndex = 0;
        for(int cols = 0; cols < output.cols; cols++){
            
            Vec3b leftIntensity = left.at<Vec3b>(rows,cols);
            float B = leftIntensity.val[0]/bucketSize; // blue, green & red values
            float G = leftIntensity.val[1]/bucketSize; // divided by 5 so colour doesn't have to be exactly the same
            float R = leftIntensity.val[2]/bucketSize; // just close enough
            int i = cols; // images start in same position
            
            /* deals with left pixel value. if not 0, keep using that value, otherwise give it a new value */
            if(numberMatrix[rows][cols] != 0){
                numMatCurrent = numberMatrix[rows][cols]; // current value is now this existing value
            } else {
                numMatIndex++; // if it is 0 the colour hasn't been seen yet, so give it a new colour value.
                numMatCurrent = numMatIndex; // the current colour is now this new value
                numberMatrix[rows][cols] = numMatCurrent;
            }
            /* goes along the row until eye width apart comparing each pixel in the right image to the original pixel in the left image */
            while(i < cols + eyeWidth && i < right.cols){
                Vec3b rightIntensity = right.at<Vec3b>(rows,i);
                float Bcompare = (rightIntensity.val[0])/bucketSize;
                float Gcompare = (rightIntensity.val[1])/bucketSize;
                float Rcompare = (rightIntensity.val[2])/bucketSize;
                
                
                if(B == Bcompare && G == Gcompare && R == Rcompare){ // if the pixels are the same(ish)
                    /* if pixel hasn't been given a value yet then give it the current value.
                     if pixel has a value that is different, replace every pixel with that value (including the current pixel) with the current value */
                    count++;
                    if(numberMatrix[rows][i] == 0){
                        numberMatrix[rows][i] = numMatCurrent;
                    } else {
                        if(numberMatrix[rows][i] != numMatCurrent){
                            int change = numberMatrix[rows][i];
                            for(int j = 0; j < output.cols; j++){
                                if(numberMatrix[rows][j] == change){
                                    numberMatrix[rows][j] = numMatCurrent;
                                }
                            }
                        }
                    }
                }
                
                i++;
            }
        }
    }
    uchar colour[numMatIndex]; //an array of colours
    bool colourCheck[numMatIndex]; //array checks whether a number has been given a colour yet
    int colourIndex = 0; //current assigned value being dealt with
    
    /* look at every item in the numbered matrix, every pixel with the same number gets given same grey/colour pixel
     if the number is 0 it is given a random greyscale/colour pixel */
    seed();
    for(int rows = 0; rows < output.rows-1; rows++){
        for(int cols = 0; cols < output.cols-1; cols++){
            if(numberMatrix[rows][cols] == 0){
                output.at<Vec3b>(rows,cols) = randomPixelGrey(); //give pixel random colour
            } else {
                colourIndex = numberMatrix[rows][cols];
                if (!colourCheck[colourIndex]) { //if the number hasn't been assigned a colour yet
                    colour[colourIndex] = randomPixelGrey(); // assign it a colour
                    colourCheck[colourIndex] = true; // track that it has been given a colour
                }
                output.at<uchar>(rows,cols) = colour[colourIndex]; // output pixel gets that colour
            }
                
            }
        }
    
    
    
    
     /*end timer */
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<< "Took: " << duration << " seconds to process " << count << " identical pairs of pixels";
    
    /* Deals with showing the images and their position on the monitor */
    namedWindow("Output", WINDOW_FREERATIO);
    moveWindow("Output", 850, 100);
    namedWindow("Left", WINDOW_AUTOSIZE);
    moveWindow("Left", 50, 100);
    namedWindow("Right", WINDOW_AUTOSIZE);
    moveWindow("Right", 500, 500);
    imshow("Left", left);
    imshow("Right", right);
    imshow("Output", output);
    //imwrite("Autostereo.jpg", output);
    waitKey(0);
    
    
}





