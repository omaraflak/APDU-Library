#include "../include/nfcManager.h"

NfcManager::NfcManager(){
    mNfcContext = NULL;
    mNfcDevice = NULL;
}

bool NfcManager::open(){
    nfc_init(&mNfcContext);
    if (mNfcContext == NULL) {
        return false;
    }

    mNfcDevice = nfc_open(mNfcContext, NULL);
    if(mNfcDevice == NULL){
        return false;
    }

    if(nfc_initiator_init(mNfcDevice) < 0) {
        return false;
    }

    mNfcModulation = {
       .nmt = NMT_ISO14443A,
       .nbr = NBR_106,
    };

    return true;
}

void NfcManager::close(){
    nfc_close(mNfcDevice);
    nfc_exit(mNfcContext);
}

void NfcManager::waitForTarget(){
    while(!isTargetPresent());
}

bool NfcManager::isTargetPresent(){
    nfc_target nfcTarget;
    return (nfc_initiator_select_passive_target(mNfcDevice, mNfcModulation, NULL, 0, &nfcTarget)>0);
}

bool NfcManager::transceive(APDU& apdu){
    std::vector<uint8_t> cmdApdu = apdu.buildCmd();
    uint8_t *capdu = &cmdApdu[0];
    size_t capdulen = cmdApdu.size();
    uint8_t rapdu[apdu.getRespMaxLength()];
    size_t rapdulen = apdu.getRespMaxLength();

    int res = nfc_initiator_transceive_bytes(mNfcDevice, capdu, capdulen, rapdu, rapdulen, 700);
    if(res<2){
        return false;
    }

    apdu.setSW1(rapdu[res-2]);
    apdu.setSW2(rapdu[res-1]);

    if(rapdu[res-2] != 0x90 || rapdu[res-1] != 0x00){
        return false;
    }

    apdu.setResp(rapdu, res-2);
    return true;
}

bool NfcManager::selectApplication(const std::string& appId, APDU& apdu){
    apdu.setClass(0x00);
    apdu.setInstruction(0xA4);
    apdu.setParams(0x04, 0x00);
    apdu.setCmd(hexStringToByteArray(appId));
    return transceive(apdu);
}
