#ifndef INC_IFRAMESCALER_HPP
#define INC_IFRAMESCALER_HPP

//opencv
#include <opencv2/core/mat.hpp>

//std
#include <memory>

namespace img_lib
{
using MatPtr = std::unique_ptr<cv::Mat>;

/// @brief Class (Functor, Command) used for reducing image size+
class IFrameScaler
{
public:
    explicit IFrameScaler(unsigned int width, unsigned int heigth, float charRatio = 1.0f);
    virtual ~IFrameScaler() = default;
    /// @brief Method used to reduce image size by combining rectangle of pixels into one
    /// @param img image to be reduced
    /// @return image reduced in dimensions so, bigger of them is equal to size
    virtual MatPtr operator()(const cv::Mat& img, bool toGrayscale = true) const = 0;
protected:
    /// @brief Defines maximum size of product
    const unsigned int _width;
    const unsigned int _heigth;

    /// @brief Describes heigth to width ratio of displayed ASCII char [terminal dependent]
    const float _charRatio;
};

/// @brief Class uses OpenCV api to reduce image size
class SimpleFrameScaler : public IFrameScaler
{
    using IFrameScaler::IFrameScaler;
public:
    virtual MatPtr operator()(const cv::Mat& img, bool toGrayscale = true) const override;
};

} //namespace img_lib
#endif //INC_IFRAMESCALER_HPP