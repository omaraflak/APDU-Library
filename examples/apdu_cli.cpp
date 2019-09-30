#include <iostream>
#include "../nfc/include/nfcManager.h"

void spaceless(std::string& str){
    std::string tmp;
    for(int i=0 ; i<str.size() ; i++){
        if(str[i] != ' '){
            tmp += str[i];
        }
    }
    str = tmp;
}

int main() {
    NfcManager manager;
    APDU apdu;

    if(manager.open()){
        std::cout << "Nfc device opened. Waiting for target...";
        manager.waitForTarget();

        std::cout << "Target detected!" << std::endl;
        std::cout << "Type 'exit' to quit the program." << std::endl;
        std::cout << "Type 'string' to convert last response to string." << std::endl << std::endl;

        std::string input;
        while(input != "exit"){
            std::cout << ">> ";
            std::getline(std::cin, input);
            spaceless(input);

            if(input == "string"){
                std::cout << apdu.getRespString() << std::endl;
            } else{
                std::vector<uint8_t> cmd = hexStringToByteArray(input);
                apdu.setAPDU(cmd);

                if(manager.transceive(apdu)){
                    std::vector<uint8_t> response = apdu.getRespBytes();
                    std::cout << "<< ";
                    print(response);
                }
            }
        }

        manager.close();
    }
    else{
        std::cout << "Could not open device" << std::endl;
    }
    return 0;
}
