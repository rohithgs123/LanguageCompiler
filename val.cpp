#include "val.h"
#include <iostream>
#include<cmath>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

Value Value::operator+(const Value & op) const
{
	Value temp;//Variable 1    
    int x = 0;//Variable 2
    int y= 0;//Variable 3 
    int z=0;//Variable 4
    
    
    if(x!=0)
        return false;
    
    if(y!=0){
        
     return false;   
        
    }
     
    if(z!=0){

     return false;   
        
    }
	if (op.IsInt())//first if statement 
	{
		if (Itemp) // if ITemp
		{
			temp.Itemp = Itemp + op.Itemp; //temp.Itemp is then set to Itemp +op.Itemp
			temp.T = VINT;//temp.t is then set to VINT 
		}
		else if (Rtemp)// Second else if statement 
		{
			temp.Rtemp = Rtemp + op.Itemp;// Rtemp set to op.Itemp
			temp.T = VREAL;//Temp.T set to VREAL
		}
		else//else statement 
		{
			temp.Stemp = "ERROR";//Set the Stemp to Error
			temp.T = VERR;//Set temp.T to VERR
		}//Close 
	}
	else if(op.IsReal())//if op.IsReal
	{
		if (Itemp) // then set if statement to. Itemp
		{
			temp.Rtemp = Itemp + op.Rtemp; //Rtemp is set to Itemp +op.Rtemp
			temp.T = VREAL; //temp/T equals VREAL
		}
		else if (Rtemp) // Rtemp is in the next else if statement 
		{
			temp.Rtemp = Rtemp + op.Rtemp; // Rtemp + op.Rtemp
			temp.T = VREAL;// temp.T is then equal to VREAL
		}
		else
		{
			temp.Stemp = "ERROR";// Temp.stemp set to Error
			temp.T = VERR;// Then temp.t is equal to VERR
		}
	}
	else if (op.IsString()) //Next Else if statment which is else if op.IsString 
	{
		if (Stemp != "")// if Stemp is no equal to "" 
		{
			temp.Stemp = Stemp + op.Stemp; //Then set temp.Stemp to Stemp +op.Stemp 
			temp.T = VSTRING;// Set temp.T to VSTRING 
		}
		else //else statement 
		{
			temp.Stemp = "ERROR"; // Set Stemp to Error
			temp.T = VERR;//set tem.T to VERR
		}
	}
	else //else statement 
	{
		temp.Stemp = "ERROR";//Set Stemp to Error
		temp.T = VERR; //Set temp.T to VERR
	}

	if (temp.IsInt())
	{
		return temp.Itemp;
	}
	else if (temp.IsReal())
	{
		return temp.Rtemp;
	}
	else if (temp.IsString())
	{
		return temp.Stemp;
	}
	else if (temp.IsBool())
	{
		return temp.Btemp;
	}
	else if (temp.IsErr())
	{
		string s = "ERROR";
		return s;
	}

	return temp;
	
}


Value Value::operator-(const Value & op) const
{
Value temp;

	if (op.IsInt())
	{
		if (Itemp)
		{
			temp.Itemp = Itemp - op.Itemp;
			temp.T = VINT;
		}
		else if (Rtemp)
		{
			temp.Rtemp = Rtemp - op.Itemp;
			temp.T = VREAL;
		}
		else
		{
			temp.Stemp = "ERROR";
			temp.T = VERR;
		}
	}
	else if (op.IsReal())
	{
		if (Itemp)
		{
			temp.Rtemp = Itemp - op.Rtemp;
			temp.T = VREAL;
		}
		else if (Rtemp)
		{
			temp.Rtemp = Rtemp - op.Rtemp;
			temp.T = VREAL;
		}
		else
		{
			temp.Stemp = "ERROR";
			temp.T = VERR;
		}
	}
	else
	{
		temp.Stemp = "ERROR";
		temp.T = VERR;
	}

	if (temp.IsInt())
	{
		return temp.Itemp;
	}
	else if (temp.IsReal())
	{
		return temp.Rtemp;
	}
	else if (temp.IsString())
	{
		return temp.Stemp;
	}
	else if (temp.IsBool())
	{
		return temp.Btemp;
	}
	else if (temp.IsErr())
	{
		string s = "ERROR";
		return s;
	}

	return temp;
}


