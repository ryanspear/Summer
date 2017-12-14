//
//  autoStereo.hpp
//  pleaseWork
//
//  Created by Ryan Spear on 12/12/17.
//  Copyright © 2017 Ryan Spear. All rights reserved.
//

#ifndef autoStereo_hpp
#define autoStereo_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace std;
using namespace cv;

class autoStereo
{
public:
    autoStereo(Mat left, Mat right, int bucketSize);
    
    int* fillNumberMatrix(Mat left, Mat right, int bucketSize, int* numberMatrix, int height);
    
    Mat produceOutput(int *numberMatrix, Mat output, int numMatIndex, int height);
    
    void showOutput(Mat output, Mat left, Mat right);
    int getWidth();
    int* getNumberMatrix();
    Mat getOutput();
    int getNumMatIndex();
    
private:
    Mat left;
    Mat right;
    Mat output;
    int width;
    int height;
    int *numberMatrix;
    int numMatIndex;
    int numMatCurrent;
};

#endif /* autoStereo_hpp */
