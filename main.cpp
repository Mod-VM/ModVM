#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <string>
#include <stack>
#include <cstdlib>
#include "main.h"
#include "conversion.h"

enum TYPES {CHAR, INT, FLOAT, DOUBLE, STRING};
enum COMMANDS {HALT, PRTCR, PRTC, PRTI, PRTF, PRTD, PRTS, PRTAC, PRTAI, PRTAF, PRTAD, PRTAS, PUSHC, PUSHI, PUSHF, PUSHD, PUSHS, PUSHAC, PUSHAI, PUSHAF, PUSHAD, PUSHAS, PUSHKC, PUSHKI, PUSHKF, PUSHKD, PUSHKS, POPC, POPI, POPF, POPD, POPS, POPX, POPAC, POPAI, POPAF, POPAD, POPAS, RDC, RDI, RDF, RDD, RDS, RDAC, RDAI, RDAF, RDAD, RDAS, JMP, JMPEQ, JMPNE, JMPGT, JMPGE, JMPLT, JMPLE, STX, STKX, INC, DEC, ADD, SUB, MUL, DIV, MOD, CMP};
bool jmpeq, jmpne, jmpge, jmpgt, jmple, jmplt;

using namespace std;
int evindex;
char* memoryMapper;

union Data {
  int i;
  float f;
  double d;
  char* s;
};

struct StackBlock {
  char typecode;
  union Data data;
};

stack<StackBlock> theStack;

char copyright[10] = {'(','C',')','C','H','U','N','K','U','N'};
int codeSegment = 0;
int dataSegment = 0;
int someIndex = 0;
ifstream inFile;
size_t size = 0;
char* oData = 0;
char* youAreHere;

//VARIABLES FOR FUNCTIONS
int tempAddress;
StackBlock tempBlock = {};
int tempInteger;
char* tempPointer;
string tempString;
bool errorFlag = false;
float tempFloat;
double tempDouble;

int cmpeval, arrindex;

int main() {

  fileOpen();

  copyrightCheck();

  while(true && !errorFlag) {
      StackBlock reset = {};
      tempBlock = reset;
      //reading example, plz test
      printf("\nNEXT BYTE hex: %x, dec: %d\n", youAreHere[evindex], youAreHere[evindex]);
      //cout << oData[i] << " + 'a' = " << (oData[i] + 'a');
      //cout << ('a') << endl;
      //cout << "\n\n";


      switch(youAreHere[evindex++]){
        case PRTCR:
          cout << "\n";
        break;
        case PRTC: prtcFunc();
        break;
        case PRTI: prtiFunc();
        break;
        case PRTF: prtfFunc();
        break;
        case PRTD:prtdFunc();
        break;
        case PRTS: prtsFunc();
        break;
        case PRTAC: prtacFunc();
        break;
        case PRTAI: prtaiFunc();
        break;
        case PRTAF: prtafFunc();
        break;
        case PRTAD: prtadFunc();
        break;
        case PRTAS: prtasFunc();
        break;
        case PUSHC: pushcFunc();
        break;
        case PUSHI: pushiFunc();
        break;
        case PUSHF: pushfFunc();
        break;
        case PUSHD: pushdFunc();
        break;
        case PUSHS: pushsFunc();
          break;
        case PUSHAC: pushacFunc();
        break;
        case PUSHAI: pushaiFunc();
        break;
        case PUSHAF: pushafFunc();
        break;
        case PUSHAD: pushadFunc();
        break;
        case PUSHAS: pushasFunc();
        break;
        case PUSHKC: pushkcFunc();
        break;
        case PUSHKI: pushkiFunc();
        break;
        case PUSHKF: pushkfFunc();
        break;
        case PUSHKD: pushkdFunc();
        break;
        case PUSHKS: pushksFunc();
        break;
        case POPC: popcFunc();
        break;
        case POPI: popiFunc();
        break;
        case POPF: popfFunc();
        break;
        case POPD: popdFunc();
        break;
        case POPS: popsFunc();
        break;
        case POPX: if(!popxFunc()) return 1;
        break;
        case POPAC: popacFunc();
        break;
        case POPAI: popaiFunc();
        break;
        case POPAF: popafFunc();
        break;
        case POPAD: popadFunc();
        break;
        case POPAS: popasFunc();
        break;
        case RDC: if(!rdcFunc()) return 1;
        break;
        case RDI: rdiFunc();
        break;
        case RDF: rdfFunc();
        break;
        case RDD: rddFunc();
        break;
        case RDS: rdsFunc();
        break;
        case RDAC: if(!rdacFunc()) return 1;
        break;
        case RDAI: rdaiFunc();
        break;
        case RDAF: rdafFunc();
        break;
        case RDAD: rdadFunc();
        break;
        case RDAS: rdasFunc();
        break;
        case JMP: jmpFunc();
        break;
        case JMPEQ: jmpeqFunc();
        break;
        case JMPNE: jmpneFunc();
        break;
        case JMPGT: jmpgtFunc();
        break;
        case JMPGE: jmpgeFunc();
        break;
        case JMPLT: jmpltFunc();
        break;
        case JMPLE: jmpleFunc();
        break;
        case STX: stxFunc();
        break;
        case STKX: stkxFunc();
        break;
        case INC: incFunc();
        break;
        case DEC: decFunc();
        break;
        case ADD: if(!addFunc()) return 1;
        break;
        case SUB: if(!subFunc()) return 1;
        break;
        case MUL: if(!mulFunc()) return 1;
        break;
        case DIV: if(!divFunc()) return 1;
        break;
        case MOD: if(!modFunc()) return 1;
        break;
        case CMP: cmpFunc();
        break;
        case HALT: system("pause");
          return 0;
        break;
        default: cout << "ERROR: Unrecognized Command.";
        break;
      }
    }
    return 1;
}  //int main()

void pushasFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]) + arrindex;
  evindex += 2;
  int length = strlen(&memoryMapper[tempAddress]);
  tempPointer = (char *) malloc(length + 1);
  strcpy(tempPointer, &memoryMapper[tempAddress]);
  tempBlock.typecode = 's';
  tempBlock.data.s = tempPointer;
  tempBlock.data.s[length] = '\0';
  theStack.push(tempBlock);
}  //void pushasFunc()

void popasFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]) + arrindex;
  evindex += 2;
  tempBlock = theStack.top();
  theStack.pop();
  tempPointer = (char*)tempBlock.data.s;
  if(tempBlock.typecode == 's')
  {
    int ind;
    for(ind = 0; tempPointer[ind] != '\0'; ind++)
      memoryMapper[tempAddress + ind] = tempPointer[ind];
    memoryMapper[tempAddress + ind] = '\0';
  }
}  //void popasFunc()

void prtasFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]) + arrindex;
  evindex += 2;
  for (int i = 0; memoryMapper[tempAddress + i] != '\0'; ++i)
    std::cout << memoryMapper[tempAddress + i];
}  //void prtasFunc()

void rdasFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]) + arrindex;
  evindex += 2;
  std::cin >> tempString;
  tempPointer = (char*) malloc(tempString.length()+1);
  strcpy(tempPointer, tempString.c_str());
  for(int ind = 0; ind < tempString.length(); ind++)
    memoryMapper[tempAddress++] = tempPointer[ind];
  memoryMapper[tempAddress] = '\0';
}  //void rdasFunc()

void popaiFunc()  //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  tempBlock = theStack.top();
  if(theStack.top().typecode == 'i')
  {
    tempInteger = tempBlock.data.i;
    tempPointer = inttochar(tempInteger);
    theStack.pop();
    for(int ind = 0; ind < 4; ind++)
      memoryMapper[tempAddress++] = tempPointer[ind];
    std::cout << chartoint(&memoryMapper[(tempAddress-4)]) << std::endl;
  }
}  //void popaiFunc()

void pushaiFunc()  //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  tempBlock.typecode = 'i';
  tempBlock.data.i = chartoint(&memoryMapper[tempAddress]);
  theStack.push(tempBlock);
}  //void pushai()

void stxFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  arrindex = chartoint(&memoryMapper[tempAddress]);
  std::cout << "this is the index: " << arrindex << std::endl;
}  //void stxFunc()

void stkxFunc() //isai
{
  arrindex = chartoint(&youAreHere[evindex]);
  evindex += 4;
}  //void stkxFunc()

bool popxFunc() //isai
{
  if(!theStack.empty() && theStack.top().typecode == 'i')
  {
    arrindex = theStack.top().data.i;
    theStack.pop();
    return true;
  }
  std::cout << "array index error!";
  return false;
}  //bool popxFunc()

void rddFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  std::cin >> tempDouble;
  tempPointer = doubletochar(tempDouble);
  for(int someIndex = 0; someIndex < 8; someIndex++)
    memoryMapper[someIndex++] = tempPointer[someIndex];
}  //void rddFunc()

void rdfFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  std::cin >> tempFloat;
  tempPointer = floattochar(tempFloat);
  for(int someIndex = 0; someIndex < 4; someIndex++)
    memoryMapper[tempAddress++] = tempPointer[someIndex];
}  //void rdfFunc()

bool rdcFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  getline(cin,tempString);
  if(tempString.length() > 1)
  {
    std::cout << "char overflow! \n";
    return false;
  }
  memoryMapper[tempAddress] = tempString[0];
  return true;
}  //void rdcFunc()

void pushdFunc() //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempBlock.typecode = 'd';
  tempBlock.data.d = chartodouble(&memoryMapper[tempAddress]);
  theStack.push(tempBlock);
}  //void pushkdFunc()

void pushfFunc()  //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempBlock.typecode = 'f';
  tempBlock.data.f = chartofloat(&memoryMapper[tempAddress]);
  theStack.push(tempBlock);
}  //void pushfFunc()

void pushcFunc()  //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempBlock.typecode = 's';
  tempBlock.data.s = new char[1];
  tempBlock.data.s[0] = memoryMapper[tempAddress];
  theStack.push(tempBlock);
}  //void pushcFunc()

void pushkdFunc()  //isai
{
  tempBlock.data.d = chartodouble(&youAreHere[evindex]);
  evindex += 8;
  tempBlock.typecode = 'd';
  theStack.push(tempBlock);
}  //void pushkdFunc()

void popdFunc()  //isai
{
  if(!theStack.empty())
  {
    tempAddress = chartodir(&youAreHere[evindex]);
    evindex += 2;
    tempBlock = theStack.top();
    if(theStack.top().typecode == 'd')
    {
      tempDouble = tempBlock.data.d;
      tempPointer = doubletochar(tempDouble);
      theStack.pop();
      for(int ind = 0; ind < 8; ind++)
        memoryMapper[tempAddress++] = tempPointer[ind];
    }
  }
}  //void popdFunc()

void prtdFunc()  //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  std::cout << chartodouble(&memoryMapper[tempAddress]);
}  //void prtdFunc()

void pushkfFunc()  //isai
{
  tempBlock.typecode = 'f';
  tempBlock.data.f = chartofloat(&youAreHere[evindex]);
  evindex += 4;
  theStack.push(tempBlock);
}  //void pushkfFunc()

void pushiFunc()  //marin
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempBlock.typecode = 'i';
  tempBlock.data.i = chartoint(&memoryMapper[tempAddress]);
  theStack.push(tempBlock);
}  //void pushiFunc()

void pushsFunc()
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  int length = strlen(&memoryMapper[tempAddress]);
  tempPointer = (char *) malloc(length + 1);
  strcpy(tempPointer, &memoryMapper[tempAddress]);
  tempBlock.typecode = 's';
  tempBlock.data.s = tempPointer;
  theStack.push(tempBlock);
}  //void pushsFunc()

void pushkcFunc()  //isai
{
  tempBlock.typecode = 's';
  tempBlock.data.s = new char[1];
  tempBlock.data.s[0] = youAreHere[evindex];
  evindex++;
  theStack.push(tempBlock);
}  //void pushkcFunc()

