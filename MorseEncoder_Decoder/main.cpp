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
#include "FileReader.h"
int main(int Argc, char* Argv[])
{
    if(std::string{Argv[1]} == "-Help" || std::string{Argv[1]} == "-help")
    {
        std::cout << "<Input File> <-Decode/-Encode> <Output File> (optional) \n" << std::endl;
        std::cout << "Morse-code is written as * = short, - = long, & = new character, | = new word\n" << std::endl;
        std::cout << "Example input code: ....<....|....|....<....|....|" << std::endl;
        return 0;
    }

    if(Argc <= 3)
    {
        auto OutputAll = [](const std::vector<char>& Vector) -> void
        {
            for(const char Character : Vector)
            {
                if(Character != '#')
                {
                    std::cout << Character;
                }
            }
            std::cout << std::endl;
        };

        if(std::string{Argv[2]} == "-Decode")
        {
            OutputAll(DecodeMorseToPlainText(std::string{Argv[1]}));
        }
        else if(std::string{Argv[2]} == "-Encode")
        {
            ForEachValidElementInRegisters(EncodePlainTextToMorse(std::string{Argv[1]}), [](const uint16 Character) -> void
            {
                std::cout << static_cast<char>(Character);
            });
            std::cout << std::endl;
        }
    }
    else
    {
        if(std::string{Argv[2]} == "-Decode")
        {
            WriteToFile(std::string{Argv[3]}, DecodeMorseToPlainText(std::string{Argv[1]}));
        }
        else if(std::string{Argv[2]} == "-Encode")
        {
            WriteToFile(std::string{Argv[3]}, EncodePlainTextToMorse(std::string{Argv[1]}));
        }
    }

    return 0;
}
