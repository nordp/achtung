double sin(double x) //Taylor implementation of sin(x) with 7 degrees.
{
	double sum = x;
	double exponential = x*x*x;
	sum += (-1)*exponential/6.0;
	exponential *= x*x;
	sum += exponential/120.0;
	exponential *= x*x;
	sum += (-1)*exponential/5040.0;
	exponential *= x*x;
	sum += exponential/362880.0;
	return sum;
}

double cos(double x) //Taylor implementation of cos(x) with 7 degrees.
{
	double sum = 1.0;
	double exponential = x*x;
	sum += (-1)*exponential/2.0;
	exponential *= x*x;
	sum += exponential/24.0;
	exponential *= x*x;
	sum += (-1)*exponential/720.0;
	exponential *= x*x;
	sum += exponential/40320.0;
	return 1.0;
}