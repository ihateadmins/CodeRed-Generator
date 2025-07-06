#include "Configuration.hpp"
#include "PiecesOfCode.hpp"

/*
# ========================================================================================= #
# Cosmetics
# ========================================================================================= #
*/

uint32_t GConfig::m_constantSpacing = 60;

uint32_t GConfig::m_commentSpacing = 30;

uint32_t GConfig::m_enumSpacing = 50;

uint32_t GConfig::m_classSpacing = 50;

uint32_t GConfig::m_structSpacing = 50;

uint32_t GConfig::m_functionSpacing = 50;

uint32_t GConfig::GetConstSpacing()
{
    return m_constantSpacing;
}

uint32_t GConfig::GetCommentSpacing()
{
    return m_commentSpacing;
}

uint32_t GConfig::GetEnumSpacing()
{
    return m_enumSpacing;
}

uint32_t GConfig::GetClassSpacing()
{
    return m_classSpacing;
}

uint32_t GConfig::GetStructSpacing()
{
    return m_structSpacing;
}

uint32_t GConfig::GetFunctionSpacing()
{
    return m_functionSpacing;
}

/*
# ========================================================================================= #
# Generator Settings
# ========================================================================================= #
*/

// If set to true this will auto include "Windows.h" in your sdk, along with renaming some windows functions that could conflict with windows macros.
bool GConfig::m_useWindows = true;

// If you want to use objects internal integer for finding static classes and functions, note that these will change every time the game updates.
bool GConfig::m_useConstants = true;

// If you want to remove the "iNative" index on functions before calling process event.
bool GConfig::m_removeNativeIndex = true;

// If you want to remove the "FUNC_Native" flag on functions before calling process event.
bool GConfig::m_removeNativeFlags = true;

// If you want the EFunctionFlags, EPropertyFlags, and EObjectFlags enums to be printed in the final sdk.
bool GConfig::m_printEnumFlags = true;

// If you want to use strongly typed enum classes over normal ones.
bool GConfig::m_useEnumClasses = true;

// Underlying enum type if you set "m_useEnumClasses" to true.
std::string GConfig::m_enumClassType = "uint8_t";

// Used to calculate property sizes and missed offsets.
uint32_t GConfig::m_gameAlignment = 0x4;

// Forced alignment used in the final sdk.
uint32_t GConfig::m_finalAlignment = 0x4;

// Names of classes or structs you don't want generated in the final sdk.
std::vector<std::string> GConfig::m_blacklistedTypes = { "FPointer", "FQWord", "FScriptDelegate" };

// Names of classes or structs you want to override with your own custom one.
std::map<std::string, std::string> GConfig::m_typeOverrides = {
    { "FExampleStruct", PiecesOfTypes::Example_Struct }
};

bool GConfig::UsingWindows()
{
    return m_useWindows;
}

bool GConfig::UsingConstants()
{
    return m_useConstants;
}

bool GConfig::RemoveNativeIndex()
{
    return m_removeNativeIndex;
}

bool GConfig::RemoveNativeFlags()
{
    return m_removeNativeFlags;
}

bool GConfig::PrintEnumFlags()
{
    return m_printEnumFlags;
}

bool GConfig::UsingEnumClasses()
{
    return m_useEnumClasses;
}

const std::string& GConfig::GetEnumClassType()
{
    return m_enumClassType;
}

uint32_t GConfig::GetGameAlignment()
{
    return m_gameAlignment;
}

uint32_t GConfig::GetFinalAlignment()
{
    return m_finalAlignment;
}

bool GConfig::IsTypeBlacklisted(const std::string& name)
{
    if (!m_blacklistedTypes.empty() && !name.empty())
    {
        return (std::find(m_blacklistedTypes.begin(), m_blacklistedTypes.end(), name) != m_blacklistedTypes.end());
    }

    return false;
}

bool GConfig::IsTypeOveridden(const std::string& name)
{
    if (!name.empty())
    {
        return m_typeOverrides.contains(name);
    }

    return false;
}

std::string GConfig::GetTypeOverride(const std::string& name)
{
    if (IsTypeOveridden(name))
    {
        return m_typeOverrides[name];
    }

    return "";
}

/*
# ========================================================================================= #
# Process Event
# ========================================================================================= #
*/

bool GConfig::m_useIndex = true;

// Position where the process event function is in UObject's VfTable.
int32_t GConfig::m_peIndex = 63;

// Half byte mask for ProcessEvent, derived from provided signature: 74 ?? 83 C0 07 83 E0 F8 E8 ?? ?? ?? ?? 8B C4
std::string GConfig::m_peMask = "xx??????x????x";

