#include <iostream>
#include "../nfc/include/nfcManager.h"

int main() {
    NfcManager manager;
    APDU apdu;

    if(manager.open()){
        std::cout << "Nfc device opened. Waiting for target..." << std::endl;

        // wait for target to tap
        manager.waitForTarget();

        // SELECT command
        if(manager.selectApplication("F222222222", apdu)){
            // do something with response, if any
            std::vector<uint8_t> responseByte = apdu.getRespBytes();
            std::string responseString = apdu.getRespString();

            // answer back
            apdu.setClass(0x00);
            apdu.setInstruction(0x00);
            apdu.setParams(0x00, 0x00);
            apdu.setCmd("Hello World !");
            apdu.buildAPDU();
            if(!manager.transceive(apdu)){
                std::cout << "Could not send message" << std::endl;
            }
        }

        manager.close();
    }
    else{
        std::cout << "Could not open device" << std::endl;
    }
    return 0;
}
