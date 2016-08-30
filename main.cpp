#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
#include "conversion.h"

enum TYPES {CHAR, INT, FLOAT, DOUBLE, STRING};
enum COMMANDS {PRTCR, PRTC, PRTI, PRTF, PRTD, PUSHC, PUSHI, PUSHF, PUSHD, PUSHS, PUSHAC, PUSHAI, PUSHAF, PUSHAD, PUSHAS, PUSHKC, PUSHKI, PUSHKF, PUSHKD, PUSHKS, POPC, POPI, POPF, POPD, POPS, POPX, POPAC, POPAI, POPAF, POPAD, POPAS, RDC, RDI, RDF, RDD, RDS, RDAC, RDAI, RDAF, RDAD, RDAS, JMP, JMPEQ, JMPNE, JMPGT, JMPGE, JMPLT, JMPLE, STX, STKX, INC, DEC, ADD, SUB, MUL, DIV, MOD, CMP, HALT};

using namespace std;


int main() {
  ifstream inFile;
  size_t size = 0;

  inFile.open("a.txt",ios::in|ios::binary|ios::ate);
  char* oData = 0;

  inFile.seekg(0, ios::end);
  size = inFile.tellg();
  cout << "Size of file: " << size << endl;
  inFile.seekg(0, ios::beg);

  oData = new char[size+1];
  inFile.read(oData, size);
  oData[size] = '\0';
  cout << "oData size: " << strlen(oData) <<  endl;
  bool newline = false;

  for(size_t i = 0; i<strlen(oData); i++) {
    //reading example, plz test
    cout << "oData["<<i<<"] " << oData[i];
    cout << "\n";
    cout << oData[i] << " + 'a' = " << (oData[i] + 'a');
    cout << ('a') << endl;
    cout << "\n\n";

    switch(oData[i]){
      case PRTCR:
      break;
      case PRTC:
      break;
      case PRTI:
      break;
      case PRTF:
      break;
      case PRTD:
      break;
      case PUSHC:
      break;
      case PUSHI:
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
      break;
      case DEC:
      break;
      case ADD:
      break;
      case SUB:
      break;
      case MUL:
      break;
      case DIV:
      break;
      case MOD:
      break;
      case CMP:
      break;
      case HALT:
      break;
      default:
        cout << "ERROR: Unrecognized Command.";
      break;
    }
  }
  cout << "Press ENTER to exit.";
  getchar();
  return 0;
}
