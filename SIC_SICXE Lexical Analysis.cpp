#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <cmath>
#include <math.h>
#include <time.h>
#include <vector>
#include <stack>
#include <queue>
#include <iomanip>
#include <sstream>
using namespace std ;

typedef vector<string> V ;

struct literal {
	string name ;
	string loc ;
	int type ;
	string mc ;
};

struct label {
	string name  ;
	string loc  ;
};

struct OpType {
	string op ;
	int format ;
};

struct RegisterType {
	string name ;
	string num ;
};

class TokenType {
  string location = "" ;
  vector<V> outerans ;
  vector<OpType> op ;
  vector<RegisterType> reg ;
  vector<string> mc, outliteral ;
  vector<string> table1, table2, table3, table4, table5, table6, table7, input, ansvector ;
  char CorS ;
  bool for6 = false, for7 = false, str = false, SIC = false  ;
  string forRead, inVector, token, temptoken ;	
  string file, name, outname ;
  string PC, BR ;
  ofstream out ;
  stringstream lloc, jjump ;
  vector<label> LT ;
  vector<literal> literalTable ;
  label tempL ;
  public :
  	
    void readfile() {
    	table5.resize(100) ;
        table6.resize(100) ;
        table7.resize(100) ;
        ifstream  fin ;
        fin.open("Table1.table") ;	    
	    while ( getline( fin, forRead ) ) {
	      while( forRead.at(forRead.size() - 1) == ' ' ) 
		     forRead.resize(forRead.size() - 1) ;
	      table1.push_back(forRead) ;   
	    }
        fin.close() ;
        
        ifstream  fin2 ;
        fin2.open("Table2.table") ;	    
	    while ( getline( fin2, forRead ) ) {
	      while( forRead.at(forRead.size() - 1) == ' ' ) 
		     forRead.resize(forRead.size() - 1) ;
	      table2.push_back(forRead) ;     
	    }
        fin2.close() ;
        
        ifstream  fin3 ;
        fin3.open("Table3.table") ;	    
	    while ( getline( fin3, forRead ) ) {
	      while( forRead.at(forRead.size() - 1) == ' ' ) 
		     forRead.resize(forRead.size() - 1) ;
	      table3.push_back(forRead) ;     
	    }
        fin3.close() ;
        
        ifstream  fin4 ;
        fin4.open("Table4.table") ;	    
	    while ( getline( fin4, forRead ) ) {
	      while( forRead.at(forRead.size() - 1) == ' ' ) 
		     forRead.resize(forRead.size() - 1) ;
	      table4.push_back(forRead) ;     
	    }
        fin4.close() ;
					
        cout << "Input file name : " ;
        cin >> file ;
        if ( file == "SIC_input.txt" )
          SIC = true ;
        ifstream  finput ;
        name = file ;
        finput.open( name.c_str() ) ;	    
	    while ( getline( finput, forRead ) ) {
	      if( forRead.size() != 0 && forRead.at(forRead.size() - 1) == ' ' ) 
		     forRead.resize(forRead.size() - 1) ;
		  if ( forRead.size() != 0 )
	        input.push_back(forRead) ;     
	    }
        finput.close() ;
    }
    
    string tolow( string a ) {
    	for( int i = 0 ; i < a.size() ; i ++ )
    	    a.at(i) = tolower(a.at(i)) ;
    	return a ;
	}
	
	string toup( string a ) {
    	for( int i = 0 ; i < a.size() ; i ++ )
    	    a.at(i) = toupper(a.at(i)) ;
    	return a ;
	}
	
    int ForTable456( vector<string> &a ) {
    	int num = 0  ;
		for( int i = 0 ; i < token.size() ; i++ ) 
			num = num + token.at(i) ;	
		num = num % 100 ;
		int re = num ;
		if ( a.at(num).size() != 0 ) {
            for( int i = 1 ; ; i++ ) {
                if ( a.at(num) == token )
					break ;
				num = num + 1 ;
				if ( num > 99 )
					num = num - 100 ;
				if ( a.at(num).size() == 0 )
					break ;
				if ( re == num ) {
					if ( a == table5 )
					  out << "(Error : Table5 is full !)"  ;
					else if ( a == table6 )
					  out << "(Error : Table6 is full !)"  ;
					else if ( a == table7 )
					  out << "(Error : Table7 is full !)"  ;
					num = -1 ;
					break ;
				} 
			}
		}
		if ( num != -1 )
		  a.at(num) = token ;
		return num ;
	}
	
	bool AllLower( string a ) {
		for( int i = 0 ; i < a.size() ; i++ ) {
			if ( a.at(i) < 97 || a.at(i) > 122 )
			  return false ;
		}
		return true ;
	}
	
	bool Upper( string a ) {
		for( int i = 0 ; i < a.size() ; i++ ) {
			if ( a.at(i) < 65 || a.at(i) > 90 )
			  return false ;
		}
		return true ;
	}
		
    void identify() {
    	temptoken = tolow( token ) ;
    	bool check = false ;
    	for( int i = 0 ; i < table1.size() && !check && !str ; i++ ) {
    		if ( temptoken == table1.at(i) ) {
    			//out << "(1," << i+1 << ")" ;
    			check = true ;
			}
		}
		
		temptoken = toup( token ) ;
		
		for( int i = 0 ; i < table2.size() && !check && !str ; i++ ) {
    		if ( temptoken == table2.at(i) ) {
    			//out << "(2," << i+1 << ")" ;
    			check = true ;
			}
		}
		for( int i = 0 ; i < table3.size() && !check && !str ; i++ ) {
    		if ( temptoken == table3.at(i) ) {
    			//out << "(3," << i+1 << ")" ;
    			check = true ;
			}
		}
		for( int i = 0 ; i < table4.size() && !check ; i++ ) {
    		if ( temptoken == table4.at(i) ) {
    			//out << "(4," << i+1 << ")" ;
    			check = true ;
			}
		}
							
		if ( for6 && !check ) {
			token = toup(token) ;
			int num = ForTable456( table6 ) ;
			//if ( num != -1 )
			  //out << "(6," << num << ")" ;
    		for6 = false ;
    		check = true ;
		}
		else if ( for7 && !check ) {
			int num = ForTable456( table7 ) ;
			//if ( num != -1 )
			  //out << "(7," << num << ")" ;
    		for7 = false ;
    		check = true ;
		}
		else if ( !check ) {
			int num = ForTable456( table5 ) ;
			//if ( num != -1 )
			  //out << "(5," << num << ")" ;
			check = true ;
		}	
	}
	
	bool checkTable4( char a ) {
		for ( int i = 0 ; i < table4.size() ; i++ ) {
			if ( a == table4.at(i).at(0) )
			  return true ;
		}
		return false ;
	}
	
