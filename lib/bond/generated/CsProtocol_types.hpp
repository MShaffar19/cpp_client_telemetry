//------------------------------------------------------------------------------
// This code was generated by a tool.
//
//   Tool : bondjson2cpp 2017.09.19.1
//   File : CsProtocol.json
//
// Changes to this file may cause incorrect behavior and will be lost when
// the code is regenerated.
// <auto-generated />
//------------------------------------------------------------------------------

#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace CsProtocol {

struct Ingest {
    // 1: required int64 time
    int64_t time = 0;
    // 2: required string clientIp
    std::string clientIp;
    // 3: optional int64 auth
    int64_t auth = 0;
    // 4: optional int64 quality
    int64_t quality = 0;
    // 5: optional int64 uploadTime
    int64_t uploadTime = 0;
    // 6: optional string userAgent
    std::string userAgent;
    // 7: optional string client
    std::string client;

    bool operator==(Ingest const& other) const
    {
        return (time == other.time)
            && (clientIp == other.clientIp)
            && (auth == other.auth)
            && (quality == other.quality)
            && (uploadTime == other.uploadTime)
            && (userAgent == other.userAgent)
            && (client == other.client);
    }

    bool operator!=(Ingest const& other) const
    {
        return !(*this == other);
    }
};

struct User {
    // 1: optional string id
    std::string id;
    // 2: optional string localId
    std::string localId;
    // 3: optional string authId
    std::string authId;
    // 4: optional string locale
    std::string locale;

    bool operator==(User const& other) const
    {
        return (id == other.id)
            && (localId == other.localId)
            && (authId == other.authId)
            && (locale == other.locale);
    }

    bool operator!=(User const& other) const
    {
        return !(*this == other);
    }
};

struct Loc {
    // 1: optional string id
    std::string id;
    // 2: optional string country
    std::string country;
    // 3: optional string timezone
    std::string timezone;

    bool operator==(Loc const& other) const
    {
        return (id == other.id)
            && (country == other.country)
            && (timezone == other.timezone);
    }

    bool operator!=(Loc const& other) const
    {
        return !(*this == other);
    }
};

struct Device {
    // 1: optional string id
    std::string id;
    // 2: optional string localId
    std::string localId;
    // 3: optional string authId
    std::string authId;
    // 4: optional string authSecId
    std::string authSecId;
    // 5: optional string deviceClass
    std::string deviceClass;
    // 6: optional string orgId
    std::string orgId;
    // 7: optional string orgAuthId
    std::string orgAuthId;
    // 8: optional string make
    std::string make;
    // 9: optional string model
    std::string model;
    // 10: optional string authIdEnt
    std::string authIdEnt;

    bool operator==(Device const& other) const
    {
        return (id == other.id)
            && (localId == other.localId)
            && (authId == other.authId)
            && (authSecId == other.authSecId)
            && (deviceClass == other.deviceClass)
            && (orgId == other.orgId)
            && (orgAuthId == other.orgAuthId)
            && (make == other.make)
            && (model == other.model)
            && (authIdEnt == other.authIdEnt);
    }

    bool operator!=(Device const& other) const
    {
        return !(*this == other);
    }
};

struct Os {
    // 1: optional string locale
    std::string locale;
    // 2: optional string expId
    std::string expId;
    // 3: optional int32 bootId
    int32_t bootId = 0;
    // 4: optional string name
    std::string name;
    // 5: optional string ver
    std::string ver;

    bool operator==(Os const& other) const
    {
        return (locale == other.locale)
            && (expId == other.expId)
            && (bootId == other.bootId)
            && (name == other.name)
            && (ver == other.ver);
    }

    bool operator!=(Os const& other) const
    {
        return !(*this == other);
    }
};

struct App {
    // 1: optional string expId
    std::string expId;
    // 2: optional string userId
    std::string userId;
    // 3: optional string env
    std::string env;
    // 4: optional int32 asId
    int32_t asId = 0;
    // 5: optional string id
    std::string id;
    // 6: optional string ver
    std::string ver;
    // 7: optional string locale
    std::string locale;
    // 8: optional string name
    std::string name;
    // 9: optional string sesId
    std::string sesId;

    bool operator==(App const& other) const
    {
        return (expId == other.expId)
            && (userId == other.userId)
            && (env == other.env)
            && (asId == other.asId)
            && (id == other.id)
            && (ver == other.ver)
            && (locale == other.locale)
            && (name == other.name)
            && (sesId == other.sesId);
    }

