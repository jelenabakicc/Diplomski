
#include "SourceSink.h"
#include "Channel.h"
#include "CommBlock.h"
#include "Config.h"



int main(int argc, char *argv[])
{

    
	///////////////////////////////////////////		 KREIRANJE OBJEKATA		/////////////////////////////////////////////

    Config simConfig;   // konfiguraciona struktora 

    // kreiranje CRC objekta
    Polynomial poly(simConfig.overheadSize,simConfig.crcGenPoly);
    CrcBlock crc(poly);

    // kreiranje predajnika i prijemnika
    CommBlock transmitter(crc,simConfig,transmit);
    CommBlock receiver(crc,simConfig,receive);

    // Kreiranje korisnika koji obavlja i operacije izvora
    SourceSink user(simConfig);

    // kreiranje objekta kanala
    Channel channel(simConfig.frameLength);

    
	////////////////////////////////////////////	 SIMULACIJA		 /////////////////////////////////////////////

    for (int i=0;i<simConfig.numOfChannels;i++)
    {
		for (int j = 0; j < 20; j++)
		{
			cout << "--------------------------------------\n";
			cout << "--------------------------------------\n";
			cout << "Channel rate: " << simConfig.bscErrorProbArray[i] << endl;

			//predajnik
			user.generateStream();     // generisanje strima izvora podataka
			transmitter.frame.fillAndProcess(user.getOutput());    // kreiranje frejmova koje uključuje parsiranje strima i dodavanje crc dodatka na svaki frejm        

			// kanal
			channel.setChannelRate(simConfig.bscErrorProbArray[i]);  //podešavanje tekuće verovatnoće greške u kanalu
			channel.fillAndProcess(transmitter.frame.getOutput()); // punjenje kanalnog bafera podacima

			//prijemnik
			receiver.frame.fillAndProcess(channel.getOutput());  // baferovanje frejmova u prijemniku 
			receiver.frame.printFrameInfo(); // ispis rezultata CRC provere

			user.calculateErrors(simConfig, receiver.frame.getOutput()); // procena broja nedetektovanih pogrešnih frejmova

		}
        
    }

    return 0;

}