	bool AllNum( string str ) {
		for ( int i = 0 ; i < str.size() ; i++ ) {
			if ( str.at(i) < '0' || str.at(i) > '9' )
			  return false ;
		}
		return true ;
	}
		
    void cutAndprint() {
    	string a ;
    	for( int i = 0 ; i < input.size() ; i++ ) {
    		for( int j = 0 ; j < input.at(i).size() ; j++ ) {
    			if ( input.at(i).at(j) != ' ' && input.at(i).at(j) != '\t' && !checkTable4(input.at(i).at(j)) ) 
    				token = token + input.at(i).at(j) ;
    			else if ( checkTable4(input.at(i).at(j)) ) {
    				if ( input.at(i).at(j) == '\'') {
    					if ( token == "C" || token == "c" ) {
    						a = token ;
    						ansvector.push_back(a) ;
    						for7 = true ;
    						token = "" ;
    						token = token + input.at(i).at(j) ;
    						ansvector.push_back(token) ;
    						identify() ;
    						CorS = 'C' ;
    						token = "" ;
    						for( int temp = j+1 ; input.at(i).at(temp) != '\'' ; temp++ ) {
    							token = token + input.at(i).at(temp) ;
    							j++ ;
    							str = true ;
    							if (temp == input.at(i).size() - 1 ) 
    							  break ;		
							}
						}
						else if ( token == "X" ||  token == "x") {
							 a = token ;
    						 ansvector.push_back(a) ;
							for6 = true ;
							token = "" ;
							token = token + input.at(i).at(j) ;
							ansvector.push_back(token) ;
    						identify() ;
    						CorS = 'X' ;
    						token = "" ;
    						for( int temp = j+1 ; input.at(i).at(temp) != '\'' ; temp++ ) {
    							token = token + input.at(i).at(temp) ;
    							j++ ;
    							str = true ;
    							if (temp == input.at(i).size() - 1 ) 
    							  break ;		
							}
						}
						else if ( CorS == 'C' || CorS == 'c' )  {
							if ( token != "" ) {
							  ansvector.push_back(token) ;
							  identify() ;
							  str = false ;
						    }
						    else
						      for7 = false ;
							CorS = '\0' ;
							token = "" ;
							token = token + input.at(i).at(j) ;
							ansvector.push_back(token) ;
    						identify() ;
    						token = "" ;
						}
						else if ( CorS == 'X' || CorS == 'x') {
							if ( token != "" ) {
							  ansvector.push_back(token) ;
							  identify() ;
							  str = false ;
						    }
						    else
						      for6 = false ;
							CorS = '\0' ;
							token = "" ;
							token = token + input.at(i).at(j) ;
							ansvector.push_back(token) ;
    						identify() ;
    						token = "" ;
						}
						else {
						  if ( token != "" ) {
						    if ( AllNum(token) ) 
    				          for6 = true ;
    				        ansvector.push_back(token) ;
						    identify() ;
					      }
					      token = "" ;
    					  token = token + input.at(i).at(j) ;
    					  ansvector.push_back(token) ;
    					  identify() ;
    					  token = "" ;
					    }
						
					}
					else if( input.at(i).at(j) == '.' ) {
						if ( token != "" ) {
						  if ( AllNum(token) ) 
    				        for6 = true ;
    				      ansvector.push_back(token) ;
						  identify() ;
					    }
						token = "" ;
    					token = token + input.at(i).at(j) ;
    					ansvector.push_back(token) ;
    					identify() ;
    					for(int pos = j ; pos < input.at(i).size()  ; pos++ ) {				
    						token = token + input.at(i).at(pos) ;
    						j++ ;
					    }
					    token = "" ;
					}
	 				else {
	 				  if ( token != "" ) {
	 				  	ansvector.push_back(token) ;
	 				    identify() ;
	 			      }
	 				  token = "" ;
		              token = token + input.at(i).at(j) ;
		              ansvector.push_back(token) ;
					  identify() ;
					  token = "" ;
				    }
				}
    			else if ( input.at(i).at(j) == ' ' || input.at(i).at(j) == '\t' ) {
    				if ( token != "" ) {
    				  if ( AllNum(token) ) 
    				    for6 = true ;
    				  ansvector.push_back(token) ;
    				  identify() ;
    				  token = "" ;
    			    }
				}
				
				if( j == input.at(i).size() - 1 ) {
					if ( token != "" ) {
						if ( AllNum(token) ) 
    				      for6 = true ;
    				    ansvector.push_back(token) ;
						identify() ;
						token = "" ;		
					}
				}				
		     }
		     //out << endl ;
		     
		     outerans.push_back( ansvector ) ;
		     ansvector.clear() ;
		}
		//for( int i = 0 ; i < ansvector.size() ; i++ )
		  //cout << ansvector.at(i) << endl ;
		/*for ( int i = 0 ; i < outerans.size() ; i++ ) {
			for ( int j = 0 ; j < outerans.at(i).size() ; j++ )
			  cout << outerans.at(i).at(j) << " " ;
			cout << endl ;
		}	*/
	}
	