    bool operator!=(App const& other) const
    {
        return !(*this == other);
    }
};

struct Utc {
    // 1: optional string stId
    std::string stId;
    // 2: optional string aId
    std::string aId;
    // 3: optional string raId
    std::string raId;
    // 4: optional string op
    std::string op;
    // 5: optional int64 cat
    int64_t cat = 0;
    // 6: optional int64 flags
    int64_t flags = 0;
    // 7: optional string sqmId
    std::string sqmId;
    // 9: optional string mon
    std::string mon;
    // 10: optional int32 cpId
    int32_t cpId = 0;
    // 11: optional string bSeq
    std::string bSeq;
    // 12: optional string epoch
    std::string epoch;
    // 13: optional int64 seq
    int64_t seq = 0;
    // 14: optional double popSample
    double popSample = 0.0;
    // 15: optional int64 eventFlags
    int64_t eventFlags = 0;
    // 16: optional int64 wsId
    int64_t wsId = 0;
    // 17: optional int64 wcmp
    int64_t wcmp = 0;
    // 18: optional int64 wPId
    int64_t wPId = 0;

    bool operator==(Utc const& other) const
    {
        return (stId == other.stId)
            && (aId == other.aId)
            && (raId == other.raId)
            && (op == other.op)
            && (cat == other.cat)
            && (flags == other.flags)
            && (sqmId == other.sqmId)
            && (mon == other.mon)
            && (cpId == other.cpId)
            && (bSeq == other.bSeq)
            && (epoch == other.epoch)
            && (seq == other.seq)
            && (popSample == other.popSample)
            && (eventFlags == other.eventFlags)
            && (wsId == other.wsId)
            && (wcmp == other.wcmp)
            && (wPId == other.wPId);
    }

    bool operator!=(Utc const& other) const
    {
        return !(*this == other);
    }
};

struct M365a {
    // 1: optional string enrolledTenantId
    std::string enrolledTenantId;
    // 2: optional uint64 msp
    uint64_t msp = 0;

    bool operator==(M365a const& other) const
    {
        return (enrolledTenantId == other.enrolledTenantId)
            && (msp == other.msp);
    }

    bool operator!=(M365a const& other) const
    {
        return !(*this == other);
    }
};

struct Xbl {
    // 5: optional map<string, string> claims
    std::map<std::string, std::string> claims;
    // 10: optional string nbf
    std::string nbf;
    // 20: optional string exp
    std::string exp;
    // 30: optional string sbx
    std::string sbx;
    // 40: optional string dty
    std::string dty;
    // 50: optional string did
    std::string did;
    // 60: optional string xid
    std::string xid;
    // 70: optional uint64 uts
    uint64_t uts = 0;
    // 80: optional string pid
    std::string pid;
    // 90: optional string dvr
    std::string dvr;
    // 100: optional uint32 tid
    uint32_t tid = 0;
    // 110: optional string tvr
    std::string tvr;
    // 120: optional string sty
    std::string sty;
    // 130: optional string sid
    std::string sid;
    // 140: optional int64 eid
    int64_t eid = 0;
    // 150: optional string ip
    std::string ip;

    bool operator==(Xbl const& other) const
    {
        return (claims == other.claims)
            && (nbf == other.nbf)
            && (exp == other.exp)
            && (sbx == other.sbx)
            && (dty == other.dty)
            && (did == other.did)
            && (xid == other.xid)
            && (uts == other.uts)
            && (pid == other.pid)
            && (dvr == other.dvr)
            && (tid == other.tid)
            && (tvr == other.tvr)
            && (sty == other.sty)
            && (sid == other.sid)
            && (eid == other.eid)
            && (ip == other.ip);
    }

    bool operator!=(Xbl const& other) const
    {
        return !(*this == other);
    }
};

