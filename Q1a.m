drums = wavread('~/drums.wav');
guitar = wavread('~/guitar.wav');
length(drums)/44100
length(guitar)/44100
guitar_signal = guitar(44100*5 : 44100*10);
drums_signal = drums(44100*5 : 44100*10);
figure
plot(drums_signal);
xlabel('time');
ylabel('amplitude');
title('Drums Signal');
figure
plot(guitar_signal);
xlabel('time');
ylabel('amplitude');
title('Guitar Signal');
add_result = guitar_signal + drums_signal;
sound(add_result,44100)
figure
plot(add_result);
xlabel('time');
ylabel('amplitude');
title('Addition Signal');
diff_result1 = guitar_signal - drums_signal;
diff_result2 = - guitar_signal + drums_signal;
figure
plot(diff_result1);
xlabel('time');
ylabel('amplitude');
title('Guit - Drums');
figure
plot(diff_result2);
xlabel('time');
ylabel('amplitude');
title('Drums - Guit');

Scale_drums = drums_signal*3;
figure
plot(Scale_drums);
xlabel('time');
ylabel('amplitude');
title('Scaled three times drums');