	void setOP() {
		op.resize(59) ;
		for ( int i = 0 ; i < 59 ; i++ ) {
			if ( i == 0 ) {
			  op.at(i).op = "18" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 1 ) {
			  op.at(i).op = "58" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 2 ) {
			  op.at(i).op = "90" ;
			  op.at(i).format = 2 ;
		    }
			else if ( i == 3 ) {
			  op.at(i).op = "40" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 4 ) {
			  op.at(i).op = "B4" ;
			  op.at(i).format = 2 ;
		    }
			else if ( i == 5 ) {
			  op.at(i).op = "28" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 6 ) {
			  op.at(i).op = "88" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 7 ) {
			  op.at(i).op = "A0" ;
			  op.at(i).format = 2 ;
		    }
			else if ( i == 8 ) {
			  op.at(i).op = "24" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 9 ) {
			  op.at(i).op = "64" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 10 ) {
			  op.at(i).op = "9C" ;
			  op.at(i).format = 2 ;
		    }
			else if ( i == 11 ) {
			  op.at(i).op = "C4" ;
			  op.at(i).format = 1 ;
		    }
			else if ( i == 12 ) {
			  op.at(i).op = "C0" ;
			  op.at(i).format = 1 ;
		    }
			else if ( i == 13 ) {
			  op.at(i).op = "F4" ;
			  op.at(i).format = 1 ;
		    }
			else if ( i == 14 ) {
			  op.at(i).op = "3C" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 15 ) {
			  op.at(i).op = "30" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 16 ) {
			  op.at(i).op = "34" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 17 ) {
			  op.at(i).op = "38" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 18 ) { 
			  op.at(i).op = "48" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 19 ) { 
			  op.at(i).op = "00" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 20 ) { 
			  op.at(i).op = "68" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 21 ) { 
			  op.at(i).op = "50" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 22 ) { 
			  op.at(i).op = "70" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 23 ) { 
			  op.at(i).op = "08" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 24 ) {	 
			  op.at(i).op = "6C" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 25 ) { 
			  op.at(i).op = "74" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 26 ) { 
			  op.at(i).op = "04" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 27 ) { 
			  op.at(i).op = "D0" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 28 ) { 
			  op.at(i).op = "20" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 29 ) { 
			  op.at(i).op = "60" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 30 ) { 
			  op.at(i).op = "98" ;
			  op.at(i).format = 2 ;
			} 
			else if ( i == 31 ) { 
			  op.at(i).op = "C8" ;
			  op.at(i).format = 1 ;
			} 
			else if ( i == 32 ) { 
			  op.at(i).op = "44" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 33 ) { 
			  op.at(i).op = "D8" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 34 ) { 
			  op.at(i).op = "AC" ;
			  op.at(i).format = 2 ;
			} 
			else if ( i == 35 ) { 
			  op.at(i).op = "4C" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 36 ) { 
			  op.at(i).op = "A4" ;
			  op.at(i).format = 2 ;
			} 
			else if ( i == 37 ) { 
			  op.at(i).op = "A8" ;
			  op.at(i).format = 2 ;
			} 
			else if ( i == 38 ) { 
			  op.at(i).op = "F0" ;
			  op.at(i).format = 1 ;
			} 
			else if ( i == 39 ) { 
			  op.at(i).op = "EC" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 40 ) { 
			  op.at(i).op = "0C" ;
			  op.at(i).format = 34 ;
		    } 
			else if ( i == 41 ) { 
			  op.at(i).op = "78" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 42 ) { 
			  op.at(i).op = "54" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 43 ) { 
			  op.at(i).op = "80" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 44 ) { 
			  op.at(i).op = "D4" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 45 ) { 
			  op.at(i).op = "14" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 46 ) { 
			  op.at(i).op = "7C" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 47 ) { 
			  op.at(i).op = "E8" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 48 ) { 
			  op.at(i).op = "84" ;	  
			  op.at(i).format = 34 ;
			} 
			else if ( i == 49 ) { 
			  op.at(i).op = "10" ;
			  op.at(i).format = 34 ;
			} 
			else if ( i == 50 ) { 
			  op.at(i).op = "1C" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 51 ) {
			  op.at(i).op = "5C" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 52 ) {
			  op.at(i).op = "94" ;
			  op.at(i).format = 2 ;
		    }
			else if ( i == 53 ) {
			  op.at(i).op = "B0" ;
			  op.at(i).format = 2 ;
		    }
			else if ( i == 54 ) {
			  op.at(i).op = "E0" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 55 ) {
			  op.at(i).op = "F8" ;
			  op.at(i).format = 1 ;
		    }
			else if ( i == 56 ) {
			  op.at(i).op = "2C" ;
			  op.at(i).format = 34 ;
		    }
			else if ( i == 57 ) {
			  op.at(i).op = "B8" ;
			  op.at(i).format = 2 ;
		    }
			else if ( i == 58 ) {
			  op.at(i).op = "DC" ;
			  op.at(i).format = 34 ;
		    }
		}		
	}
	
	string IsInstruction( string str ) {
		string null = "" ;
		for ( int i = 0 ; i < table1.size() ; i++ ) {
			if ( str == table1.at(i) )
			  return op.at(i).op ;
		}
		return null ;
	}
	
	string FindLoc( string str ) {
		string null = "" ;
		for ( int i = 0 ; i < LT.size() ; i++ ) {
			if ( str == LT.at(i).name )
			  return LT.at(i).loc ;
		}
		return null ;
	}
	
	string CreateCode( string op, string address, bool isindex ) {    // FOR SIC 
		stringstream bit ;
		int isz = 0 ;
		unsigned ans = 0, newbit = 0 ;
		string code ;
		for ( int i = 0 ; i < op.size() ; i++ ) {
			bit.clear() ;
			bit << op.at(i) ;
			bit >> hex >> newbit ;
			ans = ans << 4 ;
			ans = ans + newbit ;
			if ( ans == 0 )
			  isz++ ;
			//cout << ans << endl ;
		}
		for ( int i = 0 ; i < address.size() ; i++ ) {
			bit.clear() ;
			bit << address.at(i) ;
			bit >> hex >> newbit ;
			if ( i == 0 && isindex )
			  newbit = newbit + 8 ;
			ans = ans << 4 ;
			ans = ans + newbit ;
			if ( ans == 0 )
			  isz++ ;
			//cout << ans << endl ;
		}
		bit.clear() ;
		bit << hex << ans ;
		bit >> code ;
		for ( int i = isz ; i > 0 ; i-- )
		  code = "0" + code ;
		return code ;
	}
	
	bool IsTable2( string str ) {
		for ( int i = 0 ; i < table2.size() ; i++ ) {
			if ( str == table2.at(i) )
			  return true ;
		}
		return false ;
	}

	string ForC ( string str ) {
	    stringstream bit ;
	    unsigned ans = 0 ;
	    char newbit ;
	    int z = 0, num = 0 ;
	    string code = "" ;
	    if ( str.size() < 3 ) {
	    	for ( int i = 0 ; i < str.size() ; i++ ) {
	    		bit.clear() ;
			    bit << str.at(i) ;
			    bit >> newbit ;
			    ans = ans << 8 ;
			    ans = ans + newbit ;
			    if ( ans == 0 )
			      z = z + 1  ;
			}
			bit.clear() ;
		    bit << hex << ans ;
		    bit >> code ;
		    for ( int i = z ; i > 0 ; i-- )
		      code = "00" + code ;
		    num = str.size() ;
		    for ( int i = 3 - num ; i > 0 ; i-- )
		      code = "00" + code ;
		    return code ;
 		}
		else {		
		  for ( int i = 0 ; i < str.size() ; i++ ) {
		    	bit.clear() ;
			    bit << str.at(i) ;
			    bit >> newbit ;
			    ans = ans << 8 ;
			    ans = ans + newbit ;
			    if ( ans == 0 )
			      z = z + 1  ;
		  }
		  bit.clear() ;
		  bit << hex << ans ;
		  bit >> code ;
		  for ( int i = z ; i > 0 ; i-- )
		    code = "00" + code ;
		  return code ;
	    }
	}
	
	string ForWord ( string str ) {
		stringstream bit ;
		int num, k = 0  ;
		unsigned ans ;
		string code ;
		bit <<  str ;
		bit >> ans ;
		k = k + ans ;
		bit.clear() ;
		bit << hex << k ;
		bit >> code ;
		num = code.size() ;
 		for ( int i = 6 - num ; i > 0 ; i-- )
 		  code = "0" + code ;
		return code ;		
	}
	
