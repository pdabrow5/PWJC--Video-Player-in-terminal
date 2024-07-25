#ifndef INC_IFRAMECONVERTER_HPP
#define INC_IFRAMECONVERTER_HPP

#include <functional>
#include <string>
#include <thread>

#include <opencv2/core/mat.hpp>

namespace img_lib
{

class IFrameConverter
{
public:
    virtual void ConvertFrame(const cv::Mat& img, std::string& buffer) const = 0;
    virtual ~IFrameConverter() = default;
private:
    virtual void ConvertFromTo(cv::MatConstIterator_<uchar> src_begin, cv::MatConstIterator_<uchar> src_end,
        std::string::iterator dst_begin, std::string::iterator dst_end) const = 0;

};


//TODO in future
class ColorFrameConverter : public IFrameConverter
{
public:
    using func_type = std::function<void (std::string::iterator& i, unsigned char B, unsigned char G, unsigned char R)>;
    ColorFrameConverter(func_type func = BasicConvertPixelFunc) : _convertPixelFunc(func) {}
    ~ColorFrameConverter() = default;
    void ConvertFrame(const cv::Mat& img, std::string& buffer) const override {}; //TODO
    static void BasicConvertPixelFunc(std::string::iterator& i, unsigned char B, unsigned char G, unsigned char R){};
private:
    void ConvertFromTo(cv::MatConstIterator_<uchar> src_begin, cv::MatConstIterator_<uchar> src_end,
        std::string::iterator dst_begin, std::string::iterator dst_end) const override {}; //TODO

    const func_type _convertPixelFunc;
};

class GrayscaleFrameConverter : public IFrameConverter
{
public:
    using func_type = std::function<void (std::string::iterator& i, unsigned char C)>;
    GrayscaleFrameConverter(func_type func = BasicConvertPixelFunc) : _convertPixelFunc(func) {}
    ~GrayscaleFrameConverter() = default;
    void ConvertFrame(const cv::Mat& img, std::string& buffer) const override;
    static void BasicConvertPixelFunc(std::string::iterator& i, unsigned char C);
private:
    void ConvertFromTo(cv::MatConstIterator_<uchar> src_begin, cv::MatConstIterator_<uchar> src_end,
        std::string::iterator dst_begin, std::string::iterator dst_end) const override;

    const func_type _convertPixelFunc;
};

}

#endif //INC_IFRAMECONVERTER_HPP