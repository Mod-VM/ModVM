#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <string>
#include <stack>
#include <cstdlib>
#include "conversion.h"

//function declaration
void fileOpen();
void copyrightCheck();
void prtiFunc();
void prtsFunc();
void popsFunc();
void cmpFunc();
bool modFunc();
bool divFunc();
bool mulFunc();
bool subFunc();
bool addFunc();
void decFunc();
void incFunc();
void jmpFunc();
void jmpeqFunc();
void jmpneFunc();
void jmpgeFunc();
void jmpgtFunc();
void jmpltFunc();
void jmpleFunc();
void rdsFunc();
void rdiFunc();
void popiFunc();
void pushksFunc();
void pushkiFunc();
void pushsFunc();
void pushiFunc();
void pushkfFunc();
void popfFunc();
void prtfFunc();

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
        case PRTC:
        break;
        case PRTI: prtiFunc();
        break;
        case PRTF: prtfFunc();
        break;
        case PRTD:
        break;
        case PRTS: prtsFunc();
        break;
        case PRTAC:
        break;
        case PRTAI:
        break;
        case PRTAF:
        break;
        case PRTAD:
        break;
        case PRTAS:
        break;
        case PUSHC:
        break;
        case PUSHI: pushiFunc();
        break;
        case PUSHF:
        break;
        case PUSHD:
        break;
        case PUSHS: pushsFunc();
          break;
        case PUSHAC:
        break;
        case PUSHAI:
        break;
        case PUSHAF:
        break;
        case PUSHAD:
        break;
        case PUSHAS:
        break;
        case PUSHKC:
        break;
        case PUSHKI: pushkiFunc();
        break;
        case PUSHKF:pushkfFunc();
        break;
        case PUSHKD:
        break;
        case PUSHKS: pushksFunc();
        break;
        case POPC:
        break;
        case POPI: popiFunc();
        break;
        case POPF: popfFunc();
        break;
        case POPD:
        break;
        case POPS: popsFunc();
        break;
        case POPX:
        break;
        case POPAC:
        break;
        case POPAI:
        break;
        case POPAF:
        break;
        case POPAD:
        break;
        case POPAS:
        break;
        case RDC:
        break;
        case RDI: rdiFunc();
        break;
        case RDF:
        break;
        case RDD:
        break;
        case RDS: rdsFunc();
        break;
        case RDAC:
        break;
        case RDAI:
        break;
        case RDAF:
        break;
        case RDAD:
        break;
        case RDAS:
          //is did
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
        case STX:
        break;
        case STKX:
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
        default:
          cout << "ERROR: Unrecognized Command.";
        break;
      }
    }
    return 1;
}

void pushkfFunc()  //isai
{
  std::cout << "PUSHKF " << std::endl;
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

void pushkiFunc()  //marin
{
  cout << "PUSHKI " << endl;
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
  std::cout << "POPF " << std::endl;
  if(!theStack.empty())
  {
    tempAddress = chartodir(&youAreHere[evindex]);
    evindex = evindex + 2;
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

void popiFunc()
{
  cout << "POPI " << endl;
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
  evindex = chartodir(&youAreHere[evindex]);
  evindex+=2;
}  //void jmp

void jmpeqFunc()
{
  if(jmpeq)
    evindex = chartodir(&youAreHere[evindex]);
  else
    evindex+=2;
}  //void jmpeqFunc()

void jmpneFunc()
{
  if(jmpne)
    evindex = chartodir(&youAreHere[evindex]);
  else
    evindex+=2;
}  //void jumpneFunc()

void jmpgtFunc()
{
  if(jmpgt)
    evindex = chartodir(&youAreHere[evindex]);
  else
    evindex+=2;
}  //void jmpgtFunc()

void jmpgeFunc()
{
  if(jmpge)
    evindex = chartodir(&youAreHere[evindex]);
  else
    evindex+=2;
}  //void jmpgeFunc()

void jmpltFunc()
{
  if(jmplt)
    evindex = chartodir(&youAreHere[evindex]);
  else
    evindex+=2;
}  //void jmpltFunc()

void jmpleFunc()
{
  if(jmple)
    evindex = chartodir(&youAreHere[evindex]);
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
  else {
    if(theStack.top().typecode == 'i') {
      tempBlock = theStack.top();
      theStack.pop();
      if(theStack.top().typecode == 'i') {
        theStack.top().data.i += tempBlock.data.i;
      }
    }
    else {
      cout << "ERROR";
      return false;
    }
  }
  return true;
}  //bool addFunc()

bool subFunc()
{
  if(theStack.size() < 2)
    return false;
  else {
    if(theStack.top().typecode == 'i') {
      tempBlock = theStack.top();
      theStack.pop();
      if(theStack.top().typecode == 'i') {
        tempBlock.data.i = theStack.top().data.i - tempBlock.data.i;
        theStack.pop();
      }
      theStack.push(tempBlock);
    }
    else {
      cout << "ERROR";
      return false;
    }
  } 
  return true; 
}  //void subFunc()

bool mulFunc()
{
  if(theStack.size() >= 2) {
    if (theStack.top().typecode == 'i') {
      tempBlock.typecode = 'i';
      tempBlock.data.i = theStack.top().data.i;
      theStack.pop();
      if (theStack.top().typecode == 'i') {
        tempBlock.data.i *= theStack.top().data.i;
        theStack.pop();
      }
    }
    theStack.push(tempBlock);
    return true;
  }
  return false;
}  //mulFunc()

bool divFunc()
{
  if(theStack.size() >= 2) {
    if (theStack.top().typecode == 'i') {
      tempBlock.typecode = 'i';
      tempBlock.data.i = theStack.top().data.i;
      theStack.pop();
      if (theStack.top().typecode == 'i') {
        cout << theStack.top().data.i << " / " << tempBlock.data.i;
        tempBlock.data.i = theStack.top().data.i / tempBlock.data.i;
        theStack.pop();
      }
    }

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
  if(tempBlock.typecode == 'i') {
    if(theStack.top().typecode == 'i') {
      jmpeq = (theStack.top().data.i == tempBlock.data.i) ? true : false;
      jmpne = (theStack.top().data.i != tempBlock.data.i) ? true : false;
      jmple = (theStack.top().data.i <= tempBlock.data.i) ? true : false;
      jmplt = (theStack.top().data.i < tempBlock.data.i) ? true : false;
      jmpge = (theStack.top().data.i >= tempBlock.data.i) ? true : false;
      jmpgt = (theStack.top().data.i > tempBlock.data.i) ? true : false;
      theStack.push(tempBlock);
    }
  } else if(tempBlock.typecode == 'f') {

  } else if(tempBlock.typecode == 'd') {

  }
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
  codeSegment = chartodir(&youAreHere[10]);
  dataSegment = chartodir(&youAreHere[12]);
  memoryMapper = new char[dataSegment];

  evindex=14;
}