	bool IsTable1( string str, int &index ) {
		for ( int i = 0 ; i < table1.size() ; i++ ) {
			if ( str == table1.at(i) ) {
              index = op.at(i).format ;
			  return true ;
		    }
		}
		return false ;
	}
	
	bool IsTableOne( string str ) {
		for ( int i = 0 ; i < table1.size() ; i++ ) {
			if ( str == table1.at(i) ) {
			  return true ;
		    }
		}
		return false ;
	}
	
	string ZeroForLoc( string str, int n ) {
		int size = str.size() ;
		string code = "" ;
		if ( size < n ) {
		    for ( int i = n - size ; i > 0 ; i-- )
		      str = "0" + str ;
		    return str ;
	    }
	    else {
	    	for ( int i = size - n ; i < size ; i++ )
		      code  = code + str.at(i) ;
		    return code ;
		}
	}
	
	void BuildReg() {
		RegisterType temp ;
		
		temp.name = "a" ;
		temp.num = "0" ;
		reg.push_back(temp) ;
		temp.name = "x" ;
		temp.num = "1" ;
		reg.push_back(temp) ;
		temp.name = "l" ;
		temp.num = "2" ;
		reg.push_back(temp) ;
		temp.name = "pc" ;
		temp.num = "8" ;
		reg.push_back(temp) ;
		temp.name = "sw" ;
		temp.num = "9" ;
		reg.push_back(temp) ;
		temp.name = "b" ;
		temp.num = "3" ;
		reg.push_back(temp) ;
		temp.name = "s" ;
		temp.num = "4" ;
		reg.push_back(temp) ;
		temp.name = "t" ;
		temp.num = "5" ;
		reg.push_back(temp) ;
		temp.name = "f" ;
		temp.num = "6" ;
		reg.push_back(temp) ;
	}
	
	string FindReg( string a ) {
		string null = "" ;
		a = tolow(a) ;
		for ( int i = 0 ; i < reg.size() ; i++ ) {
			if ( a == reg.at(i).name )
			  return reg.at(i).num ;
		}
		return null ;
	}
	
	string ForFormat2( string op, string reg1, string reg2 ) {
		stringstream bit ;
		unsigned ans = 0, newbit = 0 ;
		string code ;
		for ( int i = 0 ; i < op.size() ; i++ ) {
			bit.clear() ;
			bit << op.at(i) ;
			bit >> hex >> newbit ;
			ans = ans << 4 ;
			ans = ans + newbit ;
			//cout << ans << endl ;
		}
		for ( int i = 0 ; i < reg1.size() ; i++ ) {
			bit.clear() ;
			bit << reg1.at(i) ;
			bit >> hex >> newbit ;
			ans = ans << 4 ;
			ans = ans + newbit ;
		}
		for ( int i = 0 ; i < reg2.size() ; i++ ) {
			bit.clear() ;
			bit << reg2.at(i) ;
			bit >> hex >> newbit ;
			ans = ans << 4 ;
			ans = ans + newbit ;
		}
		if ( reg2 == "" ) {
			ans = ans << 4 ;
			ans = ans + 0 ;
		}		   
		bit.clear() ;
		bit << hex << ans ;
		bit >> code ;
		return code ;  
	}
	
	string ForFormat3( int &b, int &p, string address ) {
		string null = "", code ;
		int ans = 0, addressint, POB, AD ;
		stringstream PCorBR, Aaddress, P, A ;
		P.clear() ;
		A.clear() ;
		P << PC ;
		A << address ;
		P >> hex >> POB ;
		A >> hex >> AD ;
		if ( address == "" ) {
		  b = 0 ;
		  p = 0 ;
		  // cout << "fsfsdfasfsdfsadfsf" << endl ;
		  return null ;
	    }
		else {
			p = 1 ;
			b = 0 ;
			PCorBR.clear() ;
			Aaddress.clear() ;
			if ( POB - AD >= 4096 ) {
			  PCorBR << BR ;
			  p = 0 ;
			  b = 1 ;
		    }
			else {
			  PCorBR << PC ; 
		    }
		    // cout << BR << "BBBBBBBBBBRRRRRRRRRRRRRRRRRRRR" << endl ;
			Aaddress << address ;
			PCorBR >> hex >> ans ;
			Aaddress >> hex >> addressint ;
			ans = addressint - ans ;
			code.clear() ;
			Aaddress.clear() ;
			Aaddress << hex << ans ;
			Aaddress >> code ;
	    }
		return code ;		  
	}
	
	string GenerateCode3( string op, int n, int i, int x, int b, int p, int e, string str ) {
		stringstream bit ;
		int temp = 0 ;
		unsigned ans = 0, newbit = 0 ;
		string code ;
		for ( int z = 0 ; z < op.size() ; z++ ) {
			bit.clear() ;
			bit << op.at(z) ;
			bit >> hex >> newbit ;
			ans = ans << 4 ;
			ans = ans + newbit ;
		}
		if ( n == 1 )
		  ans = ans + 2 ;
		if ( i == 1 )
		  ans = ans + 1 ;
		temp = 2*2*2*x + 2*2*b + 2*p + e ;
		ans = ans << 4 ;
		ans = ans + temp ;
		bit.clear() ;
		bit << hex << ans ;
		bit >> code ;
		code = code + str ;
		return code ; 
	}
	
	bool IsLable( string str ) {
		for (  int i = 0 ; i < LT.size() ; i++ ) {
			if ( LT.at(i).name == str )
			  return true ;
		}
		return false ;
	}
	
	int ForLiteral( string str, int& n ) {
		stringstream lloc ;
		literal empty ;
		empty.name = "" ;
		empty.type = -1 ;
		empty.loc = "" ;
		int loc ;
		lloc.clear() ;
		lloc << str ;
		lloc >> hex >> loc ;
		for ( int i = n ; i < literalTable.size() ; i++ ) {
			lloc.clear() ;
			lloc << hex << loc ;
			lloc >> literalTable.at(i).loc ; 
			literalTable.at(i).loc = ZeroForLoc( literalTable.at(i).loc, 4 ) ;
			 // cout << literalTable.at(i).name << "name-------------------------" << endl ;
			if ( literalTable.at(i).type == 1 )
			  loc = loc + 1 ;
			else if ( literalTable.at(i).type == 2)
			  loc = loc + literalTable.at(i).name.size() ;
			else 
			  loc = loc + 3 ;
			n = i ;
		}
		n++ ;
		literalTable.push_back( empty ) ;
		n++ ;
		return loc ;
	}
	
