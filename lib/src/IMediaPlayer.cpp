#include "IMediaPlayer.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>

#include <chrono>
#include <iostream>

namespace img_lib
{


MediaPlayer::MediaPlayer(size_t width, size_t heigth, float char_ratio)
{
    _width = width;
    _heigth = heigth;
    _colorMode = MediaColor::GRAYSCALE;
    _state = PlayerState::PAUSED;
    _buffer = "";
    _helperBuffer = "";
    _frameScaler = std::make_unique<SimpleFrameScaler>(width, heigth, char_ratio);
    _frameConverter = std::make_unique<GrayscaleFrameConverter>();

}

MediaPlayer::~MediaPlayer()
{
    if(_playingThread.has_value())
    {
        _playingThread->join();
    }
}
bool MediaPlayer::LoadMedia(const std::string& filename)
{
    bool ret;
    if(filename.find(".avi") != std::string::npos ||
        filename.find(".mp4") != std::string::npos)
    {
        ret = LoadVideo(filename);
    }else
    {
        ret = LoadImage(filename);
    }

    if(ret == false)
    {
        std::cout << "Loading file: " << filename << "failed!" << std::endl;
    }
    return ret;
}

bool MediaPlayer::PrintFrame(MediaColor colorMode)
{
    if(IsDataLoaded() == false) return false;
    SetMode(colorMode);
    LoadIntoBuffer(_buffer);
    PrintBuffer();
    return true;
}

bool MediaPlayer::NextFrame()
{
    StreamIterator nextFrame = _currentFrame.value();
    if(++nextFrame != _framesStream->end())
    {
        _currentFrame.value()++;
        return true;
    }
    return false;
}

bool MediaPlayer::PreviousFrame()
{
    auto nextFrame = _currentFrame.value();
    if(--nextFrame != _framesStream->begin())
    {
        _currentFrame.value()--;
        return true;
    }
    return false;
}

bool MediaPlayer::Play(bool forward, MediaColor colorMode)
{
    if(_state == PlayerState::PAUSED){
    std::chrono::milliseconds _frameTime(40); //should be done differently
    if(IsDataLoaded() == false) return false;
    SetMode(colorMode);
    LoadIntoBuffer(_buffer);
    _state = PlayerState::PLAYING;
    while(_state == PlayerState::PLAYING &&
        (forward ? NextFrame() : PreviousFrame()))
    {
        std::thread printer([this]{PrintBuffer();});
        std::thread converter([this]{LoadIntoBuffer(_helperBuffer);});
        std::this_thread::sleep_for(_frameTime);
        converter.join();
        _buffer.swap(_helperBuffer);
        printer.join();
    }
    _state = PlayerState::PAUSED;
    return true;
    }
    return false;
}

void MediaPlayer::PlayAsync(bool forward, MediaColor colorMode)
{
    if(_state == PlayerState::PAUSED)
        _playingThread = std::thread([this, forward, colorMode]{Play(forward, colorMode);});
}

void MediaPlayer::StopAsync()
{
    if(_state == PlayerState::PLAYING && _playingThread.has_value()){
        _state = PlayerState::PAUSED;
        _playingThread->join();
        _playingThread.reset();
    }
}

void MediaPlayer::SetMode(MediaColor colorMode)
{
    _colorMode = colorMode;
    if(_colorMode == MediaColor::GRAYSCALE)
        _frameConverter = std::make_unique<GrayscaleFrameConverter>();
    else
        _frameConverter = std::make_unique<ColorFrameConverter>();
}

bool MediaPlayer::IsDataLoaded()
{
    if(!_framesStream || !_currentFrame) return false; // check if data is loaded
    if(_currentFrame.value() == _framesStream->end()) return false; // check if iterator is valid
    return true;
}

bool MediaPlayer::LoadImage(const std::string& filename)
{
    cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    if(img.empty()) return false;
    _framesStream = std::make_optional<FramesStream>();
    _framesStream->push_back(std::move(img));
    _currentFrame = _framesStream->begin();
    return true;
}

bool MediaPlayer::LoadVideo(const std::string& filename)
{
    static cv::VideoCapture capture;
    static cv::Mat frame;
    capture.open(filename);
    if(capture.isOpened() == false) return false;
    _framesStream = std::make_optional<FramesStream>();
    int i = 0;
    while(true)
    {
        capture >> frame;
        if(frame.empty()) break;
        _framesStream->push_back(std::move(frame));
        std::cout << i++ << std::endl;
    }
    _currentFrame = _framesStream->begin();
    return true;
}

bool MediaPlayer::LoadIntoBuffer(std::string& buffer)
{
    if(IsDataLoaded() == false) return false;
    auto scaled_frame = (*_frameScaler)(*(_currentFrame.value()), _colorMode == MediaColor::GRAYSCALE);
    _frameConverter->ConvertFrame(*scaled_frame, buffer);
    return true;

}

void MediaPlayer::ResetCursor()
{
    printf("\033[%d;%dH", 1, 1);
}
void MediaPlayer::PrintBuffer()
{
    ResetCursor();
    std::cout << _buffer;
}
}