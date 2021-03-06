/*
 * SampleData.h
 *
 * Created by Marcel Luethi
 *
 * Copyright (c) 2011 University of Basel
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __SAMPLE_DATA_TXX
#define __SAMPLE_DATA_TXX

namespace statismo {

template <class Representer>
SampleData<Representer>*
SampleData<Representer>::Load(const Representer* representer, const H5::Group& dsGroup)
{
	VectorType dsVector;
	std::string sampleType = HDF5Utils::readString(dsGroup, "./sampletype");
	SampleData* newSample = 0;
	if (sampleType == "SampleData") {
		newSample = new SampleData<Representer>(representer);
	}
	else if (sampleType == "SampleDataWithSurrogates") {
		newSample = new SampleDataWithSurrogates<Representer>(representer);
	}
	else {
		throw StatisticalModelException((std::string("Unknown sampletype in hdf5 group: ") +sampleType).c_str());
	}
	newSample->LoadInternal(dsGroup);
	return newSample;
}

template <class Representer>
void
SampleData<Representer>::Save(const H5::Group& dsGroup) const {
	if (dynamic_cast<const SampleDataWithSurrogates<Representer>* >(this) != 0) {
		HDF5Utils::writeString(dsGroup, "./sampletype", "SampleDataWithSurrogates");
	}
	else {
		HDF5Utils::writeString(dsGroup, "./sampletype", "SampleData");
	}
	SaveInternal(dsGroup);
}

}

#endif // __SAMPLE_DATA_TXX