	string LocInLiteral( string str ) {
		string null = "" ;
		for ( int i = 0 ; i < literalTable.size() ; i++ ) {
			if ( str == literalTable.at(i).name )
			  return literalTable.at(i).loc ;
		}
		return null ;
	}
	
	bool AtoF ( string str ) {
		for ( int i= 0 ; i < str.size() ; i++ ) {
			if ( str.at(i) < 'A' || str.at(i) > 'F' || str.at(i) < '0' || str.at(i) > 'A' )
			  return false ;
		}
		return true ;
	}
	
	bool IsTable567( string str ) {
		for ( int i = 0 ; i < table5.size() ; i++ ) {
			if ( str == table5.at(i) )
			  return true ;
		} 
		for ( int i = 0 ; i < table6.size() ; i++ ) {
			if ( str == table5.at(i) )
			  return true ;
		} 
		for ( int i = 0 ; i < table7.size() ; i++ ) {
			if ( str == table5.at(i) )
			  return true ;
		} 
		return false ;
	}
	void ErrorSIC() {
		for ( int i = 0 ; i < outerans.size() ; i++ ) {
			if ( IsTable567( outerans.at(i).at(0) ) || IsTableOne(outerans.at(i).at(0)) || IsTable2( outerans.at(i).at(0) ) || outerans.at(i).at(0) == "."   ) {
				for ( int j = 1 ; j < outerans.at(i).size() ; j++ ) {
					if ( IsTableOne(outerans.at(i).at(j-1)) || IsTable2( outerans.at(i).at(j-1) ) ) {
						if ( IsLable( outerans.at(i).at(j) ) )
						  ;
						else if ( IsTable2( outerans.at(i).at(j) ) )
						  ;
						else if ( outerans.at(i).at(j) == "C" )
						  ;
						else if ( outerans.at(i).at(j) == "X" )
						  ; 
						else if ( (outerans.at(i).at(j) >= "0" && outerans.at(i).at(j) <= "9999") )
						  ;
						else
						  outerans.at(i).at(j) = "" ;
					}
					else if ( IsLable( outerans.at(i).at(j-1) ) ) {
						if ( IsTableOne(outerans.at(i).at(j)) || IsTable2( outerans.at(i).at(j) ) )
						  ;
						else if ( outerans.at(i).at(j) == "," )
						  ;
						else 
						  outerans.at(i).at(j)= "" ;
					}
					else if ( outerans.at(i).at(j-1) == "C" || outerans.at(i).at(j-1) == "X" ) {
						if ( outerans.at(i).at(j) == "\'" )
						  ;
						else 
						  outerans.at(i).at(j) = "" ;
					}
					else if ( outerans.at(i).at(j-1) == "\'" ){
						if ( AtoF(outerans.at(i).at(j)) )
						  ;
						else
						  outerans.at(i).at(j) = "" ;
					}
					else if ( AtoF(outerans.at(i).at(j-1)) ) {
						if (outerans.at(i).at(j) == "\'" )
						  ;
						else
						  outerans.at(i).at(j)= "" ;
					}
					else if ( outerans.at(i).at(j-1) == "," ) {
						if (outerans.at(i).at(j) == "X" )
						  ;
						else
						  outerans.at(i).at(j) = "" ;
					}			  
				}
			}
			else
			  outerans.at(i).at(0) = "" ;
		}
	}
	void assemblerPass1() {
		int plus = 0, literalloc = 0 ;
		LT.resize( outerans.size() ) ;
		int locInt = 0, jump = 0, num = 0, equ = 0 , ea = 0 ;
		string garbage, store, BR, OT = "" ;
		literal tempL ;
		bool check = false ;
		for( int i = 0 ; i < outerans.at(0).size() ; i++ ) {
			if ( i+1 < outerans.at(0).size() && outerans.at(0).at(i) == "START"  ) 			
			  location = outerans.at(0).at(i+1) ;			  
		}
		if ( location == "" )
		  location = "0000" ; 
		
		LT.at(0).loc = location ;
		LT.at(0).loc = ZeroForLoc( LT.at(0).loc, 4 ) ;
		
		lloc << location ;
		lloc >> hex >> locInt ;
		for ( int i = 0 ; i < outerans.size() ; i++ ) {
			if ( i != 0 && outerans.at(i).at(0) != "." ) {
			    lloc >> LT.at(i).loc ;
			    LT.at(i).loc = ZeroForLoc( LT.at(i).loc, 4 ) ;
			    store = LT.at(i).loc ;
		    }
			else 
			    lloc >> garbage ;
			for ( int j = 0 ; j < outerans.at(i).size() ; j++ ) {
				if ( j == 0 ) {
				  for( int k = 0 ; k < table5.size() ; k++ ) {
				     	if ( outerans.at(i).at(j) == table5.at(k) ) {
					    	LT.at(i).name = table5.at(k) ;
					    }
				  }
			    }
			    if ( outerans.at(i).at(j) == "RESW" || outerans.at(i).at(j) == "RESB" ) {
			    	check = true ;
			    	jjump.clear() ;
			    	location = outerans.at(i).at(j+1) ;
			    	jjump << location ;
			    	jjump >> jump ;
			    	if (outerans.at(i).at(j) == "RESW" )
			    	  locInt = locInt + jump * 3 ;
			    	else
			    	  locInt = locInt + jump ;	
				}
				else if ( outerans.at(i).at(j) == "BYTE" || outerans.at(i).at(j) == "WORD" ) {
					check = true ;
					if (outerans.at(i).at(j) == "WORD" )
			    	  locInt = locInt + 3 ;
			    	else {
			    	  if (outerans.at(i).at(j+1) == "X" ){
			    	  	locInt = locInt + 1 ;
					  }
					  else {
					  	num = outerans.at(i).at(j+3).size()  ;
						locInt = locInt + num ; 
					  }   
			        }
				}
				else if ( outerans.at(i).at(j) == "EQU" ) {
					if ( outerans.at(i).at(j+1) == "*" ) {
						check = true ;
					}
					else if ( outerans.at(i).size() > 3 ) {
						check = true ;
						for ( int now = j + 1 ; now < outerans.at(i).size() ; now++ ) {
							if ( IsLable(outerans.at(i).at(now) ) ) {
								jjump.clear() ;
								jjump << FindLoc(outerans.at(i).at(now)) ;
								jjump >> hex >> equ ;
							}
							if ( (outerans.at(i).at(now) == "+" || outerans.at(i).at(now) == "-" )&& IsLable(outerans.at(i).at(now+1) ) ) {
								ea = equ ;
								jjump.clear() ;
								jjump << FindLoc(outerans.at(i).at(now+1)) ;
								jjump >> hex >> equ ;
								if ( outerans.at(i).at(now) == "+" )
								  ea = ea + equ ;
								else 
								  ea = ea - equ ;
								now++ ;
								lloc.clear() ; 
			    	            lloc << hex << ea ;
			    	            lloc >> LT.at(i).loc ;
			    	            LT.at(i).loc = ZeroForLoc( LT.at(i).loc, 4 ) ;
							}
						}
					}
					else {
					  check = true ;
					  jjump.clear() ;
			    	  location = outerans.at(i).at(j+1) ;
			    	  jjump << location ;
			    	  jjump >> jump ;
			    	  locInt = jump ;
			    	  lloc.clear() ; 
			    	  lloc << hex << locInt ;
			    	  lloc >> LT.at(i).loc ;
			    	  LT.at(i).loc = ZeroForLoc( LT.at(i).loc, 4 ) ;
			    	  lloc.clear() ; 
			    	  lloc << store ;
			    	  lloc >> locInt ;
			        }
				}
				else if ( outerans.at(i).at(j) == "=" ) {
					bool kk = false ;
					for ( int p = j ; p < outerans.at(i).size() ; p++ )
					  OT = OT + outerans.at(i).at(p) ;
					for ( int k = 0 ; k < outliteral.size() ; k++ ) {
						if ( OT == outliteral.at(k) )
						  kk = true ;
					}
					if ( !kk )
					  outliteral.push_back(OT) ;
					kk = false ;
					if ( j+2 <outerans.at(i).size() && outerans.at(i).at(j+2) == "\'" ) {
						tempL.name = outerans.at(i).at(j+3) ;
						if ( outerans.at(i).at(j+1) == "X" ) {
						  tempL.type = 1 ;
						  tempL.mc = outerans.at(i).at(j+3) ;
					    }
						else  {
						  tempL.type = 2 ;
						  tempL.mc = ForC( outerans.at(i).at(j+3) ) ;
					    }
						for ( int k = 0 ; k < literalTable.size() ; k++ ) {
						  if ( tempL.name == literalTable.at(k).name )
						    kk = true ;
					    }
					    if ( !kk )
					      literalTable.push_back( tempL ) ;
					}
					else {
						tempL.name = outerans.at(i).at(j+1) ;
						tempL.type = 3 ;
						tempL.mc =  ForWord(outerans.at(i).at(j+1) ) ;
						for ( int k = 0 ; k < literalTable.size() ; k++ ) {
						  if ( tempL.name == literalTable.at(k).name )
						    kk = true ;
					    }
					    if ( !kk )
					      literalTable.push_back( tempL ) ;
					}
					kk = false ;
					OT = "" ;
					tempL.name = "" ;
					tempL.type = -1 ;
					tempL.loc = "" ;
					// cout << "END LLLLL" << endl ; 
			    }
			    else if ( outerans.at(i).at(j) == "LTORG" || outerans.at(i).at(j) == "END" ) {
			    	check = true ;
			    	locInt = ForLiteral( store, literalloc ) ;
			    	outliteral.push_back( "" ) ;
					//cout << "fffffffffffffffffff" <<   literalloc << endl ;  	
				} 
				else if ( outerans.at(i).at(j) == "BASE" )
				  check = true ;

				if ( IsTable1( tolow( outerans.at(i).at(j) ), plus) ) {
					if ( plus == 34 ) {
					  if ( j-1 >= 0 && outerans.at(i).at(j-1) == "+" )
					    plus = 4 ;
					  else 
					    plus = 3 ;
				    }				
				}
			}
						 
			lloc.clear() ;
			if ( SIC ) {
			  if ( i != 0 && outerans.at(i).at(0) != "." && !check ) 
		        locInt = locInt + 3 ; 	      
			}
			else {
			  if ( i != 0 && outerans.at(i).at(0) != "." && !check ) 
		        locInt = locInt + plus ; 
		    }
		    lloc << hex << locInt ;
			tempL.name = "" ;
			tempL.loc = "" ;
			if ( check )
			  check = false ;
			
		}
		
		// cout << literalTable.size() << endl ;
		
		/*for ( int i = 0 ; i < literalTable.size() ; i++ )	
		  cout << literalTable.at(i).loc ; */
		
		/*for ( int i = 0 ; i < outerans.size() ; i++ ) {
			for ( int j = 0 ; j < outerans.at(i).size() ; j++ )
			  cout << outerans.at(i).at(j) << " " ;
			cout << endl ;
		}*/
		
		/*for ( int i = 0 ; i < LT.size() ; i++ ) {
			cout << LT.at(i).name << " " << LT.at(i).loc << endl;
		}*/
	}
	
