# audio_ini_par

### Introduction
Load the ini file and set the default audio parameters.
Divided into AO and AI. The settings are separated.
If there is no INI file, it will use the default configuration.

After compiling, two DEMOs are produced:
    load_audio_ai_tmp
    load_audio_ao_tmp
The default generated ini filenames are:
audio_ai_par.ini
audio_ao_par.ini

The generated demo is in the project's bin folder.
Copy to the board and execute the ai DEMO:
    ./load_audio_ai_tmp 
After running, it starts AMIC recording. You need to manually stop it with “ctrl+c”, which will close and produce the Chn0_Amic_8K_16bit_MONO.wav recording file.
    ./load_audio_ao_tmp Chn0_Amic_8K_16bit_MONO.wav
It can play this, or you can play your own audio file directly.
If you directly execute ./load_audio_ao_tmp by default, it will play the ./8K_16bit_MONO_60s.wav file.
Audio files are in the wav folder.

To specify playback:
    ./load_audio_ao_tmp ./wav/8K_16bit_MONO_60s.wav    

### API Description
See `audio_ao_par.h` and `audio_ai_par.h`.
