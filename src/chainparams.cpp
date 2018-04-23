// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The GraphicsCoin developers
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
    const int64_t nOneWeek = 7*24*60*60;
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
        pchMessageStart[0] = 0x34;
        pchMessageStart[1] = 0x49;
        pchMessageStart[2] = 0x33;
        pchMessageStart[3] = 0x4a;
        nDefaultPort = 4096;
        nRPCPort = 4093;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "Audaces Fortuna Juvat - 2018-04-23";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1524516965, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1524516965;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 53683;

       /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == dd868b1a2ee686cd1bb4391697827416dc00f8bed2e0c9f1ce6ddcea6bac5572
        block.nTime = 1524516965
        block.nNonce = 53683
        block.GetHash = efc62a616e63a58a331875e8ec181288bff23ec179e47a385c1f86cb5cf61fbf
       */

        hashGenesisBlock = genesis.GetHash();		
        assert(hashGenesisBlock == uint256("0xefc62a616e63a58a331875e8ec181288bff23ec179e47a385c1f86cb5cf61fbf"));
        assert(genesis.hashMerkleRoot == uint256("0xdd868b1a2ee686cd1bb4391697827416dc00f8bed2e0c9f1ce6ddcea6bac5572"));

        //vSeeds.push_back(CDNSSeedData("seed1", "64.150.189.104"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 38);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 62);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 83);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x1f)(0x46)(0x20)(0x9f).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x1f)(0x88)(0x95)(0xbf).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 0x7fffffff;
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
        pchMessageStart[0] = 0x03;
        pchMessageStart[1] = 0x1c;
        pchMessageStart[2] = 0x6c;
        pchMessageStart[3] = 0x30;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 14);
        nDefaultPort = 3052;
        nRPCPort = 3050;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 13731;

       /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == dd868b1a2ee686cd1bb4391697827416dc00f8bed2e0c9f1ce6ddcea6bac5572
        block.nTime = 1520366800
        block.nNonce = 13731
        block.GetHash = aff44d1af53327e7101a5665818b794cc90e88d86dd5d6b8c6725e39374d1934
       */
        
        hashGenesisBlock = genesis.GetHash();		
        assert(hashGenesisBlock == uint256("0xaff44d1af53327e7101a5665818b794cc90e88d86dd5d6b8c6725e39374d1934"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 145);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x82)(0x3a)(0xa0)(0x03).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x82)(0x3a)(0x06)(0x97).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;




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

        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);



    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