void pushkiFunc()  //marin
{
  tempBlock.typecode = 'i';
  tempBlock.data.i = chartoint(&youAreHere[evindex]);
  evindex += 4;
  theStack.push(tempBlock);
}  //void pushkiFunc()

void pushksFunc()
{
  tempInteger = youAreHere[evindex++];
  tempPointer = (char*)malloc(tempInteger+1);
  strncpy(tempPointer,&youAreHere[evindex],tempInteger);
  evindex += tempInteger;
  tempBlock.typecode = 's';
  tempBlock.data.s = tempPointer;
  theStack.push(tempBlock);
}  //void pushksFunc()

void popfFunc() //isai
{
  if(!theStack.empty())
  {
    tempAddress = chartodir(&youAreHere[evindex]);
    evindex += 2;
    tempBlock = theStack.top();
    if(tempBlock.typecode = 'f')
    {
      theStack.pop();
      tempFloat = tempBlock.data.f;
      tempPointer = floattochar(tempFloat);
      for(someIndex = 0; someIndex < 4; someIndex++)
        memoryMapper[tempAddress++] = tempPointer[someIndex];
    }
  }
}  //void popfFunc()

void popcFunc()  //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempBlock = theStack.top();
  if(tempBlock.typecode = 's')
  {
    theStack.pop();
    tempPointer = new char[1];
    tempPointer[0] = tempBlock.data.s[0];
    memoryMapper[tempAddress] = tempPointer[0];
  }
}  //void popcFunc()

void popiFunc()
{
  if(!theStack.empty()) {
    tempAddress = chartodir(&youAreHere[evindex]);
    evindex = evindex + 2;
    tempBlock = theStack.top();
    if(tempBlock.typecode = 'i') {
      theStack.pop();
      tempInteger = tempBlock.data.i;
      tempPointer = inttochar(tempInteger);
      for(someIndex = 0; someIndex < 4; someIndex++)
        memoryMapper[tempAddress++] = tempPointer[someIndex];
    }
  }
}  //void popiFunc()

void rdiFunc()  //marin
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex+=2;
  cin >> tempInteger;
  tempPointer = inttochar(tempInteger);
  for(someIndex = 0; someIndex < 4; someIndex++)
    memoryMapper[tempAddress++] = tempPointer[someIndex];
}  //void rdiFunc()

void rdsFunc()
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex+=2;
  getline(cin,tempString);
  for(someIndex = 0; someIndex<tempString.length(); someIndex++)
    memoryMapper[tempAddress++] = tempString[someIndex];
  memoryMapper[tempAddress] = '\0';
}  //void rdsFunc()

void jmpFunc()
{
  evindex = chartodir(&youAreHere[evindex]) + 14;
}  //void jmp

void jmpeqFunc()
{
  if(cmpeval == 0)
    evindex = chartodir(&youAreHere[evindex]) + 14;
  else
    evindex+=2;
}  //void jmpeqFunc()

void jmpneFunc()
{
  if(cmpeval != 0)
    evindex = chartodir(&youAreHere[evindex]) + 14;
  else
    evindex+=2;
}  //void jumpneFunc()

void jmpgtFunc()
{
  if(cmpeval > 0)
    evindex = chartodir(&youAreHere[evindex]) + 14;
  else
    evindex+=2;
}  //void jmpgtFunc()

void jmpgeFunc()
{
  if(cmpeval > -1)
    evindex = chartodir(&youAreHere[evindex]) + 14;
  else
    evindex+=2;
}  //void jmpgeFunc()

void jmpltFunc()
{
  if(cmpeval < 0)
    evindex = chartodir(&youAreHere[evindex]) + 14;
  else
    evindex+=2;
}  //void jmpltFunc()

void jmpleFunc()
{
  if(cmpeval < 1)
    evindex = chartodir(&youAreHere[evindex]) + 14;
  else
    evindex+=2;
}  //void jmpleFunc()

void incFunc()
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempInteger = chartoint(&memoryMapper[tempAddress]);
  tempInteger++;
  tempPointer = inttochar(tempInteger);
  for(someIndex = 0; someIndex < 4; someIndex++)
    memoryMapper[tempAddress++] = tempPointer[someIndex];
}  //void incFunc()

