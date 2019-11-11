#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

#define TARGET_PARTITION "/dev/hidraw5"

#define FREQUENCY 0x81
#define FUNCTION 0x82
#define POWER 0x83
#define BIAS 0x84
#define LED 0x85

#define READ 0x72
#define WRITE 0x77

struct morfeusCMD {
	char direction;
	char reg;
	char data[14];
};

int main(void) {
	
	int morfeus = open(TARGET_PARTITION, O_RDWR | O_CREAT);

	if (morfeus == -1) {
		return -1; 
	}	

	// char buffer [] = { 0x77, 0x83 ,0x01,0x01 ,0x01,0x01 ,0x01,0x01 ,0x01,0x01, 0x00,0x00, 0x00,0x00, 0x00};

	// 8f0d1801 = 2400000001
	char buffer [16] = { READ ,FREQUENCY ,0x00 ,0x00 ,0x00 ,0x00 ,0x8F ,0x0D ,0x18 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 };
	char response [16];


	// get Frequency
	// 72 81 00 00 00 00 8F 0D 18 01 1C AA FC 7F 00 00

	// get Power (it was 1)
	// 72 83 00 00 00 00 00 00 00 01 0B 23 FF 7F 00 00

	// get Bias Tee (it was off)
	// 72 84 00 00 00 00 00 00 00 00 C8 67 FD 7F 00 00

	// set Mixer
	// 77 82 00 00 00 00 00 00 00 00 00 00 00 00 00 00

	// get Mixer
	// 72 82 00 00 00 00 00 00 00 00 F8 E8 FD 7F 00 00

	// set Generator
	// 77 82 01 01 01 01 01 01 01 01 00 00 00 00 00 00

	// get Generator
	// 72 82 00 00 00 00 00 00 00 01 22 7F FC 7F 00 00

	//write(morfeus, buffer, sizeof(buffer)); 

	struct morfeusCMD cmd;
	cmd.direction = READ;

	cmd.reg = FREQUENCY;
	write(morfeus, (char *)&cmd, sizeof(cmd)); 
	read(morfeus, response, sizeof(response)); 
	
	unsigned int freq = response[6]<<24;
	freq += response[7]<<16;
	freq += response[8]<<8;
	freq += response[9];

	cmd.reg = POWER;
	write(morfeus, (char *)&cmd, sizeof(cmd)); 
	read(morfeus, response, sizeof(response)); 

	int voltage = response[9];

	cmd.reg = FUNCTION;
	write(morfeus, (char *)&cmd, sizeof(cmd)); 
	read(morfeus, response, sizeof(response)); 

	char mode = (response[9] == 1)?'G':'M';

	cmd.reg = BIAS;
	write(morfeus, (char *)&cmd, sizeof(cmd)); 
	read(morfeus, response, sizeof(response)); 

	int bias = (response[9] == 1);

	cmd.reg = LED;
	write(morfeus, (char *)&cmd, sizeof(cmd)); 
	read(morfeus, response, sizeof(response)); 

	// int bias = (response[9] == 1);

	printf("Frequency %u\nPower 0.%dv\nMode %s\nBias Tee : %s\nLed : %d\n",freq, voltage, mode == 'M'?"Mixer":"Generator", bias?"On":"Off", response[9]);

	close(morfeus);

	sync();
}