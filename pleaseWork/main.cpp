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
    Mat left = imread("left.jpg");
    Mat right = imread("right.jpg");
    int bucketSize = 4;
    
    autoStereo gram(left, right, bucketSize);
    
    gram.fillNumberMatrix(left, right, bucketSize, gram.getNumberMatrix(), gram.getHeight());
    
    gram.produceOutput(gram.getNumberMatrix(), gram.getOutput(), gram.getNumMatIndex(), gram.getHeight());
    
    
    
}





