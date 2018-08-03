//khai bao thu vien can dung

#include"stdio.h"
#include"stdlib.h"
#include"conio.h"

struct Data{						//tao struct Data gom
	char add[10];					//bien luu dia chi gom 10 ki tu
	char data[100];					//bien luu data gom 100 ki tu
	int count_add;					//bien dem so ki tu add trong string

};
typedef struct Data data;			//dinh nghia kieu du lieu moi

int process1(char s){				//ham bien doi ki tu ve dang int
	int t;
	if(s<='9'){
		t =(int) s - 48; 
	}		//tra ve ki tu dang int dua theo bang ASCII
	else if(s <='F') {
		t =(int) s - 55; 
	} 
	return (t);
}
	

int sum1(int sum,char s1,char s2){			//tinh sum sau khi truyen 2 ki tu s1s2
	int t1 = process1(s1);					//t1 la kieu int sau khi bien doi char s1
	int t2 = process1(s2);					//t2 la kieu int sau khi bien doi char s2
	sum +=t1*16+t2;							//bien doi 2 ki tu s1s2 ve dang decimal. tong sum = ki tu dau nhan voi 16 cong voi ki tu tiep theo
	if(sum>256){							//neu tong > 256 (FF)
		sum = sum-256;						//tong sum = tong -256 . ta chi xet 2 ki tu cuoi
	}
	return sum;								//tra ve bien ket qua sum
}

int sum2(int sum,char s0,char s1,char s2,char s3){		//tinh sum sau khi truyen them 4 ki tu s0s1s2s2s3
	int t0 = process1(s0);								//t0 la kieu int sau khi bien doi char s0
	int t1 = process1(s1);								//t1 la kieu int sau khi bien doi char s1
	int t2 = process1(s2);								//t2 la kieu int sau khi bien doi char s2
	int t3 = process1(s3);								//t3 la kieu int sau khi bien doi char s3
	sum +=t0*16*16*16+t1*16*16+16*t2+t3+1;				//tinh tong sum  t0 t1 t2 t3 tuong ung voi hexa 
	return sum;											//tra ve bien sum
}

checksum(int count, char s[100],int err){
	int sum = 0,i;									//tao bien sum = 0;
	char s1,s2;										//khai bao bien s1s2 luu 2 gia tri lien tiep trong s
	for(i=2;i<100;i=i+2){						//cho bien i chay tu 0 den 100 voi step = 2
		if(s[i]!=0 &&s[i]!='\n'){					//chay den khi het dong
			s1=s[i];								//ki tu s1 = s[i]
			s2 = s[i+1];							//ki tu s2 = s[i+1]
//			cout<<s1<<s2<<endl;						//hien thi ki tu s1s2
			sum = sum1(sum,s1,s2);					//sum = ket qua sau khi thuc hien ham sum1
		}
	}	
	if(sum!=255){									//neu tong sum khac 255 (tong sum khac FF)
		printf("\nloi check sum o dong %d\n",count);
		err+=1;										//tang bien error len 1
		puts(s);									//hien thi dong string loi	
	}
	return err;										//tra ve bien error
}

bytecount(int count,char s[100],int err){
	char b[2];										//string luu 2 ki tu dau cua byte count (so byte)
	b[0] = s[2];									//b0 la ki tu dau
	b[1] = s[3];									//b1 la ki tu cuoi
	int sum = 0,i;									//cho bien sum = 0 dang int
	sum+=sum2(sum,'0','0',b[0],b[1]);				//chuyen byte count sang dang int
	int dem = 0;									//bien dem cac ki tu sau dong by
	for(i=2;i<100;i=i+2){						//ta khong dem 2 ki tu dau
		if(s[i]!=0 &&s[i]!='\n'){					//dem den khi het dong
			dem+=1;									//bien dem tang len 1
		}
	}

	if(dem!=sum){												//neu so ki tu dem duoc khac byte count
		err = err + 1;										//err tang len 1
		printf("\nloi check sum o dong %d\n",count);			//hien thi dong cho loi byte count dong
		puts(s);									//hien thi dong loi
	}
	return err;										//tra ve so loi trong ham con
	
}

checkword(int count,char s[100],int err){			//kiem tra loi ki tu trong string s va tra ve gia tri error
	int i,kiemTra =0;									//ktra luu so ki tu khong hop le
	for(i=1;i<100;i++){							//ktra tu ki tu thu 2 .  Neu ma ki tu khac voi ma hexa
		if(s[i]!='\n'&&s[i]!='\0'&&s[i]!='0' &&s[i]!='1'&&s[i]!='2'&&s[i]!='3'&&s[i]!='4'&&s[i]!='5'&&s[i]!='6'&&s[i]!='7'&&s[i]!='8'&&s[i]!='9'&&s[i]!='A'&&s[i]!='B'&&s[i]!='C'&&s[i]!='D'&&s[i]!='E'&&s[i]!='F'){
			kiemTra +=1;							//tang bien kiemtra len 1
		}
	}
	if(kiemTra > 0){									//neu xuat hien ki tu khong thuoc hexa
		err = err+1 ;									//err = err +1;
		printf("ki tu k hop le dong %d : \n",count);		//hien thi dong ki tu khong hop le
		puts(s);										//hien thi dong string co ki tu ko hop le
	}
	return err;
}

