# Soundboard
I didn't find any good soundboard application for linux so I created one. It uses pulseaudio modules to achieve a universal interface. You can select every recording stream for the audio output. The GUI is written with Qt.

It is currently in alpha because I don't know if this works for everyone.

## Dependencies
Please refer your distro instructions for how to install them
- [pulseaudio](https://www.archlinux.org/packages/extra/x86_64/pulseaudio/)
- [mpeg123](https://www.archlinux.org/packages/extra/x86_64/mpg123/) (for playing mp3 files)

# Compile it yourself
```sh
git clone https://github.com/D3S0X/Soundboard.git
cd Soundboard
cmake .
make
./Soundboard
```

# TODO
- Find a fancy name
- Save configuration in .config folder instead of in the same folder as the binary
- Play sounds async
- Implement stop feature
- Double click items to play
