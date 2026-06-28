#pragma once

#include "auxilary_data.h"

namespace Editor
{
	class AuxilaryDataMultiSpeed final : public AuxilaryData
	{
	public:
		AuxilaryDataMultiSpeed();

		void Reset() override;

		const unsigned char GetMultiplier() const;
		void SetMultiplier(const unsigned char inMultiplier);

	protected:
		std::vector<unsigned char> GenerateSaveData() const override;
		unsigned short GetGeneratedFileVersion() const override;

		bool RestoreFromSaveData(unsigned short inDataVersion, std::vector<unsigned char> inData) override;

	private:
		unsigned char m_Multiplier;
	};
}
