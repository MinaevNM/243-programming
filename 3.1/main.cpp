#include <iostream> 
#include <complex> 

#pragma warning(disable: 4996) 

using namespace std; 

const double pi = 3.14159265358979323846; 
 
complex<double> * FFT( complex<double> * polynom, int degree ) 
{ 
	complex<double> * values = new complex<double>[degree]; 

	if (degree == 1) 
	{ 
		values[0] = polynom[0]; 
		return values; 
	} 

	complex<double> * roots = new complex<double>[degree]; 
	for (int i = 0; i < degree; i++) 
	{ 
		double phi = 2 * pi * i / degree; 
		roots[i] = complex<double>(cos(phi), sin(phi)); 
	} 

	complex<double> * pol1 = new complex<double>[degree / 2]; 
	complex<double> * pol2 = new complex<double>[degree / 2]; 

	for (int i = 0; i < degree; i++) 
	{ 
		if (!(i % 2)) 
			pol1[i / 2] = polynom[i]; 
		else 
			pol2[i / 2] = polynom[i]; 
	} 

	complex<double> * val1 = new complex<double>[degree / 2]; 
	complex<double> * val2 = new complex<double>[degree / 2]; 

	val1 = FFT(pol1, degree / 2); 
	val2 = FFT(pol2, degree / 2); 

	/*
	for (int i = 0; i < degree; i++) 
		values[i] = val1[i % (degree / 2)] + roots[i] * val2[i % (degree / 2)]; */

	for (int i = 0; i < degree / 2; i++)
	{
		values[i] = val1[i] + roots[i] * val2[i];
		values[i + degree / 2] = val1[i] - roots[i] * val2[i];
	}


	delete [] val1; 
	delete [] val2; 
	delete [] pol1; 
	delete [] pol2; 
	delete [] roots; 

	return values; 
} 


complex<double> * IFFT( complex<double> * values, int degree ) 
{ 
	complex<double> * polynom = new complex<double>[degree]; 

	if (degree == 1) 
	{ 
		polynom[0] = values[0];		
		return polynom;		
	}	 

	complex<double> * val1 = new complex<double>[degree / 2]; 
	complex<double> * val2 = new complex<double>[degree / 2]; 

	for (int i = 0; i < degree; i++) 
	{ 
		if (!(i % 2)) 
			val1[i / 2] = values[i]; 
		else 
			val2[i / 2] = values[i]; 
	} 

	complex<double> * pol1 = new complex<double>[degree / 2]; 
	complex<double> * pol2 = new complex<double>[degree / 2]; 

	pol1 = IFFT(val1, degree / 2); 
	pol2 = IFFT(val2, degree / 2); 

	double phi = -2 * pi / degree; 
	complex<double> root = complex<double>(1, 0); 
	complex<double> dr = complex<double>(cos(phi), sin(phi)); 

	for (int i = 0; i < degree / 2; i++) 
	{ 
		polynom[i] = (pol1[i] + root * pol2[i]) * 0.5; 
		polynom[i + degree / 2] = (pol1[i] - root * pol2[i]) * 0.5; 
		root *= dr; 
	} 

	delete [] val1; 
	delete [] val2; 
	delete [] pol1; 
	delete [] pol2; 
 
	return polynom; 
} 


