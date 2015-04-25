void vol_button(WAVE *sound){
    play_wave(sound,1);
}

void vol_wrong(WAVE *sound){
    play_wave(sound,1);
}

void bgm(int x,MIDI *sound){
   if(x==1)play_midi(sound,-1);else pause_midi(sound);
}