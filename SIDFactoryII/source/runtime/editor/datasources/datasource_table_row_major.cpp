#include "datasource_table_row_major.h"
#include "runtime/emulation/cpumemory.h"

#include "foundation/base/assert.h"

#include <vector>

namespace Editor
{
	DataSourceTableRowMajor::DataSourceTableRowMajor(Emulation::CPUMemory* inCPUMemory, unsigned short inSourceAddress, int inRowCount, int inColumnCount)
		: DataSourceTable(inCPUMemory, inSourceAddress, inRowCount, inColumnCount)
	{
		PullDataFromSource();
	}

	DataSourceTableRowMajor::~DataSourceTableRowMajor()
	{
	}

	//------------------------------------------------------------------------------------------------------------------

	bool DataSourceTableRowMajor::PushDataToSource()
	{
		FOUNDATION_ASSERT(m_CPUMemory != nullptr);
		FOUNDATION_ASSERT(m_CPUMemory->IsLocked());
		FOUNDATION_ASSERT(m_Data != nullptr);

		if (m_ScaleMultiplier > 1)
		{
			std::vector<unsigned char> scaled(m_Data, m_Data + m_DataSize);
			for (int i = 0; i < m_DataSize; ++i)
			{
				unsigned char val = scaled[i];
				if (val > 0 && val < 0x80)
				{
					int sv = static_cast<int>(val) * m_ScaleMultiplier;
					if (sv > 0x7e)
						sv = 0x7e;
					scaled[i] = static_cast<unsigned char>(sv);
				}
			}
			m_CPUMemory->SetData(m_SourceAddress, scaled.data(), m_DataSize);
		}
		else
		{
			m_CPUMemory->SetData(m_SourceAddress, m_Data, m_DataSize);
		}

		return true;
	}

	//------------------------------------------------------------------------------------------------------------------

	void DataSourceTableRowMajor::PullDataFromSource()
	{
		FOUNDATION_ASSERT(m_CPUMemory != nullptr);
		FOUNDATION_ASSERT(m_Data != nullptr);

		m_CPUMemory->Lock();
		m_CPUMemory->GetData(m_SourceAddress, m_Data, m_DataSize);
		m_CPUMemory->Unlock();

		if (m_ScaleMultiplier > 1)
		{
			for (int i = 0; i < m_DataSize; ++i)
			{
				unsigned char data = m_Data[i];
				if (data > 0 && data < 0x80)
					m_Data[i] = static_cast<unsigned char>(static_cast<int>(data) / m_ScaleMultiplier);
			}
		}
	}
}