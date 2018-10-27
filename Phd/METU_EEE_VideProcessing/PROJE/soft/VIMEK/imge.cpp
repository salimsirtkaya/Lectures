#include "stdafx.h"
#include "imge.h"
#include <time.h>

CImge::CImge(short h, short w): width(w),height(h)
{
	int i;

	Image=new double*[height]; /*Exception!!!*/
	for (i=0;i<height;i++)
		Image[i]=new double[width]; /*Exception!!!*/
}

CImge::CImge(CGdiplusWrapper &source)
{
	width=source.m_pBmp->GetWidth();
	height=source.m_pBmp->GetHeight();
	int i;

	Image=new double*[height]; /*Exception!!!*/
	for (i=0;i<height;i++)
		Image[i]=new double[width]; /*Exception!!!*/
	BitmapData bmpdata;
	BYTE* buf;
	buf=source.GetPixels(bmpdata);
	Buff2GrayIm(buf,height,width,IMAGE);
	delete [] buf;
}

void CImge::FromFile(CString filename)
{
	CGdiplusWrapper source(filename);

	width=source.m_pBmp->GetWidth();
	height=source.m_pBmp->GetHeight();
	int i;

	Image=new double*[height]; /*Exception!!!*/
	for (i=0;i<height;i++)
		Image[i]=new double[width]; /*Exception!!!*/
	BitmapData bmpdata;
	BYTE* buf;
	buf=source.GetPixels(bmpdata);
	Buff2GrayIm(buf,height,width,IMAGE);
	delete [] buf;
}
/*COPY CONSTRUCTOR*/

CImge::CImge(const CImge& rhs)
{
	int i,j;
	width=rhs.width;
	height=rhs.height;
	Image=new double*[height]; /*Exception!!!*/
	for (i=0;i<height;i++)
		Image[i]=new double[width]; /*Exception!!!*/
	
	for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
			Image[i][j]=rhs.Image[i][j];
	}
}

/*DESTRUCTOR*/

CImge::~CImge()
{
	int i;
	for (i=0;i<height;i++)
	{
		delete[] Image[i];
		Image[i]=0;
	}
	delete[] Image;
	Image=0;
}

/* []OPERATOR for CImge */

double* CImge::operator [] (short index)
{
	return Image[index];
}

/* = OPERATOR */

CImge CImge::operator = (const CImge& rhs)
{
	if (this==&rhs)
		return *this;

	int i;
	if (width!=rhs.width && height!=rhs.height)
	{
		for (i=0;i<height;i++)
		{
			delete[] Image[i];
			Image[i]=0;
		}
		delete[] Image;
		
		height=rhs.height;
		width=rhs.width;
		Image=new double*[height];
		
		for (i=0;i<height;i++)
			Image[i]=new double[width]; 
	}

	size_t count=sizeof(double)*width;
	for (i=0;i<height;i++)
		memcpy(Image[i],rhs.Image[i],count);
	
	return *this;
}

/* () OPERATOR */

double& CImge::operator () (short i, short j)
{
	ASSERT ((i > -1)&&(i < this->height));
	ASSERT ((j > -1)&&(j < this->width));

	return Image[i][j];
}


/* + OPERATION of two CImge objects */

CImge operator + (const CImge& Addend,const CImge& Adder)
{
	ASSERT(Addend.width == Adder.width);
	ASSERT(Addend.height == Adder.height);

	CImge temp(Adder.height,Adder.width);
	int i,j;
	for (i=0;i<temp.height;i++)
	{
		for (j=0;j<temp.width;j++)
			temp.Image[i][j]=Addend.Image[i][j]+Adder.Image[i][j];
	}
	return temp;
}

/* + OPERATION of a CImge and a double */

CImge operator+ (const CImge& Translated, double Translator)
{
	CImge temp(Translated.height,Translated.width);
	int i,j;
	for (i=0;i<temp.height;i++)
	{
		for (j=0;j<temp.width;j++)
			temp.Image[i][j]=Translated.Image[i][j]+Translator;
	}
	return temp;
}


