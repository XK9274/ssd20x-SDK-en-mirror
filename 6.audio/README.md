# Summary

- Audio related DMEO

## ai_ao_ini

- If the ini file does not exist, it will be created by default. After running the demo, the parameters inside the ini will be automatically loaded to set AI and AO.
- SSD202 - SDK verification for v030 version
- Mainly use MI’s AI and AO interfaces
- **When running the demo, an ini file will be created in the running path. You need to ensure that the currently running folder has write permissions. Otherwise, the operation may fail**
- [Details](./ai_ao_ini/README.md);

## mp3_player

- Original simple MP3 player <https://gitee.com/mFlying/RunTimeDemo/tree/master/MultiPlayer/mp3player>
- run

```shell
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
./Mp3Player layout_test.mp3
```

## alsa_playback_1

- Simply call alsa playback to play the audio test
- alsa lib and related configurations need to exist in the environment

```shell
./alsa_playback_1 ./res/48K_16bit_STERO_30s.wav
```

## alsa_playback_2

- Simply call alsa playback and mixer to play audio tests
- alsa lib and related configurations need to exist in the environment
- Adjustable volume

```shell
./alsa_playback_2 ./res/48K_16bit_STERO_30s.wav 20000
```