struct Javascript {
    // 10: optional string libVer
    std::string libVer;
    // 15: optional string osName
    std::string osName;
    // 20: optional string browser
    std::string browser;
    // 21: optional string browserVersion
    std::string browserVersion;
    // 25: optional string platform
    std::string platform;
    // 30: optional string make
    std::string make;
    // 35: optional string model
    std::string model;
    // 40: optional string screenSize
    std::string screenSize;
    // 45: optional string msfpc
    std::string msfpc;
    // 50: optional string mc1Id
    std::string mc1Id;
    // 60: optional uint64 mc1Lu
    uint64_t mc1Lu = 0;
    // 70: optional bool isMc1New
    bool isMc1New = false;
    // 80: optional string ms0
    std::string ms0;
    // 90: optional string anid
    std::string anid;
    // 100: optional string a
    std::string a;
    // 110: optional string msResearch
    std::string msResearch;
    // 120: optional string csrvc
    std::string csrvc;
    // 130: optional string rtCell
    std::string rtCell;
    // 140: optional string rtEndAction
    std::string rtEndAction;
    // 150: optional string rtPermId
    std::string rtPermId;
    // 160: optional string r
    std::string r;
    // 170: optional string wtFpc
    std::string wtFpc;
    // 180: optional string omniId
    std::string omniId;
    // 190: optional string gsfxSession
    std::string gsfxSession;
    // 200: optional string domain
    std::string domain;
    // 210: required bool userConsent
    bool userConsent = false;
    // 220: optional string browserLang
    std::string browserLang;
    // 230: optional string serviceName
    std::string serviceName;
    // 999: optional string dnt
    std::string dnt;

    bool operator==(Javascript const& other) const
    {
        return (libVer == other.libVer)
            && (osName == other.osName)
            && (browser == other.browser)
            && (browserVersion == other.browserVersion)
            && (platform == other.platform)
            && (make == other.make)
            && (model == other.model)
            && (screenSize == other.screenSize)
            && (msfpc == other.msfpc)
            && (mc1Id == other.mc1Id)
            && (mc1Lu == other.mc1Lu)
            && (isMc1New == other.isMc1New)
            && (ms0 == other.ms0)
            && (anid == other.anid)
            && (a == other.a)
            && (msResearch == other.msResearch)
            && (csrvc == other.csrvc)
            && (rtCell == other.rtCell)
            && (rtEndAction == other.rtEndAction)
            && (rtPermId == other.rtPermId)
            && (r == other.r)
            && (wtFpc == other.wtFpc)
            && (omniId == other.omniId)
            && (gsfxSession == other.gsfxSession)
            && (domain == other.domain)
            && (userConsent == other.userConsent)
            && (browserLang == other.browserLang)
            && (serviceName == other.serviceName)
            && (dnt == other.dnt);
    }

    bool operator!=(Javascript const& other) const
    {
        return !(*this == other);
    }
};

struct Protocol {
    // 1: optional int32 metadataCrc
    int32_t metadataCrc = 0;
    // 2: optional vector<vector<string>> ticketKeys
    std::vector<std::vector<std::string>> ticketKeys;
    // 3: optional string devMake
    std::string devMake;
    // 4: optional string devModel
    std::string devModel;
    // 5: optional uint64 msp
    uint64_t msp = 0;

    bool operator==(Protocol const& other) const
    {
        return (metadataCrc == other.metadataCrc)
            && (ticketKeys == other.ticketKeys)
            && (devMake == other.devMake)
            && (devModel == other.devModel)
            && (msp == other.msp);
    }

    bool operator!=(Protocol const& other) const
    {
        return !(*this == other);
    }
};

struct Receipts {
    // 1: optional int64 originalTime
    int64_t originalTime = 0;
    // 2: optional int64 uploadTime
    int64_t uploadTime = 0;
    // 3: optional string originalName
    std::string originalName;
    // 4: optional uint64 flags
    uint64_t flags = 0;

    bool operator==(Receipts const& other) const
    {
        return (originalTime == other.originalTime)
            && (uploadTime == other.uploadTime)
            && (originalName == other.originalName)
            && (flags == other.flags);
    }

    bool operator!=(Receipts const& other) const
    {
        return !(*this == other);
    }
};

struct Net {
    // 1: optional string provider
    std::string provider;
    // 2: optional string cost
    std::string cost;
    // 3: optional string type
    std::string type;

    bool operator==(Net const& other) const
    {
        return (provider == other.provider)
            && (cost == other.cost)
            && (type == other.type);
    }

    bool operator!=(Net const& other) const
    {
        return !(*this == other);
    }
};

struct Sdk {
    // 1: optional string ver
    std::string ver;
    // 2: optional string epoch
    std::string epoch;
    // 3: optional int64 seq
    int64_t seq = 0;
    // 4: optional string installId
    std::string installId;
    // 5: optional string libVer
    std::string libVer;