CImge operator- (const CImge&Subtracted ,const CImge& Subtractor)
{
	ASSERT(Subtracted.width == Subtractor.width);
	ASSERT(Subtracted.height == Subtractor.height);

	CImge temp(Subtractor.height,Subtractor.width);
	int i,j;
	for (i=0;i<temp.height;i++)
	{
		for (j=0;j<temp.width;j++)
			temp.Image[i][j]=Subtracted.Image[i][j]-Subtractor.Image[i][j];
	}
	return temp;
}


CImge operator- (const CImge& Translated,double Translator)
{
	CImge temp(Translated.height,Translated.width);
	int i,j;
	for (i=0;i<temp.height;i++)
	{
		for (j=0;j<temp.width;j++)
			temp.Image[i][j]=Translated.Image[i][j]-Translator;
	}
	return temp;
}


CImge operator* (const CImge&Multiplier ,double Multiplicant)
{
	CImge temp(Multiplier.height,Multiplier.width);
	int i,j;
	for (i=0;i<temp.height;i++)
	{
		for (j=0;j<temp.width;j++)
			temp.Image[i][j]=Multiplier.Image[i][j]*Multiplicant;
	}
	return temp;

}

CImge operator * (const CImge&Multiplier1 ,const CImge&Multiplier2)
{
	int h1=Multiplier1.height;
	int w1=Multiplier1.width;
	int h2=Multiplier2.height;
	int w2=Multiplier2.width;

	CImge temp(h1,w2);

	temp.SetAllPxlsTo(0);

	for (int k=0;k<h1;k++)
	{
		for (int l=0;l<w2;l++)
		{
			for(int i=0;i<w1;i++)
				temp.Image[k][l]+=Multiplier1.Image[k][i]*Multiplier2.Image[i][l];
		}
	}

	return temp;

}

void CImge::Resize(short i, short j)
{
	if((i==height)&&(j==width))
		return;

	//CImge temp(i,j);
	double**  temp;
	int ind1;
	temp=new double*[i];
	for (ind1=0;ind1<i;ind1++)
		temp[ind1]=new double[j];
	
	size_t count=sizeof(double)*width;
	for (ind1=0;ind1<height;ind1++)
		memcpy(temp[ind1],Image[ind1],count);
	for (ind1=0;ind1<height;ind1++)
	{
		delete[] Image[ind1];
		Image[ind1]=0;
	}
	delete[] Image;
	Image=0;
	Image=temp;
	height=i;
	width=j;
}

void CImge::Buff2GrayIm(unsigned char* buf, short h, short w, BUFFER_FROM buffer_from)
{
	Resize(h,w);
	int i,j;
	int b_index;

	if (buffer_from==IMAGE)
	{
		int padding=width%4;//4-((width*3)%4);
		for (i=height-1;i>=0;i--)
		{
			b_index=i*(width*3+padding);
			for (j=width-1;j>=0;j--)
				Image[i][j]=buf[j*3+b_index];
		}
	}

	else
	{
		int size, h_index;
		size=(height*width-1);
	
		for (i=height-1;i>=0;i--)
		{
			h_index=size-i*(width);
			for (j=width-1;j>=0;j--)
			{
				b_index=(h_index-j)*3;
				Image[i][width-1-j]=buf[b_index];
			}
		}

	}
}


void CImge::GrayIm2Buff(unsigned char* & buf) /* buffer'i CGdiplusWrapper nesnesine yüklemek
													istedigimizi varsayarak... (stride=4k) */
{
	int padding=width%4;//4-((width*3)%4);
	int i,j,size;
	size=height*(3*width+padding);
	buf=new unsigned char[size];
	int b_index,h_index;

	for (i=height-1;i>=0;i--)
	{
		h_index=i*(3*width+padding);
		for (j=width-1;j>=0;j--)
		{
			b_index=h_index+j*3;
			buf[b_index]=buf[b_index+1]=buf[b_index+2]=Image[i][j];
		}
	}

}
	
CImge CImge::Transpose()
{
	CImge temp=*this;

	int h=temp.height;
	int w=temp.width;

	CImge Result(w,h);

	short ind1,ind2;
	for (ind1=0;ind1<w;ind1++)
		for (ind2=0;ind2<h;ind2++)
			Result(ind1,ind2)=temp(ind2,ind1);
	return Result;
}

