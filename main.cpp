#include "extractor.h"
#include <limits>
using namespace std;

int main() {
  extractor extrctr;
  cout << "\n\nExtracting data ..." << endl;
  cout << "\nExtracting from: " << extrctr.getPreparedPathString() << endl;
  cout << "\nImporting to: " << extrctr.getDesktopPathString() << endl;
  
  extrctr.createDestinationFolder(extrctr.getDesktopPathString());
  extrctr.copyFilesToDestination(extrctr.getPreparedPathString(), extrctr.getDesktopPathString());

  cout << "Press ENTER to exit...\n\n";
  cin.ignore(numeric_limits<streamsize>::max(), '\n' );
  return 0;
}