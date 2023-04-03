
#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <intrin.h>

#include "GetCpuIndex.h"

namespace GWTools{

std::string GetCpuIndex(){
	typedef struct tagCpui{
		tagCpui(){
			interArray[0] = 0;
			interArray[1] = 0;
			interArray[2] = 0;
			interArray[3] = 0;
		};
		tagCpui& operator=(const tagCpui& value){
			interArray[0] = value.interArray[0];
			interArray[1] = value.interArray[1];
			interArray[2] = value.interArray[2];
			interArray[3] = value.interArray[3];

			return *this;
		};

		int interArray[4];
	}Cpui;

	//string strCpuType = GetCPUType();
	int nIds_,i;
	std::vector<Cpui> data_;
	Cpui cpui;
	char vendor_serialnumber[0x14] = { 0 };

	// Calling __cpuid with 0x0 as the function_id argument
	// gets the number of the highest valid function ID.
	__cpuid(cpui.interArray, 0);
	nIds_ = cpui.interArray[0];

	for (i = 0; i <= nIds_; ++i){
		__cpuidex(cpui.interArray, i, 0);
		data_.push_back(cpui);
	}

	sprintf_s(vendor_serialnumber, sizeof(vendor_serialnumber), "%08X%08X", data_[1].interArray[3], data_[1].interArray[0]);
	std::string strRet = vendor_serialnumber;
	return strRet;
}

}// GWTools