// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2014-2015 Dash Developers
// Copyright (c) 2017-2018 The EMC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"
#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "base58.h"
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

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// Hardcoded seeds.
static void getHardcodedSeeds(std::vector<CAddress> &vSeedsOut)
{
    std::vector<std::string> ips;
    ips.push_back("206.189.71.184");
    ips.push_back("37.139.28.75");
    ips.push_back("138.68.4.151");

    const int64_t oneWeek = 7 * 24 * 60 * 60;
    for (size_t i = 0; i < ips.size(); ++i)
    {
        CAddress addr(CService(ips[i], 21507));
        addr.nTime = GetTime() - GetRand(oneWeek) - oneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0xdb;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("MHQCAQEEIPpijy/5b8N+O4Blg9DtpBHfIeHn8DecH9RKKBQx7hDSoAcGBSuBBAAKoUQDQgAE1y5S+Q2EcaTbs4vzgO2DOeB1Nb7nS0O1vki9yI3W4ecu7x6FwYLfqZMSWBz63gKPpnJQEWZQ+lIOY/ew4wXdRg==");
        nDefaultPort = 21507;
        nRPCPort = 21508;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16); // starting difficulty is 1 / 2^12

        const char* pszTimestamp = "Carlo Calucci - Exclusive Masternode Coin (EMC) 01-05-2018";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();

	// original 1516154401
        CTransaction txNew(1, 1525191146, vin, vout, 0);

        LogPrintf("genesis mainnet transaction:  %s\n", txNew.ToString().c_str());

        genesis.vtx.push_back(txNew);

        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1525191130; // 01-05-2018
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 415077;

        hashGenesisBlock = genesis.GetHash();

        //LogPrintf("Display genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());
	    //LogPrintf("Display merkle root so we can input it below %s\n", genesis.hashMerkleRoot.ToString().c_str());

		
        assert(hashGenesisBlock == uint256("a88595be18bc8c7531595bba1e99f579616d6d9b332aa20ce493559950d4c9a9"));
        assert(genesis.hashMerkleRoot == uint256("776bdfeece04e73693cf0f765e5fce6fcd231a630dd54d4b4647d3b0efdc6f6d"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,33); // E
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,21);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,41);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x99)(0x75)(0x45)(0xE2).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x99)(0x73)(0x43)(0xE3).convert_to_container<std::vector<unsigned char> >();

	// NOTE: MODIFIED THIS TO 0.0.0.0
    vSeeds.push_back(CDNSSeedData("1",  "206.189.71.184"));
	vSeeds.push_back(CDNSSeedData("2",  "37.139.28.75"));
	vSeeds.push_back(CDNSSeedData("3",  "138.68.4.151"));


	convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        getHardcodedSeeds(vFixedSeeds);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "ENN69NtAnZrsnUUwWbrjPhuPm4JSmrxnNb";

        nLastPOWBlock = 225000;
        nPOSStartBlock = 2250;
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
        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0xd5;
        pchMessageStart[2] = 0xa6;
        pchMessageStart[3] = 0xb8;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("MHQCAQEEIH3O67k5Ad2dOt+a6LuLZWLH4gzZ0+V2XVPhCb5Id1B/oAcGBSuBBAAKoUQDQgAEjtbe/+Vxtrpc0aTuDDyOP8S2Giw1tJPe5ZHFj9HYqM6MDkKa4LcOYN5Hxg5KhYV9QwDQ+mcOef4WkFvPZfnr0g==");
        nDefaultPort = 23707;
        nRPCPort = 23708;
        strDataDir = "testnet";
        genesis.nTime    = 1520638730;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 353317;

        hashGenesisBlock = genesis.GetHash();

        LogPrintf("Display test genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());
	    LogPrintf("Display test merkle root so we can input it below %s\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(genesis.hashMerkleRoot == uint256(""));
        assert(hashGenesisBlock == uint256(""));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,25);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x98)(0x74)(0x44)(0xE1).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x98)(0x72)(0x42)(0xE2).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 225000;
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
