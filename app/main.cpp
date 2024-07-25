#include "IMediaPlayer.hpp"

#include <chrono>
#include <iostream>
#include <string>

void Foo(const std::string& filename)
{
    std::chrono::milliseconds time(3000);
    img_lib::MediaPlayer player{900, 180, 2.2f};
    player.LoadMedia(filename);
    player.PrintFrame();
    player.PlayAsync();
    std::cout << "SLEEP1 " << std::time(0) << std::endl;
    std::this_thread::sleep_for(time);
    player.StopAsync();
    std::cout << "SLEEP2 " << std::time(0) << std::endl;
    std::this_thread::sleep_for(time);
    player.PlayAsync(false);
    std::cout << "SLEEP3 " << std::time(0) << std::endl;
    std::this_thread::sleep_for(time);
    std::cout << "AFTER " << std::time(0) << std::endl;
    std::this_thread::sleep_for(time);
    player.Play();
}

int main(int argc, char *argv[])
{
    /*
    printf("\033[0;30m@");
    printf("\033[0;31m@");
    printf("\033[0;32m@");
    printf("\033[0;33m@");
    printf("\033[0;34m@");
    printf("\033[0;35m@");
    printf("\033[0;36m@");
    printf("\033[0;37m@");
    printf("\n");
    printf("\033[1;30m@");
    printf("\033[1;31m@");
    printf("\033[1;32m@");
    printf("\033[1;33m@");
    printf("\033[1;34m@");
    printf("\033[1;35m@");
    printf("\033[1;36m@");
    printf("\033[1;37m@");
    printf("\n");
    printf("\033[2;30m@");
    printf("\033[2;31m@");
    printf("\033[2;32m@");
    printf("\033[2;33m@");
    printf("\033[2;34m@");
    printf("\033[2;35m@");
    printf("\033[2;36m@");
    printf("\033[2;37m@\n\033[0m");
    printf("\n");
    printf("\033[3;30m@");
    printf("\033[3;31m@");
    printf("\033[3;32m@");
    printf("\033[4;33m@");
    printf("\033[5;34m@");
    printf("\033[6;35m@");
    printf("\033[7;36m@");
    printf("\033[8;37m@\n\033[0m");


    printf("\x1B[32mTexting\033[0m\t\t");
    printf("\x1B[33mTexting\033[0m\t\t");
    printf("\x1B[34mTexting\033[0m\t\t");
    printf("\x1B[35mTexting\033[0m\n");
    */
    std::string filename{argv[1]};
    Foo(filename);
    std::cout << "end of main\n";
    return 0;
}