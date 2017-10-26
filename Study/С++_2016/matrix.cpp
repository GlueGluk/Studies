#include "matrix.hpp"

	matrix::matrix(const matrix &p) {
		int i,j,k=0;
		m=p.m;
		n=p.n;
		a=new double[sizeof(double)*m*n];
		for(i=0;i<m;i++) {
			for(j=0;j<n;j++) {
				a[k]=p.a[k];
				k++;
				}
			}
		}
	matrix matrix::operator=(const matrix &p) {
		int i;
		if(this==&p) return *this;
		delete []a;
		m=p.m;
		n=p.n;
		a=new double[sizeof(double)*m*n];
		for(i=0;i<m*n;i++) a[i]=p.a[i];
		return *this;
		}

	matrix::matrix(double p) {
		a=new double[sizeof(double)];
		a[0]=p;
		n=1;m=1;
	}
	matrix::matrix(double* ar,int m1) {
		int i;
		m=m1;
		n=1;
		a=new double[sizeof(double)*m];
		for(i=0;i<m;i++)
			a[i]=ar[i];
	}
	matrix::matrix(int n1,double *ar) {
		int i;
		n=n1;
		m=1;
		a=new double [sizeof(double)*n];
		for(i=0;i<n;i++) a[i]=ar[i];
	}	
	matrix::matrix(char *s){
		int i=0,x=0,y=0,z=0,fl=0,j,k;
		char *t=s;
		while(t[i]!='{') i++;
		i++;
		while(1) {
			if(t[i]=='{'){
				if(fl==0) fl++;
				else throw err("Check the string you input");
			}
			if ((t[i]==',')and(fl==1)) {
						z++;
						}
			if(t[i]=='}') {
				if(fl==1) fl--;
				else break;
				if(y==0) y=z;
				else if(z!=y) throw err("Wrong array size");
				x++;
				z=0;
				}
			i++;
			}
		m=x;
		n=y+1;
		k=0;
		t=s;
		x=0;
		while(t[x]!='{') x++;
		x++;
		while(t[x]!='{') x++;
		x++;
		t=&t[x];
		a=new double [sizeof(double)*m*n];
		for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				x=0;
				a[k]=strtod(t,&t);
				while((t[x]!=',')and(t[x]!='{')and (t[x]!='}')) {
								x++;
								}
				if(t[x]=='}') {
					x++; 
					while ((t[x]!=',')and(t[x]!='{')and(t[x]!='}')) x++;
					if(t[x]==',') 
						while(t[x]!='{') x++;
					if(t[x]=='}') break;
					}
				x++;
				t=&t[x];
				k++;
				}
			}
	}
				
	double* matrix::operator[] (int p) {
		if (p<=m) return &a[p*n];
		else throw err("No such element");
	}

	matrix matrix::zero(int x,int y) {
		int i;
		matrix p;
		p.m=x; p.n=y;
		p.a=new double[sizeof(double)*x*y];
		for(i=0;i<x*y;i++) p.a[i]=0;
		return p;
		}

	matrix matrix::identity(int x) {
		int i;
		matrix p;
		p.m=x;
		p.n=x;
		p.a=new double[sizeof(double)*x*x];
		for(i=0;i<x*x;i++){
			if(i%(x+1)==0) p.a[i]=1;
			else p.a[i]=0;
		}
		return p;
		}	
	matrix matrix::diagonal(double *vals,int x) {
		int i;
		matrix p;
		p.m=x;
		p.n=x;
		p.a=new double[sizeof(double)*x*x];
		for(i=0;i<x*x;i++) {
			if(i%(x+1)==0) p.a[i]=vals[i/(x+1)];
			else p.a[i]=0;
		}
		return p;
		}
	matrix matrix::transpose() {
		int i,j;
		matrix p;
		p.m=n;
		p.n=m;
		p.a=new double[sizeof(double)*m*n];
		for(i=0;i<n;i++) 
			for(j=0; j<m;j++) 
				p.a[i*m+j]=a[i+n*j];
		return p;
		}
	matrix matrix::reshape(int x,int y) {
		if(x*y!=m*n) throw err("Matrix sizes don't match");
		m=x;
		n=y;
		return *this;
	}
	matrix matrix::operator+ (const matrix &p) {
		int i;
		if((m!=p.m)or(n!=p.n)) throw err("Sizes don't match");
		matrix t;
		t.m=m;
		t.n=n;
		t.a=new double[sizeof(double)*m*n];
		for(i=0;i<m*n;i++) t.a[i]=a[i]+p.a[i];
		return t;
		}
	matrix matrix::operator+= (const matrix &p) {
		int i;
		if((m!=p.m)or(n!=p.n)) throw err("Sizes don't match");
		for(i=0;i<m*n;i++) a[i]=a[i]+p.a[i];
		return *this;
		}
	matrix matrix::operator- (const matrix &p) {
		int i;
		if((m!=p.m)or(n!=p.n)) throw err("Sizes don't match");
		matrix t;
		t.m=m;
		t.n=n;
		t.a=new double[sizeof(double)*m*n];
		for(i=0;i<m*n;i++) t.a[i]=a[i]-p.a[i];
		return t;
		}
	matrix matrix::operator-= (const matrix &p) {
		int i;
		if((m!=p.m)or(n!=p.n)) throw err("Sizes don't match");
		for(i=0;i<m*n;i++) a[i]=a[i]-p.a[i];
		return *this;
		}
	matrix matrix::operator* (const matrix &p) {
		int i,j,k;
		double s;
		if((m!=p.n)or(n!=p.m)) throw err("Sizes don't match");
		matrix t;
		t.m=m;
		t.n=m;
		t.a=new double[sizeof(double)*m*m];
		for(i=0;i<m;i++)
			for(j=0;j<m;j++) {
					s=0;
					for(k=0;k<n;k++) 
						s+=a[i*n+k]*p.a[k*m+j];
					t.a[i*m+j]=s;
				}
		return t;
		}
	matrix matrix::operator*= (const matrix &p) {
		int i,j,k;
		double s;
		if((m!=p.n)or(n!=p.m)) throw err("Sizes don't match");
		matrix t;
		t.m=m;
		t.n=m;
		t.a=new double[sizeof(double)*m*m];
		for(i=0;i<m;i++)
			for(j=0;j<m;j++) {
					s=0;
					for(k=0;k<n;k++) 
						s+=a[i*n+k]*p.a[k*m+j];
					t.a[i*m+j]=s;
				}
		*this=t;
		return *this;
		}
	matrix matrix::operator- () {
		int i;
		for(i=0;i<m*n;i++) a[i]=-a[i];
		return *this;
		}
	int matrix::operator== (const matrix &p) {
		int i;
		if((m!=p.m)or(n!=p.n)) throw err("Sizes don't match");
		for(i=0;i<m*n;i++) 
			if(abs(a[i]-p.a[i])>eps) return 0;
		return 1;
		}
	int matrix::operator!= (const matrix &p) {
		int i;
		if((m!=p.m)or(n!=p.n)) throw err("Sizes don't match");
		for(i=0;i<m*n;i++) 
			if(abs(a[i]-p.a[i])>eps) return 1;
		return 0;
		}
	matrix matrix::sorted(bool descending=false) {
		int i,j,k;
		double tmp;
		matrix t;
		t.m=m;
		t.n=n;
		t.a=new double[sizeof(double)*m*n];
		for(i=0;i<(m+1)*(n+1);i++) t.a[i]=a[i];
		for(k=0;k<m;k++) 
			for(i=k*n;i<(k*n+n-1);i++)
				for(j=i;j<(k*n+n);j++){
					if(descending==false) {
						if(t.a[i]>t.a[j]){
							tmp=t.a[i];
							t.a[i]=t.a[j];
							t.a[j]=tmp;
							}
					}
					else {
						if(t.a[i]<t.a[j]){
							tmp=t.a[i];
							t.a[i]=t.a[j];
							t.a[j]=tmp;
						}
					}
				}				
		return t;
		}
			
	matrix matrix::max(int k=1) {
		int i,j;
		matrix t=this->sorted(true);
		matrix p;
		p.m=m;
		p.n=k;
		p.a=new double[sizeof(double)*m*k];
		for(i=0;i<m;i++) 
			for(j=0;j<k;j++){
				p.a[i*k+j]=t.a[n*i+j];
				}
		return p;
		}
	void matrix::print_m() {
		int i,j;
		std::ofstream o("tmp.txt");
		for(i=0;i<m;i++) {
			for(j=0;j<n;j++) 
				o<<a[i*n+j]<<"   ";
			o<<std::endl;
			}
		o.close();
		}

const double matrix::eps=0.01;
