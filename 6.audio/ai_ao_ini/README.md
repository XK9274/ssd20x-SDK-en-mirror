# `audio_ini_par`

## Introduction
- **Purpose:** Load the `.ini` file and set the default audio parameters.
- **Sections:** Divided into AO and AI. Each has its own settings.
- **Default Configuration:** If there is no INI file provided, the program will use a built-in default configuration.

## DEMO Generation
- After compiling, the following demos are produced:
  - `load_audio_ai_tmp`
  - `load_audio_ao_tmp`
- Default generated `.ini` filenames:
  - `audio_ai_par.ini`
  - `audio_ao_par.ini`

## Execution
1. The generated demos are located in the project's `bin` folder.
2. Transfer them to the board.
3. Execute the ai DEMO: `./load_audio_ai_tmp`
   - This begins AMIC recording.
   - Manual termination required using “ctrl+c”.
   - Produces `Chn0_Amic_8K_16bit_MONO.wav` recording file.
4. Play the recording: `./load_audio_ao_tmp Chn0_Amic_8K_16bit_MONO.wav`
   - Alternatively, you can play your own audio file.
   - Default execution (`./load_audio_ao_tmp`) plays the `./8K_16bit_MONO_60s.wav` file.

**Note:** All audio files should be located in the `wav` directory.

- **Specific Playback:** 


## API Description
- For more details on the API, refer to the following files:
- `audio_ao_par.h`
- `audio_ai_par.h`