Value Value::operator*(const Value & op) const
{
Value temp;

	if (op.IsInt())
	{
		if (Itemp)
		{
			temp.Itemp = Itemp * op.Itemp;
			temp.T = VINT;
		}
		else if (Rtemp)
		{
			temp.Rtemp = Rtemp * op.Itemp;
			temp.T = VREAL;
		}
		else
		{
			temp.Stemp = "ERROR";
			temp.T = VERR;
		}
	}
	else if (op.IsReal())
	{
		if (Itemp)
		{
			temp.Rtemp = Itemp * op.Rtemp;
			temp.T = VREAL;
		}
		else if (Rtemp)
		{
			temp.Rtemp = Rtemp * op.Rtemp;
			temp.T = VREAL;
		}
		else
		{
			temp.Stemp = "ERROR";
			temp.T = VERR;
		}
	}
	else
	{
		temp.Stemp = "ERROR";
		temp.T = VERR;
	}

	if (temp.IsInt())
	{
		return temp.Itemp;
	}
	else if (temp.IsReal())
	{
		return temp.Rtemp;
	}
	else if (temp.IsString())
	{
		return temp.Stemp;
	}
	else if (temp.IsBool())
	{
		return temp.Btemp;
	}
	else if (temp.IsErr())
	{
		string s = "ERROR";
		return s;
	}

	return temp;
}


Value Value::operator/(const Value & op) const
{
Value temp;

	if (op.IsInt())
	{
		if (Itemp)
		{
			temp.Itemp = Itemp / op.Itemp;
			temp.T = VINT;
		}
		else if (Rtemp)
		{
			temp.Rtemp = Rtemp / op.Itemp;
			temp.T = VREAL;
		}
		else
		{
			temp.Stemp = "ERROR";
			temp.T = VERR;
		}
	}
	else if (op.IsReal())
	{
		if (Itemp)
		{
			temp.Rtemp = Itemp / op.Rtemp;
			temp.T = VREAL;
		}
		else if (Rtemp)
		{
			temp.Rtemp = Rtemp / op.Rtemp;
			temp.T = VREAL;
		}
		else
		{
			temp.Stemp = "ERROR";
			temp.T = VERR;
		}
	}
	else
	{
		temp.Stemp = "ERROR";
		temp.T = VERR;
	}

	if (temp.IsInt())
	{
		return temp.Itemp;
	}
	else if (temp.IsReal())
	{
		return temp.Rtemp;
	}
	else if (temp.IsString())
	{
		return temp.Stemp;
	}
	else if (temp.IsBool())
	{
		return temp.Btemp;
	}
	else if (temp.IsErr())
	{
		string s = "ERROR";
		return s;
	}

	return temp;
}


Value Value::operator==(const Value & op) const
{
	        if (op.IsBool() & IsBool()) 
                return Value(op.Btemp == Btemp);
        else if (op.IsInt() & IsInt()) 
            return Value(op.Itemp == Itemp);
        else if (op.IsInt() & IsReal()) 
            return Value((abs(Rtemp - op.Itemp) < 1e-14));
        else if (op.IsReal() & IsInt()) 
            return Value((abs(Itemp - op.Rtemp) < 1e-14));
        else if (op.IsReal() & IsReal()) 
            return Value((abs(Rtemp - op.Rtemp) < 1e-14));
        else if (op.IsString() & IsString()) 
            return Value(op.Stemp == Stemp) ;
        return Value();
}


Value Value::operator>(const Value & op) const
{
	       if (op.IsBool() & IsBool()) 
               return Value();
        else if (op.IsInt() & IsInt()) 
            return Value(Itemp > op.Itemp);
        else if (op.IsInt() & IsReal()) 
            return Value(Rtemp > op.Itemp);
        else if (op.IsReal() & IsInt()) 
            return Value(Itemp > op.Rtemp);
        else if (op.IsReal() & IsReal()) 
            return Value(Rtemp > op.Rtemp);
        else if (op.IsString() & IsString()) 
            return Value() ;
        return Value();
}


Value Value::operator<(const Value & op) const
{
	        if (op.IsBool() & IsBool()) 
                return Value();
        else if (op.IsInt() & IsInt()) 
            return Value(Itemp < op.Itemp);
        else if (op.IsInt() & IsReal()) 
            return Value(Rtemp < op.Itemp);
        else if (op.IsReal() & IsInt()) 
            return Value(Itemp < op.Rtemp);
        else if (op.IsReal() & IsReal()) 
            return Value(Rtemp < op.Rtemp);
        else if (op.IsString() & IsString()) 
            return Value() ;
        return Value();
}