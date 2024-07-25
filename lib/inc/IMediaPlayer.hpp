#ifndef INC_IMEDIAPLAYER_HPP
#define INC_IMEDIAPLAYER_HPP

#include "IFrameConverter.hpp"
#include "IFrameScaler.hpp"

#include <atomic>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <thread>
#include <optional>

namespace img_lib
{

class MediaPlayer
{
public:
    enum class MediaColor
    {
        BGR,
        GRAYSCALE
    };
    MediaPlayer(size_t width, size_t heigth, float char_ratio);
    ~MediaPlayer();
    bool LoadMedia(const std::string& filename);
    bool PrintFrame(MediaColor colorMode = MediaColor::GRAYSCALE);
    bool NextFrame();
    bool PreviousFrame();
    bool Play(bool forward = true, MediaColor colorMode = MediaColor::GRAYSCALE);
    void PlayAsync(bool forward = true, MediaColor colorMode = MediaColor::GRAYSCALE);
    void StopAsync();
    void SetMode(MediaColor colorMode);
    bool IsDataLoaded();

private:
    enum class PlayerState{
        PAUSED,
        PLAYING
    };
    using FramesStream = std::list<cv::Mat>;
    using StreamIterator = FramesStream::iterator;
    bool LoadImage(const std::string& filename);
    bool LoadVideo(const std::string& filename);
    bool LoadIntoBuffer(std::string& buffer);
    void ResetCursor();
    void PrintBuffer();
    size_t _width;
    size_t _heigth;
    MediaColor _colorMode;
    std::atomic<PlayerState> _state;
    std::optional<std::thread> _playingThread;
    std::string _buffer;
    std::string _helperBuffer;
    std::unique_ptr<IFrameScaler> _frameScaler;
    std::unique_ptr<IFrameConverter> _frameConverter;
    std::optional<FramesStream> _framesStream;
    std::optional<StreamIterator> _currentFrame;
};



} //namespace img_lib
#endif //INC_IMEDIAPLAYER_HPP