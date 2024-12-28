#pragma once
#define Assemble CClutchAssemble
class CAssemblesCollection;
class CClutchAssemble
{
	protected:
		double D, L, l, b1, D1, d, c, d1, c1, D2, b, r, f;
	public:
		CClutchAssemble();
		CClutchAssemble(double D, double L, double l, double b1, double D1, double d, double c, double d1, double c1, double D2, double b, double r, double f);
		double Getf();
		double Getr();
		double Getb();
		double GetD2();
		double Getc1();
		double Getd1();
		double Getc();
		double Getd();
		double GetD1();
		double Getb1();
		double Getl();
		double GetL();
		double GetD();
protected:
	friend class CAssemblesCollection;
};