// First value is the actual hex escaped pattern, second value is the string version of it printed in the final sdk.
std::pair<uint8_t*, std::string> GConfig::m_pePattern = { (uint8_t*)"\x74\x00\x83\xc0\x07\x83\xe0\xf8\xe8\x00\x00\x00\x00\x8b\xc4", "\\x74\\x00\\x83\\xc0\\x07\\x83\\xe0\\xf8\\xe8\\x00\\x00\\x00\\x00\\x8b\\xc4" };

bool GConfig::UsingProcessEventIndex()
{
    return (m_useIndex && (m_peIndex != -1));
}

int32_t GConfig::GetProcessEventIndex()
{
    return m_peIndex;
}

const std::string& GConfig::GetProcessEventMask()
{
    return m_peMask;
}

uint8_t* GConfig::GetProcessEventPattern()
{
    return m_pePattern.first;
}

const std::string& GConfig::GetProcessEventStr()
{
    return m_pePattern.second;
}

/*
# ========================================================================================= #
# Global Objects & Names
# ========================================================================================= #
*/

// Use offsets since GObjects and GNames offsets are provided.
bool GConfig::m_useOffsets = false;

uintptr_t GConfig::m_gobjectOffset = 0x13465A54;

// Half byte mask for GObjects, from provided signature: A1 ?? ?? ?? ?? 8B ?? ?? 8B ?? ?? 25 00 02 00 00
std::string GConfig::m_gobjectMask = "x????x??x??xxxxx";

// GObjects pattern from provided signature.
																																				   
std::pair<uint8_t*, std::string> GConfig::m_gobjectPattern = { (uint8_t*)"\xa1\x00\x00\x00\x00\x8b\x00\x00\x8b\x00\x00\x25\x00\x02\x00\x00", "\\xa1\\x00\\x00\\x00\\x00\\x8b\\x00\\x00\\x8b\\x00\\x00\\x25\\x00\\x02\\x00\\x00" };

// GNames offset from provided data: 0x13454180.
uintptr_t GConfig::m_gnameOffset = 0x13454180;

// Half byte mask for GNames, from provided signature: 8B 0D ?? ?? ?? ?? 83 3C 81 00 74
std::string GConfig::m_gnameMask = "xx????xxxxx";

// GNames pattern from provided signature.
																																				 
std::pair<uint8_t*, std::string> GConfig::m_gnamePattern = { (uint8_t*)"\x8b\x0d\x00\x00\x00\x00\x83\x3c\x81\x00\x74", "\\x8b\\x0d\\x00\\x00\\x00\\x00\\x83\\x3c\\x81\\x00\\x74" };

bool GConfig::UsingOffsets()
{
    return m_useOffsets;
}

uintptr_t GConfig::GetGObjectOffset()
{
    return m_gobjectOffset;
}

uint8_t* GConfig::GetGObjectPattern()
{
    return m_gobjectPattern.first;
}

const std::string& GConfig::GetGObjectStr()
{
    return m_gobjectPattern.second;
}

const std::string& GConfig::GetGObjectMask()
{
    return m_gobjectMask;
}

uintptr_t GConfig::GetGNameOffset()
{
    return m_gnameOffset;
}

uint8_t* GConfig::GetGNamePattern()
{
    return m_gnamePattern.first;
}

const std::string& GConfig::GetGNameStr()
{
    return m_gnamePattern.second;
}

const std::string& GConfig::GetGNameMask()
{
    return m_gnameMask;
}

/*
# ========================================================================================= #
# Game Info
# ========================================================================================= #
*/

// Mainly just used for the printed headers at the top of each generated file.
std::string GConfig::m_gameNameLong = "Global Agenda";

// This is used for the output folder name, along with the printed headers at the top of each file.
std::string GConfig::m_gameNameShort = "GASDK";

// Optional, mainly for your own sake, like comparing sdks you generate or release to people.
std::string GConfig::m_gameVersion = "2.0.0.0";

// Directory folder that your want your sdk to be generated in.
std::filesystem::path GConfig::m_outputPath = "gasdk_generated";

const std::string& GConfig::GetGameNameLong()
{
    return m_gameNameLong;
}

const std::string& GConfig::GetGameNameShort()
{
    return m_gameNameShort;
}

const std::string& GConfig::GetGameVersion()
{
    return m_gameVersion;
}

const std::filesystem::path& GConfig::GetOutputPath()
{
    return m_outputPath;
}

bool GConfig::HasOutputPath()
{
    return (!GetOutputPath().string().empty() && (GetOutputPath().string() != "I_FORGOT_TO_SET_A_PATH"));
}