    bool operator==(Sdk const& other) const
    {
        return (ver == other.ver)
            && (epoch == other.epoch)
            && (seq == other.seq)
            && (installId == other.installId)
            && (libVer == other.libVer);
    }

    bool operator!=(Sdk const& other) const
    {
        return !(*this == other);
    }
};

struct Cloud {
    // 1: optional string fullEnvName
    std::string fullEnvName;
    // 2: optional string location
    std::string location;
    // 3: optional string environment
    std::string environment;
    // 4: optional string deploymentUnit
    std::string deploymentUnit;
    // 5: optional string name
    std::string name;
    // 6: optional string roleInstance
    std::string roleInstance;
    // 7: optional string role
    std::string role;

    bool operator==(Cloud const& other) const
    {
        return (fullEnvName == other.fullEnvName)
            && (location == other.location)
            && (environment == other.environment)
            && (deploymentUnit == other.deploymentUnit)
            && (name == other.name)
            && (roleInstance == other.roleInstance)
            && (role == other.role);
    }

    bool operator!=(Cloud const& other) const
    {
        return !(*this == other);
    }
};

struct Service {
    // 1: optional string name
    std::string name;
    // 2: optional string role
    std::string role;
    // 3: optional string roleVersion
    std::string roleVersion;

    bool operator==(Service const& other) const
    {
        return (name == other.name)
            && (role == other.role)
            && (roleVersion == other.roleVersion);
    }

    bool operator!=(Service const& other) const
    {
        return !(*this == other);
    }
};

struct Cs {
    // 1: optional string sig
    std::string sig;

    bool operator==(Cs const& other) const
    {
        return (sig == other.sig);
    }

    bool operator!=(Cs const& other) const
    {
        return !(*this == other);
    }
};

struct Mscv {
    // 1: optional string cV
    std::string cV;

    bool operator==(Mscv const& other) const
    {
        return (cV == other.cV);
    }

    bool operator!=(Mscv const& other) const
    {
        return !(*this == other);
    }
};

struct IntWeb {
    // 1: optional string mc1Id
    std::string mc1Id;
    // 2: optional string msfpc
    std::string msfpc;
    // 3: optional string anid
    std::string anid;
    // 4: optional string serviceName
    std::string serviceName;
    // 5: optional map<string, string> mscom
    std::map<std::string, std::string> mscom;

    bool operator==(IntWeb const& other) const
    {
        return (mc1Id == other.mc1Id)
            && (msfpc == other.msfpc)
            && (anid == other.anid)
            && (serviceName == other.serviceName)
            && (mscom == other.mscom);
    }

    bool operator!=(IntWeb const& other) const
    {
        return !(*this == other);
    }
};

struct IntService {
    // 1: optional string fullEnvName
    std::string fullEnvName;
    // 2: optional string location
    std::string location;
    // 3: optional string environment
    std::string environment;
    // 4: optional string deploymentUnit
    std::string deploymentUnit;
    // 5: optional string name
    std::string name;

    bool operator==(IntService const& other) const
    {
        return (fullEnvName == other.fullEnvName)
            && (location == other.location)
            && (environment == other.environment)
            && (deploymentUnit == other.deploymentUnit)
            && (name == other.name);
    }

    bool operator!=(IntService const& other) const
    {
        return !(*this == other);
    }
};

struct Web {
    // 10: optional string browser
    std::string browser;
    // 20: optional string browserVer
    std::string browserVer;
    // 30: optional string screenRes
    std::string screenRes;
    // 40: optional string domain
    std::string domain;
    // 50: required bool userConsent
    bool userConsent = false;
    // 60: optional string browserLang
    std::string browserLang;
    // 70: optional bool isManual
    bool isManual = false;

    bool operator==(Web const& other) const
    {
        return (browser == other.browser)
            && (browserVer == other.browserVer)
            && (screenRes == other.screenRes)
            && (domain == other.domain)
            && (userConsent == other.userConsent)
            && (browserLang == other.browserLang)
            && (isManual == other.isManual);
    }

    bool operator!=(Web const& other) const
    {
        return !(*this == other);
    }
};