CImge CImge::Crop(short left_x, short left_y, short right_x, short right_y)
{
	short new_height, new_width;
	new_height=right_y-left_y+1;
	new_width=right_x-left_x+1;
	CImge temp(new_height,new_width);
	int ind1;
	size_t count=sizeof(double)*new_width;
	for (ind1=0;ind1<new_height;ind1++)
		memcpy(temp[ind1],&(Image[left_y+ind1][left_x]),count);
	return temp;
}


double CImge::Sqrd_Norm()
{
	double norm=0;
	int i,j;
	for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
			norm+=Image[i][j]*Image[i][j];
	}
	return norm;
}


double CImge::Mean()
{
	double mean=0;
	int i,j;
	for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
			mean+=Image[i][j];
	}
	return (mean/(width*height));
}

double CImge::Variance()
{
	double mean=Mean();
	double var=0;
	int i,j;
	for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
			var+=(Image[i][j]-mean)*(Image[i][j]-mean);
	}
	return (var/(width*height-1));	
}

CImge CImge::Diff_y()
{
	CImge temp=*this;

	temp.Extrapolate(1,1);

	int h=temp.height;
	int w=temp.width;

	CImge Result(h-2,w-2);

	for (int ind1=0; ind1<h-2; ind1++)
		for (int ind2=0; ind2<w-2;ind2++)
			Result(ind1,ind2)=0.5*(temp(ind1+1,ind2+2)-temp(ind1+1,ind2));

	return Result;
}

CImge CImge::Diff_x()
{
	CImge temp=*this;

	temp.Extrapolate(1,1);

	int h=temp.height;
	int w=temp.width;

	CImge Result(h-2,w-2);
	
	for (int ind1=0; ind1<h-2; ind1++)
		for (int ind2=0; ind2<w-2;ind2++)
			Result(ind1,ind2)=0.5*(temp(ind1+2,ind2+1)-temp(ind1,ind2+1));
	return Result;
}

CImge CImge::Abs()
{
	CImge temp=*this;

	int h=temp.height;
	int w=temp.width;

	CImge Result(h,w);
	
	for (int ind1=0; ind1<h; ind1++)
		for (int ind2=0; ind2<w;ind2++)
			Result(ind1,ind2)=abs(temp(ind1,ind2));
	return Result;
}

void CImge::Feature_inv(CImge &I_x, CImge &I_y,int wind)
{
	CImge temp=*this;

	CImge vec(2,2);

	int h=temp.height;
	int w=temp.width;
	int win_x;
	int win_y;
	double eig;
	int maxFeatureNo = 100;
	double grad_threshold = 4500.0;

	CImge Grad(2,2);
	CImge Eig(h,w);


	Eig.SetAllPxlsTo(0);

	/*see the random function with current time so that we'll have a different random number at each run*/
	srand( (unsigned)time( NULL ) );
	Feature_no=0;
	int x,y;
	int iter =0;
	int inner_iter=0;

	/*Randomly select 100 feature points that have an intensity gradient 
	  greater than a prescribed threshold*/

	while(Feature_no < maxFeatureNo)
	{
		/*randomly select a point on the image*/
		x = (int) h * ((double)rand() / RAND_MAX );
		y = (int) w * ((double)rand() / RAND_MAX );	

		/*check whether the randomly selected point is inside the gardient calculation area*/
		if (x<=wind)
			x = x + wind + 1;
		if (x>=(h-wind))
			x = x - wind - 1;
		if (y<=wind)
			y = y + wind + 1;
		if (y>=(w-wind))
			y = y - wind - 1;

		
		/*Calculate the intensity gradient matrix of this point*/
		Grad.SetAllPxlsTo(0);
		
		for (win_x=x-wind;win_x<=x+wind;win_x++)
		{
			for(win_y=y-wind;win_y<=y+wind;win_y++)
			{
				Grad(0,0)+=pow(I_x(win_x,win_y),2);
				Grad(0,1)+=I_x(win_x,win_y)*I_y(win_x,win_y);
				Grad(1,1)+=pow(I_y(win_x,win_y),2);
			}
		}
		
		Grad(1,0)=Grad(0,1);
		
		double* val=new double[2];
		
		Grad.Eigen(val,vec);
		
		if (val[0]>=val[1])
			eig=val[1];
		else
			eig=val[0];
		
		Eig(x,y)=eig;
		delete[] val;
		
		if (Eig(x,y) > grad_threshold)
		{
			mFeature[Feature_no].x = (double)x;
			mFeature[Feature_no].y = (double)y;
			Feature_no++;		
		}

		iter++;

		if (iter > 1000*(inner_iter+1))
		{
			inner_iter++;
			grad_threshold = grad_threshold / (inner_iter+1);
		}
	}
}

