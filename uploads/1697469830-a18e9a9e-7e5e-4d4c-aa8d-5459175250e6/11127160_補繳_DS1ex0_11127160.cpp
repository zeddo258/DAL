#include <iostream>
#include <cmath>
using namespace std;

int loop( int n ) {
	int a[99] ;
	a[0] = 1 ;
	a[1] = 2 ;
	if ( n == 1 ) {
		return a[0] ;
	}
	else if ( n == 2 ) {
		return a[1] ;
	}
	for ( int i=2 ; i<n ; i++ ) {
		a[i] = a[i-1] + a[i-2] ;
	}
	return a[n-1] ;
}

int factorloop( int p, int f ) {
	while ( p%f != 0 ) {
		f = f - 1 ;
	}
	return f ;
}

int recursion( int n ) {
	if ( n == 1 ) {
		return 1 ;
	}
	else if ( n == 2 ) {
		return 2 ;
	}
	
	return recursion( n-1 ) + recursion( n-2 ) ;
}

int factorrecursion( int p, int f ) {
	if ( p%f == 0 ) {
		return f ;
	}
	return factorrecursion( p,  f-1 ) ;
}

int main()
{

    int num ;
    int n, f1, f2 ;
    int innerloop, outerloop = 0 ;
    int innerrecursion, outerrecursion = 0 ;
// =========================================================================loop 
    cout << "Enter an interger equals or less than 92 : " ;
    cin >> n ;
    for ( int i = 0 ; i < n ; i++ ) {
    	num = loop(i+1) ;
    	cout << "[" << i+1 << "]" ; 
    	cout << num ;
    	f1 = factorloop(num, sqrt(num)) ;
    	f2 = num / f1 ;
    	innerloop = sqrt(num) - f1 ;
    	innerloop++ ;
    	outerloop = outerloop + innerloop ;
    	cout << " = " << f1 << "*" << f2 << " (Inner loop: " << innerloop << " times)" << endl ;
	}
    cout << "<Outer loop: " << outerloop << " times>" << endl ;
// =========================================================================recursion
    cout << "Enter an interger equals or less than 92 : " ;
    cin >> n ;
    
    for ( int i = 0 ; i < n ; i++ ) {
    	num = recursion(i+1) ;
    	f1 = factorrecursion(num, sqrt(num)) ;
    	f2 = num / f1 ;
    	innerrecursion = sqrt(num) - factorrecursion(recursion(i+1), sqrt(num)) ;
    	innerrecursion++ ;
    	outerrecursion = outerrecursion + innerrecursion ;
    	cout  << "[" << i+1 << "]" << recursion(i+1) << " = " << f1 << "*" << f2 << " (Inner recursion: " << innerrecursion << " times)" << endl ;
	}
    cout << "<Outer recursion: " << outerrecursion << " times>" << endl ;
    
    return 0;
}

