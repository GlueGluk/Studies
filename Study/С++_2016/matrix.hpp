#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;

class matrix {
		double *a;
		int m,n;
		
	public:
		matrix(){
			a=NULL;
			n=0;m=0;
		}
		matrix(const matrix &p);
		matrix operator=(const matrix &p);
		~matrix() {
			if(a!=NULL) delete []a;
			}
			
		matrix(double p);
		matrix(double* ar,int m1);
		matrix(int n1,double *ar);
		matrix(char *s);				
 		class err{
			public:
				const char *s;
				err(const char *str){
					s=str;
				}
		};
		
		double* operator[] (int p);
		static matrix zero(int x,int y);
		static matrix identity(int x);		
		static matrix diagonal(double *vals,int x);
		int rows() {
			return m;
			}
		int columns() {
			return n;
			}
		matrix transpose();	
		matrix reshape(int x,int y);
		void set(int i,int j,double v) {
			if ((i>=m)or(j>=n)) throw err("No such element");
			a[i*n+j]=v;
		}
		matrix operator+ (const matrix &p);
		matrix operator+= (const matrix &p);
		matrix operator- (const matrix &p);
		matrix operator-= (const matrix &p);
		matrix operator* (const matrix &p);
		matrix operator*= (const matrix &p);
		matrix operator- ();
		static const double eps;	
		int operator== (const matrix &p);
		int operator!= (const matrix &p);
		matrix sorted(bool descending);
		matrix max(int k);
		void print_m();
};
