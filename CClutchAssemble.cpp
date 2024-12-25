#include "pch.h"
#include "CClutchAssemble.h"
CClutchAssemble::CClutchAssemble(double _D, double _L, double _l, double _b1, double _D1, double _d, double _c, double _d1, double _c1, double _D2, double _b, double _r, double _f)
{
	D = _D;
	L = _L;
	l = _l;
	b1 = _b1;
	D1 = _D1;
	d = _d;
	c = _c;
	d1 = _d1;
	c1 = _c1;
	D2 = _D2;
	b = _b;
	r = _r;
	f = _f;
}

double CClutchAssemble::Getf()
{
	return f;
}

double CClutchAssemble::Getr()
{
	return r;
}

double CClutchAssemble::Getb()
{
	return b;
}

double CClutchAssemble::GetD2()
{
	return D2;
}

double CClutchAssemble::Getc1()
{
	return c1;
}

double CClutchAssemble::Getd1()
{
	return d1;
}

double CClutchAssemble::Getc()
{
	return c;
}

double CClutchAssemble::Getd()
{
	return d;
}

double CClutchAssemble::GetD1()
{
	return D1;
}
double CClutchAssemble::Getb1()
{
	return b1;
}

double CClutchAssemble::Getl()
{
	return l;
}

double CClutchAssemble::GetL()
{
	return L;
}

double CClutchAssemble::GetD()
{
	return D;
}