CImge CImge::Product(double a)
{
	CImge temp=*this;

	int h=temp.height;
	int w=temp.width;

	CImge Result(h,w);
	
	for (int ind1=0; ind1<h; ind1++)
		for (int ind2=0; ind2<w;ind2++)
			Result(ind1,ind2)=a*temp(ind1,ind2);
	return Result;

}

CImge CImge::Interpolate(short h_new,short w_new)
{
//	Resize(h_new,w_new);
	CImge	temp(h_new,w_new);
	CImge paddedSource=*this;
	float*	h_new_indices=new float[h_new];
	float*	w_new_indices=new float[w_new];
	float	w_ratio, h_ratio;
	int		i, j, m, n;
	int		i_src, j_src;
	double	new_pixel;

	paddedSource.Extrapolate(2,2);
	w_ratio=(float)(width-1)/(w_new-1);
	h_ratio=(float)(height-1)/(h_new-1);

	if (h_new<w_new)
	{
		for (i=0;i<h_new;i++)
		{
			h_new_indices[i]=i*h_ratio+2;
			w_new_indices[i]=i*w_ratio+2;
		}
		for (i=h_new;i<w_new;i++)
			w_new_indices[i]=i*w_ratio+2;
	}
	else
	{
		for (i=0;i<w_new;i++)
		{
			h_new_indices[i]=i*h_ratio+2;
			w_new_indices[i]=i*w_ratio+2;			
		}
		for (i=w_new;i<h_new;i++)
			h_new_indices[i]=i*h_ratio+2;
	}

	for (i=0;i<h_new;i++)
	{
		for (j=0;j<w_new;j++)
		{
			i_src=h_new_indices[i];
			j_src=w_new_indices[j];
			new_pixel=0;
			for (m=-1;m<3;m++)
			{
				for (n=-1;n<3;n++)
					new_pixel+=paddedSource(i_src+m,j_src+n)*WeightFunc(m-h_new_indices[i]+i_src)*WeightFunc(w_new_indices[j]-j_src-n);
			}
			temp(i,j)=new_pixel;
		}
	}

	delete[] h_new_indices;
	delete[] w_new_indices;
	return temp;
}


void CImge::tri_diagonalize(double *d,double *e, CImge &A, double tol)
{
	int i, j, k, l;
	double f, g, h, hh;
	int L=width;

	for (i = 0; i < L; i++) 
		for (j = 0; j <= i; j++) 
			A(i, j) = Image[i][j];

	for (i = L - 1; i > 0; i--) 
	{
		l = i - 2;
		f = A(i, i - 1);
		g = 0.0;
		for (k = 0; k <= l; k++) 
		{
			g += A(i,k)*A(i,k);
		}
		h = g + f*f;
		if (g <= tol) {
			e[i] = f;
			h = 0.0;
			d[i] = h;
			continue;
		}
		l++;
		g = sqrt(h);
		if (f >= 0.0) g = -g;
		e[i] = g;
		h = h - f*g;
		A(i,i - 1) = f - g;
		f = 0.0;
		for (j = 0; j <= l; j++) {
			A(j , i) = A(i,j)/h;
			g = 0.0;
			for (k = 0; k <= j; k++) {
				g += A(j,k)*A(i,k);
			}
			for (k = j + 1; k <= l; k++) {
				g += A(k,j)*A(i,k);				
			}
			e[j] = g/h;
			f += g*A(j,i);
		}
		hh = f/(h + h);
		for (j = 0; j <= l; j++) {
			f = A(i,j);
			g = e[j] - hh*f;
			e[j] = g;
			for (k = 0; k <= j; k++) {
				A(j,k) = A(j,k) - f*e[k] - g*A(i,k);
			}
		}
		d[i] = h;
	}
	d[0] = e[0] = 0.0;
	for (i = 0; i < L; i++) {
		l = i - 1;
		if (d[i] != 0.0) {
			for (j = 0; j <= l; j++) {
				g = 0.0;
				for (k = 0; k <= l; k++) {
					g += A(i,k)*A(k,j);
				}
				for (k = 0; k <= l; k++) {
					A(k,j) = A(k,j) - g*A(k,i);
				}
			}
		}
		d[i] = A(i,i);
		A(i,i) = 1.0;
		for (j = 0; j <= l; j++) {
			A(i,j) = A(j,i) = 0.0;
		}
	}
}


