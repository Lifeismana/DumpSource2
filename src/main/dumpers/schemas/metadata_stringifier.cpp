/**
 * =============================================================================
 * DumpSource2
 * Copyright (C) 2024 ValveResourceFormat Contributors
 * 
 * source2gen
 * Copyright 2024 neverlosecc
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "schemas.h"
#include "globalvariables.h"
#include "interfaces.h"
#include "schemasystem/schemasystem.h"
#include <filesystem>
#include <fstream>
#include <map>
#include <unordered_set>
#include <algorithm>
#include "metadatalist.h"
#include <optional>
#include <cstring>
#include <fmt/format.h>
#include "metadata_stringifier.h"
#include <modules.h>
#include <regex>

class SimpleCUtlString {
public:
	const char* Get() {
		return m_pString;
	}
private:
	const char* m_pString = nullptr;
};

namespace Dumpers::Schemas
{

std::map<std::string, std::vector<std::regex>> g_replaceMap{
	{
		"CTestBlendContainer",
		{
			std::regex(R"#(("m_nStreamingSize":) .*,)#"),
			std::regex(R"#(("m_nRate":) .*,)#"),
			std::regex(R"#(("m_nFormat":) .*,)#"),
			std::regex(R"#(("m_nSampleCount":) .*,)#"),
			std::regex(R"#(("m_nLoopStart":) .*,)#"),
			std::regex(R"#(("m_nLoopEnd":) .*,)#"),
			std::regex(R"#(("m_nChannels":) .*,)#"),
		}
	},
	{
		"CVoiceContainerBlender",
		{
			std::regex(R"#(("m_nStreamingSize":) .*,)#"),
			std::regex(R"#(("m_nRate":) .*,)#"),
			std::regex(R"#(("m_nFormat":) .*,)#"),
			std::regex(R"#(("m_nSampleCount":) .*,)#"),
			std::regex(R"#(("m_nLoopStart":) .*,)#"),
			std::regex(R"#(("m_nLoopEnd":) .*,)#"),
			std::regex(R"#(("m_nChannels":) .*,)#"),
		}
	},
	{
		"CVoiceContainerEnvelope",
		{
			std::regex(R"#(("m_nStreamingSize":) .*,)#"),
			std::regex(R"#(("m_nRate":) .*,)#"),
			std::regex(R"#(("m_nFormat":) .*,)#"),
			std::regex(R"#(("m_nSampleCount":) .*,)#"),
			std::regex(R"#(("m_nLoopStart":) .*,)#"),
			std::regex(R"#(("m_nLoopEnd":) .*,)#"),
			std::regex(R"#(("m_nChannels":) .*,)#"),
		}
	},
	{
		"CVoiceContainerSet",
		{
			std::regex(R"#(("m_nStreamingSize":) .*,)#"),
			std::regex(R"#(("m_nRate":) .*,)#"),
			std::regex(R"#(("m_nFormat":) .*,)#"),
			std::regex(R"#(("m_nSampleCount":) .*,)#"),
			std::regex(R"#(("m_nLoopStart":) .*,)#"),
			std::regex(R"#(("m_nLoopEnd":) .*,)#"),
			std::regex(R"#(("m_nChannels":) .*,)#"),
		}
	},
	{
		"CVoiceContainerStaticAdditiveSynth",
		{
			std::regex(R"#(("m_nStreamingSize":) .*,)#"),
			std::regex(R"#(("m_nRate":) .*,)#"),
			std::regex(R"#(("m_nFormat":) .*,)#"),
			std::regex(R"#(("m_nSampleCount":) .*,)#"),
			std::regex(R"#(("m_nLoopStart":) .*,)#"),
			std::regex(R"#(("m_nLoopEnd":) .*,)#"),
			std::regex(R"#(("m_nChannels":) .*,)#"),
		}
	},
	{
		"CVoiceContainerSwitch",
		{
			std::regex(R"#(("m_nStreamingSize":) .*,)#"),
			std::regex(R"#(("m_nRate":) .*,)#"),
			std::regex(R"#(("m_nFormat":) .*,)#"),
			std::regex(R"#(("m_nSampleCount":) .*,)#"),
			std::regex(R"#(("m_nLoopStart":) .*,)#"),
			std::regex(R"#(("m_nLoopEnd":) .*,)#"),
			std::regex(R"#(("m_nChannels":) .*,)#"),
		}
	},
	{
		"VMixDynamics3BandDesc_t",
		{
			std::regex(R"#(("m_fldbKneeWidth":) .*,)#"),
			std::regex(R"#(("m_flLowCutoffFreq":) .*,)#"),
		}
	},
		{
		"VMixVocoderDesc_t",
		{
			std::regex(R"#(("m_fldBModGain":) .*,)#"),
		}
	},
	{
		"CLookAtUpdateNode",
		{
			std::regex(R"#(("m_target":) .*,)#"),
		}
	},
	{
		"CFootLockUpdateNode",
		{
			std::regex(R"#(("m_flTiltPlanePitchSpringStrength":) .*,)#"),
			std::regex(R"#(("m_flTiltPlaneRollSpringStrength":) .*,)#"),
		}
	},
	{
		"CBlockSelectionMetricEvaluator",
		{
			std::regex(R"#(("m_means":)[\s\S]*?\],)#"),
			std::regex(R"#(("m_standardDeviations":)[\s\S]*?\],)#"),
		}
	},
	{
		"CFeNamedJiggleBone",
		{
			std::regex(R"#(("m_transform":)[\s\S]*?\],)#"),
			std::regex(R"#(("m_nJiggleParent":) .*,)#"),
		}
	},
	{
		"Dop26_t",
		{
			std::regex(R"#(("m_flSupport":)[\s\S]*?\])#"),
		}
	},
	{
		"FourCovMatrices3",
		{
			std::regex(R"#(("m_vDiag":)[\s\S]*?\],)#"),
		}
	},
	{
		"CVoxelVisibility",
		{
			std::regex(R"#(("m_nOffset":) .*,)#"),
			std::regex(R"#(("m_nElementCount":) .*,)#"),
		}
	},
	{
		"CDOTAFightingGameActionDefinition",
		{
			std::regex(R"#(("m_nActionID":) .*,)#"),
		}
	},
	{
		"CDOTAMinesweeperGameDefinition",
		{
			std::regex(R"#(("m_flTimeLimit":) .*,)#"),
			std::regex(R"#(("m_nStageProgressionTimerIncrease":) .*,)#"),
			std::regex(R"#(("m_nTimerIncreaseExpireClicks":) .*,)#"),
			std::regex(R"#(("m_nTimerIncreaseChance":) .*,)#"),
		}
	},
	{
		"CDOTAOverworldDefinition",
		{
			std::regex(R"#(("m_eAssociatedEvent":) .*,)#"),
		}
	},
	{
		"CSurvivorsGameModeDefinition",
		{
			std::regex(R"#(("m_vCollisionIndicatorColorPlayer":)[\s\S]*?\],)#"),
			std::regex(R"#(("m_vCollisionIndicatorColorEnemy":)[\s\S]*?\],)#"),
		}
	},
	{
		"CSurvivorsPowerUpDefinition",
		{
			std::regex(R"#(("m_vWarmupEffectColor":)[\s\S]*?\],)#"),
		}
	},
};

// Determine how and if to output metadata entry value based on it's type.
std::optional<std::string> GetMetadataValue(const SchemaMetadataEntryData_t& entry, const char* metadataTargetName)
{
	if (g_mapMetadataNameToValue.find(entry.m_pszName) != g_mapMetadataNameToValue.end())
	{
		auto valueType = g_mapMetadataNameToValue.at(entry.m_pszName);
		switch (valueType)
		{
			case MetadataValueType::STRING:
			{
				auto value = *static_cast<const char**>(entry.m_pData);
				Globals::stringsIgnoreStream << value << "\n";
				return fmt::format("\"{}\"", value);
			}
			case MetadataValueType::INTEGER:
				return std::to_string(*static_cast<int*>(entry.m_pData));
			case MetadataValueType::FLOAT:
				return std::to_string(*static_cast<float*>(entry.m_pData));
			case MetadataValueType::INLINE_STRING:
			{
				// max 8 characters. Also check for null term.
				char* result = static_cast<char*>(entry.m_pData);
				for (uint8_t i = 0; i < 8; ++i) {
					if (result[i] == '\0') {
						return fmt::format("\"{}\"", std::string(result, i));
					}
				}
				return fmt::format("\"{}\"", std::string(result, 8));
			}
			case MetadataValueType::VARNAME:
			{
				auto value = static_cast<CSchemaVarName*>(entry.m_pData);

				const auto check_ptr = [](const char* ptr) -> bool {
					// Authored: source2gen
					// @note: hotfix for the deadlock 14/09/24 update,
					// where they filled some ptrs with -1 instead of nullptr
					return ptr != nullptr && ptr != reinterpret_cast<const char*>(-1);
				};

				std::stringstream stringStream;
				auto hasType = check_ptr(value->m_pszType);
				auto hasName = check_ptr(value->m_pszName);

				stringStream << "\"";

				if (hasType)
					stringStream << value->m_pszType;

				if (hasName)
				{
					if (hasType)
						stringStream << " ";
					stringStream << value->m_pszName;
				}

				stringStream << "\"";

				return stringStream.str();
			}
			case MetadataValueType::KV3DEFAULTS:
				typedef void* (*GetKV3DefaultsFn)();
				typedef int (*SaveKV3AsJsonFn)(void* kv3, SimpleCUtlString& err, SimpleCUtlString& str);

				if (!entry.m_pData || !(*(void**)entry.m_pData) || !strcmp(metadataTargetName, "CastSphereSATParams_t")) return "Could not parse KV3 Defaults";

				auto value = reinterpret_cast<GetKV3DefaultsFn>(*(void**)entry.m_pData)();
				
				if (!value) return "Could not parse KV3 Defaults";

#ifdef WIN32
				static auto SaveKV3AsJson = Modules::tier0->GetSymbol<SaveKV3AsJsonFn>("?SaveKV3AsJSON@@YA_NPEBVKeyValues3@@PEAVCUtlString@@1@Z");
#else
				static auto SaveKV3AsJson = Modules::tier0->GetSymbol<SaveKV3AsJsonFn>("_Z13SaveKV3AsJSONPK10KeyValues3P10CUtlStringS3_");	
#endif
				if (!SaveKV3AsJson) {
					spdlog::critical("SaveKV3AsJson not found");
					return {};
				}

				SimpleCUtlString err;
				SimpleCUtlString buf;
				int res = SaveKV3AsJson(*(void**)value, err, buf);

				if (res) {
					std::string out = buf.Get();
					if (g_replaceMap.find(metadataTargetName) != g_replaceMap.end())
					{
						const auto& regexVector = g_replaceMap.at(metadataTargetName);

						for (const auto& regex : regexVector) {
							out = std::regex_replace(out, regex, "$1 <HIDDEN FOR DIFF>,");
						}
					}

					return out;
				}

				return "Could not parse KV3 Defaults";
		}
	}

	return {};
}

} // namespace Dumpers::Schemas