void decFunc()
{
    tempAddress = chartodir(&youAreHere[evindex]);
    evindex += 2;
    tempInteger = chartoint(&memoryMapper[tempAddress]);
    tempInteger--;
    tempPointer = inttochar(tempInteger);
    for(someIndex = 0; someIndex < 4; someIndex++)
      memoryMapper[tempAddress++] = tempPointer[someIndex];
}  //void decFunc()

bool addFunc()
{
  if(theStack.size() < 2)
    return false;
  else
  {
    tempBlock = theStack.top();
    theStack.pop();
    StackBlock changeType = {};
    double newDoubleValue;
    float newFloatValue;
    switch(tempBlock.typecode)
    {
      case 'i':
        if(theStack.top().typecode == 'i')
        {
            theStack.top().data.i += tempBlock.data.i;
            break;
        }
        if(theStack.top().typecode == 'f')
        {
            changeType = theStack.top();
            theStack.pop();
            newFloatValue = changeType.data.f + tempBlock.data.i;
            tempBlock.typecode = 'f';
            tempBlock.data.f = newFloatValue;
            theStack.push(tempBlock);
            break;
        }
        if(theStack.top().typecode == 'd')
        {
            changeType = theStack.top();
            theStack.pop();
            newDoubleValue = changeType.data.d + tempBlock.data.i;
            tempBlock.typecode = 'd';
            tempBlock.data.d = newDoubleValue;
            theStack.push(tempBlock);
            break;
        }
        break;
      case 'f':
        if(theStack.top().typecode == 'f')
        {
            theStack.top().data.f += tempBlock.data.f;
            break;
        }
        if(theStack.top().typecode == 'i')
        {
            theStack.top().data.f += tempBlock.data.i;
            break;
        }
        if(theStack.top().typecode == 'd')
        {
            changeType = theStack.top();
            theStack.pop();
            newDoubleValue = changeType.data.d + tempBlock.data.d;
            tempBlock.typecode = 'd';
            tempBlock.data.d = newDoubleValue;
            theStack.push(tempBlock);
            break;
        }
      break;
      case 'd':
        if (theStack.top().typecode == 'd')
        {
            theStack.top().data.d += tempBlock.data.d;
            break;
        }
        if(theStack.top().typecode == 'i')
        {
            theStack.top().data.d += tempBlock.data.i;
            break;
        }
        if(theStack.top().typecode == 'f')
        {
            theStack.top().data.d += tempBlock.data.f;
            break;
        }
        break;
    }
  }
  return true;
}  //bool addFunc()

bool subFunc()
{
  if(theStack.size() < 2)
    return false;
  else {
    tempBlock = theStack.top();
    theStack.pop();
    switch(tempBlock.typecode) {
      case 'i':
        if(theStack.top().typecode == 'i') {
          tempBlock.data.i = theStack.top().data.i - tempBlock.data.i;
        }
      break;
      case 'f':
        if(theStack.top().typecode == 'f')
        {
          tempBlock.data.f = theStack.top().data.f - tempBlock.data.f;
        }
      break;
      case 'd':
        if(theStack.top().typecode == 'd')
        {
          tempBlock.data.d = theStack.top().data.d - tempBlock.data.d;
        }
      break;
    }
    theStack.pop();
    theStack.push(tempBlock);
  }
  return true;
}  //void subFunc()

bool mulFunc()
{
  if(theStack.size() >= 2) {
    tempBlock = theStack.top();
    theStack.pop();
    switch(tempBlock.typecode)
    {
      case 'i':
        if (theStack.top().typecode == 'i') {
          tempBlock.data.i *= theStack.top().data.i;
        }
      break;
      case 'f':
        if(theStack.top().typecode == 'f')
          tempBlock.data.f *= theStack.top().data.f;
      break;
      case 'd':
        if(theStack.top().typecode =='d')
          tempBlock.data.d *= theStack.top().data.d;
    }
    theStack.pop();
    theStack.push(tempBlock);
    return true;
  }
  return false;
}  //mulFunc()