namespace _bond_enumerators {
namespace ValueKind {
enum ValueKind {
    ValueInt64         = 0,
    ValueUInt64        = 1,
    ValueInt32         = 2,
    ValueUInt32        = 3,
    ValueDouble        = 4,
    ValueString        = 5,
    ValueBool          = 6,
    ValueDateTime      = 7,
    ValueGuid          = 8,
    ValueArrayInt64    = 9,
    ValueArrayUInt64   = 10,
    ValueArrayInt32    = 11,
    ValueArrayUInt32   = 12,
    ValueArrayDouble   = 13,
    ValueArrayString   = 14,
    ValueArrayBool     = 15,
    ValueArrayDateTime = 16,
    ValueArrayGuid     = 17
};
}
}
using namespace _bond_enumerators::ValueKind;

namespace _bond_enumerators {
namespace PIIKind {
enum PIIKind {
    NotSet            = 0,
    DistinguishedName = 1,
    GenericData       = 2,
    IPV4Address       = 3,
    IPv6Address       = 4,
    MailSubject       = 5,
    PhoneNumber       = 6,
    QueryString       = 7,
    SipAddress        = 8,
    SmtpAddress       = 9,
    Identity          = 10,
    Uri               = 11,
    Fqdn              = 12,
    IPV4AddressLegacy = 13
};
}
}
using namespace _bond_enumerators::PIIKind;

struct PII {
    // 1: optional PIIKind Kind
    ::CsProtocol::PIIKind Kind = ::CsProtocol::PIIKind::NotSet;

    bool operator==(PII const& other) const
    {
        return (Kind == other.Kind);
    }

    bool operator!=(PII const& other) const
    {
        return !(*this == other);
    }
};

namespace _bond_enumerators {
namespace CustomerContentKind {
enum CustomerContentKind {
    NotSet         = 0,
    GenericContent = 1
};
}
}
using namespace _bond_enumerators::CustomerContentKind;

struct CustomerContent {
    // 1: optional CustomerContentKind Kind
    ::CsProtocol::CustomerContentKind Kind = ::CsProtocol::CustomerContentKind::NotSet;

    bool operator==(CustomerContent const& other) const
    {
        return (Kind == other.Kind);
    }

    bool operator!=(CustomerContent const& other) const
    {
        return !(*this == other);
    }
};

struct Attributes {
    // 1: optional vector<PII> pii
    std::vector< ::CsProtocol::PII> pii;
    // 2: optional vector<CustomerContent> customerContent
    std::vector< ::CsProtocol::CustomerContent> customerContent;

    bool operator==(Attributes const& other) const
    {
        return (pii == other.pii)
            && (customerContent == other.customerContent);
    }

    bool operator!=(Attributes const& other) const
    {
        return !(*this == other);
    }
};

struct Value {
    // 1: optional ValueKind type
    ::CsProtocol::ValueKind type = ::CsProtocol::ValueKind::ValueString;
    // 2: optional vector<Attributes> attributes
    std::vector< ::CsProtocol::Attributes> attributes;
    // 3: optional string stringValue
    std::string stringValue;
    // 4: optional int64 longValue
    int64_t longValue = 0;
    // 5: optional double doubleValue
    double doubleValue = 0.0;
    // 6: optional vector<vector<uint8>> guidValue
    std::vector<std::vector<uint8_t>> guidValue;
    // 10: optional vector<vector<string>> stringArray
    std::vector<std::vector<std::string>> stringArray;
    // 11: optional vector<vector<int64>> longArray
    std::vector<std::vector<int64_t>> longArray;
    // 12: optional vector<vector<double>> doubleArray
    std::vector<std::vector<double>> doubleArray;
    // 13: optional vector<vector<vector<uint8>>> guidArray
    std::vector<std::vector<std::vector<uint8_t>>> guidArray;

    bool operator==(Value const& other) const
    {
        return (type == other.type)
            && (attributes == other.attributes)
            && (stringValue == other.stringValue)
            && (longValue == other.longValue)
            && (doubleValue == other.doubleValue)
            && (guidValue == other.guidValue)
            && (stringArray == other.stringArray)
            && (longArray == other.longArray)
            && (doubleArray == other.doubleArray)
            && (guidArray == other.guidArray);
    }

    bool operator!=(Value const& other) const
    {
        return !(*this == other);
    }
};

struct Data {
    // 1: optional map<string, Value> properties
    std::map<std::string, ::CsProtocol::Value> properties;

    bool operator==(Data const& other) const
    {
        return (properties == other.properties);
    }

    bool operator!=(Data const& other) const
    {
        return !(*this == other);
    }
};