int CImge::calc_eigenstructure(double *d, double *e, CImge &A, double macheps)
{
	int i, j, k, l, m;
	double b, c, f, g, h, p, r, s;
	int L=width;
	for (i = 1; i < L; i++) e[i - 1] = e[i];
	e[L - 1] = b = f = 0.0;
	for (l = 0; l < L; l++) {
		h = macheps*(fabs(d[l]) + fabs(e[l]));
		if (b < h) b = h;
		for (m = l; m < L; m++) {
			if (fabs(e[m]) <= b) break;
		}
		j = 0;
		if (m != l) do {
			if (j++ == 30) return -1;
			p = (d[l + 1] - d[l])/(2.0*e[l]);
			r = sqrt(p*p + 1);
			h = d[l] - e[l]/(p + (p < 0.0 ? -r : r));
			for (i = l; i < L; i++) d[i] = d[i] - h;
			f += h;
			p = d[m];
			c = 1.0;
			s = 0.0;
			for (i = m - 1; i >= l; i--) {
				g = c*e[i];
				h = c*p;
				if (fabs(p) >= fabs(e[i])) {
					c = e[i]/p;
					r = sqrt(c*c + 1);
					e[i + 1] = s*p*r;
					s = c/r;
					c = 1.0/r;
				} else {
					c = p/e[i];
					r = sqrt(c*c + 1);
					e[i + 1] = s*e[i]*r;
					s = 1.0/r;
					c = c/r;
				}
				p = c*d[i] - s*g;
				d[i + 1] = h + s*(c*g + s*d[i]);
				for (k = 0; k < L; k++) {
					h = A(k,i + 1);
					A(k , i + 1) = s*A(k,i) + c*h;
					A(k,i) = c*A(k,i) - s*h;
				}
			}
			e[l] = s*p;
			d[l] = c*p;
		} while (fabs(e[l]) > b);
		d[l] = d[l] + f;
	}

/* order the eigenvectors  */
	for (i = 0; i < L; i++) {
		k = i;
		p = d[i];
		for (j = i + 1; j < L; j++) {
			if (d[j] < p) {
				k = j;
				p = d[j];
			}
		}
		if (k != i) {
			d[k] = d[i];
			d[i] = p;
			for (j = 0; j < L; j++) {
				p = A(j,i);
				A(j,i) = A(j,k);
				A(j,k) = p;
			}
		}
	}
	return 0;
}


int CImge::Eigen(double* val, CImge &Vec)
{
	double tol=1.0e-8, macheps=1.0e-8;
	double* e=new double[width];
	tri_diagonalize(val,e,Vec,tol);
	return calc_eigenstructure(val,e,Vec,macheps);
	delete [] e;
}

void CImge::MinMax(double& mn, double& mx, int& indx, int& indy)
{
	mn=LONG_MAX;
	mx=LONG_MIN;

	for(int ind1=0;ind1<height;ind1++)
	{
		for (int ind2=0; ind2<width;ind2++)
		{
			mn=(mn<Image[ind1][ind2])?mn:Image[ind1][ind2];
			if(Image[ind1][ind2]>mx)
			{
				mx=Image[ind1][ind2];
				indx=ind1;
				indy=ind2;
			}
			
			//mx=(mx>Image[ind1][ind2])?mx:Image[ind1][ind2];
									
		}
	}
}

