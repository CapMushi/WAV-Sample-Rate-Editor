WAV Sample Rate Editor Description: 
This repository contains C++ programs for editing WAV (Waveform Audio File Format) files. The programs allow various operations such as modifying the sample rate, applying filters, combining audio files, and more.

Features:
1. Up-Sampling and Down-Sampling
2. Up-Sampling: Doubles the sample rate of a WAV file.
3. Down-Sampling: Reduces the sample rate of a WAV file.
4. Moving Average Filter
5. Applies a moving average filter to smooth out the audio signal.
6. Merge Audio Files
7. Combines two WAV files into one, generating two versions with different sample rates.
8. File Playback
8. Plays a specified WAV file using the default system audio player.

Prerequisites:
Operating System: Windows
Development Environment: Visual Studio or any C++ compiler with Windows SDK

INSTRUCTIONS
1. Clone the Repository
   git clone https://github.com/CapMushi/WAV-Sample-Rate-Editor.git
2. Compile and Build
   Open the project in your C++ development environment.
   Add the source files (Sound.cpp and wavfile.cpp) and iclude the header file (wavfile.h)
   Build the project to generate the executable.
3. Run the Program
   Execute the compiled executable.
   Enter the wav file name in the format name.wav example dhani.wav
   A menu will be diplayed choose accordingly.

Make sure the wav files you want to manipulate are in the same directory as the project.

Contributions are welcome! Feel free to fork the repository, create pull requests, or open issues for suggestions and bug reports.
