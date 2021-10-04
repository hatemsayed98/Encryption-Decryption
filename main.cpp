#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
using namespace std;
class Cipher
{

private:
    static void toUpper(string &msg)
    {
        for(int i = 0; i < msg.length(); i++)
        {
            if (msg[i] >= 'a' && msg[i] <= 'z')
            {
                msg[i] -= 'a' ;
                msg[i] += 'A';
            }
        }
    }
    static  string decToBinary(int n)
    {
        string binarySequence ="";
        while (n > 0)
        {

            binarySequence += to_string(n % 2);
            n = n / 2;
        }
        return binarySequence;
    }
    static string replaceBinaryWithAB(string binarySequence)
    {
        string a_b_ReplacedSequence = "";
        for(int i = 4; i >= 0; i--)
        {
            if(i >= binarySequence.length() )
            {
                a_b_ReplacedSequence += 'a';
                continue;
            }


            if(binarySequence[i] =='1')
                a_b_ReplacedSequence += 'b';
            else
                a_b_ReplacedSequence += 'a';
        }
        return a_b_ReplacedSequence;
    }
    static string replaceABWithBinary(string a_b_Sequence)
    {
        string binarySequence = "";
        for(int i = 0; i<a_b_Sequence.length(); i++)
        {
            if(a_b_Sequence[i] =='b')
                binarySequence += '1';
            else
                binarySequence += '0';
        }
        return binarySequence;
    }
    static int binaryToDecimal(string num)
    {
        int dec_value = 0;

        int base = 1;

        int len = num.length();
        for (int i = len - 1; i >= 0; i--)
        {
            if (num[i] == '1')
                dec_value += base;
            base = base * 2;
        }
        return dec_value;
    }
    static int getPosition(const char *array, size_t size, char c)
    {
        const char* end = array + size;
        const char* match = std::find(array, end, c);
        return (end == match)? -1 : (match-array);
    }