void CImge::Extrapolate(int row, int col)
{
	double**  temp;
	int ind1,ind2;
	temp=new double*[height+2*row];
	for (ind1=0;ind1<height+2*row;ind1++)
		temp[ind1]=new double[width+2*col];
	
	size_t count=sizeof(double)*width;
	for (ind1=0;ind1<height;ind1++)
		memcpy(&temp[ind1+row][col],Image[ind1],count);
	for(ind1=0;ind1<row;ind1++)
	{
		memcpy(&temp[ind1][col],Image[row-ind1-1],count);
		memcpy(&temp[height+ind1+row][col],Image[height-1-ind1],count);
	}
	for(ind1=0;ind1<col;ind1++)
	{
		for (ind2=0;ind2<height+2*row;ind2++)
		{
			temp[ind2][ind1]=temp[ind2][2*col-ind1-1];
			temp[ind2][width+col+ind1]=temp[ind2][width-1-ind1+col];
		}
	}

	for (ind1=0;ind1<height;ind1++)
	{
		delete[] Image[ind1];
		Image[ind1]=0;
	}
	delete[] Image;
	Image=0;
	Image=temp;
	height=height+2*row;
	width=width+2*col;
}

#define Kernell(I,x,y)  0.1406 *I(2*(x),2*(y)) + 0.0938 *(I(2*(x)-1,2*(y))+I(2*(x),2*(y)-1)+I(2*(x)+1,2*(y))+I(2*(x),2*(y)+1))+\
	0.0625*(I(2*(x)-1,2*(y)-1)+I(2*(x)-1,2*(y)+1)+I(2*(x)+1,2*(y)-1)+I(2*(x)+1,2*(y)+1))+0.0156*(I(2*(x)-1,2*(y)-2)+I(2*(x)-2\
	,2*(y)-1)+I(2*(x)-2,2*(y)+1)+I(2*(x)+1,2*(y)-2)+I(2*(x)+2,2*(y)-1)+I(2*(x)+2,2*(y)+1)+I(2*(x)+1,2*(y)+2)+I(2*(x)-1,\
	2*(y)+2))+0.0234*(I(2*(x),2*(y)+2)+I(2*(x),2*(y)-2)+I(2*(x)-2,2*(y))+I(2*(x)+2,2*(y)))+0.0039*(I(2*(x)-2,2*(y)-2)\
	+I(2*(x)-2,2*(y)+2)+I(2*(x)+2,2*(y)-2)+I(2*(x)+2,2*(y)+2))

CImge CImge::PyramidSeed()
{
	CImge temp=*this;
	int h_new=(int)temp.height/2;
	int w_new=(int)temp.width/2;
	temp.Extrapolate(2,2);
	CImge res(h_new,w_new);
	for(int ind1=0;ind1<res.height;ind1++)
		for(int ind2=0;ind2<res.width;ind2++)
			res(ind1,ind2)=Kernell(temp,(ind1+1),(ind2+1));
	return res;
}

CImge CImge::Inverse()
{
	CImge temp=*this;

	CImge result(2,2);

	double det=0;

	det=temp(0,0)*temp(1,1)-temp(0,1)*temp(1,0);


	result(0,0)=1/det*temp(1,1);
	result(0,1)=1/det*-temp(0,1);
	result(1,0)=1/det*-temp(1,0);
	result(1,1)=1/det*temp(0,0);

	return result;
}

CImge CImge::Inv()
{
	short i,nc,ind1;
	CImge index(1,height);
	CImge LU;
	index.SetAllPxlsTo(0);
	LU=*this;
	double sign=1.0,tol=1e-10;
	crout(LU,index,sign,tol);
	CImge dgl(height,width);
	dgl.SetAllPxlsTo(0);
	for (ind1=0;ind1<height;ind1++)
		dgl(ind1,ind1)=1;
	CImge inv(height,width);
	inv.SetAllPxlsTo(0);
	CImge b(1,height);
	b.SetAllPxlsTo(0);
	nc=width;
	for (i=0;i<nc;i++)
	{
		memcpy(b.Image[0],dgl.Image[i],sizeof(double)*width);
		luSolve(LU,index,b,tol);
		memcpy(inv.Image[i],b.Image[0],sizeof(double)*width);
	}
	inv=inv.Transpose();
	return inv;
}

