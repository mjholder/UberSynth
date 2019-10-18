#include <iostream>
#include "olcNoiseMaker.h"
using namespace std;

atomic<double> dFrequencyOutput = 0.0; // Hz

double MakeNoise(double dTime) {
	double dOutput = 0.2 * sin(dFrequencyOutput * 2 * PI * dTime);

	if(dOutput > 0.0) {
		dOutput = 0.2;
	} else {
		dOutput = 0.0;
	}

	return dOutput;
}

int main() {
	wcout << "UberSynth" << endl;

	// Get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display findings
	for(auto d : devices) wcout << "Found Output Device:" << d << endl;

	// Create sound machine. 
	// 44100 is 2x human hearing Hz. Frequency
	// short is bitrate, 16 bits. Amplitude
	// 1 is number of channels. Stereo or Mono
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	// Link noise function to noise sound machine
	sound.SetUserFunction(MakeNoise);

	double dBaseFrequency = 110.0; // A2
	double d12thRoot = pow(2.0, 1.0 / 12.0);

	while(true) {
		// Add a keyboard

		bool bKeyPressed = false;
		for(int i = 0; i < 15; i++) {
			if(GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\scbe"[i])) & 0x8000) {
				dFrequencyOutput = dBaseFrequency * pow(d12thRoot, i);
				bKeyPressed = true;
			}
		}

		if(!bKeyPressed) {
			dFrequencyOutput = 0.0;
		}
	}

	return 0;
}