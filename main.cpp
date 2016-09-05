#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <string>
#include <stack>
#include "conversion.h"

enum TYPES {CHAR, INT, FLOAT, DOUBLE, STRING};
enum COMMANDS {HALT, PRTCR, PRTC, PRTI, PRTF, PRTD, PUSHC, PUSHI, PUSHF, PUSHD, PUSHS, PUSHAC, PUSHAI, PUSHAF, PUSHAD, PUSHAS, PUSHKC, PUSHKI, PUSHKF, PUSHKD, PUSHKS, POPC, POPI, POPF, POPD, POPS, POPX, POPAC, POPAI, POPAF, POPAD, POPAS, RDC, RDI, RDF, RDD, RDS, RDAC, RDAI, RDAF, RDAD, RDAS, JMP, JMPEQ, JMPNE, JMPGT, JMPGE, JMPLT, JMPLE, STX, STKX, INC, DEC, ADD, SUB, MUL, DIV, MOD, CMP};

using namespace std;
int index;
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

int main() {
  stack<StackBlock> theStack;

  char copyright[10] = {'(','C',')','C','H','U','N','K','U','N'};
  int codeSegment = 0;
  int dataSegment = 0;
  int someIndex = 0;
  ifstream inFile;
  size_t size = 0;

  inFile.open("CK.chop",ios::in|ios::binary|ios::ate);
  char* oData = 0;

  inFile.seekg(0, ios::end);
  size = inFile.tellg();
  cout << "Size of file: " << size << endl;
  inFile.seekg(0, ios::beg);

  oData = new char[size+1];
  inFile.read(oData, size);
  oData[size] = '\0';
  cout << "oData size: " << strlen(oData) <<  endl;

  char* youAreHere;
  youAreHere = oData;

  while(someIndex<10) {
    if(copyright[someIndex++] != *youAreHere++) {
      cout << "FATAL ERROR: Key not present.";
      return 1;
    }
  }
  codeSegment = chartoint(&youAreHere[10]);
  dataSegment = chartoint(&youAreHere[14]);
  memoryMapper = new char[dataSegment];

  index=18;

  //VARIABLES FOR FUNCTIONS
  int tempAddress;
  StackBlock tempBlock = {};
  int tempInteger;
  char* tempPointer;

  while(true) {
    tempBlock = {};
    //reading example, plz test
    cout << "NEXT CHAR: " << youAreHere[index];
    cout << "\n";
    //cout << oData[i] << " + 'a' = " << (oData[i] + 'a');
    //cout << ('a') << endl;
    //cout << "\n\n";

    switch(youAreHere[index++]){
      case PRTCR:
        cout << "\n";
      break;
      case PRTC:
      break;
      case PRTI:
        //Marin
        tempAddress = chartodir(&youAreHere[index]);
        index += 2;
        cout << chartoint(&memoryMapper[tempAddress]);
      break;
      case PRTF:
      break;
      case PRTD:
      break;
      case PUSHC:
      break;
      case PUSHI:
        //Marin
        tempAddress = chartodir(&youAreHere[index]);
        index += 2;
        tempBlock.typecode = 'i';
        tempBlock.data.i = chartoint(&memoryMapper[tempAddress]);
        theStack.push(tempBlock);
      break;
      case PUSHF:
      break;
      case PUSHD:
      break;
      case PUSHS:
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
      case PUSHKI:
        //Marin
        tempBlock.typecode = 'i';
        tempBlock.data.i = chartoint(&youAreHere[index]);
        index += 4;
        theStack.push(tempBlock);
      break;
      case PUSHKF:
      break;
      case PUSHKD:
      break;
      case PUSHKS:
      break;
      case POPC:
      break;
      case POPI:
        if(!theStack.empty()) {
             tempAddress = chartodir(&youAreHere[index]);
             index = index + 2;
             tempBlock = theStack.top();
             if(tempBlock.typecode = 'i') {
                 theStack.pop();
                 tempInteger = tempBlock.data.i;
                 tempPointer = inttochar(tempInteger);
                 for(someIndex = 0; someIndex < 4; someIndex++) {
                   memoryMapper[tempAddress++] = tempPointer[someIndex];
                 }
             }
         }
      break;
      case POPF:
      break;
      case POPD:
      break;
      case POPS:
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
      case RDI:
        //Marin
        tempAddress = chartodir(&youAreHere[index]);
        index+=2;
        cin >> tempInteger;
        tempPointer = inttochar(tempInteger);
        for(someIndex = 0; someIndex < 4; someIndex++){
          memoryMapper[tempAddress++] = tempPointer[someIndex];
        }
      break;
      case RDF:
      break;
      case RDD:
      break;
      case RDS:
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
      case JMP:
      break;
      case JMPEQ:
      break;
      case JMPNE:
      break;
      case JMPGT:
      break;
      case JMPGE:
      break;
      case JMPLT:
      break;
      case JMPLE:
      break;
      case STX:
      break;
      case STKX:
      break;
      case INC:
        tempAddress = chartodir(&youAreHere[index]);
        index += 2;
        tempInteger = chartoint(&memoryMapper[tempAddress]);
        tempInteger++;
        tempPointer = inttochar(tempInteger);
        for(someIndex = 0; someIndex < 4; someIndex++)
          memoryMapper[tempAddress++] = tempPointer[someIndex];
      break;
      case DEC:
        tempAddress = chartodir(&youAreHere[index]);
        index += 2;
        tempInteger = chartoint(&memoryMapper[tempAddress]);
        tempInteger--;
        tempPointer = inttochar(tempInteger);
        for(someIndex = 0; someIndex < 4; someIndex++)
          memoryMapper[tempAddress++] = tempPointer[someIndex];
      break;
      case ADD:
        if(theStack.size() < 2)
            return 1;
        else {
            if(theStack.top().typecode == 'i') {
              tempBlock = theStack.top();
              theStack.pop();
              if(theStack.top().typecode == 'i') {
                theStack.data.i += tempBlock.data.i;
                theStack.pop();
              }
              theStack.push(tempBlock);
            }
            else {
              cout << "ERROR";
              return 1;
            }
          }
      break;
      case SUB:
      if(theStack.size() < 2)
          return 1;
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
            return 1;
          }
        }
      break;
      case MUL:
        if(theStack.size >= 2) {
          if (theStack.top().typecode == 'i') {
            tempBlock.typecode = 'i';
            tempBlock.data.i = theStack.top().data.i;
            theStack.pop();
          }
          if (theStack.top().typecode == 'i') {
            tempBlock.data.i *= theStack.top().data.i;
            theStack.pop();
          }
          theStack.push(tempBlock);
        }
      break;
      case DIV:
        if(theStack.size >= 2) {
          if (theStack.top().typecode == 'i') {
            tempBlock.typecode = 'i';
            tempBlock.data.i = theStack.top().data.i;
            theStack.pop();
          }
          if (theStack.top().typecode == 'i') {
            tempBlock.data.i = theStack.top().data.i / tempBlock.data.i;
            theStack.pop();
          }
          theStack.push(tempBlock);
        }
      break;
      case MOD:
        // n%m
        if(theStack.size() >= 2) {
          tempBlock = theStack.top();
          theStack.pop();
          if(tempBlock.typecode == 'i') {
            if(theStack.top().typecode == 'i')
              theStack.top().data.i = (theStack.top().data.i % tempBlock.data.i);
          }
        }
        else
          return 0;
      break;
      case CMP:
      break;
      case HALT:
        return 0;
      break;
      default:
        cout << "ERROR: Unrecognized Command.";
      break;
    }
  }
}
