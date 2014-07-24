// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
    
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0x08;
        pchMessageStart[2] = 0xac;
        pchMessageStart[3] = 0xff;
        vAlertPubKey = ParseHex("04d6e392b1027d00e1725209237296b390aba0723d40415a85fa65b8039ce46acb167e518b74053749db15998c5c8f28534fea06776c82693815e7078c5bee5ac5");
        nDefaultPort = 10888;
        nRPCPort = 10889;
        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_GROESTL] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SKEIN]   = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_QUBIT]   = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 80640 * 12;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
  
        const char* pszTimestamp = "2014-10-10 Hashers United Conference Begins in Las Vegas";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040f0afa74e6b8f2f5f93f59838cb745759cdb21db27e37f07b20a3f709a8cccbf0a85973fbb70220a0d96c9c503d4ed1db5daa93c8ae031e27b27a5e5497dafb5") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = BLOCK_VERSION_DEFAULT;
        genesis.nTime    = 1406088612;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 2603612;

        //// debug print
        hashGenesisBlock = genesis.GetHash();
        while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
            if (++genesis.nNonce==0) break;
             hashGenesisBlock = genesis.GetHash();
        }

        printf("MAIN: %s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n", bnProofOfWorkLimit[ALGO_SHA256D].GetCompact());
        genesis.print();

        assert(hashGenesisBlock == uint256("0x0000036e2938977c0eed0255278d083cd58b192bbeb7567e7f9fc0428d9ea4dc"));
        assert(genesis.hashMerkleRoot == uint256("0x587a1add784ab06de0f8af00fc4f1dd5d40cae61909df5b88345b2f978e5682c"));

        vSeeds.push_back(CDNSSeedData("127.0.0.1", "127.0.0.1"));

        base58Prefixes[PUBKEY_ADDRESS] = 50;
        base58Prefixes[SCRIPT_ADDRESS] = 9;
        base58Prefixes[SECRET_KEY] = 178;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' 
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
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
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0x08;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0x99;
        pchMessageStart[3] = 0x88;
        vAlertPubKey = ParseHex("040a178fce95b88b6e46601d1b1490d8569e20380416ba6fed3f38f3068f6908c25da1d2f41478d2323709dc3b2480148d40d8907752bb1ce15d9fda23bf295728");
        nDefaultPort = 20888;
        nRPCPort = 20889;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1392876393;
        genesis.nNonce = 0;
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
            if (++genesis.nNonce==0) break;
           hashGenesisBlock = genesis.GetHash();
        }
        printf("TEST: %s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();
        
        assert(hashGenesisBlock == uint256("0x0000046783ab5288748cef46e4efeae33cb442a1cf6522aca89f59ba5001a8da"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("127.0.0.1", "127.0.0.1"));

        base58Prefixes[PUBKEY_ADDRESS] = 88;
        base58Prefixes[SCRIPT_ADDRESS] = 188;
        base58Prefixes[SECRET_KEY] = 239;

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
        pchMessageStart[0] = 0xf0;
        pchMessageStart[1] = 0xa1;
        pchMessageStart[2] = 0x88;
        pchMessageStart[3] = 0xcd;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_GROESTL] = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_SKEIN]   = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_QUBIT]   = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 4;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("REG: %s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();

        //assert(hashGenesisBlock == uint256("0x0"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;
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