struct Record {
    // 1: required string ver
    std::string ver;
    // 2: required string name
    std::string name;
    // 3: required int64 time
    int64_t time = 0;
    // 4: optional double popSample
    double popSample = 100;
    // 5: optional string iKey
    std::string iKey;
    // 6: optional int64 flags
    int64_t flags = 0;
    // 7: optional string cV
    std::string cV;
    // 20: optional vector<Ingest> extIngest
    std::vector< ::CsProtocol::Ingest> extIngest;
    // 21: optional vector<Protocol> extProtocol
    std::vector< ::CsProtocol::Protocol> extProtocol;
    // 22: optional vector<User> extUser
    std::vector< ::CsProtocol::User> extUser;
    // 23: optional vector<Device> extDevice
    std::vector< ::CsProtocol::Device> extDevice;
    // 24: optional vector<Os> extOs
    std::vector< ::CsProtocol::Os> extOs;
    // 25: optional vector<App> extApp
    std::vector< ::CsProtocol::App> extApp;
    // 26: optional vector<Utc> extUtc
    std::vector< ::CsProtocol::Utc> extUtc;
    // 27: optional vector<Xbl> extXbl
    std::vector< ::CsProtocol::Xbl> extXbl;
    // 28: optional vector<Javascript> extJavascript
    std::vector< ::CsProtocol::Javascript> extJavascript;
    // 29: optional vector<Receipts> extReceipts
    std::vector< ::CsProtocol::Receipts> extReceipts;
    // 31: optional vector<Net> extNet
    std::vector< ::CsProtocol::Net> extNet;
    // 32: optional vector<Sdk> extSdk
    std::vector< ::CsProtocol::Sdk> extSdk;
    // 33: optional vector<Loc> extLoc
    std::vector< ::CsProtocol::Loc> extLoc;
    // 34: optional vector<Cloud> extCloud
    std::vector< ::CsProtocol::Cloud> extCloud;
    // 35: optional vector<Service> extService
    std::vector< ::CsProtocol::Service> extService;
    // 36: optional vector<Cs> extCs
    std::vector< ::CsProtocol::Cs> extCs;
    // 37: optional vector<M365a> extM365a
    std::vector< ::CsProtocol::M365a> extM365a;
    // 41: optional vector<Data> ext
    std::vector< ::CsProtocol::Data> ext;
    // 42: optional vector<Mscv> extMscv
    std::vector< ::CsProtocol::Mscv> extMscv;
    // 43: optional vector<IntWeb> extIntWeb
    std::vector< ::CsProtocol::IntWeb> extIntWeb;
    // 44: optional vector<IntService> extIntService
    std::vector< ::CsProtocol::IntService> extIntService;
    // 45: optional vector<Web> extWeb
    std::vector< ::CsProtocol::Web> extWeb;
    // 51: optional map<string, string> tags
    std::map<std::string, std::string> tags;
    // 60: optional string baseType
    std::string baseType;
    // 61: optional vector<Data> baseData
    std::vector< ::CsProtocol::Data> baseData;
    // 70: optional vector<Data> data
    std::vector< ::CsProtocol::Data> data;

    bool operator==(Record const& other) const
    {
        return (ver == other.ver)
            && (name == other.name)
            && (time == other.time)
            && (popSample == other.popSample)
            && (iKey == other.iKey)
            && (flags == other.flags)
            && (cV == other.cV)
            && (extIngest == other.extIngest)
            && (extProtocol == other.extProtocol)
            && (extUser == other.extUser)
            && (extDevice == other.extDevice)
            && (extOs == other.extOs)
            && (extApp == other.extApp)
            && (extUtc == other.extUtc)
            && (extXbl == other.extXbl)
            && (extJavascript == other.extJavascript)
            && (extReceipts == other.extReceipts)
            && (extNet == other.extNet)
            && (extSdk == other.extSdk)
            && (extLoc == other.extLoc)
            && (extCloud == other.extCloud)
            && (extService == other.extService)
            && (extCs == other.extCs)
            && (extM365a == other.extM365a)
            && (ext == other.ext)
            && (extMscv == other.extMscv)
            && (extIntWeb == other.extIntWeb)
            && (extIntService == other.extIntService)
            && (extWeb == other.extWeb)
            && (tags == other.tags)
            && (baseType == other.baseType)
            && (baseData == other.baseData)
            && (data == other.data);
    }

    bool operator!=(Record const& other) const
    {
        return !(*this == other);
    }
};

} // namespace CsProtocol
