/*
 * UVA 400 Unix ls
 * 2004-12-13
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

#define COLUMN_CAPACITY 60


int main(int argc, char** argv)
{

    while(true) {
        int nFiles;
        cin >> nFiles;
        if (! cin)
            break;

        vector<string> filenames;
        filenames.resize(nFiles);

        for(int i=0; i<nFiles; i++) {
            cin >> filenames[i];
        }
        sort(filenames.begin(), filenames.end());

        size_t nMaxFilenameLen = 0;
        for(vector<string>::const_iterator it = filenames.begin(); it != filenames.end(); it++) {
            nMaxFilenameLen = max(nMaxFilenameLen, it->length());
        }

        size_t nColumns = (COLUMN_CAPACITY+2)/(nMaxFilenameLen+2);
        size_t nRows = (nFiles + nColumns-1)/nColumns;

        cout << string(60, '-') << endl;
        for(int iRow=0; iRow<nRows; iRow++) {
            for(int iColumn=0; iColumn<nColumns; iColumn++) {
                int index = iRow + nRows*iColumn;

                if (index >= nFiles)
                    break;

                cout << filenames[index];
                cout << string(nMaxFilenameLen - filenames[index].length(), ' ');
                if (iColumn < nColumns-1)
                    cout << "  ";
            }
            cout << endl;
        }

    }

    return 0;
}