checkadd(int count,char s[100],data *t,int countAddS5){
	int l=0,i;							//l la bien luu do dai ki tu khac NULL trong string s ta truyen
	for(i=0;i<100;i++){				//cho i chay tu 0 den 100
		if(s[i]=='\n'){					//neu gap ki thu ket thuc dong
			l = i;						//gan l =i
		}
	}
	if(s[1]=='0' || s[1]=='1' || s[1]=='9'){		//neu la S0 hoac S1 hoac S9 data la dang 16 bit
		t->count_add = 4;							//so ki tu address dong  = 4 ki tu sau do 
		countAddS5 = t->count_add;					//countAddS5 = so ki tu dong truoc no
	}
	else if(s[1]=='2' || s[1]=='8'){				//neu la S2 S8 data line 24 bit 
		t->count_add = 6;							// so ki tu address  = 6 ki tu tiep theo 
		countAddS5 = t->count_add;					//countAddS5 = so ki tu dong truoc no
	}	
	else if(s[1]=='3' || s[1]=='7'){				//neu S3 hoac S7 data line 32 bit
		t->count_add = 8;							//address = 8 ki tu tiep thep
		countAddS5 = t->count_add;					//gan countAddS5 = so ki tu dong truoc no
	}
	else {											//neu S5
		t->count_add = countAddS5;					//so ki tu bang countS5
	}
	for(i=0;i<l-4;i++){							//cho i chay tu 0 den ki tu xuong dong -4.tru 4 tru 2 ki tu dau va 2 ki tu checksum o cuoi string
		if(i<t->count_add){							// neu i ma nho hon so ki tu dia chi dong do
			t->add[i]= s[i+2]; 						//gan address vi tri i = gia tri stringo vi tri i+2 //o day ta k luu 2 ki tu dau tien
		}
		else{
			t->data[i-(t->count_add)] =s[i+2]; 
		}
	}

	return countAddS5;				//tra ve so ki tu address  dong  S5

}

save(int count,char s[100],int err,int countAddS5){
	data *t;												//khai bao 1 co tro t kieu data
	t = (data *)calloc(1,sizeof(data));						//tao kich thuoc de luu du lieu address va data trong dong
	if(err>0){												//neu error > 0 - dong xuat hien loi
//		cout<<"err = "<<err<<endl;							//hien thi error
	}
	else{
		countAddS5 = checkadd(count,s,t,countAddS5);		//so ki tu address truoc dong s5 gan ban result ham check add
		printf(" writing...\n");							//hien thi dong chu writing
		FILE *write;
//		write = fopen("Result_read_Srecord.txt","a+");		//mo file che do a+
		write = fopen("Result_read_Freg.txt","a+");			//mo file che do a+
		fputs(t->add,write);								//ghi address vao file
		fputs("<-----",write);								//ghi ki tu <----- vao file
		fputs(t->data,write);								//ghi data vao file
		fputs("\n",write);					 				//ghi xuong dong file
		fclose(write);										//dong file ghi
	}

	return countAddS5;			//tra ve so ki tu address cua dong truoc dong S5
}

process(char s[100],int count,int err,int countAddS5){		//xu lu dong str sau khi lay ra tu file va countAddS5
	char s1 = s[0],s2 = s[1];						//s1,s2 luu ki tu thu nhat va thu 2 cua string s
	int i;
	if(s1=='S' ){			//neu ki tu dau tien la S
		if(s[1]<'0' || s[1]>'9'){		//neu ki tu thu 2 khac 0 hoac 9
			printf(" ki tu sau S k hop le dong %d",count);	//hien thi "ki tu sau S k hop le'
			puts(s);											//hien thi dong string s truyen vao
		}
		else{													//neu  ki tu thu 2 la 0 hoac 9
			err+=checkword(count,s,err);						//cong cac loi sau khi kiem tra  cac ki tu trong string s truyen vao
			err+=checksum(count,s,err);							//cong cac loi sau khi kiem tra check sum cac ki tu trong string s truyen vao
			err+=bytecount(count,s,err);						//cong cac loi sau khi kiem tra  byte count trong string s truyen vao
			countAddS5 = save(count,s,err,countAddS5);			//countAddS5  = gia tri tra ve sau khi thuc thi ham save
		}
		

	}
	else if(s[0]!=0){											//Neu ki tu dau tien khac NULL va khac S
		printf("loi ki tu S dau tien \n");					//Hien thi loi ki tu S dau tien
		printf("loi o dong %d ",count);					//in ra loi o dong 
			for(i=0;i<100;i++){								//cho i chay tu 0 -> 100
				printf("%d",s[i]);										//hien tung phan tu cua string s ma ta dua vao
			}
		printf("\n");												//hien thi ki tu xuong dong
	}

	return countAddS5;											//ket qua tra ve so ki tu address cua dong truoc dong S5
}


int main(int argc, char** argv) {
	FILE *fp, *write;								//con tro fp dung trong FILE
	int i;
	int count=0;							//bien dem cac dong trong file
	int err = 0;							//bien luu loi trong moi dong
	int countAddS5 = 0;						//bien luu so ki tu trong dong S5
	char str[100];							//string luu gia tri moi dong duoc lay tu file
	fp = fopen("freg","r");
	write = fopen("Result_read_Freg.txt","a+");
//	fp = fopen("srecord_example","r");			//mo file srecord che do chi doc
//	write = fopen("Result_read_Srecord.txt","a+");
	if(fp==NULL){								//neu file trong
		printf("can't read file\n");			//hien thi khong doc duoc file
	}

	while(!feof(fp)){							//file co data
		for(i=0;i<100;i++){					//cho i chay tu 0 den 100
			str[i]=0;							//cho mang str ve NULL
		}
		fgets(str,100,fp);						//copy tung dong trong file fp vao trong mang str
		count +=1;								//khi doc 1 dong thi bien count tang len 1
		countAddS5 = process(str,count,err,countAddS5);			//bien luu so ki tu address dong S5 = ket qua return cua ham process
																//countAddS5 = so ki tu addess cua bit dung truoc dong S5
	}
	printf("\ndone");						//hien thi ki tu done khi ket thuc chuong trinh
	
	return 0;
}
