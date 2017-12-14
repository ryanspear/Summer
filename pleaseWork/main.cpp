//
//  main.cpp
//  pleaseWork
//
//  Created by Ryan Spear on 12/3/17.
//  Copyright © 2017 Ryan Spear. All rights reserved.
//

#include "autoStereo.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace cv;
using namespace std;


int main(int argv, char** argc) {
 
    Mat left = imread("faceLeft.jpg");
    Mat right = imread("faceRight.jpg");
    int bucketSize = 2;

    autoStereo gram(left, right, bucketSize);

    gram.fillNumberMatrix(left, right, bucketSize, gram.getNumberMatrix(), gram.getWidth());

    gram.produceOutput(gram.getNumberMatrix(), gram.getOutput(), gram.getNumMatIndex(), gram.getWidth());

    gram.showOutput(gram.getOutput(), left, right);
    
}





