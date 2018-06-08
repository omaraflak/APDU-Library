#ifndef APDU_H
#define APDU_H

#include <vector>
#include <cstdint>
#include <string>
#include <cassert>

#include "nfcUtils.h"

class APDU {
    private:
        // command
        uint8_t mCla;
        uint8_t mIns;
        std::vector<uint8_t> mParams;
        std::vector<uint8_t> mLc;
        std::vector<uint8_t> mCmd;
        std::vector<uint8_t> mLe;
        size_t mExpectedRespLength;

        // response
        uint8_t mSW1;
        uint8_t mSW2;
        std::vector<uint8_t> mResp;

        // extended apdu
        bool mExtended;
        size_t mCmdMaxLength;
        size_t mRespMaxLength;

    public:
        APDU();
        void reset();

        // command
        void setClass(const uint8_t& cla);
        void setInstruction(const uint8_t& ins);
        void setParams(const uint8_t& p1, const uint8_t& p2);
        void setCmd(const std::string& data);
        void setCmd(const std::vector<uint8_t>& data);
        void setExpectedRespLength(const size_t& length);
        void updateCmdLength();

        uint8_t getClass() const;
        uint8_t getInstruction() const;
        std::vector<uint8_t> getParams() const;
        std::string getCmdString() const;
        std::vector<uint8_t> getCmdBytes() const;
        size_t getExpectedRespLength() const;
        std::vector<uint8_t> buildCmd() const;

        // response
        void setSW1(const uint8_t& SW1);
        void setSW2(const uint8_t& SW2);
        void setResp(const std::string& response);
        void setResp(const uint8_t* resp, const size_t& length);

        uint8_t getSW1() const;
        uint8_t getSW2() const;
        std::string getRespString() const;
        std::vector<uint8_t> getRespBytes() const;
        std::vector<uint8_t> buildResp() const;

        // extended apdu
        void setExtended(bool enabled);
        bool isExtended() const;
        size_t getCmdMaxLength() const;
        size_t getRespMaxLength() const;
};

#endif