char * FastMultiply( char * str1, char * str2, int degree ) 
{ 
	complex<double> * pol1 = new complex<double>[2 * degree]; 
	complex<double> * pol2 = new complex<double>[2 * degree]; 
	complex<double> * pol3 = new complex<double>[2 * degree]; 

	for (int i = 0; i < degree; i++)
	{
		pol1[i] = complex<double>(0, 0);
		pol2[i] = complex<double>(0, 0);
	}

	for (int i = 0; i < degree; i++) 
	{ 
		pol1[i + degree] = complex<double>(str1[i], 0); 
		pol2[i + degree] = complex<double>(str2[i], 0); 
	} 
	 
	complex<double> * val1 = new complex<double>[2 * degree]; 
	complex<double> * val2 = new complex<double>[2 * degree]; 
	complex<double> * val3 = new complex<double>[2 * degree]; 

	val1 = FFT(pol1, 2 * degree); 
	val2 = FFT(pol2, 2 * degree); 
	
	cout << "pol1 = ";
	for (int i = 0; i < 2 * degree; i++)
		cout << (int)real(pol1[i]);
	cout << endl;

	cout << "pol2 = ";
	for (int i = 0; i < 2 * degree; i++)
		cout << (int)real(pol2[i]);
	cout << endl;
	/*
	cout << "val1            val2" << endl;

	for (int i = 0; i < 2 * degree; i++)
		cout << val1[i] << "            " << val2[i] << endl;
	exit(0);
	*/
	for (int i = 0; i < 2 * degree; i++) 
		val3[i] = val1[i] * val2[i];
	
	pol3 = IFFT(val3, 2 * degree); 
	
	cout << "pol3 = ";
	for (int i = 0; i < 2 * degree; i++)
		cout << (int)(real(pol3[i]) + 0.5);
	cout << endl;
	exit(0);
	
	char * str3 = new char[2 * degree - 1]; 
	 
	for (int i = 0; i < 2 * degree - 1; i++) 
		str3[i] = (char)real(pol3[i + 1]); 

	delete [] pol1; 
	delete [] pol2; 
	delete [] pol3; 
	delete [] val1; 
	delete [] val2; 
	delete [] val3; 

	return str3; 
} 


void addShiftsForChar( char c, char * str1n, char * str2n, int n, int * shift ) 
{ 
	char * str1 = new char[n]; 
	char * str2 = new char[n]; 

	for (int i = 0; i < n; i++) 
	{ 
		if (str1n[i] == c) 
			str1[i] = 1; 
		else 
			str1[i] = 0; 
		if (str2n[i] == c) 
			str2[i] = 1; 
		else 
			str2[i] = 0; 
	} 

	for (int i = 0; i < n / 2; i++) 
		swap(str2[i], str2[n - i - 1]); 

	char * str3 = new char[2 * n - 1]; 
	/* 
	memset(str3, 0, (2 * n - 1) * sizeof(char)); 
	 
	for (int i = 0; i < n; i++) 
		if (str2[n - i - 1] == 1) 
			for (int j = 0; j < n; j++) 
				str3[2 * n - 2 - (i + j)] += str1[n - j - 1]; 
	*/ 
	/*
	for (int i = 0; i < n; i++)
		cout << (int)str1[i];
	cout << endl;

	for (int i = 0; i < n; i++)
		cout << (int)str2[i];
	cout << endl;
	*/
	str3 = FastMultiply(str1, str2, n); 
	/*
	for (int i = 0; i < 2 * n - 1; i++)
		cout << (int)str3[i];
	cout << endl;
	exit(0);
	*/
	shift[0] += (int)str3[n - 1]; 
	 
	for (int i = 0; i < n - 1; i++) 
		shift[i + 1] += ((int)str3[i] + (int)str3[i + n]); 
		 
	delete [] str1; 
	delete [] str2; 
	delete [] str3; 
} 


void main() 
{ 
	int n; 
	char * str1n; 
	char * str2n; 

	freopen("input.txt", "rt", stdin); 
	freopen("output.txt", "wt", stdout); 
	 
	cin >> n; 

	str1n = new char[n + 1]; 
	str2n = new char[n + 1]; 

	cin >> str1n; 
	cin >> str2n; 

	int * shift = new int[n]; 
	memset(shift, 0, n * sizeof(int)); 

	addShiftsForChar('A', str1n, str2n, n, shift); 
	addShiftsForChar('C', str1n, str2n, n, shift); 
	addShiftsForChar('G', str1n, str2n, n, shift); 
	addShiftsForChar('T', str1n, str2n, n, shift); 

	int max = 0; 

	for (int i = 1; i < n; i++) 
		if (shift[i] > shift[max]) 
			max =  i; 

	cout << shift[max] << ' ' << max << endl; 

	delete [] shift; 
	delete [] str1n; 
	delete [] str2n; 
} 
