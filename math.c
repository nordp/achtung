
double sin(double x) //Taylor implementation of sin(x) with 7 degrees.
{
//	double sum = x;
//	double exponential = x*x*x;
//	sum += (-1)*exponential/6.0;
//	exponential *= x*x;
//	sum += exponential/120.0;
//	exponential *= x*x;
//	sum += (-1)*exponential/5040.0;
//	exponential *= x*x;
//	sum += exponential/362880.0;
//	return sum;

const float PI = 3.14159265358f;
const float B = 4.0f / PI;
const float C = -4.0f / (PI * PI);
const float P = 0.225f;

	float temp = x;
	if(x < 0)
		temp = -x;
    float y = B * x + C * x * temp;
	float temp2 = y;
	if(y < 0)
		temp2 = -y;
    return P * (y * temp2 - y) + y;
}

double cos(double x) //Taylor implementation of cos(x) with 7 degrees.
{
//	double sum = 1.0;
//	double exponential = x*x;
//	sum += (-1)*exponential/2.0;
//	exponential *= x*x;
//	sum += exponential/24.0;
//	exponential *= x*x;
//	sum += (-1)*exponential/720.0;
//	exponential *= x*x;
//	sum += exponential/40320.0;
//	return 1.0;
	
	const float PI = 3.14159265358f;
	
	float temp = x;
	if(x > 0)
		temp = -x;
		
    temp += PI/2;

    return sin(temp);
}