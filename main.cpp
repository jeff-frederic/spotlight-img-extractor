#include "extractor.h"
#include <limits>
using namespace std;

int main() {
  extractor extrctr;
  
  cout << "\nExtracting data ..." << endl;
  cout << "Extracting from: " << extrctr.getPreparedPathString() << endl;
  cout << "Importing to: " << extrctr.getDesktopPathString() << endl << endl;
  
  extrctr.createDestinationFolder(extrctr.getDesktopPathString());
  extrctr.copyFilesToDestination(extrctr.getPreparedPathString(), extrctr.getDesktopPathString());
  
  cout << "\nPress ENTER to exit...\n\n";
  cin.ignore(numeric_limits<streamsize>::max(), '\n' );
  return 0;
}