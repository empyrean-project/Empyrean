// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x44;
        pchMessageStart[1] = 0x66;
        pchMessageStart[2] = 0xea;
        pchMessageStart[3] = 0xf5;
        vAlertPubKey = ParseHex("0416262ca3e7a6feef6a54765b96e9056bc6b132a04b94acefeace80695c62f7c2f81f85d251a216df3be197653f454852a2d08c631aad5ca3cbe565d5257fe028");
        nDefaultPort = 4243;
        nRPCPort = 4242;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "http://chicago.cbslocal.com/2017/10/26/robbery-us-bank-branch-burbank/";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1509307740, vin, vout, 0); 
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1509307740; 
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 435126;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x3e5cc58a9d1e1ac5f3e22e1cbb208be982ad72355195eed231aab3ffc120504c"));
        assert(genesis.hashMerkleRoot == uint256("0x145d478397a28947934b928ac5cbaab9db5a543768797dc84eaeb1dd05c62517"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,38);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,6);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,99);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x77)(0xe6)(0x4d).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x77)(0xb3)(0x5f).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 60;
        if(nBestHeight > nLastPoWBlock) // Scaled down for PoS only phase
        {
          nTargetSpacing = 40;
        }

        nTargetTimespan = 12 * nTargetSpacing;
        nLastPoWBlock = 20000;
        nStartPoSBlock = 100;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x64;
        pchMessageStart[1] = 0x9d;
        pchMessageStart[2] = 0x83;
        pchMessageStart[3] = 0xc2;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("043e7a6feef6a54765b96e9056bc6b132a04b94e80695c62f7c2f81f85d251a216df3be197653f454852a2d08c631aad5ca3cbe5616262caacefeac5d5257fe028");
        nDefaultPort = 14243;
        nRPCPort = 14242;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 94351;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x4c5b2159aca6a1f94ba6753dfd6e66b97dadc7154ffbc13fbb3276f0c2b58c05"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,81);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,16);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,53);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x05)(0x66)(0x8e)(0x4e).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x05)(0x66)(0xA7)(0xBd).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 60;
        nLastPoWBlock = 2000;
        nStartPoSBlock = 1;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x18;
        pchMessageStart[1] = 0xd3;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0x2e;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 4);
        genesis.nTime = 1509307740;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 7094;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 4241;
        strDataDir = "regtest";

        assert(hashGenesisBlock == uint256("0x15ca65932c1c415d4531d6d545fe4a84b120fccc2266813ffd9fbfe34e845f0e"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
