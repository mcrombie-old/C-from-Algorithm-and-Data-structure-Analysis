#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <iomanip> //for setting bases
#include <stdlib.h>

/*
implements the karatsuba multiplication algorithm
*/

using namespace std;

int StrToInt(string String){
    //using a standard string to integer conversion http://stackoverflow.com/questions/7663709/convert-string-to-int-c
    int thevalue;

    std::istringstream ss(String);
    ss >> thevalue;
    return thevalue;
}
// Code inspired by example from this page: http://www.sanfoundry.com/cpp-program-convert-a-decimal-base-any-base/
int convert10tob(int N, int b)
{
     if (N == 0)
        return 0;
     int x = N % b;
     N = N / b;
     if (x < 0)
        N += 1;
     convert10tob(N, b);
     if (x < 0){
        cout<< (x + (b * -1));
     }else{
         cout<< x;
     }
     //cout<< x < 0 ? x + (b * -1) : x;
     return 0;
}

// Code inspired by example from this page: https://quickcodex.wordpress.com/2013/12/16/c-convert-a-number-from-any-base-to-decimal/
int toB10(int n, int base_of_n){
    string n_string = static_cast<ostringstream*>( &(ostringstream() << n) )->str();
    char aux[n_string.size()], *end;
    strcpy(aux,n_string.c_str());
    return strtol(aux,&end,base_of_n);

}

unsigned karatsuba(int I1, int I2, int B){
    //Converts non base 10 numbers into base 10 for the karatsuba calculation
    if (B != 10){
        I1 = toB10(I1, B);
        I2 = toB10(I2, B);
    }

    //integer to string conversion (http://www.cplusplus.com/articles/D9j2Nwbp/)
    string I1_string = static_cast<ostringstream*>( &(ostringstream() << I1) )->str();
    string I2_string = static_cast<ostringstream*>( &(ostringstream() << I2) )->str();

    int I1_length = I1_string.length(); //number of digits in each
    int I2_length = I2_string.length();
    int higher_length = fmax(I1_length, I2_length); //higher digits
    int lower_length = fmin(I1_length, I2_length); //lower digits

    int split = lower_length/2 + lower_length % 2; //will be used to multiply

    //More efficient to use basic multiplier for values less than 4
    if (lower_length < 4){
        return I1 * I2;
    }

    //This is necessary incase two numbers with odd nubmered digits are multilpied together.
    if (lower_length == higher_length and lower_length % 2 != 0){
        lower_length += 1;
    }

    //If there is an uneven number of digits, this should rectify
    if (higher_length % 2 != 0 or lower_length % 2 != 0){
        I1_string = I1_string + "0";
        I2_string = I2_string + "0";
    }

    unsigned lop = 0;
    //makes the numbers even and saves the extra numbers of a larger string to be added later.
    if (I1_length != I2_length){
        if (I1_length < I2_length){
            int lop_length = I2_length - I1_length;
            string lop_string = I2_string.substr(0,lop_length);
            lop = StrToInt(lop_string) * pow(10,lower_length) * I1;
            I2_string = I2_string.substr(lop_length, 1000);
        }
        if (I2_length < I1_length){
            int lop_length = I1_length - I2_length;
            string lop_string = I1_string.substr(0,lop_length);
            lop = StrToInt(lop_string) * pow(10,lower_length) * I2; //use recursion here!
            I1_string = I1_string.substr(lop_length, 1000);
        }
    }

    //converts to strings of even sizes
    string a_str = I1_string.substr(0,split);
    string b_str = I1_string.substr(split,split);
    string c_str = I2_string.substr(0,split);
    string d_str = I2_string.substr(split,split);

    //converts to numbers
    unsigned a = StrToInt(a_str);
    unsigned b = StrToInt(b_str);
    unsigned c = StrToInt(c_str);
    unsigned d = StrToInt(d_str);

    //recursive karatsuba multiplications
    unsigned m = karatsuba(a,c, B);
    unsigned m2 = karatsuba(b,d, B);
    unsigned m3 = karatsuba(a + b, c + d, B);

    //possibly unneseccary simplified values
    unsigned w = m * pow(10, lower_length);
    unsigned w2 = m2;
    unsigned w3 = (m3-m2-m) * pow(10, split);//(14040 - 4984 - 2278) * 100;

    //final result
    unsigned result = w + w2 + w3 + lop;
    unsigned result_int = result;

    return result_int;
}

int school_add(int I1, int I2, int B){
     //integer to string conversion (http://www.cplusplus.com/articles/D9j2Nwbp/)
    string I1_string = static_cast<ostringstream*>( &(ostringstream() << I1) )->str();
    string I2_string = static_cast<ostringstream*>( &(ostringstream() << I2) )->str();

    int c = 0;
    int counter = 0; //sets counter variable
    int length = 0; //assume length to start at 0

    if (I1_string.length() != I2_string.length()){
        if (I1_string.length() > I2_string.length()){
            length = I1_string.length();
        } else {
            length = I2_string.length();
        }
    }else{
        length = I1_string.length();
    }

    int Array[length];
    int I1_int = 0;
    int I2_int = 0;
    int I1_length1 = I1_string.length();
    int I2_length2 = I2_string.length(); //these things

    for (int n = length; n > 0; n--){

         if (counter >= I1_length1){
            I1_int = 0;
         }else{
            char I1_char = I1_string[I1_string.length() - 1 - counter];
            I1_int = I1_char - '0';
         }

         if (counter >= I2_length2){
            I2_int = 0;
         }else{
            char I2_char = I2_string[I2_string.length() - 1 - counter];
            I2_int = I2_char - '0';
         }

         int digit = I1_int + I2_int + c;

         if (digit > B-1){
            int newdigit = digit % B;
            Array[counter] = newdigit;
            c = 1;
         }else {
             Array[counter] = digit;
             c = 0;
         }

         counter += 1;

         if (counter == length){
            if (c==1){
                Array[counter] = 1;
                length += 1; //sets the length 1 higher so if the added numbers have more digits thnan the last, it includes the first sigit9
            }
         }

    }

    string result = "";

    for (int x=0; x<length; x++){
        int z = Array[x];
        string z_string = static_cast<ostringstream*>( &(ostringstream() << z) )->str();
        result += z_string;
    }
    result = string(result.rbegin(),result.rend());
    int result_int = StrToInt(result);
    return result_int;
    return 0;
}

int main()
{
    int I1;
    int I2;
    int B;

    cin >> I1 >> I2 >> B;

    cout<<school_add(I1, I2, B);
    cout<<" ";

    if (B == 10){
        cout<<karatsuba(I1, I2, B);
    }else{
        convert10tob(karatsuba(I1, I2, B), B);
    }

    return 0;
}
