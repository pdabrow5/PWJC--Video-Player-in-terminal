#include "IFrameScaler.hpp"

//OpenCV
#include <opencv2/imgproc.hpp>

#include <iostream>

namespace img_lib
{

IFrameScaler::IFrameScaler(unsigned int width, unsigned int heigth, float charRatio): _width(width), _heigth(heigth), _charRatio(charRatio) {}

MatPtr SimpleFrameScaler::operator()(const cv::Mat& img, bool toGrayscale) const
{
    static const float window_ratio = (float)_heigth / (float)_width;
    float oldCols = img.cols; float oldRows = img.rows;
    MatPtr ret = std::make_unique<cv::Mat>();
    float newCols; float newRows;
    oldCols = oldCols * _charRatio;
    float frame_ratio = oldRows / oldCols;
    if(frame_ratio < window_ratio)
    {
        newCols = _width;
        newRows = (float)_width * frame_ratio;
    }else
    {
        newRows = _heigth;
        newCols = (float)_heigth / frame_ratio;
    }
    cv::resize(img, *ret, cv::Size(newCols, newRows), 0, 0, cv::INTER_LINEAR);
    if(toGrayscale && img.channels() == 3)
    {
        MatPtr grayRet = std::make_unique<cv::Mat>();
        cv::cvtColor(*ret, *grayRet, cv::COLOR_BGR2GRAY);
        return grayRet;
    }
    return ret;
}

} //namespace img_lib