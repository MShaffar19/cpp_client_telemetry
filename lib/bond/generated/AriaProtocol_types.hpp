//------------------------------------------------------------------------------
// This code was generated by a tool.
//
//   Tool : bondjson2cpp 2016.12.18.1
//   File : AriaProtocol.json
//
// Changes to this file may cause incorrect behavior and will be lost when
// the code is regenerated.
// <auto-generated />
//------------------------------------------------------------------------------

#pragma once
#include "PAL/PAL.hpp"
#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace AriaProtocol {

namespace _bond_enumerators {
namespace RecordType {
enum RecordType {
    NotSet                  = 0,
    Event                   = 1,
    PerformanceCounter      = 2,
    Anomaly                 = 3,
    Prediction              = 4,
    TraceLog                = 5,
    EventSourceLog          = 6,
    HttpLog                 = 7,
    PerformanceCounterAzure = 8,
    PerformanceCounterGfs   = 9
};
}
}
using namespace _bond_enumerators::RecordType;

namespace _bond_enumerators {
namespace PIIScrubber {
enum PIIScrubber {
    NotSet    = 0,
    O365      = 1,
    SkypeBI   = 2,
    SkypeData = 3
};
}
}
using namespace _bond_enumerators::PIIScrubber;

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
    // 1: optional PIIScrubber ScrubType
    ::AriaProtocol::PIIScrubber ScrubType = ::AriaProtocol::PIIScrubber::NotSet;
    // 2: optional PIIKind Kind
    ::AriaProtocol::PIIKind Kind = ::AriaProtocol::PIIKind::NotSet;
    // 3: optional string RawContent
    std::string RawContent;

    bool operator==(PII const& other) const
    {
        return (ScrubType == other.ScrubType)
            && (Kind == other.Kind)
            && (RawContent == other.RawContent);
    }

    bool operator!=(PII const& other) const
    {
        return !(*this == other);
    }
};

struct Record {
    // 1: optional string Id
    std::string Id;
    // 3: optional int64 Timestamp
    int64_t Timestamp = 0;
    // 4: optional map<string, string> ConfigurationIds
    std::map<std::string, std::string> ConfigurationIds;
    // 5: optional string Type
    std::string Type;
    // 6: optional string EventType
    std::string EventType;
    // 13: optional map<string, string> Extension
    std::map<std::string, std::string> Extension;
    // 19: optional map<string, string> ContextIds
    std::map<std::string, std::string> ContextIds;
    // 24: optional RecordType RecordType
    RecordType RecordType = RecordType::Event;
    // 30: optional map<string, PII> PIIExtensions
    std::map<std::string, PII> PIIExtensions;
    // 31: optional map<string, bool> TypedExtensionBoolean
    std::map<std::string, bool> TypedExtensionBoolean;
    // 32: optional map<string, int64> TypedExtensionDateTime
    std::map<std::string, int64_t> TypedExtensionDateTime;
    // 33: optional map<string, int64> TypedExtensionInt64
    std::map<std::string, int64_t> TypedExtensionInt64;
    // 34: optional map<string, double> TypedExtensionDouble
    std::map<std::string, double> TypedExtensionDouble;
    // 35: optional map<string, vector<uint8>> TypedExtensionGuid
    std::map<std::string, std::vector<uint8_t>> TypedExtensionGuid;

	Record()
	{
		Id = Microsoft::Applications::Telemetry::PAL::generateUuidString();
		Timestamp = Microsoft::Applications::Telemetry::PAL::getUtcSystemTimeMs();
	}

	bool operator==(const Record& other) const
	{
        return (Id == other.Id)
            && (Timestamp == other.Timestamp)
            && (ConfigurationIds == other.ConfigurationIds)
            && (Type == other.Type)
            && (EventType == other.EventType)
            && (Extension == other.Extension)
            && (ContextIds == other.ContextIds)
            && (RecordType == other.RecordType)
            && (PIIExtensions == other.PIIExtensions)
            && (TypedExtensionBoolean == other.TypedExtensionBoolean)
            && (TypedExtensionDateTime == other.TypedExtensionDateTime)
            && (TypedExtensionInt64 == other.TypedExtensionInt64)
            && (TypedExtensionDouble == other.TypedExtensionDouble)
            && (TypedExtensionGuid == other.TypedExtensionGuid);
	}

	bool operator!=(const Record& other) const
	{
		return !(*this == other);
	}
};


struct DataPackage {
    // 1: optional string Type
    std::string Type;
    // 2: optional string Source
    std::string Source;
    // 3: optional string Version
    std::string Version;
    // 4: optional map<string, string> Ids
    std::map<std::string, std::string> Ids;
    // 5: optional string DataPackageId
    std::string DataPackageId;
    // 6: optional int64 Timestamp
    int64_t Timestamp = 0;
    // 7: optional int32 SchemaVersion
    int32_t SchemaVersion = 0;
    // 8: optional vector<Record> Records
    std::vector< ::AriaProtocol::Record> Records;

    bool operator==(DataPackage const& other) const
    {
        return (Type == other.Type)
            && (Source == other.Source)
            && (Version == other.Version)
            && (Ids == other.Ids)
            && (DataPackageId == other.DataPackageId)
            && (Timestamp == other.Timestamp)
            && (SchemaVersion == other.SchemaVersion)
            && (Records == other.Records);
    }

    bool operator!=(DataPackage const& other) const
    {
        return !(*this == other);
    }
};

struct ClientToCollectorRequest {
    // 1: optional vector<DataPackage> DataPackages
    std::vector< ::AriaProtocol::DataPackage> DataPackages;
    // 2: optional int32 RequestRetryCount
    int32_t RequestRetryCount = 0;
    // 3: optional map<string, vector<DataPackage>> TokenToDataPackagesMap
    std::map<std::string, std::vector< ::AriaProtocol::DataPackage>> TokenToDataPackagesMap;

    bool operator==(ClientToCollectorRequest const& other) const
    {
        return (DataPackages == other.DataPackages)
            && (RequestRetryCount == other.RequestRetryCount)
            && (TokenToDataPackagesMap == other.TokenToDataPackagesMap);
    }

    bool operator!=(ClientToCollectorRequest const& other) const
    {
        return !(*this == other);
    }
};

} // namespace AriaProtocol