bool divFunc()
{
  if(theStack.size() >= 2) {
    tempBlock = theStack.top();
    theStack.pop();
    switch(theStack.top().typecode)
    {
      case 'i':
        if (theStack.top().typecode == 'i')
          tempBlock.data.i = theStack.top().data.i / tempBlock.data.i;
      break;
      case 'f':
        if(theStack.top().typecode == 'f')
          tempBlock.data.f = theStack.top().data.f / tempBlock.data.f;
      break;
      case 'd':
        if(theStack.top().typecode == 'd')
          tempBlock.data.d = theStack.top().data.d / tempBlock.data.d;
      break;
    }
    theStack.pop();
    theStack.push(tempBlock);
    return true;
  }
  return false;
}  //void divFunc()

bool modFunc()
{
  // n%m
  if(theStack.size() >= 2) {
    tempBlock = theStack.top();
    theStack.pop();
    if(tempBlock.typecode == 'i') {
      if(theStack.top().typecode == 'i')
        theStack.top().data.i = (theStack.top().data.i % tempBlock.data.i);
    }
    return true;
  }
  return false;
}  //void modFunc()

void cmpFunc()
{
  tempBlock = theStack.top();
  theStack.pop();
  switch(tempBlock.typecode)
  {
    case 'i':
      if(theStack.top().typecode == 'i')
        cmpeval = 0;
        if(theStack.top().data.i > tempBlock.data.i)
          cmpeval++;
        else if(theStack.top().data.i < tempBlock.data.i)
          cmpeval--;
    break;
    case 'f':
      if(theStack.top().typecode == 'f')
        cmpeval = 0;
        if(theStack.top().data.f > tempBlock.data.f)
          cmpeval++;
        else if(theStack.top().data.f < tempBlock.data.f)
          cmpeval--;
    break;
    case 'd':
      if(theStack.top().typecode == 'd')
        cmpeval = 0;
        if(theStack.top().data.d > tempBlock.data.d)
          cmpeval++;
        else if(theStack.top().data.d < tempBlock.data.d)
          cmpeval--;
  }
  theStack.pop();
}  //cmpFunc()

void popsFunc()
{
  if(!theStack.empty())
  {
    tempAddress = chartodir(&youAreHere[evindex]);
    evindex += 2;
    tempBlock = theStack.top();
    if(tempBlock.typecode == 's')
    {
      theStack.pop();
      tempPointer = tempBlock.data.s;
      for(someIndex = 0; tempPointer[someIndex] != '\0';someIndex++)
        memoryMapper[tempAddress++] = tempPointer[someIndex];
      memoryMapper[tempAddress] = '\0';
    }
  }
}  //void popsFunc()

void prtsFunc()
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  while(memoryMapper[tempAddress] != '\0')
    cout << memoryMapper[tempAddress++];
}  //void prtsFunc()

void prtiFunc()  //marin
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  cout << chartoint(&memoryMapper[tempAddress]);
} // prtiFunc()
void prtcFunc()  //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  cout << memoryMapper[tempAddress];
}  // void prtcFunc()

void prtfFunc()  //isai
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  cout << chartofloat(&memoryMapper[tempAddress]);
}  //void prtfFunc()

void fileOpen()
{
  inFile.open("CK.chop",ios::in|ios::binary|ios::ate);

  inFile.seekg(0, ios::end);
  size = inFile.tellg();
  cout << "Size of file: " << size << endl;
  inFile.seekg(0, ios::beg);

  oData = new char[size+1];
  inFile.read(oData, size);
  oData[size] = '\0';
  cout << "oData size: " << strlen(oData) <<  endl;
} // void fileOpen()

void copyrightCheck()
{
  youAreHere = oData;

  while(someIndex<10) {
    if(copyright[someIndex] != youAreHere[someIndex]) {
      cout << "FATAL ERROR: Key not present.\n";
      errorFlag = true;
      return ;
    }
    someIndex++;
  }

  cout << "copyright successfuly validated!\n";
  codeSegment = chartodir(&youAreHere[12]);
  dataSegment = chartodir(&youAreHere[10]);
  memoryMapper = new char[dataSegment];

  evindex=14;
}

