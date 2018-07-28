#include"iostream"
#include"cstring"
#include"stdio.h"
#include"stdlib.h"
using namespace std;

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
//	cout<<"sum1 = "<<sum<<endl;
	return sum;
}

int sum2(int sum,char s1,char s2,char s3){
	int t1 = process1(s1);
	int t2 = process1(s2);
	int t3 = process1(s3);
	sum +=t1*16*16+16*t2+t3+1;		//count from 0
	return sum;
}

process(char s[100],int count){
	char s1 = s[0],s2 = s[1];
	if(int(s1)==83){			//ki tu dau la S
		if(int(s2)==51){	//ki tu tiep theo la 3.dang xet th S3
			int sum = 0;
//			for(int i=2;i<100;i=i+2){
			for(int i=2;i<=68;i=i+2){
				if(s[i]!=0){
					s1=s[i];
				s2 = s[i+1];
//				cout<<s1<<s2<<endl;
				sum = sum1(sum,s1,s2);
				}
			}	
			if(sum!=255){		//tong = FF
				cout<<"\nloi o dong "<<count<<" :"<<endl;
				for(int i=0;i<100;i++){
					cout<<s[i];	
				}
				cout<<endl;
			}
//			else cout<<"k loi"<<endl;
		}
			
		else if(int (s2)==53){
			int sum = 0;
			cout<<"count = "<<count<<endl;	
			sum+=sum2(sum,s[9],s[10],s[11]);	//chua tinh dong s5
			cout<<"\ntong so dong :"<<sum<<endl;
				
		}
	}

}


int main(){
	FILE *fp;
	int count=0;
	char str[100],c;
	fp = fopen("srecord_example","r");
	if(fp==NULL){
		cout<<"can't read file"<<endl;
	}

	while(!feof(fp)){
		for(int i=0;i<100;i++){
			str[i]=0;		//cac gia tri trong day tra ve null
		}
//		str = (char *)calloc(100,sizeof(char));
		char *s;
		fgets(str,100,fp);	//copy tung dong vao trong mang str
		count +=1;

		process(str,count);
	}
	cout<<"\ndone"<<endl;
	
	return 0;
}