	void assemblerPass2() {
		unsigned a, b ;
		bool isindex = false ;
		string op = "", address = "", mmc = "" ;
		string reg1 = "", reg2 = "" ;
		int forFormat = 0, loc = 0, ppp ;
		int Nbit = 0, Ibit = 0, Xbit = 0, Bbit = 0, Pbit = 0, Ebit = 0 ; 
		stringstream bbit, nnum ;
		mc.push_back(mmc) ;
	    for ( int i = 1 ; i < outerans.size() ; i++ ) {
	    	if ( i+1 < outerans.size() )
	    	  PC = LT.at(i+1).loc ;
	    	for ( int j = 0 ; j < outerans.at(i).size() ; j++ ) {
	    		if ( "BASE" == toup(outerans.at(i).at(j)) ) {
	    			if ( IsLable( outerans.at(i).at(j+1) ) )
					  BR = FindLoc( outerans.at(i).at(j+1) ) ;
					else {
					  nnum.clear() ;
					  nnum << outerans.at(i).at(j+1) ;
		              nnum >> ppp ;
		              nnum.clear() ;
		              nnum << hex << ppp ;
		              nnum >> BR ;
					  BR = ZeroForLoc( BR, 4 ) ;
				    }
				    // cout << BR << "RIvenRivenRiven" << endl ;
	    	    }
	    		if ( IsTable2(outerans.at(i).at(j)) ) {
	    			if ( outerans.at(i).at(j) == "WORD" || outerans.at(i).at(j) == "BYTE" ) {
	    				if ( outerans.at(i).at(j) == "BYTE" ) {
	    					if(outerans.at(i).at(j+1) == "X" )
	    					  mmc = outerans.at(i).at(j+3) ;
	    					else if(outerans.at(i).at(j+1) == "C" ) 
	    					  mmc = ForC( outerans.at(i).at(j+3) ) ;
	    					else
	    					  mmc = ForWord(outerans.at(i).at(j+1) ) ;
							// cout << mmc << endl ;	
							mc.push_back( mmc ) ;
							mmc = "" ;
							j = outerans.at(i).size() ;
						}
						else {
							if(outerans.at(i).at(j+1) == "X" )
	    					  mmc = ZeroForLoc(outerans.at(i).at(j+3), 6) ;
	    					else if(outerans.at(i).at(j+1) == "C" ) 
	    					  mmc = ForC( outerans.at(i).at(j+3) ) ;
	    					else 
							  mmc = ForWord( outerans.at(i).at(j+1) ) ;
							// cout << mmc << endl ;
							mc.push_back( mmc ) ;
							mmc = "" ;
							j = outerans.at(i).size() ;
						}
					} 
					else {
						mmc = "" ;
						// cout << mmc << endl ;
						mc.push_back( mmc ) ;
					}        
				}
				else if ( outerans.at(i).at(0) == "." ) {
					mmc = "" ;
					// cout << mmc << endl ;
					mc.push_back( mmc ) ;
				}
	    		else if ( IsTable1( tolow(outerans.at(i).at(j) ), forFormat ) && SIC ) {	
	    			op = IsInstruction( tolow(outerans.at(i).at(j)) ) ;
	    			//cout << op << endl ;
	    			if ( op != "" ) {
					  if ( j+1 < outerans.at(i).size() )		
	    			    address = FindLoc( outerans.at(i).at(j+1) );
	    			  else 
	    			    address = "0000" ;
	    			  //cout << "addressssssssssssssssssss    " <<address << endl ;
				      if ( j+2 < outerans.at(i).size() && outerans.at(i).at(j+3) == "X" )
	    		        isindex = true ;
	    		      mmc = CreateCode( op, address, isindex ) ;
	    		      mmc = ZeroForLoc( mmc, 6 ) ;
	    		      mc.push_back( mmc ) ;
	    		      // cout << mmc << endl ;
	    		      op = "" ;
	    		      address = "" ;
	    		      mmc = "" ;
	    		      j = outerans.at(i).size() ;
	    		      isindex = false ;
	    		    }
	    	    }
	    	    else if ( IsTable1( tolow(outerans.at(i).at(j) ), forFormat ) && forFormat == 1  ) {
	    	    	mmc = IsInstruction( tolow(outerans.at(i).at(j)) ) ;
	    	    	// cout << mmc << endl ;
	    	    	mmc = ZeroForLoc( mmc, 2 ) ;
					mc.push_back( mmc ) ; 
					mmc = "" ;
				}
				else if ( IsTable1( tolow( outerans.at(i).at(j) ), forFormat ) && forFormat == 2 ){
					op = IsInstruction( tolow(outerans.at(i).at(j)) ) ;
					// cout << op << "oooooooooooooop" << endl ;
					reg1 = FindReg( outerans.at(i).at(j+1) ) ;
					if ( j+3 < outerans.at(i).size() )
					  reg2 = FindReg( outerans.at(i).at(j+3) ) ;
					mmc = ForFormat2( op, reg1, reg2 ) ;
					mmc = ZeroForLoc( mmc, 4 ) ;
					// cout << mmc << "mmmmmmmmmmmmmmmmmmmmmmmmmmc" << endl ;
					mc.push_back( mmc ) ; 
					reg1 = "" ;
					reg2 = "" ;
				}
				else if ( IsTable1( tolow( outerans.at(i).at(j) ), forFormat ) && forFormat == 34 ) {
					op = IsInstruction( tolow(outerans.at(i).at(j)) ) ;
					if ( j > 0 && outerans.at(i).at(j-1) == "+" ) {
						Ebit = 1 ;
						if ( j+1 < outerans.at(i).size() && outerans.at(i).at(j+1) == "@" )
						  Nbit = 1 ;
						if ( j+1 < outerans.at(i).size() && outerans.at(i).at(j+1) == "#" )
						  Ibit = 1 ;
						for ( int p = 0 ; p < outerans.at(i).size() ; p++ )  {
						  if ( outerans.at(i).at(p) == "x" || outerans.at(i).at(p) == "X" && outerans.at(i).at(p-1) == "," && IsLable(outerans.at(i).at(p-2))  )
						    Xbit = 1 ;
						  if ( ( Nbit == 0 && Ibit == 0 )|| Xbit == 1  ) {
						  	Nbit = 1 ;
						  	Ibit = 1 ;	
						  }
					    }
					    if ( outerans.at(i).at( outerans.at(i).size()-1 ) == "\'" )
					      address = LocInLiteral(outerans.at(i).at( outerans.at(i).size()-2 )) ;
					    else{
					    	address = FindLoc( outerans.at(i).at( outerans.at(i).size()-1 ) ) ;
					    	if ( address == "" )
					    	  address = LocInLiteral(outerans.at(i).at( outerans.at(i).size()-1 )) ;
					    	if ( Xbit == 1 && address == "" )   
					          address = FindLoc(outerans.at(i).at( outerans.at(i).size()-3 )) ;
					    	if ( address == "" ) {
					    	  address = ForWord( outerans.at(i).at( outerans.at(i).size()-1 ) ) ;
					        }
						}
					    
					    
					    address = ZeroForLoc( address, 5 ) ;
					    mmc = GenerateCode3( op, Nbit, Ibit, Xbit, Bbit, Pbit, Ebit, address ) ;
					    mmc = ZeroForLoc( mmc, 8 ) ;
					    // cout << mmc << " mmccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc" << endl ;  
						Nbit = 0 ;
						Ibit = 0 ;
						Xbit = 0 ;
						Bbit = 0 ;  
						Pbit = 0 ;
						Ebit = 0 ;  
					}
					else {
						Ebit = 0 ;
						if ( j+1 < outerans.at(i).size() && outerans.at(i).at(j+1) == "@" )
						  Nbit = 1 ;
						if ( j+1 < outerans.at(i).size() && outerans.at(i).at(j+1) == "#" )
						  Ibit = 1 ;
						for ( int p = 0 ; p < outerans.at(i).size() ; p++ )  {
						  if ( (outerans.at(i).at(p) == "x" || outerans.at(i).at(p) == "X" ) && outerans.at(i).at(p-1) == "," && IsLable(outerans.at(i).at(p-2))  )
						    Xbit = 1 ;
						  if (( Nbit == 0 && Ibit == 0 ) || Xbit == 1  ) {
						  	Nbit = 1 ;
						  	Ibit = 1 ;	
						  }
					    }
					    
					    if ( outerans.at(i).at( outerans.at(i).size()-1 ) == "\'" )
					      address = LocInLiteral(outerans.at(i).at( outerans.at(i).size()-2 )) ;
					    else{
					    	address = FindLoc( outerans.at(i).at( outerans.at(i).size()-1 ) ) ;
					    	if ( address == "" ) 			    	  
					    	  address = LocInLiteral(outerans.at(i).at( outerans.at(i).size()-1 )) ;
					    	if ( Xbit == 1 && address == "" )   
					          address = FindLoc(outerans.at(i).at( outerans.at(i).size()-3 )) ;
						}
											
						address = ForFormat3( Bbit, Pbit, address ) ;
						if( address == "" && Ibit == 1 && Nbit == 0 )
						  address = outerans.at(i).at( outerans.at(i).size()-1 ) ;
					    //cout << Bbit << Pbit << endl ;
					    address = ZeroForLoc( address, 3 ) ;
					    mmc = GenerateCode3( op, Nbit, Ibit, Xbit, Bbit, Pbit, Ebit, address ) ;
					    mmc = ZeroForLoc( mmc, 6 ) ;
		                // cout << mmc << " mmccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc" << endl ;
						Nbit = 0 ;
						Ibit = 0 ;
						Xbit = 0 ;
						Bbit = 0 ;  
						Pbit = 0 ;
						Ebit = 0 ;
					}
		
					mc.push_back( mmc ) ; 
					j = outerans.at(i).size() ;
				}
			}
		}
		// cout << "--------------------------------------" << endl ;
		/*for ( int i = 0 ; i < mc.size() ; i++ )
		  cout << mc.at(i) << endl ;*/
	}
	
