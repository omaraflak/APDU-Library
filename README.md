# PN532 & Android HCE

As part of a school project, I had to make an NFC connection between my Android and the PN532 V3 chip.

I thought this code might be useful to others, so I'm just putting it here. It's written in C++.

It should probably work with other chips than the PN532.

# Compile

Enter the repo directory then simply :

```
make
```

# Dependency : Libnfc

This code uses [libnfc](https://github.com/nfc-tools/libnfc)

If you're on Linux, you can install libnfc simply by doing :

```
git clone https://github.com/nfc-tools/libnfc.git
autoreconf -vis
./configure --enable-doc
make
sudo make install
```

# Notice

The code contains an implementation of the APDU protocol according to [Wikipedia](https://fr.wikipedia.org/wiki/Application_Protocol_Data_Unit).
However, I'm not entierly sure if I implemented correctly the **extended apdu** protocol. The `PN532` doesn't support it anyway...

# How to use

Use the `NfcManager` to simplify the process of detecting, opening and transceiving data.

```c++
NfcManager manager;
if(manager.open()){
    if(manager.isTargetPresent()){
        // do things ...
    }
    manager.close();
}
```

Once the device opened, use the `APDU` class to send and receive APDUs commands.
If you want to perform a **select** command, you would do :

```c++
APDU apdu;
apdu.setClass(0x00);
apdu.setInstruction(0xA4);
apdu.setParams(0x04, 0x00);
apdu.setCmd(hexStringToByteArray(appId));
apdu.buildAPDU();
manager.transceive(apdu);
```

To know more about APDUs instruction codes etc, read the beautiful [ISO standard](http://cardwerk.com/smart-card-standard-iso7816-4-section-5-basic-organizations)

When `manager.transceive()` ends, the `APDU` object will contain the response, if any. You can get it like this :

```c++
std::vector<uint8_t> responseBytes = apdu.getRespBytes();
std::string responseString = apdu.getRespString();
```

That said, `NfcManager` already implements the `select` command, you just need to do this :

```c++
manager.selectApplication(appId, apdu);
```

You can find a full example here : **[main.cpp](https://github.com/OmarAflak/PN532-Android-HCE/blob/master/src/main.cpp)**
