/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <iostream>
#include <vector>
#include <tiff.h>
#include <fstream>
#include <string>
#include "Simd_Library-main/SimdRegisterLibrary.h"

using ByteVector = std::vector<uint8>;

ByteVector DecodeMorseToPlainText(const std::string& PathToFile);

std::vector<Simd::uint16_8> EncodePlainTextToMorse(const std::string& PathToFile);

void WriteToFile(const std::string& PathToOutFile, const ByteVector& StringToWrite);
void WriteToFile(const std::string& PathToOutFile, const std::vector<Simd::uint16_8>& StringToWrite);

template<typename RegisterType, typename Callback>
INLINE void ForEachElementNotZeroInRegisters(const std::vector<RegisterType>& VectorRegisters, Callback CallbackFunction)
{
    for(const RegisterType& Register : VectorRegisters)
    {
        for(size_t Index{0}; Index < RegisterType::GetNumElements(); ++Index)
        {
            if(Register[Index] != 0)
            {
                CallbackFunction(Register[Index]);
            }
        }
    }
}