    static  map<char, string> getMorseTable()
    {
        const map<char, string> lookup =
        {
            {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},
            {'E', "."},     {'F', "..-."},   {'G', "--."},   {'H', "...."},
            {'I', ".."},    {'J', ".---"},  {'K', "-.-"},  {'L', ".-.."},
            {'M', "--"},    {'N', "-."},    {'O',   "---"}, {'P', ".--."},
            {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
            {'U', "..-"},   {'V',  "...-"}, {'W', ".--"},  {'X',  "-..-"},
            {'Y', "-.--"},  {'Z', "--.."},
            {'0', "-----"}, {'1',".----"},  {'2',"..---"},  {'3',"...--"},
            {'4',"....-"},  {'5',"....."},  {'6',"-...."}, {'7',"--..."},
            {'8',"---.."},  {'9',"----."},  {',',"--..--"}, {'.',".-.-.-"},
            {'?',"..--.."}, {'/',"-..-."},  {'-',"-....-"},{'(',"-.--."},
            {')',"-.--.-"}
        };
        return lookup;
    }
    static char getKeyByValueMap(  map<char, string> Map, string value)
    {
        for (auto& it : Map)
        {
            if (it.second == value)
                return  it.first ;
        }
        return NULL;
    }

    static int hexToDecimal(string hexVal)
    {
        int len = hexVal.length();

        int base1 = 1;

        int dec_val = 0;

        for (int i = len - 1; i >= 0; i--)
        {
            if (hexVal[i] >= '0' && hexVal[i] <= '9')
            {
                dec_val += (hexVal[i] - '0') * base1;

                base1 = base1 * 16;
            }

            else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
            {
                dec_val += (hexVal[i] - 'A' + 10) * base1;

                base1 = base1 * 16;
            }
        }
        return dec_val;
    }
    static void reverseStr(string& str)
    {
        int n = str.length();
        for (int i = 0; i < n / 2; i++)
            swap(str[i], str[n - i - 1]);
    }
    static string decToHexa(int s)
    {
        int n = s;
        string hexaDeciNum;
        while (n != 0)
        {
            int temp = 0;
            temp = n % 16;
            if (temp < 10)
            {
                hexaDeciNum+= temp + '0' ;

            }
            else
            {
                hexaDeciNum += temp + 'A' - 10;
            }
            n = n / 16;
        }

        reverseStr(hexaDeciNum);
        return hexaDeciNum;
    }
public :
    Cipher() {}

    static string affineEncode(string msg, int a, int b)
    {
        toUpper(msg);
        string encoded = "";
        for(int i = 0; i < msg.length(); i++)
        {
            if(msg[i] == ' ')
                encoded += msg[i];
            else
                encoded += (((((msg[i] - 'A') * a) + b) % 26) + 'A');
        }
        return encoded;
    }

    static string affineDecode(string msg, int a, int b)
    {
        toUpper(msg);
        int c;
        for(int i = 0; i < 26; i++)
        {
            int temp_c = (a * i) % 26;
            if(temp_c == 1)
            {
                c = i;
                break;
            }
        }

        string decoded = "";
        for(int i = 0; i < msg.length(); i++)
        {
            if(msg[i] ==' ')
                decoded += ' ';
            else
                decoded += (c * (msg[i] + 'A' - b) % 26) + 'A';
        }
        return decoded;
    }

    static string ceasarEncode(string msg, int shifts, bool rightShift)
    {
        string encoded = "";
        for(int i = 0; i < msg.length(); i++)
        {
            if(msg[i] == ' ')
            {
                encoded += ' ';
                continue;
            }

            char a_or_A ;
            char z_or_Z;
            if(msg[i] >= 'A' && msg[i] <= 'Z')
            {
                a_or_A = 'A';
                z_or_Z = 'Z';
            }
            else
            {
                a_or_A = 'a';
                z_or_Z = 'z';
            }

            if(rightShift)
            {
                encoded += ((msg[i] - a_or_A + shifts) % 26) + a_or_A;
            }

            else
            {
                char decodedChar = ((msg[i] - a_or_A) - shifts) % 26 + a_or_A ;
                if(decodedChar < a_or_A)
                    decodedChar = decodedChar - a_or_A + z_or_Z + 1;
                encoded += decodedChar;
            }
        }
        return encoded;
    }

    static string ceasarDecode(string msg, int shifts, bool rightShift)
    {
        return ceasarEncode(msg, shifts, !rightShift);
    }
    static string atbashEncode(string msg)
    {
        string encode ="";
        for(int i = 0; i < msg.length(); i++)
        {
            int halfAlphabet = 12;
            if(msg[i] >= 'A' && msg[i] <= 'Z')
            {
                encode += (char)(halfAlphabet + (halfAlphabet - (msg[i] - 'A')) +1 + 'A');
            }
            else
            {
                encode += (char)(halfAlphabet + (halfAlphabet - (msg[i] - 'a')) +1 + 'a');
            }
        }
        return encode;
    }
    static string atbashDecode(string msg)
    {
        return atbashEncode(msg);
    }
    static string rot13Encode(string msg)
    {
        string encode = "";
        for(int i = 0; i < msg.length(); i++)
        {
            if(msg[i] >= 'A' && msg[i] <= 'Z')
                encode += ((msg[i] - 'A' + 13)% 26)+'A';
            else
                encode += ((msg[i] - 'a' + 13)% 26)+'a';
        }
        return encode;
    }
    static string baconianEncode(string msg)
    {
        string encode="";
        for(int i = 0; i < msg.length(); i++)
        {
            if(msg[i] == ' ')
            {
                encode += ' ';
                continue;
            }
            if(msg[i] >= 'A' && msg[i] <= 'Z')
                encode += replaceBinaryWithAB( decToBinary(msg[i] - 'A'));
            else
                encode += replaceBinaryWithAB( decToBinary(msg[i] - 'a'));
            encode += ' ';
        }
        return encode;
    }
    static string baconianDecode(string msg)
    {
        string decode="";
        string a_b_Sequence = "";
        int counter = 0;
        for(int i = 0; i < msg.length(); i++)
        {
            if(i == msg.length() - 1 )
            {
                a_b_Sequence += msg[i];
                counter++;
            }
            if(msg[i]==' ')
            {
                decode += (char)(binaryToDecimal(replaceABWithBinary(a_b_Sequence)) + 'A');
                counter =0;
                a_b_Sequence ="";
                continue;
            }
            if(counter == 5 )
            {
                decode += (char)(binaryToDecimal(replaceABWithBinary(a_b_Sequence)) + 'A');
                counter =0;
                a_b_Sequence ="";
            }
            counter ++;
            a_b_Sequence += msg[i];
        }
        return decode;
    }
    static string simpleSubstitutionEncode(string msg, string keyWord)
    {
        string encode = "";
        toUpper(keyWord);
        toUpper(msg);
        char keyAlphabet[26];
        for(int i =0; i < keyWord.length(); i++)
        {
            keyAlphabet[i] = keyWord[i];
        }

        int indexInKey = keyWord.length();
        for(int i ='A'; i <= 'Z' ; i++)
        {
            if (keyWord.find(i) != std::string::npos)
                continue; // found
            else
            {
                keyAlphabet[indexInKey] = i;
                indexInKey++;
            }
        }

        for(int i = 0; i < msg.length(); i++)
        {
            if(msg[i] ==' ')
            {
                encode += ' ';
                continue;
            }

            encode += keyAlphabet[(int)(msg[i] - 'A')];
        }
        return encode;
    }

    static string simpleSubstitutionDecode(string msg, string keyWord)
    {
        string decode = "";
        toUpper(keyWord);
        toUpper(msg);
        char keyAlphabet[26];
        for(int i =0; i < keyWord.length(); i++)
        {
            keyAlphabet[i] = keyWord[i];
        }

        int indexInKey = keyWord.length();
        for(int i ='A'; i <= 'Z' ; i++)
        {
            if (keyWord.find(i) != std::string::npos)
                continue; // found
            else
            {
                keyAlphabet[indexInKey] = i;
                indexInKey++;
            }
        }

        for(int i = 0; i < msg.length(); i++)
        {
            if(msg[i] ==' ')
            {
                decode += ' ';
                continue;
            }
            decode += getPosition(keyAlphabet, 26, msg[i]) + 'A';
        }
        return decode;
    }

    static string polybiusSquareEncoder(string msg)
    {
        toUpper(msg);
        string encode ="";
        for(int i =0; i < msg.length(); i++)
        {
            if(msg[i]==' ')
            {
                encode += ' ';
                continue;
            }
            int row, col;
            row = ((msg[i] - 'A') / 5)+1;
            col = ((msg[i] - 'A') % 5)+1;
            encode += row + '0';
            encode += col + '0';
        }
        return encode;
    }
    static string polybiusSquareDecoder(string msg)
    {
        toUpper(msg);
        string decode ="";
        for(int i =0; i < msg.length(); i+=2)
        {
            if(msg[i]==' ')
            {
                decode+=' ';
                i--;
                continue;
            }
            int row = (msg[i] - '0');
            int col = (msg[i+1]- '0');

            decode += (((row-1) * 5)
                       + (col -1))
                      + 'A';
        }
        return decode;
    }
    static string morseCodeEncoder(string msg)
    {
        toUpper(msg);
        string encode ="";
        int len = msg.length();
        map<char, string> lookup = getMorseTable();

        for(int i =0; i < len; i++)
        {
            if(msg[i] ==' ')
            {
                encode += "   ";
                continue;
            }
            auto itr = lookup.find(msg[i]);
            encode += itr->second;
            if(i != msg.length()-1 && msg[i+1] != ' ')
                encode += ' ';
        }
        return encode;
    }



    static string morseCodeDecoder(string msg)
    {
        map<char, string> lookup = getMorseTable();
        string decode ="";
        int len = msg.length();
        string code = "";
        for(int i =0; i< len; i++)
        {
            if(i == len -1)
                code+= msg[i];
            if(msg[i] == ' ' ||i == len -1)
            {
                char decodedValue = getKeyByValueMap(lookup, code);

                if(decodedValue != NULL)
                    decode += decodedValue;
                code ="";
                if(i< len - 2&& msg[i] == ' ' && msg[i+1] == ' ' && msg[i+2] ==' ')
                {
                    decode += ' ';
                    i+=2;
                }
            }
            else
                code+= msg[i];
        }
        return decode;
    }

    static string xorHexEncode(string msg, char key)
    {
        string encode ="";
        int len = msg.length();
        for(int i= 0; i< len; i++)
        {
            if(msg[i]==' ')
                encode += ' ';
            else
                encode +=( msg[i] ^key);
        }
        string encodeInHex = "";
        len = encode.length();
        for(int i= 0; i< len; i++)
        {
            if(encode[i]==' ')
                encodeInHex += ' ';
            else
            {
                encodeInHex += decToHexa((int)encode[i]);
                encodeInHex += ' ';
            }
        }

        return encodeInHex;
    }

    static string xorHexDecode(string msg, char key)
    {
        string decode ="";
        string decimalMsg = "";
        string hexEncoded ="";

        int counter =0;
        int len = msg.length();
        for(int i= 0; i< len; i++)
        {

            if(msg[i]==' ')
            {

                decimalMsg += hexToDecimal(hexEncoded);

                hexEncoded = "";
                counter =0;
                if(i <len-1 && msg[i]==' ' && msg[i+1] ==' ')
                {
                    i++;
                    decimalMsg += ' ';
                }
            }
            else if(i == len -1)
            {
                hexEncoded+= msg[i];
                decimalMsg += hexToDecimal(hexEncoded);
                hexEncoded = "";
                counter =0;
            }
            else if( counter == 8)
            {
                i--;
                decimalMsg += hexToDecimal(hexEncoded);
                hexEncoded = "";
                counter =0;
            }
            else
            {
                counter ++;
                hexEncoded+= msg[i];
            }
        }
        len = decimalMsg.length();
        for(int i= 0; i< len; i++)
        {
            if(decimalMsg[i]==' ')
                decode += ' ';
            else
                decode +=( decimalMsg[i] ^key);
        }
        return decode;
    }

    static string railFenceEncode(string msg, int key)
    {
        string encode ="";

        int len = msg.length();
        char railMatrix [key][len];
        for(int i=0; i < key; i++)
            for(int j = 0; j < len; j++)
                railMatrix[i][j] = '+';

        int row =0;
        bool rowDownDirection = false;
        for(int col=0; col < len; col++)
        {
            if(row == key - 1 || row <= 0)
            {
                rowDownDirection = !rowDownDirection;
            }
            railMatrix[row][col] = msg[col];
            if(rowDownDirection)
                row++;
            else
                row--;
        }

        for(int i=0; i < key; i++)
        {
            for(int j = 0; j < len; j+=1 )
            {
                if(railMatrix[i][j] != '+')
                    encode+= railMatrix[i][j];
            }
        }
        return encode;
    }

    static string railFenceDecode(string msg, int key)
    {
        string decode ="";
        int len = msg.length();
        char railMatrix [key][len];
        for(int i=0; i < key; i++)
            for(int j = 0; j < len; j++)
                railMatrix[i][j] = '-';
        int row =0;
        bool rowDownDirection = false;
        for(int col=0; col < len; col++)
        {
            if(row == key - 1 || row <= 0)
            {
                rowDownDirection = !rowDownDirection;
            }
            railMatrix[row][col] = '*';
            if(rowDownDirection)
                row++;
            else
                row--;
        }
        int col =0;
        for(int i =0; i < key; i++)
            for(int j=i; j < len; j++)
                if(railMatrix[i][j]=='*')
                    railMatrix[i][j]= msg[col++];

        row = 0;
        for( col=0; col < len; col++)
        {
            if(row == key - 1 || row <= 0)
            {
                rowDownDirection = !rowDownDirection;
            }
            decode += railMatrix[row][col] ;
            if(rowDownDirection)
                row++;
            else
                row--;
        }
        return decode;
    }
};

int main()
{
    /*string enc = Cipher::affineEncode("AFFINE affine", 5, 8);
    cout<<enc<<endl;
    cout<<Cipher::affineDecode(enc,5,8);*/

    //string caeserCipher = Cipher::ceasarEncode("ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz", 5, 1);
    //cout<<"ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz"<<endl
    // <<caeserCipher<<endl;

    //cout<<endl<<"ABCDEFGHIJKLMNOPQRSTUVWXYZ"<<endl<<endl<<Cipher::atbashEncode("ZYXWVUTSRQPONMLKJIHGFEDCBA");

    //cout<< endl<<Cipher::rot13Encode("ABCDEFGHIJKLMNOPQRSTUVWXYZpo");

    // cout<< endl<<Cipher::baconianEncode("ABCDEFGHIJKLMNOPQRSTUVWXYZpo");
    //cout<< Cipher::baconianDecode("baaba bbaab abbaabbaaa");
    //cout<<Cipher::simpleSubstitutionEncode("I love C plus PLUS", "ZebrA")<<endl;
    //cout<<Cipher::simpleSubstitutionDecode("g jmua b njtq njtq", "ZebrA");
    //cout<<Cipher::polybiusSquareDecoder(Cipher::polybiusSquareEncoder("abcde f g h i j k l m n o p q r s t u v w x y z" ));
    //cout<<Cipher::morseCodeDecoder(Cipher::morseCodeEncoder("I love C plus plus"));
    //string s = Cipher::xorHexEncode("I LIKE CbLUS bLUS",'P');
    //cout<<s<<endl<<Cipher::xorHexDecode (s,'P') ;
    string s =Cipher::railFenceEncode("defendtheeastwallofthecastle",4);
    cout<<s<<endl<<Cipher::railFenceDecode(s,4);
    return 0;
}
