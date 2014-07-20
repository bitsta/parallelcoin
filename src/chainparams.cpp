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
        vAlertPubKey = ParseHex("04fe8a17065a19b88f150305dda9ad209acb6bbe9b07cfaa36bcb383630b5b6f4c406a03acd0d77e2cbc4e9093c327c4f41df01c5791458066da7c1c337d0d15d3");
        nDefaultPort = 11047;
        nRPCPort = 11048;
        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 250000;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
  
        const char* pszTimestamp = "NYTimes 2014-07-19 - Dell Begins Accepting Bitcoin";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e0d27172510c6806889740edafe6e63eb23fca32786fccfdb282bb2876a9f43b228245df057661ff943f6150716a20ea1851e8a7e9f54e620297664618438dae") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = BLOCK_VERSION_DEFAULT;
        genesis.nTime    = 1405749601;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 2354982;

        hashGenesisBlock = genesis.GetHash();
        
        assert(hashGenesisBlock == uint256("0x00000c3a564759f66cf25dfe5a487bbf5c055e19525ec7cd84e4df599bfbb194"));
        assert(genesis.hashMerkleRoot == uint256("0x5b6b6892104e90c97678c51c6706f988c83a373c1add4e6a1169f32dd8fbd8e5"));

        vSeeds.push_back(CDNSSeedData("seed1.coinworks.info", "seed1.coinworks.info"));
        vSeeds.push_back(CDNSSeedData("seed3.coinworks.info", "seed3.coinworks.info"));
        vSeeds.push_back(CDNSSeedData("seed5.coinworks.info", "seed5.coinworks.info"));
        vSeeds.push_back(CDNSSeedData("seed6.coinworks.info", "seed6.coinworks.info"));
        vSeeds.push_back(CDNSSeedData("seed7.coinworks.info", "seed7.coinworks.info"));

        base58Prefixes[PUBKEY_ADDRESS] = 83;
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
        vAlertPubKey = ParseHex("042d0fcbaa5d80a255cffc4c51eb34e5633f3717cb695c6f2e697f8288bfea58584cca3e60d4074ccbec9cbcd09976567cae82335dfe3142a02fe16a84378a0101");
        nDefaultPort = 21047;
        nRPCPort = 21048;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1405750002;
        genesis.nNonce = 1062634;
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
        //    if (++genesis.nNonce==0) break;
        //   hashGenesisBlock = genesis.GetHash();
        //}

        //printf("TEST: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //genesis.print();
        
        assert(hashGenesisBlock == uint256("0x00000c05280ebeb2351fbf26d0c245d36fe80e8bd6349e80ce6c54663ed4630e"));

        vFixedSeeds.clear();
        vSeeds.clear();
		vSeeds.push_back(CDNSSeedData("seed1.coinworks.info", "seed1.coinworks.info"));

        base58Prefixes[PUBKEY_ADDRESS] = 18;
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
        genesis.nTime = 1405750164;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 5;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 31047;
        strDataDir = "regtest";
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SHA256D].getuint256()){
        //    if (++genesis.nNonce==0) break;
        //    hashGenesisBlock = genesis.GetHash();
        //}

        //printf("REG: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //genesis.print();

        assert(hashGenesisBlock == uint256("0x4d3009dd1971071eb35d70334d3d47b8a1cb3c04e1ae90d5a3037e24494428d6"));

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