void CImge::SetAllPxlsTo(double value)
{
	int ind1, ind2;
	for (ind1=0;ind1<height;ind1++)
		for (ind2=0;ind2<width;ind2++)
			Image[ind1][ind2]=value;
}

short crout( CImge& A, CImge& index, double& sign, double tol)
{
   short n = A.height ;
   if ( n != A.width ) {
      return 0 ;
   } // if
   if ( n != index.width)
   {
	   index.Resize(1,n) ;
	   index.SetAllPxlsTo(0);
   }

   short    i, imax, j, k, zeros = 0 ;
   double   sum ;
   double     big, temp ;
   CImge   scale(1,n) ;
   sign = 1.0 ;
   for ( i = 0; i < n ; i++ ) {
      big = 0.0 ;
      for ( j = 0; j < n; j++ ) {
         temp = (double) fabs( (double) A(i,j) ) ;
         if ( temp > big )
            big = temp ;
      } 
      scale(0,i) = ( big == 0.0 ? 0.0 : 1.0 / big ) ;
   } 

   for ( j = 0; j < n; j++ ) {
      for ( i = 0; i < j; i++ ) {
         sum = (DOUBLE) A(i,j) ;
         for ( k = 0; k < i; k++ )
            sum -= A(i,k) * A(k,j) ;
         A(i,j) = (double) sum ;
      } 
      big = 0.0 ;
      for ( i = j; i < n; i++ ) {
         sum = (double) A(i,j) ;
         for ( k = 0; k < j; k++ )
            sum -= A(i,k) * A(k,j) ;
         A(i,j) = (double) sum ;
         temp = scale(0,i) * ( (double) fabs( sum ) ) ;
         if ( temp >= big ) {
            big = temp ;
            imax = i ;
         } 
      }  
      if ( j != imax ) {
         for ( k = 0; k < n; k++ ) {
            temp = A( imax, k ) ;
            A( imax, k ) = A(j,k) ;
            A(j,k) = temp ;
         }
         sign = - sign ;
         scale(0, imax) = scale(0,j) ;
      } 
      index(0,j) = imax;

	  double val=A(j,j);
      if ( fabs( A(j,j) ) < tol )
         zeros++ ;
      else if ( j != n ) {
         temp = 1.0 / A(j,j) ;
         for ( i = j+1; i < n; i++ )
            A(i,j) *= temp;
      }
   } 
   if ( zeros )
      return 0;
   return zeros ;
}

short luSolve( CImge& A, CImge& index,CImge& b, double tol)
{
   short  n = A.height ;
   if ( b.height != 1 )       return 0;
   if ( n != b.width )	 return 0;
   short  i, nonzero=0, iperm, j ;
   double sum, zero = 0.0 ;

   for ( i = 0; i < n ; i++ )
      if ( fabs(A(i,i) ) < tol )
         return i ;

   for ( i = 0; i < n; i++ ) {
      iperm = index(0,i) ;
      sum = (double) b(0, iperm ) ;
      b(0, iperm) = b(0,i) ;
      if ( nonzero )
         for ( j = nonzero-1; j <= i-1; j++ )
            sum -= A(i,j) * b(0,j) ;
      else if ( sum != zero )
         nonzero = i+1 ;
      b(0,i) = (double) sum ;
   } 

   for ( i = n-1; i >= 0; i-- ) {
      sum = (double) b(0,i) ;
      for ( j = i+1; j < n; j++ )
         sum -= A(i,j) * b(0,j) ;
      b(0,i) = (double) ( sum / A(i,i) ) ;
   } 
   return 0 ;
} 

BOOL CImge::ImShow(HWND hWnd,Rect dispArea)
{
	CGdiplusWrapper temp;
	BYTE* buf;
	BOOL result;
	this->GrayIm2Buff(buf);
	temp.LoadPixelData(buf,Point(width,height));
	result=temp.Display(hWnd, dispArea);
	delete [] buf;//exception ihtimali?
	return result;
}