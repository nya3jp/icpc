#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <limits>
#include <iomanip>
#include <cmath>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

typedef vector<double> vector_t;
typedef vector<vector_t> matrix_t;
 
const double INF = numeric_limits<double>::infinity();


void invalid(string reason) {
  cerr << "Invalid MPS format: " << reason << endl;
  exit(1);
}

#define assume(s) { string token; cin >> token; if (token != s) invalid(); }

int main(int argc, char** argv) {

  bool verbose = false;
  bool ultraverbose = false;
  int sig = 1;

  for(int i = 1; i < argc; i++) {
    if (argv[i] == string("-v"))
      verbose = true;
    if (argv[i] == string("-vv"))
      ultraverbose = verbose = true;
    if (argv[i] == string("-m"))
      sig = -1;
  }

  string line;

  getline(cin, line);
  getline(cin, line);
  if (line != "ROWS")
    invalid("ROWS not found");

  set<string> rowset;
  map<string, int> types;
  string objective;

  for(;;) {
    getline(cin, line);
    if (line == "COLUMNS")
      break;
    if (!cin)
      invalid("unterminated ROWS");
    istringstream is(line);
    string typestr, name;
    is >> typestr >> name;
    int type;
    if (typestr == "E")
      type = 0;
    else if (typestr == "G")
      type = 1;
    else if (typestr == "L")
      type = -1;
    else if (typestr == "N")
      type = 28;
    else
      invalid("unknown inequality type");
    if (type == 28) {
      if (objective.empty())
	objective = name;
      else
	invalid("duplicated objective function");
    }
    rowset.insert(name);
    types[name] = type;
  }
  if (objective.empty())
    invalid("no objective function");

  if (verbose)
    cerr << rowset.size() << " rows." << endl;

  set<string> colset;
  map<string, map<string, double> > values;
  for(;;) {
    getline(cin, line);
    if (line == "RHS" || line == "BOUNDS" || line == "ENDATA")
      break;
    if (!cin)
      invalid("unterminated COLUMNS");
    istringstream is(line);
    string col;
    is >> col;
    colset.insert(col);
    for(;;) {
      string row;
      double a;
      if (!(is >> row >> a))
	break;
      values[row][col] = a;
    }
  }

  if (verbose)
    cerr << colset.size() << " columns." << endl;

  map<string, double> rhs;
  if (line == "RHS") {
    for(;;) {
      getline(cin, line);
      if (line == "BOUNDS" || line == "ENDATA")
	break;
      if (!cin)
	invalid("unterminated RHS");
      istringstream is(line);
      for(;;) {
	string row;
	if (!(is >> row))
	  break;
	if (rowset.count(row) == 0)
	  continue;
	double b;
	if (!(is >> b))
	  break;
	rhs[row] = b;
      }
    }
  }

  if (verbose)
    cerr << rhs.size() << " rhs." << endl;

  if (rhs.count(objective) > 0)
    invalid("rhs of objective function exists");

  map<string, pair<double, double> > bounds;
  if (line == "BOUNDS") {
    for(;;) {
      getline(cin, line);
      if (line == "ENDATA")
	break;
      if (!cin)
	invalid("unterminated BOUNDS");
      istringstream is(line);
      string side, name, col;
      double x;
      is >> side >> name >> col >> x;
      if (!is && side != "FR")
	invalid("unknown BOUNDS format");
      if (colset.count(col) == 0)
	invalid("unknown column in BOUNDS");
      if (bounds.count(col) == 0)
	bounds[col] = make_pair(-INF, INF);
      if (side == "LO")
	bounds[col].first = x;
      else if (side == "UP")
	bounds[col].second = x;
      else if (side == "FX")
	bounds[col].first = bounds[col].second = x;
      else if (side == "FR")
	;
      else
	invalid("unknown bound type");
    }
  }
  FOR(it, rowset) {
    string row = *it;
    if (bounds.count(row) == 0)
      bounds[row] = make_pair(0, INF);
  }

  if (ultraverbose) {
    cerr << string(80, '-') << endl;
    FOR(row_it, rowset) {
      string row = *row_it;
      if (row == objective)
	cerr << "[OBJECTIVE] ";
      cerr << row << ": ";
      FOR(col_it, colset) {
	string col = *col_it;
	if (col_it != colset.begin())
	  cerr << " + ";
	cerr << setprecision(5) << (values[row].count(col) > 0 ? values[row][col] : 0.0) << col;
      }
      cerr << " ";
      cerr << (types[row] == 28 ? "-" : types[row] == 0 ? "==" : types[row] > 0 ? ">=" : "<=");
      cerr << " " << setprecision(5) << rhs[row] << endl;
    }
    cerr << string(80, '-') << endl;
    cerr << "converting to normal form" << endl;
  }

  FOR(row_it, rowset) {
    string row = *row_it;
    int type = types[row];
    if (type == 28) {
    }
    else if (type > 0) {
      string newcol = row + "#ineq";
      colset.insert(newcol);
      values[row][newcol] = -1;
    }
    else if (type < 0) {
      string newcol = row + "#ineq";
      colset.insert(newcol);
      values[row][newcol] = 1;
    }
  }

  vector<string> newrows, newcols;
  FOR(col_it, colset) {
    string col = *col_it;
    if (bounds.count(col) == 0)
      continue;
    pair<double,double> bound = bounds[col];
    if (!(-INF < bound.first) && !(bound.second < INF)) {
      if (verbose)
	cerr << col << " is unbound" << endl;
      string newcol = col + "#bound";
      newcols.push_back(newcol);
      FOR(it, rowset) {
	string row = *it;
	if (values[row].count(col) > 0)
	  values[row][newcol] = -values[row][col];
      }
    }
    else if (!(-INF < bound.first)) {
      // x <= U  <=>  y >= 0 (y = U - x, x = U - y)
      double u = bound.second;
      if (verbose)
	cerr << col << " is bound under " << u << endl;
      FOR(it, rowset) {
	string row = *it;
	if (values[row].count(col) > 0) {
	  rhs[row] -= u * values[row][col];
	  values[row][col] *= -1;
	}
      }
    }
    else if (!(bound.second < INF)) {
      // L <= x  <=>  y >= 0 (y = x - L, x = y + L)
      double l = bound.first;
      if (verbose)
	cerr << col << " is bound above " << l << endl;
      FOR(it, rowset) {
	string row = *it;
	if (values[row].count(col) > 0) {
	  rhs[row] -= l * values[row][col];
	}
      }
    }
    else {
      // L <= x <= U  <=>  0 <= y <= T (y = x - L, T = U - L, x = y + L)
      double l = bound.first, u = bound.second;
      if (verbose)
	cerr << col << " is bound between " << l << " to " << u << endl;
      FOR(it, rowset) {
	string row = *it;
	if (values[row].count(col) > 0)
	  rhs[row] -= l * values[row][col];
      }
      {
	string newrow = col + "#bound";
	string newcol = col + "#bound";
	newrows.push_back(newrow);
	newcols.push_back(newcol);
	values[newrow][col] = values[newrow][newcol] = 1;
	rhs[newrow] = u - l;
      }
    }
  }
  rowset.insert(ALLOF(newrows));
  colset.insert(ALLOF(newcols));

  if (ultraverbose) {
    cerr << string(80, '-') << endl;
    FOR(row_it, rowset) {
      string row = *row_it;
      if (row == objective)
	cerr << "[OBJECTIVE] ";
      cerr << row << ": ";
      FOR(col_it, colset) {
	string col = *col_it;
	if (col_it != colset.begin())
	  cerr << " + ";
	cerr << setprecision(5) << (values[row].count(col) > 0 ? values[row][col] : 0.0) << col;
      }
      cerr << " ";
      cerr << (types[row] == 28 ? "-" : "==");
      cerr << " " << setprecision(5) << rhs[row] << endl;
    }
    cerr << string(80, '-') << endl;
  }

  const int nRows = rowset.size(), nCols = colset.size();

  cout << nRows-1 << " " << nCols << endl << endl;

  FOR(col_it, colset) {
    string col = *col_it;
    double value = values[objective][col];
    cout << setprecision(10) << sig*value << " ";
  }
  cout << setprecision(10) << sig*-rhs[objective] << endl << endl;

  FOR(row_it, rowset) {
    string row = *row_it;
    if (row == objective)
      continue;
    FOR(col_it, colset) {
      string col = *col_it;
      double value = values[row][col];
      cout << setprecision(10) << value << " ";
    }
    cout << "  " << setprecision(10) << rhs[row] << endl;
  }

  return 0;
}

