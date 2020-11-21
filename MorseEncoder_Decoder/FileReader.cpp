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
#include <list>
#include "FileReader.h"
namespace MorseCodes
{
    inline constexpr int16 Short{'*'};
    inline constexpr int16 Long{'-'};
    inline constexpr int16 NewWord{'|'};
    inline constexpr int16 SeparateChar{'&'};
    inline constexpr char Unrecognized{'#'};

    inline constexpr Simd::int16_8 NullChar{0, 0, 0, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 NewWordChar{NewWord, 0, 0, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 SeparateCharacterChar{SeparateChar, 0, 0, 0, 0, 0, 0, 0};

    inline constexpr Simd::int16_8 A{Short, Long, 0, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 B{Long, Short, Short, Short, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 C{Long, Short, Long, Short, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 D{Long, Short, Short, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 E{Short, 0, 0, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 F{Short, Short, Long, Short, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 G{Long, Long, Short, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 H{Short, Short, Short, Short, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 I{Short, Short, 0, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 J{Short, Long, Long, Long, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 K{Long, Short, Long, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 L{Short, Long, Short, Short, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 M{Long, Long, 0, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 N{Long, Short, 0, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 O{Long, Long, Long, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 P{Short, Long, Long, Short, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 Q{Long, Long, Short, Long, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 R{Short, Long, Short, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 S{Short, Short, Short, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 T{Long, 0, 0, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 U{Short, Short, Long, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 V{Short, Short, Short, Long, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 W{Short, Long, Long, 0, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 X{Long, Short, Short, Long, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 Y{Long, Short, Long, Long, 0, 0, 0, 0};
    inline constexpr Simd::int16_8 Z{Long, Long, Short, Short, 0, 0, 0, 0};

    inline constexpr Simd::int16_8 Zero{Long, Long, Long, Long, Long, 0, 0, 0};
    inline constexpr Simd::int16_8 One{Short, Long, Long, Long, Long, 0, 0, 0};
    inline constexpr Simd::int16_8 Two{Short, Short, Long, Long, Long, 0, 0, 0};
    inline constexpr Simd::int16_8 Three{Short, Short, Short, Long, Long, 0, 0, 0};
    inline constexpr Simd::int16_8 Four{Short, Short, Short, Short, Long, 0, 0, 0};
    inline constexpr Simd::int16_8 Five{Short, Short, Short, Short, Short, 0, 0, 0};
    inline constexpr Simd::int16_8 Six{Long, Short, Short, Short, Short, 0, 0, 0};
    inline constexpr Simd::int16_8 Seven{Long, Long, Short, Short, Short, 0, 0, 0};
    inline constexpr Simd::int16_8 Eight{Long, Long, Long, Long, Short, 0, 0, 0};
    inline constexpr Simd::int16_8 Nine{Long, Long, Long, Long, Long, 0, 0, 0};
}

std::vector<char> DecodeMorseToPlainText(const std::string& PathToFile)
{
    constexpr auto GetCharacterFromMorse = [](const Simd::int16_8& MorseCode) -> char
    {
        using namespace MorseCodes;

        if(MorseCode == A) return 'A';
        else if(MorseCode == B) return 'B';
        else if(MorseCode == C) return 'C';
        else if(MorseCode == D) return 'D';
        else if(MorseCode == E) return 'E';
        else if(MorseCode == F) return 'F';
        else if(MorseCode == G) return 'G';
        else if(MorseCode == H) return 'H';
        else if(MorseCode == I) return 'I';
        else if(MorseCode == J) return 'J';
        else if(MorseCode == K) return 'K';
        else if(MorseCode == L) return 'L';
        else if(MorseCode == M) return 'M';
        else if(MorseCode == N) return 'N';
        else if(MorseCode == O) return 'O';
        else if(MorseCode == P) return 'P';
        else if(MorseCode == Q) return 'Q';
        else if(MorseCode == R) return 'R';
        else if(MorseCode == S) return 'S';
        else if(MorseCode == T) return 'T';
        else if(MorseCode == U) return 'U';
        else if(MorseCode == V) return 'V';
        else if(MorseCode == W) return 'W';
        else if(MorseCode == X) return 'X';
        else if(MorseCode == Y) return 'Y';
        else if(MorseCode == Z) return 'Z';
        else if(MorseCode == Zero) return '0';
        else if(MorseCode == One) return '1';
        else if(MorseCode == Two) return '2';
        else if(MorseCode == Three) return '3';
        else if(MorseCode == Four) return '4';
        else if(MorseCode == Five) return '5';
        else if(MorseCode == Six) return '6';
        else if(MorseCode == Seven) return '7';
        else if(MorseCode == Eight) return '8';
        else if(MorseCode == Nine) return '9';
        else if(MorseCode == NewWordChar) return ' ';
        else if(MorseCode == NullChar) return '#';

        return '#';
    };

    auto DecodeFile = [&GetCharacterFromMorse, &PathToFile]() -> std::vector<char>
    {
        std::fstream FStream{};

        FStream.open(PathToFile, std::ios::in);

        std::vector<char> PlainTextVector{};

        if(!FStream)
        {
            std::cerr << "Failed to open file with path: " << PathToFile << std::endl;
            return PlainTextVector;
        }

        Simd::int16_8 MorseCode{};

        for(int8 RegisterIndex{0}; !FStream.eof(); ++RegisterIndex)
        {
            char TempChar;

            FStream >> std::noskipws >> TempChar;

            if unlikely(TempChar == static_cast<char>(MorseCodes::SeparateChar))
            {
                PlainTextVector.emplace_back(GetCharacterFromMorse(MorseCode));

                MorseCode = static_cast<int16>(0);
                RegisterIndex = -1;
            }
            else if unlikely(TempChar == static_cast<char>(MorseCodes::NewWord))
            {
                PlainTextVector.emplace_back(GetCharacterFromMorse(MorseCode));
                PlainTextVector.emplace_back(' ');

                MorseCode = static_cast<int16>(0);
                RegisterIndex = -1;
            }
            else
            {
                check(RegisterIndex < 8)

                MorseCode.Register[RegisterIndex] = static_cast<int16>(static_cast<uint8>(TempChar));
            }
        }

        FStream.close();

        return PlainTextVector;
    };

    return DecodeFile();
}

std::vector<Simd::int16_8> EncodePlainTextToMorse(const std::string& PathToFile)
{
    constexpr auto GetMorseFromCharacter = [](char Character) -> Simd::int16_8
    {
        using namespace MorseCodes;

        Character -= 32 * (Character >= 'a' && Character <= 'z');

        switch(Character)
        {
            case 'A': return A;
            case 'B': return B;
            case 'C': return C;
            case 'D': return D;
            case 'E': return E;
            case 'F': return F;
            case 'G': return G;
            case 'H': return H;
            case 'I': return I;
            case 'j': return J;
            case 'K': return K;
            case 'L': return L;
            case 'M': return M;
            case 'N': return N;
            case 'O': return O;
            case 'P': return P;
            case 'Q': return Q;
            case 'R': return R;
            case 'S': return S;
            case 'T': return T;
            case 'U': return U;
            case 'V': return V;
            case 'W': return W;
            case 'X': return X;
            case 'Y': return Y;
            case 'Z': return Z;
            case '0': return Zero;
            case '1': return One;
            case '2': return Two;
            case '3': return Three;
            case '4': return Four;
            case '5': return Five;
            case '6': return Six;
            case '7': return Seven;
            case '8': return Eight;
            case '9': return Nine;
            case ' ': return NewWordChar;

            default: return NullChar;
        }
    };

    std::fstream FStream{};

    FStream.open(PathToFile, std::ios::in);

    std::vector<Simd::int16_8> MorseCodeVector{};

    if(!FStream)
    {
        std::cerr << "Failed to open file with path: " << PathToFile << std::endl;
        return MorseCodeVector;
    }

    while(!FStream.eof())
    {
        char TempChar;

        FStream >> std::noskipws >> TempChar;

        if unlikely(MorseCodeVector.emplace_back(GetMorseFromCharacter(TempChar)) == MorseCodes::NewWordChar)
        {
            MorseCodeVector.erase(MorseCodeVector.cend() - 2);
        }
        else
        {
            MorseCodeVector.emplace_back(MorseCodes::SeparateCharacterChar);
        }
    }

    MorseCodeVector.erase(MorseCodeVector.end());

    FStream.close();

    return MorseCodeVector;
}

void WriteToFile(const std::string& PathToOutFile, const std::vector<char>& StringToWrite)
{
    std::fstream FStream{};

    FStream.open(PathToOutFile, std::ios::out);

    if(!FStream)
    {
        std::cerr << "Failed to open file with path: " << PathToOutFile << std::endl;
        return;
    }

    for(const char Character : StringToWrite)
    {
        if(Character != MorseCodes::Unrecognized)
        {
            FStream << Character;
        }
    }

    FStream.close();
}

void WriteToFile(const std::string& PathToOutFile, const std::vector<Simd::int16_8>& StringToWrite)
{
    std::fstream FStream{};

    FStream.open(PathToOutFile, std::ios::out);
    
    if(!FStream)
    {
        std::cerr << "Failed to open file with path: " << PathToOutFile << std::endl;
        return;
    }

    ForEachElementNotZeroInRegisters(StringToWrite, [&FStream](const int16 Character) -> void
    {
        if(Character != MorseCodes::Unrecognized)
        {
            FStream << static_cast<char>(Character);
        }
    });

    FStream.close();
}
