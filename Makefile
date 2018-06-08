CC = g++
ODIR = obj
PROG = main
CXXFLAGS = -std=c++11 -lnfc

OBJS = $(ODIR)/apdu.o $(ODIR)/nfcManager.o $(ODIR)/nfcUtils.o $(ODIR)/main.o
$(PROG) : $(ODIR) $(OBJS)
	$(CC) -o $@ $(OBJS) $(CXXFLAGS)

$(ODIR)/apdu.o : ./nfc/src/apdu.cpp ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c ./nfc/src/apdu.cpp -o $@ $(CXXFLAGS)

$(ODIR)/nfcManager.o : ./nfc/src/nfcManager.cpp ./nfc/include/nfcManager.h ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c ./nfc/src/nfcManager.cpp -o $@ $(CXXFLAGS)

$(ODIR)/nfcUtils.o : ./nfc/src/nfcUtils.cpp ./nfc/include/nfcUtils.h
	$(CC) -c ./nfc/src/nfcUtils.cpp -o $@ $(CXXFLAGS)

$(ODIR)/main.o : ./src/main.cpp ./nfc/include/nfcManager.h ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c ./src/main.cpp -o $@ $(CXXFLAGS)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(PROG) ]; then rm $(PROG); fi
