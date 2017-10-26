#include "matrix.hpp"

int main() {
	int k=0;
	try{
		char buf[50];
		int p;
		matrix m(1);
		m.print_m();
		p=0;
		ifstream o1("tmp.txt");
		while (o1) {
			o1>>buf;
			if(o1) p++;
		}
		o1.close();
		remove("tmp.txt");
		cout<<"Testing constr(double): ";
		if((strcmp(buf,"1")==0)&&(p==1)){
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"constr(double) not working; error"<<endl;
		cout<<"Testing double indexing: ";
		if((strcmp(buf,"1")==0)&&(m[0][0]==1)){
			k++;
			cout<<"found the matrix element; fine"<<endl;
		}
		else cout<<"couldn't find the element; error"<<endl;
		cout<<"Testing columns: ";
		if(m.columns()==1){
			cout<<"fine"<<endl;
			k++;
		}
		else cout<<"not working; error"<<endl;
		cout<<"Testing rows: ";
		if(m.rows()==1) {
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"not working; error"<<endl;
		m[0][0]=5;
		cout<<"Testing if operator = works: ";
		if(m[0][0]==5) {
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"element changing not working; error"<<endl;
		matrix m1("{{1.0,2},{5,3.8}}");
		cout<<"Testing constr(string): ";
		if((m1[0][0]==1)&&(m1[0][1]==2)&&(m1[1][0]==5)&&(m1[1][1]==3.8)&&(m1.columns()==2)&&(m1.rows()==2)){
			k++;
			cout<<"is working; fine"<<endl;
		}
		else cout<<"not working; error"<<endl;
		matrix m2=matrix::identity(3);
		cout<<"Testing if identity works fine: ";
		if((m2[1][1]==1)&&(m2[2][1]==0)&&(m2.columns()==3)&&(m2.rows()==3)){
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"identity not working; error"<<endl;
		m2.set(2,1,5);
		cout<<"Testing if set works: ";
		if(m2[2][1]==5){
			k++;
			cout<<"element set; fine"<<endl;
		}
		else cout<<"set not working; error"<<endl;
		matrix m4=m2.sorted(true);
		cout<<"Testing if function sorted works: ";
		if((m4[1][0]==1)&&(m4.columns()==m2.columns())&&(m4.rows()==m2.rows())&&(m4[0][0]==1)&&(m4[0][1]==0)) {
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"sorted not working; error"<<endl;
		cout<<"Testing operator !=: ";
		if(matrix::identity(2)!=matrix("{{1,0},{0,1}}")) cout<<"something wrong; error"<<endl;
		else {
			k++;
			cout<<"result is equal; fine"<<endl;
		}
		matrix m5("{{3.5,2.8,11},{8,7.2,0}}");
		matrix m3=m5.max(2);
		cout<<"Testing function max: ";
		if((m3.columns()==2)&&(m3[0][0]==11)&&(m3.rows()==2)&&(m3[0][1]==3.5)&&(m3[1][0]==8)&&(m3[1][1]==7.2)) {
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"max not working; error"<<endl;
		m3+=matrix::identity(2);
		cout<<"Testing operator +=: ";
		if((m3[0][0]==12)&&(m3[1][0]==8)&&(m3[0][1]==3.5)&&(m3[1][1]==8.2)) {
			k++;
			cout<<"result is correct; fine"<<endl;
		}
		else cout<<"op += not working; error"<<endl;
		m3*=matrix::zero(2,2);
		cout<<"Testing operator *=: ";
		if(m3[0][0]==0) {
			k++;
			cout<<"resuilt is correct; fine"<<endl;
		}
		else cout<<"op *= not working; error"<<endl;
		-m1;
		cout<<"Testing orerator -: ";
		if((m1[0][0]==-1)&&(m1[0][1]==-2)&&(m1[1][0]==-5)&&(m1[1][1]==-3.8)&&(m1.columns()==2)&&(m1.rows()==2)) {
			k++;
			cout<<"result is correct; fine"<<endl;
		}
		else cout<<"op - not working; error"<<endl;
		matrix m7("{{12,-8,3},{6.1,7,2.5}}");
		matrix m8=m7.transpose();
		cout<<"Testing transpse: ";
		if((m8[1][0]==-8)&&(m8[0][0]==12)&&(m8[0][1]==6.1)&&(m8.columns()==2)&&(m8.rows()==3)) {
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"transpose not working; error"<<endl;
		double *v;
		v=new double[sizeof(double)*3];
		v[0]=5.8;
		v[1]=-1;
		v[2]=9.3;
		cout<<"Testing diagonal: ";
		if(matrix::diagonal(v,3)==matrix("{{5.8,0,0},{0,-1,0},{0,0,9.3}}")) {
			k++;
			cout<<"equal; fine"<<endl;
		}
		else cout<<"diagonal not working; error"<<endl;
		matrix m9;
		m9=m7*m8;
		cout<<"Testing operator *: ";
		if((m9.columns()==2)&&(m9.rows()==2)&&(m9[0][0]==217)) {
			k++;
			cout<<"result is correct; fine"<<endl;
		}
		else cout<<"op * not working; error"<<endl;
		m8=m7;
		cout<<"Testing operator =: ";
		if(m8==m7) {
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"oper = not working; error"<<endl;
		cout<<"Testing reshape: ";
		m8.reshape(2,3);
		if((m8.columns()==3)&&(m8.rows()==2)){
			k++;
			cout<<"reshaped; fine"<<endl;
		}
		else cout<<"failed to reshape; error"<<endl;
		cout<<"Testing constr of string: ";
		matrix m10(3,v);
		if((m10[0][0]==5.8)&&(m10[0][1]==-1)&&(m10[0][2]==9.3)&&(m10.rows()==1)&&(m10.columns()==3)){
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"error"<<endl;
		cout<<"Testing constr of column: ";
		matrix m11(v,3);
		if((m11[0][0]==5.8)&&(m11[1][0]==-1)&&(m11[2][0]==9.3)&&(m11.rows()==3)&&(m11.columns()==1)){
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"error"<<endl;
		cout<<"Testing zero: ";
		matrix m12=matrix::zero(2,3);
		if((m12[0][0]==0)&&(m12[1][0]==0)&&(m12[1][1]==0)&&(m12[1][2]==0)&&(m12[0][1]==0)&&(m12[0][2]==0)&&(m12.rows()==2)&&(m12.columns()==3)) {
			k++;
			cout<<"fine"<<endl;
		}
		else cout<<"error"<<endl;
		cout<<"Testing exceptions: ";
		matrix m6=m2+m5;
	}
	catch(matrix::err a) {
		k++;
		cout<<"error caught: "<<a.s<<" ;fine"<<endl;
	}
	catch(...) {
		cout<<"Unexpected error"<<endl;
	}
	cout<<k<<" tests of 23 passed"<<endl;
}
	