	void AssemblerPrint() {
		outname = name +  "_output.txt" ;
    	out.open(outname.c_str()) ;
    if ( SIC ) {
	  out << "Line" << "\t" << "Loc" << "\t" << "Source statement" << "\t\t" << "Object code" << endl << endl ;
		
	  for ( int i = 5, j = 0 ; j < outerans.size() ; i = i + 5, j++ ) {
	    out << setw(3) << i << "\t" ;
		if ( LT.at(j).loc != "" )
		  out << toup(LT.at(j).loc )<< "\t" ;
		else
		  out << "\t" ;
		for ( int k = 0 ; k < input.at(j).size() ; k++ ) {
		  out << input.at(j).at(k)  ;
		  if ( k == input.at(j).size() - 1 && input.at(j).at(k) != 'X' )
			out << "\t" ;
		  if ( input.at(j).size() <= 5 &&  k == input.at(j).size() - 1 )
			out << "\t" ;
		}			
		if ( mc.at(j) != "" )
		  out << "\t" << toup( mc.at(j) )  << endl ;
		else
		  out << endl ; 
	  }
	} 
    else {
    	int loc = 0 ;
    	bool check = false ;
    	out << "Line" << "  " << "Location" << "  " << "Source code" << setw(40) << "Object code" << endl ;
    	out << "----" << "  " << "---------" <<  " " << "-------------------------" << setw(26) << "-----------" << endl ;
    	int count = 0 ;
    	for ( int i = 5, j = 0 ; j < outerans.size() ; i = i + 5, j++ ) {
    	
		  for ( int k = 0 ; k < outerans.at(j).size() ; k++ ) {
		    if ( outerans.at(j).at(k) == "LTORG" || outerans.at(j).at(k) == "END" || outerans.at(j).at(k) == "BASE" ) {
		      check = true ;
		    }	
		  }			
	      out << setw(4) << i << "  " ;
		  if ( LT.at(j).loc != "" && !check )
		    out << toup(LT.at(j).loc )<< "  " << "\t" ;
		  else
		    out << "      " << "\t" ;
		
		  check = false ;	
		for ( int k = 0 ; k < outerans.at(j).size() ; k++ ) {
		  if ( k == 0 && IsLable(outerans.at(j).at(k) )  ) {
		    out << outerans.at(j).at(k) << "\t" ;
		    count++ ;
		  }
		  else if ( k == 0 && !IsLable(outerans.at(j).at(k) ) && outerans.at(j).at(k) != "+" ) {
		    out << "\t" << outerans.at(j).at(k) << "\t" ;
		    count++ ;
		    count++ ;
		  }
		  else if ( k == outerans.at(j).size() - 1 ) {
		    out << outerans.at(j).at(k) << "\t"  ;
		    count++ ;
		  }
		  else if ( k+1 < outerans.at(j).size() && (IsTableOne(tolow(outerans.at(j).at(k))) || IsTable2(outerans.at(j).at(k)) || IsLable(outerans.at(j).at(k)) ) && outerans.at(j).at(k+1) != "\'"
		            && outerans.at(j).at(k+1) != "+" && outerans.at(j).at(k+1) != "-" && outerans.at(j).at(k+1) != ","  ) {
		    out << outerans.at(j).at(k) << "\t"  ;
		    count++ ;
		  }
		  else if ( k+1 < outerans.at(j).size() &&  IsLable(outerans.at(j).at(k)) && ( outerans.at(j).at(k+1) == "\'" || outerans.at(j).at(k+1) == "+" || outerans.at(j).at(k+1) == "-"
		            || outerans.at(j).at(k+1) == "," ) )
		    out << outerans.at(j).at(k)    ;
		  else if ( (!IsTableOne(tolow(outerans.at(j).at(k) )) && !IsTable2(outerans.at(j).at(k)) && !IsLable(outerans.at(j).at(k)) ) )
		    out << outerans.at(j).at(k)  ;
		  
		  if ( outerans.at(j).at(k) == "LTORG" || outerans.at(j).at(k) == "END" ) {
		    check = true ;
		  }
			
		}	
				
		if ( mc.at(j) != "" ) {
		  if ( outerans.at(j).at(outerans.at(j).size()-1) == "X" && outerans.at(j).at(outerans.at(j).size()-2) == "," && IsLable(outerans.at(j).at(outerans.at(j).size()-3) )  ) {
		  	for( int i = count ; i < 4 ; i++ ) 
		    out << "\t"  ;
		  } 
		  else {
		    for( int i = count ; i < 5 ; i++ ) 
		      out << "\t"  ;
	      }
		  out << toup( mc.at(j) )  << endl ;
	    }
		else
		  out << endl ; 
		  
		count = 0 ;
	    
	    if ( check ) {
	      for ( int i = loc ; i < literalTable.size() && literalTable.at(i).name != ""  ; i++ ) {
		  	out  << "      " << toup(literalTable.at(i).loc) << "\t*\t" <<  outliteral.at(i) << "\t\t\t\t" << toup(literalTable.at(i).mc) <<  endl ;
		  	loc = i ;
		  }
		  loc = loc + 2 ;
		}
		//out << loc << endl ;
		
		if ( check )
		  check = false ;
	  }
	}	  		
	    out.close()	;	
	}
	
};

int main() {
  TokenType T ;
  T.readfile() ; 
  T.cutAndprint() ;
  T.setOP() ;
  T.BuildReg() ;
  T.assemblerPass1() ;
  T.assemblerPass2() ;
  T.AssemblerPrint()  ;
  cout << "Done." <<  endl  ;
} 
