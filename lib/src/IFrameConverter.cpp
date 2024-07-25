#include "IFrameConverter.hpp"

#include <vector>
#include <iostream>

namespace img_lib
{

void GrayscaleFrameConverter::ConvertFrame(const cv::Mat& img, std::string& buffer) const
{
    size_t row_len = img.cols;
    size_t col_len = img.rows;
    size_t req_space = col_len * (row_len + 1); //+1 for \n char
    if(buffer.size() < req_space)
    {
        buffer.resize(req_space);
    }
    auto row_begin = img.begin<uchar>();
    auto row_end = img.begin<uchar>() + row_len;
    auto b_begin = buffer.begin();
    auto b_end = b_begin + row_len;
    for(size_t r = 0; r < col_len; ++r)
    {
        ConvertFromTo(row_begin, row_end, b_begin, buffer.end());
        *b_end++ = '\n';
        row_begin += row_len;
        row_end += row_len;
        b_begin = b_end;
        b_end += row_len;
    }
}

void GrayscaleFrameConverter::BasicConvertPixelFunc(std::string::iterator &i, unsigned char C)
{
    static const std::vector<char> map = {' ', ':', ';', '!', '{', '(', 'X', '%', '0', 'H', '@', 'N'};
    static const float step = 256.0f / ((float)map.size());
    size_t n = ((float)(C) / step);
    *i = map[n];

}

void GrayscaleFrameConverter::ConvertFromTo(cv::MatConstIterator_<uchar> src_begin, cv::MatConstIterator_<uchar> src_end,
        std::string::iterator dst_begin, std::string::iterator dst_end) const
{
    for(; src_begin != src_end && dst_begin != dst_end; ++src_begin, ++dst_begin)
    {
        _convertPixelFunc(dst_begin, *src_begin);
    }
}

}