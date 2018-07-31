#include"iostream"
#include"cstring"
#include"stdio.h"
#include"stdlib.h"
#include"fstream"
using namespace std;

struct Data{
	char add[10];
	char data[100];
	int x;

};
typedef struct Data data;

int process1(char s){
	return (int(s)<60? int(s)-48 : int(s)-55);
}

int sum1(int sum,char s1,char s2){
	int t1 = process1(s1);
	int t2 = process1(s2);
	sum +=t1*16+t2;
	if(sum>256){	//neu char s3 la ki tu x
		sum = sum-256;
	}
	return sum;
}

int sum2(int sum,char s0,char s1,char s2,char s3){
	int t1 = process1(s1);
	int t2 = process1(s2);
	int t3 = process1(s3);
	int t0 = process1(s0);
	sum +=t0*16*16*16+t1*16*16+16*t2+t3+1;		//count from 0
	return sum;
}

checksum(int count, char s[100],int err){
	int sum = 0;
	char s1,s2;
	for(int i=2;i<100;i=i+2){
		if(s[i]!=0 &&s[i]!='\n'){
			s1=s[i];
			s2 = s[i+1];
//					cout<<s1<<s2<<endl;
			sum = sum1(sum,s1,s2);
		}
	}	
	if(sum!=255){		//tong = FF
		cout<<"\nloi check sum o dong "<<count<<" :"<<endl;
		err+=1;
		puts(s);
	}
	return err;
}

bytecount(int count,char s[100],int err){
	char b[2];
	b[0] = s[2];
	b[1] = s[3];
	int sum = 0;
	sum+=sum2(sum,'0','0',b[0],b[1]);
	int d = 0;			//bien dem
	for(int i=2;i<100;i=i+2){
		if(s[i]!=0 &&s[i]!='\n'){
			d+=1;
		}
	}

	if(d!=sum){
		err = err + 1;
		cout<<"loi byte count o dong : "<<count<<endl;
		puts(s);
	}
	return err;
	
}

checkword(int count,char s[100],int err){
	int k =0;
	for(int i=1;i<100;i++){	//ktra tu ki tu thu 2
		if(s[i]!='\n'&&s[i]!='\0'&&s[i]!='0' &&s[i]!='1'&&s[i]!='2'&&s[i]!='3'&&s[i]!='4'&&s[i]!='5'&&s[i]!='6'&&s[i]!='7'&&s[i]!='8'&&s[i]!='9'&&s[i]!='A'&&s[i]!='B'&&s[i]!='C'&&s[i]!='D'&&s[i]!='E'&&s[i]!='F'){
			k+=1;
		}
	}
	if(k>0){
		err = err+1 ;
		cout<<"ki tu k hop le dong "<<count<<endl;
		puts(s);
	}
	return err;
}

data checkadd(int count,char s[100],data *t){
	int l=0;
	for(int i=0;i<100;i++){
		if(s[i]=='\n'){
			l = i;	
		}
	}
	if(s[1]=='0' || s[1]=='1' || s[1]=='9' ||s[1]=='5'){
		t->x = 4;				//16 bit
	}
	else if(s[1]=='2' || s[1]=='8'){
		t->x = 6;			//24 bit
	}
	else{
		t->x = 8;			//32 bit
	}
	for(int i=0;i<l-4;i++){
		if(i<t->x){
			t->add[i]= s[i+2]; 
		}
		else{
			t->data[i-(t->x)] =s[i+2]; 
		}
	}

}

save(int count,char s[100],int err){
	int l=0;
	data *t;
	t = (data *)calloc(1,sizeof(data));
	if(err>0){
//		cout<<"err = "<<err<<endl;
	}
	else{
		checkadd(count,s,t);
		cout<<" writing..."<<endl;
		fstream f;
		f.open("write_srecord.txt",ios ::app);
//		f.open("write_freg.txt",ios ::app);8
		f<<t->add <<" <------- "<<t->data;	//ghi temp vao f
		f<<endl;
		f.close();
	}	
}

process(char s[100],int count,int err){
	char s1 = s[0],s2 = s[1];
	if(s1=='S' ){			//ki tu dau la S
		err+=checkword(count,s,err);
		err+=checksum(count,s,err);
		err+=bytecount(count,s,err);
		save(count,s,err);

	}
	else if(s[0]!=0){
		cout<<"loi ki tu S dau tien "<<endl;
		cout<<"loi o dong "<<count<<" :"<<endl;
			for(int i=0;i<100;i++){
				cout<<s[i];	
			}
		cout<<endl;	
	}

}


int main(int argc, char** argv) {
	FILE *fp;
	int count=0;
	int err = 0;
	char str[100];
//	fp = fopen("freg","r");
	fp = fopen("srecord_example","r");
	if(fp==NULL){
		cout<<"can't read file"<<endl;
	}

	while(!feof(fp)){
		for(int i=0;i<100;i++){
			str[i]=0;		//cac gia tri trong day tra ve null
		}

		char *s;
		fgets(str,100,fp);	//copy tung dong vao trong mang str
		count +=1;

		process(str,count,err);
	}
	cout<<"\ndone"<<endl;
	
	return 0;
}