void prtafFunc() //marin
{
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  cout << chartofloat(&memoryMapper[tempAddress]) << endl;
} // void prtafFunc()

void pushafFunc() //marin
{
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  tempBlock.typecode = 'f';
  tempBlock.data.f = chartofloat(&memoryMapper[tempAddress]);
  theStack.push(tempBlock);
} //void pushafFunc()

void popafFunc() //marin
{
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  tempBlock = theStack.top();
  if(theStack.top().typecode == 'f')
  {
    tempFloat = tempBlock.data.f;
    tempPointer = floattochar(tempFloat);
    theStack.pop();
    for(int ind = 0; ind < 4; ind++)
      memoryMapper[tempAddress++] = tempPointer[ind];
  }
} //void popafFunc()

void rdafFunc() //marin
{
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  cin >> tempFloat;
  tempPointer = floattochar(tempFloat);
  for(int someIndex = 0; someIndex < 4; someIndex++)
    memoryMapper[tempAddress++] = tempPointer[someIndex];
} //void rdafFunc()

void prtadFunc() { //alex
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempInteger = 8*arrindex;
  tempAddress += tempInteger;
  cout << tempAddress << endl;
  cout << chartodouble(&memoryMapper[tempAddress]);
} //void prtadFunc()

void pushadFunc() { //alex
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempInteger = 8*arrindex;
  tempAddress += tempInteger;
  tempBlock.typecode = 'd';
  tempBlock.data.d = chartodouble(&memoryMapper[tempAddress]);
  theStack.push(tempBlock);
} //void pushadFunc()

void rdadFunc() { //alex
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempInteger = 8*arrindex;
  tempAddress += tempInteger;
  cin >> tempDouble;
  tempPointer = doubletochar(tempDouble);
  for(someIndex = 0; someIndex < 8; someIndex++)
    memoryMapper[tempAddress++] = tempPointer[someIndex];
} //void rdadFunc()

void popadFunc() { //alex
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  tempBlock = theStack.top();
  if(theStack.top().typecode == 'd')
  {
    tempFloat = tempBlock.data.d;
    tempPointer = doubletochar(tempFloat);
    theStack.pop();
    for(int ind = 0; ind < 4; ind++)
      memoryMapper[tempAddress++] = tempPointer[ind];
  }
} //void popadFunc()

void prtacFunc() //luis
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  cout << memoryMapper[tempAddress+(arrindex)];
} //void prtacFunc()

void popacFunc() //luis
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempBlock = theStack.top();
  if(tempBlock.typecode = 's')
  {
    theStack.pop();
    tempPointer = new char[1];
    cout << "char " << tempBlock.data.s[0] << endl;
    tempPointer[0] = tempBlock.data.s[0];
    memoryMapper[tempAddress+(arrindex)] = tempPointer[0];
  }
} //void popacFunc()

void pushacFunc()  //luis
{
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  tempBlock.typecode = 's';
  tempBlock.data.s = new char[1];
  tempBlock.data.s[0] = memoryMapper[tempAddress+(arrindex)];
  theStack.push(tempBlock);
}  //void pushcFunc()

bool rdacFunc() //luis
{
  cout << "RDAC " << endl;
  tempAddress = chartodir(&youAreHere[evindex]);
  evindex += 2;
  getline(cin,tempString);
  if(tempString.length() > 1)
  {
    std::cout << "Char Overflow! \n";
    return false;
  }
  memoryMapper[tempAddress+(arrindex)] = tempString[0];
  return true;
}

void prtaiFunc()//jl
{
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  cout << chartoint(&memoryMapper[tempAddress]);
}

void rdaiFunc()//jl
{
  tempAddress = chartodir(&youAreHere[evindex]);
  tempAddress += (arrindex * 4);
  evindex += 2;
  cin >> tempInteger;

  tempPointer = inttochar(tempInteger);
  for(int someIndex = 0; someIndex < 4; someIndex++)
      memoryMapper[tempAddress++] = tempPointer[someIndex];
}
