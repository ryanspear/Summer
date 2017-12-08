//
//  outputCreator.hpp
//  pleaseWork
//
//  Created by Ryan Spear on 12/8/17.
//  Copyright © 2017 Ryan Spear. All rights reserved.
//

#ifndef outputCreator_hpp
#define outputCreator_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <ctime>

uchar randomPixelGrey();
uchar seedPixelGrey(int seed);
cv::Vec3b randomPixelColour();
cv::Vec3b seedPixelColour(int seed);
void colourOutput(int (&arr)[M][N], cv::Mat img);
void greyOutput(int (&arr)[M][N], cv::Mat img);


#endif /* outputCreator_hpp */
