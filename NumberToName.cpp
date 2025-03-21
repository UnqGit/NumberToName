#include <iostream>
#include <vector>
#include <cmath>
#include <cctype>
#include <sstream>
#include <string>
using namespace std;

const string ones[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
const string suffix[] = {"", "Thousand", "Million", "Billion", "Trillion", "Quadrillion", "Quintillion", "Sextillion", "Septillion", "Octillion", "Nonillion"};
const string majSuffix[] = {"Decillion", "Vigintillion", "Trigintillion", "Quadragintillion", "Quinquagintillion", "Sexagintillion", "Septuagintillion", "Octogintillion", "Nonagintillion"};
const string tens[] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const string prefix[] = {"", "Un", "Duo", "Tre", "Quatuor", "Quint", "Sex", "Septen", "Octo", "Novem"};

string suffix_adder(int i){
  if(i < 11) return (" "+suffix[i]);
  i-=11;
  string pre = prefix[i%10];
  string suf = majSuffix[i/10];
  if(pre.length()>0) suf[0] = tolower(suf[0]);
  string result = " "+pre+suf;
  return result;
} 

string fractional_helper(string& str){
  if(str.length()<1)return "";
  string result = "Point";
  for(int i = 0; i < str.length(); i++){
    char k = str[i];
    result += " " + ones[(int)(k-'0')];
  }
  return result;
}

string space(string result){
  return result.length()>1 ? " ":"";
}

string helper(int num){
  if(num==0) return "";
  string result = "";
  if(num >= 100){
    result += ones[num/100] + " Hundred";
    num%=100;
  }
  if(num >= 20){
    result += space(result) + tens[num/10];
    num%=10;
    if(num>0) result += space(result) + ones[num];
    num=0;
  }
  if(num > 0) result += space(result) + ones[num%20];
  return result;
}

string BeforeInt(string num){
  string result = "";
  if(num == "0") result = "Zero";
  vector<int> more;
  string toadd="";
  for(int i = num.length()-1; i >= 0; i--){
    toadd = num[i] + toadd;
    if(toadd.length()==3||i==0){
      int newnum = stoi(toadd);
      toadd = "";
      more.push_back(newnum);
    }
  }
  for(int i = 0; i < more.size(); i++){
    if(more[i]>0)result = helper(more[i]) + suffix_adder(i) + space(result) + result; 
  }
  return result;
}

void input_corrector(string& input){
  string sign;
  input.erase(0, input.find_first_not_of(" \t\n"));
  input.erase(input.find_last_not_of(" \t\n")+1);
  if(input[0]=='-'||input[0]=='+'){
    sign = input[0];
    input.erase(0, 1);
  }
  input.erase(0, input.find_first_not_of(" 0\t\n"));
  input = sign + input;
}

int input_checker(string input){
  bool decimalPoint = false;
  for(int i = 0; i < input.size(); i++){
    if(!isdigit(input[i])){
      if(input[i] == '.' && !decimalPoint)decimalPoint = true;
      else if((input[i] == '-' || input[i] == '+') && i == 0)continue;
      else return 0;
    }
  }
  int i=0;
  for(int u=0; u<input.size(); u++){
    if(isdigit(input[u])) i++;
    if(input[u]=='.')break;
  }
  if(i>303) return 1;
  return 2;
}

void numToName(string input){
  stringstream ss(input);
  string integer, decimal, result, presentation;
  bool neg = false;
  getline(ss, integer, '.');
  getline(ss, decimal);
  decimal.erase(decimal.find_last_not_of("0")+1);
  if(!isdigit(integer[0])){
    if(integer[0]=='-') neg = true;
    integer.erase(0,1);
  }
  if(integer.length()<1) integer="0";
  result = BeforeInt(integer);
  if(decimal.length()!=0) result += " " + fractional_helper(decimal);
  if(result!="Zero"){
    if(neg)result = "Negative " + result;
  }
  stringstream sd(result);
  int i = 0;
  while(sd >> presentation){
    i+=presentation.length();
    cout << presentation << " ";
    if(i>60){
      cout << "\n";
      i = 0;
    }
  }
}

int main(){
  while(true){
    string input;
    cout << "Enter your number: ";
    getline(cin, input);
    input_corrector(input);
    int l = input_checker(input);
    while(l!=2){
      if(l==0) cout << "Not a valid number.\n";
      else cout << "Number too big for this program.\n";
      cout << "\nEnter again: ";
      getline(cin, input);
      input_corrector(input);
      l = input_checker(input);
    }
    numToName(input);
    cout << "\n\n";
  }
}
