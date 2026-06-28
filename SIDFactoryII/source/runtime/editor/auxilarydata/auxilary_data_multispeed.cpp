#include "auxilary_data_multispeed.h"
#include "auxilary_data_utils.h"
#include "utils/c64file.h"
#include "foundation/base/assert.h"

namespace Editor
{
	AuxilaryDataMultiSpeed::AuxilaryDataMultiSpeed()
		: AuxilaryData(Type::MultiSpeed)
	{
		Reset();
	}


	void AuxilaryDataMultiSpeed::Reset()
	{
		m_Multiplier = 1;
	}


	const unsigned char AuxilaryDataMultiSpeed::GetMultiplier() const
	{
		return m_Multiplier < 1 ? 1 : m_Multiplier;
	}


	void AuxilaryDataMultiSpeed::SetMultiplier(const unsigned char inMultiplier)
	{
		m_Multiplier = inMultiplier < 1 ? 1 : inMultiplier;
	}


	std::vector<unsigned char> AuxilaryDataMultiSpeed::GenerateSaveData() const
	{
		std::vector<unsigned char> output;

		AuxilaryDataUtils::SaveDataPushByte(output, m_Multiplier);

		return output;
	}


	unsigned short AuxilaryDataMultiSpeed::GetGeneratedFileVersion() const
	{
		return 1;
	}


	bool AuxilaryDataMultiSpeed::RestoreFromSaveData(unsigned short inDataVersion, std::vector<unsigned char> inData)
	{
		if (inData.empty())
		{
			m_Multiplier = 1;
			return true;
		}

		auto it = inData.begin();
		m_Multiplier = AuxilaryDataUtils::LoadDataPullByte(it);

		if (m_Multiplier < 1)
			m_Multiplier = 1;

		return true;
	}
}
