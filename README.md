# PWJC_2023Z_G

## Brief
Repozytorium zawierające projekt zespołowy realizowany w ramach przedmiotu PWJC 2023Z.

Tematem projektu jest stworzenie odtwarzacza zdjęć (oraz video - jeśli będzie to możliwe) w terminalu.
Odtwarzacz ma za zadanie konwertować zdjęcia/klatki filmu do tablic znaków kodu ASCII, następnie wyświetlać je w postaci standardowego wyjścia terminala.

## Wymagania

Aplikacja powinna być wieloplatformowa, uruchamiać się zarówno na systemach rodziny Unix, jak i Windows.

- Dokumentacja aplikacji zostanie napisana przy pomocy narzędzia Doxygen
- Standard C++20
- Framework testów jednostkowych:


## Konfiguracja
Aby zbudować projekt należy posiadać:
- Kompilator kompatybilny z c++20
- Cmake
- OpenCV (https://www.geeksforgeeks.org/how-to-install-opencv-in-c-on-linux/)

## Biblioteka
Z założenia, stworzona biblioteka ma konwertować (wyświetlać) zdjęcia przu pomocy standardowego wyścia 
(w terminalu). Aby tego dokonać, należy grafikę analizować piksel po pikselu oraz znaleźć znak ASCII najlepiej odpowiadający danemu fragmentowi obazu. W tym celu mogą zostać użyty poniżej zamieszczony zestaw:\

![plot](example_pixels.png)

