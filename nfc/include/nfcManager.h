#ifndef COMMUNICATOR
#define COMMUNICATOR

#include <cstdlib>
#include <string>
#include <vector>
#include <nfc/nfc.h>

#include "apdu.h"

class NfcManager {
    private:
        nfc_context* mNfcContext;
        nfc_device* mNfcDevice;
        nfc_modulation mNfcModulation;

    public:
        NfcManager();

        bool open();
        void close();
        void waitForTarget();
        bool isTargetPresent();
        bool transceive(APDU& apdu);
        bool selectApplication(const std::string& appId, APDU& apdu);
};

#endif
