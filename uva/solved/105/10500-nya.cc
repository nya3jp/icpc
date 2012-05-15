/*
 * UVA 10500 - Robot maps
 * 2006-01-14
 * by nya
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>
#include <cassert>

enum Cell
{
    Unknown,
    Empty,
    Occupied,
};

template<class T>
struct Matrix : public std::vector< std::vector<T> >
{
    Matrix(int n, int m, const T& value = T())
        : std::vector< std::vector<T> >(n, std::vector<T>(m, value)), n(n), m(m)
    {}
private:
    const int n, m;
};

typedef Matrix<Cell> Map;
typedef Matrix<bool> VisitedMap;

int main()
{
    while(true)
    {
        int nRows, nCols;
        std::cin >> nRows >> nCols;
        if (nRows == 0 && nCols == 0)
            break;

        Map actualMap(nRows+2, nCols+2, Occupied);

        int iInitRow, iInitCol;
        std::cin >> iInitRow >> iInitCol;

        for(int iRow = 1; iRow <= nRows; iRow++)
        {
            for(int iCol = 1; iCol <= nCols; iCol++)
            {
                char ch;
                std::cin >> ch;
                actualMap[iRow][iCol] = (ch == 'X' ? Occupied : Empty);
            }
        }

        Map traversalMap(nRows+2, nCols+2, Unknown);
        VisitedMap visited(nRows+2, nCols+2, false);
        int nMoves;
        {
            int iRow = iInitRow;
            int iCol = iInitCol;
            nMoves = -1;
            while(!visited[iRow][iCol])
            {
                nMoves++;
                visited[iRow][iCol] = true;
                traversalMap[iRow][iCol] = actualMap[iRow][iCol];
                traversalMap[iRow-1][iCol] = actualMap[iRow-1][iCol];
                traversalMap[iRow][iCol+1] = actualMap[iRow][iCol+1];
                traversalMap[iRow+1][iCol] = actualMap[iRow+1][iCol];
                traversalMap[iRow][iCol-1] = actualMap[iRow][iCol-1];
                if (!visited[iRow-1][iCol] && actualMap[iRow-1][iCol] == Empty)
                    iRow--;
                else if (!visited[iRow][iCol+1] && actualMap[iRow][iCol+1] == Empty)
                    iCol++;
                else if (!visited[iRow+1][iCol] && actualMap[iRow+1][iCol] == Empty)
                    iRow++;
                else if (!visited[iRow][iCol-1] && actualMap[iRow][iCol-1] == Empty)
                    iCol--;
            }
        }

        std::cout << std::endl;
        for(int iRow = 1; iRow <= nRows; iRow++)
        {
            for(int iCol = 1; iCol <= nCols; iCol++)
            {
                std::cout << "|---";
            }
            std::cout << "|" << std::endl;
            for(int iCol = 1; iCol <= nCols; iCol++)
            {
                std::cout << "| ";
                switch(traversalMap[iRow][iCol])
                {
                case Unknown:
                    std::cout << "?";
                    break;
                case Empty:
                    std::cout << "0";
                    break;
                case Occupied:
                    std::cout << "X";
                    break;
                }
                std::cout << " ";
            }
            std::cout << "|" << std::endl;
        }
        {
            for(int iCol = 1; iCol <= nCols; iCol++)
            {
                std::cout << "|---";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << std::endl;
        std::cout << "NUMBER OF MOVEMENTS: " << nMoves << std::endl;

    }

    return 0;
}
