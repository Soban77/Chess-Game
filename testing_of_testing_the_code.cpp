#include<iostream>
#include<string>
#include<string.h>
#include<windows.h>
using namespace std;

class piece;
class pawn;
class bishop;
class knight;
class rook;
class queen;
class king;

//This function takes elimination move array of any piece object and it's size and position of king and finds if king position is in this array  
bool checking(string *pe,int size,string position)
{
	bool flag=false;
	
	for(int i=0;i<size;i++)
	{
		if(pe[i]==position)
		{
			flag = true;
		}
	}
	
	if(flag==false)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

//converting the position of a piece into the location(column) in grid array
int convertposition(string position)
{
	char arr[8]={'a','b','c','d','e','f','g','h'},temp;
	int i,column;
	
	temp = position[0];
	
	for(i=0;i<8;i++)
	{
		if(arr[i]==temp)
		{
			column = i;
		}
	}
	
	return column;
}

class board{
	
	protected:
		
		string grid[8][8];
		
	public:
		
		//Initializing the grid
		board()
		{
			int i,j;
			
			grid[0][0] = "Wrook";
			grid[0][1] = "Wknight";
			grid[0][2] = "Wbishop";
			grid[0][3] = "Wqueen";
			grid[0][4] = "Wking";
			grid[0][5] = "Wbishop";
			grid[0][6] = "Wknight";
			grid[0][7]  ="Wrook";
			
			for(i=1;i<2;i++)
			{
				for(j=0;j<8;j++)
				{
					grid[i][j] = "Wpawn";
				}
			}
			
			for(i=2;i<6;i++)
			{
				for(j=0;j<8;j++)
				{
					grid[i][j] = "empty";
				}
			}
			
			for(i=6;i<7;i++)
			{
				for(j=0;j<8;j++)
				{
					grid[i][j] = "Bpawn";
				}
			}
			
			grid[7][0] = "Brook";
			grid[7][1] = "Bknight";
			grid[7][2] = "Bbishop";
			grid[7][3] = "Bqueen";
			grid[7][4] = "Bking";
			grid[7][5] = "Bbishop";
			grid[7][6] = "Bknight";
			grid[7][7] = "Brook";
		}
		
		//checking if the grid of input row and column is empty or not
		bool isempty(int row,int column)
		{
			if(row>7 || row<0 || column>7 || column<0)
			{
				return false;
			}
			
			if(grid[row][column]=="empty")
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool isenemy(int row,int column,string color)
		{
			string s;
			
			if(row>7 || row<0 || column>7 || column<0)
			{
				return false;
			}
			
			s = grid[row][column];
			
			if(s[0]=='W' && color=="black")
			{
				return true;
			}
			else if(s[0]=='B' && color=="white")
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		//changing the grid when a piece have moved
		void updategrid(string move,string position)//this move is the position at which piece needs to move on and position is the initial position
		{
			int x,y,z,k;
			
			x = int(move[1])-49;
			y = convertposition(move);
			
			z = int(position[1])-49;
			k = convertposition(position);
			
			grid[x][y] = grid[z][k];
			grid[z][k] = "empty";
			
	    }
	    
		void display()	
		{
			cout<<endl;
			cout<<endl;
			
			HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
			int e=1;
			
			SetConsoleTextAttribute(hconsole, 15);
			
			for(int i=0;i<8;i++)
			{ 	
				cout<<e+i<<"   ";
				
				for(int j=0;j<8;j++)
				{	
					if(grid[i][j]=="empty")
					{
						SetConsoleTextAttribute(hconsole, 4);
						 
						cout<<". ";
						
						SetConsoleTextAttribute(hconsole, 15);
					}
					else if(grid[i][j]=="Brook" || grid[i][j]=="Wrook")
					{
						cout<<"r ";
					}
					else if(grid[i][j]=="Bbishop" || grid[i][j]=="Wbishop")
					{
						cout<<"b ";
					}
					else if(grid[i][j]=="Bpawn" || grid[i][j]=="Wpawn")
					{
						cout<<"p ";
					}
					else if(grid[i][j]=="Bknight" || grid[i][j]=="Wknight")
					{
						cout<<"n ";
					}
					else if(grid[i][j]=="Bqueen" || grid[i][j]=="Wqueen")
					{
						cout<<"q ";
					}
					else if(grid[i][j]=="Bking" || grid[i][j]=="Wking")
					{
						cout<<"k ";
					}
				}
				
				cout<<endl;
				
				if(i==7)
			    {
			    	cout<<endl;
			    	cout<<"    a b c d e f g h";
			    }
			}
		}
		
		void displaymoves(string *pp,string *pe,int count,int size)
		{
			cout<<endl;
			cout<<endl;
			
			HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
			
			SetConsoleTextAttribute(hconsole, 15);
			
			//cout<<count;
			
			int x[count],y[count],m[size],n[size],e=1;
			string position;
			bool flag=false,isfound=false;
			
			for(int i=0;i<count;i++)
			{
				position = pp[i];
				
				x[i] = int(position[1])-49;
			    y[i] = convertposition(position);
			}
			
			for(int i=0;i<size;i++)
			{
				position = pe[i];
				
				m[i] = int(position[1])-49;
			    n[i] = convertposition(position);
			}
			
			for(int i=0;i<8;i++)
			{
				cout<<e+i<<"   ";
				
				for(int j=0;j<8;j++)
				{
					for(int k=0;k<count;k++)
            		{
            			if(x[k]==i && y[k]==j)
            			{
            				if(grid[i][j]=="empty")
            				{
            					SetConsoleTextAttribute(hconsole, 117); 
            					
            					cout<<"- ";
            					
            					SetConsoleTextAttribute(hconsole, 15); 
							}
							else
							{
								isfound = true;
							}
							
            				flag = true;
						}
            		}
            		
            		for(int k=0;k<size;k++)
            		{
            			if(m[k]==i && n[k]==j)
            			{
            				isfound = true;
						}
            		}
            		
					if(grid[i][j]=="empty" && flag==false)
					{
						SetConsoleTextAttribute(hconsole, 4); 
						
						cout<<". ";
						
						SetConsoleTextAttribute(hconsole, 15); 
					}
					else if(grid[i][j]=="Brook" || grid[i][j]=="Wrook")
					{
						if(isfound==true)
						{
							SetConsoleTextAttribute(hconsole, 122); 
							
							cout<<"R ";
							
							SetConsoleTextAttribute(hconsole, 15);
						}
						else
						{
							cout<<"r ";
						}
					}
					else if(grid[i][j]=="Bbishop" || grid[i][j]=="Wbishop")
					{
						if(isfound==true)
						{
							SetConsoleTextAttribute(hconsole, 122); 
							
							cout<<"B ";
							
							SetConsoleTextAttribute(hconsole, 15);
						}
						else
						{
							cout<<"b ";
						}
					}
					else if(grid[i][j]=="Bpawn" || grid[i][j]=="Wpawn")
					{
						if(isfound==true)
						{
							SetConsoleTextAttribute(hconsole, 122); 
							
							cout<<"P ";
							
							SetConsoleTextAttribute(hconsole, 15);
						}
						else
						{
							cout<<"p ";
						}
					}
					else if(grid[i][j]=="Bknight" || grid[i][j]=="Wknight")
					{
						if(isfound==true)
						{
							SetConsoleTextAttribute(hconsole, 122); 
							
							cout<<"N ";
							
							SetConsoleTextAttribute(hconsole, 15);
						}
						else
						{
							cout<<"n ";
						}
					}
					else if(grid[i][j]=="Bqueen" || grid[i][j]=="Wqueen")
					{
						if(isfound==true)
						{
							SetConsoleTextAttribute(hconsole, 122); 
							
							cout<<"Q ";
							
							SetConsoleTextAttribute(hconsole, 15);
						}
						else
						{
							cout<<"q ";
						}
					}
					else if(grid[i][j]=="Bking" || grid[i][j]=="Wking")
					{
						if(isfound==true)
						{
							SetConsoleTextAttribute(hconsole, 122); 
							
							cout<<"K ";
							
							SetConsoleTextAttribute(hconsole, 15);
						}
						else
						{
							cout<<"k ";
						}
					}
					
					flag = false;
					isfound = false;
				}
				
				cout<<endl;
				
				if(i==7)
			    {
			    	cout<<endl;
			    	cout<<"    a b c d e f g h";
			    }
			}
		}
		
	    board operator=(board b)
        {
        	board c;
        	int i,j;
			
	        for(i=0;i<8;i++)
        	{
        	    for(j=0;j<8;j++)
        		{
        			c.grid[i][j] = b.grid[i][j];
        		}
        	}
			
        	return c;
        }
        
        string** getgrid()
        {
        	string **g;
        	
        	g = new string*[8];
        	
        	for(int i=0;i<8;i++)
        	{
        		*(g+i) = new string[8];
			}
			
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					g[i][j] = grid[i][j];
				}
			}
			
			return g;
		}
};

class piece{
	
	protected:
		
		string name,color,position,*pp,*pe;
		//pp is possible positions of that piece.
		//pe is possible elimination
		int points,count,size;
		//count is the size of pp.
		//size is the size of pe.
		board b,*p;
		
	public:
		
		board* movepiece(string move)
		{
			int i,j;
			bool flag=false;
			
			for(i=0;i<count;i++)
			{
				if(pp[i]==move)
				{
					p->updategrid(move,position);
					position = move;
					flag = true;
				}
			}
			
			if(flag==false)
			{
			    for(i=0;i<size;i++)
    			{
    				if(pe[i]==move)
    				{
    					p->updategrid(move,position);
						position = move;
    					flag = true;
    				}
    			}	
			}
			
			if(flag==true)
			{
				cout<<endl<<"your move is succesfull!"<<endl;
				return p;
			}
			else
			{
				cout<<endl<<"your move is not succesfull!"<<endl;
				return p;
			}
		}
		
		void setboard(board *b)
		{
			p = b;
		}
		
		virtual void showmoves()=0;
		virtual void setname()=0;
		
		void setposition(string pos)
		{
			position = pos;
		}
		
		string* getpe()
		{
			return pe;
		}
		
		int getpeSize()
		{
			return size;
		}
		
		string* getpp()
		{
			return pp;
		}
		
		int getppSize()
		{
			return count;
		}
		
		string getname()
		{
			return name;
		}
		
		string getcolor()
		{
			return color;
		}
		
		string getposition()
		{
			return position;
		}
		
		void setdetails(string color,string position,int points,board *b)
		{
			this->color = color;
			this->position = position;
			this->points = points;
			count = 0;
			size = 0;
			p = b;
		}
};

class pawn:public piece{
	
	public:
		
		void setname()
		{
			name = "pawn";
		}
		
		void showmoves()
		{
			size = 0;
			count = 0;
			
			int x,y,z;
			
			x = int(position[1])-49;
			
			//checking if piece is to have first move
			if(x==1 || x==6)
			{
				if(x==1 && position!="xx")
				{
					if(color=="white")
					{
						string pos1,pos2;
						
						pos1 = position[1]+1;
						pos2 = position[0];
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isempty(y,z))
						{
							count++;
							
							if(count==1)
							{
								pp = new string[count];
						    	pp[count-1] = pos2;
							}
							else
							{
								string *temp;
								
								temp = new string[count-1];
								temp = pp;
								
								delete pp;
								
								pp = new string[count];
								
								for(int l=0;l<count-1;l++)
								{
									pp[l] = temp[l];
								}
								
								pp[count-1] = pos2;
								
								delete temp;
							}
						}
						
						pos1 = position[1]+2;
						pos2 = position[0];
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isempty(y,z))
						{
							count++;
							
							if(count==1)
							{
								pp = new string[count];
						    	pp[count-1] = pos2;
							}
							else
							{
								string *temp;
								
								temp = new string[count-1];
								temp = pp;
								
								delete pp;
								
								pp = new string[count];
								
								for(int l=0;l<count-1;l++)
								{
									pp[l] = temp[l];
								}
								
								pp[count-1] = pos2;
								
								delete temp;
							}
						}
						
						pos1 = position[1]+1;
						
						if(position[0]!='h')
						{
							pos2 = position[0]+1;
							pos2 = pos2+pos1;
							
							y = int(pos2[1])-49;
				    		z = convertposition(pos2);
				    		
				    		if(p->isenemy(y,z,color))
					    	{
					    		size++;
							
					    		if(size==1)
					    		{
						    		pe = new string[size];
						        	pe[size-1] = pos2;
						    	}
						    	else
						    	{
						    		string *temp;
								
						    		temp = new string[size-1];
						    		temp = pe;
								
						    		delete pe;
								
						    		pe = new string[size];
								
						    		for(int l=0;l<size-1;l++)
						    		{
						    			pe[l] = temp[l];
						    		}
								
						    		pe[size-1] = pos2;
								
						    		delete temp;
						    	}
					    	}
						}
						else if(position[0]!='a')
						{
							pos2 = position[0]-1;
							pos2 = pos2+pos1;
							
							y = int(pos2[1])-49;
				    		z = convertposition(pos2);
				    		
				    		if(p->isenemy(y,z,color))
					    	{
					    		size++;
							
					    		if(size==1)
					    		{
						    		pe = new string[size];
						        	pe[size-1] = pos2;
						    	}
						    	else
						    	{
						    		string *temp;
								
						    		temp = new string[size-1];
						    		temp = pe;
								
						    		delete pe;
								
						    		pe = new string[size];
								
						    		for(int l=0;l<size-1;l++)
						    		{
						    			pe[l] = temp[l];
						    		}
								
						    		pe[size-1] = pos2;
								
						    		delete temp;
						    	}
					    	}
						}	
					}
				}
				else if(x==6 && position!="xx")
				{
					if(color=="black")
					{
						string pos1,pos2;
						
						pos1 = position[1]-1;
						pos2 = position[0];
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(b.isempty(y,z))
						{
							count++;
							
							if(count==1)
							{
								pp = new string[count];
						    	pp[count-1] = pos2;
							}
							else
							{
								string *temp;
								
								temp = new string[count-1];
								temp = pp;
								
								delete pp;
								
								pp = new string[count];
								
								for(int l=0;l<count-1;l++)
								{
									pp[l] = temp[l];
								}
								
								pp[count-1] = pos2;
								
								delete temp;
							}
						}
						
						pos1 = position[1]-2;
						pos2 = position[0];
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isempty(y,z))
						{
							count++;
							
							if(count==1)
							{
								pp = new string[count];
						    	pp[count-1] = pos2;
							}
							else
							{
								string *temp;
								
								temp = new string[count-1];
								temp = pp;
								
								delete pp;
								
								pp = new string[count];
								
								for(int l=0;l<count-1;l++)
								{
									pp[l] = temp[l];
								}
								
								pp[count-1] = pos2;
								
								delete temp;
							}
						}
						
						pos1 = position[1]-1;
						
						if(position[0]!='h')
						{
							pos2 = position[0]+1;
							pos2 = pos2+pos1;
							
							y = int(pos2[1])-49;
				    		z = convertposition(pos2);
				    		
				    		if(p->isenemy(y,z,color))
					    	{
					    		size++;
							
					    		if(size==1)
					    		{
						    		pe = new string[size];
						        	pe[size-1] = pos2;
						    	}
						    	else
						    	{
						    		string *temp;
								
						    		temp = new string[size-1];
						    		temp = pe;
								
						    		delete pe;
								
						    		pe = new string[size];
								
						    		for(int l=0;l<size-1;l++)
						    		{
						    			pe[l] = temp[l];
						    		}
								
						    		pe[size-1] = pos2;
								
						    		delete temp;
						    	}
					    	}
						}
						else if(position[0]!='a')
						{
							pos2 = position[0]-1;
							pos2 = pos2+pos1;
							
							y = int(pos2[1])-49;
				    		z = convertposition(pos2);
				    		
				    		if(p->isenemy(y,z,color))
					    	{
					    		size++;
							
					    		if(size==1)
					    		{
						    		pe = new string[size];
						        	pe[size-1] = pos2;
						    	}
						    	else
						    	{
						    		string *temp;
								
						    		temp = new string[size-1];
						    		temp = pe;
								
						    		delete pe;
								
						    		pe = new string[size];
								
						    		for(int l=0;l<size-1;l++)
						    		{
						    			pe[l] = temp[l];
						    		}
								
						    		pe[size-1] = pos2;
								
						    		delete temp;
						    	}
					    	}
						}	
					}
				}
			}
			else if(position!="xx")//other than first move of piece that is not eliminated.
			{
				if(color=="white")
				{
					if(x!=7)
					{
						string pos1,pos2;
						
						pos1 = position[1]+1;
						pos2 = position[0];
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isempty(y,z))
						{
							count++;
							
							if(count==1)
							{
								pp = new string[count];
						    	pp[count-1] = pos2;
							}
							else
							{
								string *temp;
								
								temp = new string[count-1];
								temp = pp;
								
								delete pp;
								
								pp = new string[count];
								
								for(int l=0;l<count-1;l++)
								{
									pp[l] = temp[l];
								}
								
								pp[count-1] = pos2;
								
								delete temp;
							}
						}
						
						pos1 = position[1]+1;
						
						if(position[0]!='h')
						{
							pos2 = position[0]+1;
						}
						
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isenemy(y,z,color))
					    {
					    	size++;
							
					    	if(size==1)
					    	{
						    	pe = new string[size];
						        pe[size-1] = pos2;
						    }
						    else
						    {
						    	string *temp;
								
						    	temp = new string[size-1];
						    	temp = pe;
								
						    	delete pe;
								
						    	pe = new string[size];
								
						    	for(int l=0;l<size-1;l++)
						    	{
						    		pe[l] = temp[l];
						    	}
								
						    	pe[size-1] = pos2;
								
						    	delete temp;
						    }
					    }
					    
					    if(position[0]!='a')
						{
							pos2 = position[0]-1;
						}
						
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isenemy(y,z,color))
					    {
					    	size++;
							
					    	if(size==1)
					    	{
						    	pe = new string[size];
						        pe[size-1] = pos2;
						    }
						    else
						    {
						    	string *temp;
								
						    	temp = new string[size-1];
						    	temp = pe;
								
						    	delete pe;
								
						    	pe = new string[size];
								
						    	for(int l=0;l<size-1;l++)
						    	{
						    		pe[l] = temp[l];
						    	}
								
						    	pe[size-1] = pos2;
								
						    	delete temp;
						    }
					    }
					}
				}
				else if(color=="black")
				{
					if(x!=0)
					{
						string pos1,pos2;
						
						pos1 = position[1]-1;
						pos2 = position[0];
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isempty(y,z))
						{
							count++;
							
							if(count==1)
							{
								pp = new string[count];
						    	pp[count-1] = pos2;
							}
							else
							{
								string *temp;
								
								temp = new string[count-1];
								temp = pp;
								
								delete pp;
								
								pp = new string[count];
								
								for(int l=0;l<count-1;l++)
								{
									pp[l] = temp[l];
								}
								
								pp[count-1] = pos2;
								
								delete temp;
							}
						}
						
						pos1 = position[1]-1;
						
						if(position[0]!='h')
						{
							pos2 = position[0]+1;
						}
						
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isenemy(y,z,color))
					    {
					    	size++;
							
					    	if(size==1)
					    	{
						    	pe = new string[size];
						        pe[size-1] = pos2;
						    }
						    else
						    {
						    	string *temp;
								
						    	temp = new string[size-1];
						    	temp = pe;
								
						    	delete pe;
								
						    	pe = new string[size];
								
						    	for(int l=0;l<size-1;l++)
						    	{
						    		pe[l] = temp[l];
						    	}
								
						    	pe[size-1] = pos2;
								
						    	delete temp;
						    }
					    }
					    
					    if(position[0]!='a')
						{
							pos2 = position[0]-1;
						}
						
						pos2 = pos2+pos1;
						
						y = int(pos2[1])-49;
						z = convertposition(pos2);
						
						if(p->isenemy(y,z,color))
					    {
					    	size++;
							
					    	if(size==1)
					    	{
						    	pe = new string[size];
						        pe[size-1] = pos2;
						    }
						    else
						    {
						    	string *temp;
								
						    	temp = new string[size-1];
						    	temp = pe;
								
						    	delete pe;
								
						    	pe = new string[size];
								
						    	for(int l=0;l<size-1;l++)
						    	{
						    		pe[l] = temp[l];
						    	}
								
						    	pe[size-1] = pos2;
								
						    	delete temp;
						    }
					    }
					}
				}
			}
		}
};

class bishop:public piece{
	
	public:
		
		
		void setname()
		{
			name = "bishop";
		}
		
		void showmoves()
		{	
			size = 0;
			count = 0;
			
			int x,y,z,i=0,flag=0;
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			string pos1,pos2,pos3;
			
			//for moving in cross towards bottom right
			while(y!=7 && x!=7 && flag==0)
			{
				i++;
				x++;
				y++;
						
				pos1 = position[1]+i;
				pos2 = position[0]+i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos2;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos2;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving in cross towards top left
			while(y!=0 && x!=0 && flag==0)
			{
				i++;
				x--;
				y--;
						
				pos1 = position[1]-i;
				pos2 = position[0]-i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving in cross towards top right
			while(y!=7 && x!=0 && flag==0)
			{
				i++;
				x--;
				y++;
						
				pos1 = position[1]-i;
				pos2 = position[0]+i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving in cross towards bottom left
			while(y!=0 && x!=7 && flag==0)
			{
				i++;
				x++;
				y--;
						
				pos1 = position[1]+i;
				pos2 = position[0]-i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}	
		}
};

class rook:public piece{
	
	public:
		
		void setname()
		{
			name = "rook";
		}
		
		void showmoves()
		{
			size = 0;
			count = 0;
			
			int x,y,z,i=0,flag=0;
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			string pos1,pos2,pos3;
			//for moving down
			while(x!=7 && flag==0)
			{
				i++;
				x++;
						
				pos1 = position[1]+i;
				pos2 = position[0];
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving right
			while(y!=7 && flag==0)
			{
				i++;
				y++;
						
				pos1 = position[1];
				pos2 = position[0]+i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			
			//for moving up
			while(x!=0 && flag==0)
			{
				i++;
				x--;
						
				pos1 = position[1]-i;
				pos2 = position[0];
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving left
			while(y!=0 && flag==0)
			{
				i++;
				y--;
						
				pos1 = position[1];
				pos2 = position[0]-i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
		}
};

class queen:public piece{
	
	public:
		
		void setname()
		{
			name = "queen";
		}
		
		void showmoves()
		{
			size = 0;
			count = 0;
			
			int x,y,z,i=0,flag=0;
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			string pos1,pos2,pos3;
			//for moving down
			while(x!=7 && flag==0)
			{
				i++;
				x++;
						
				pos1 = position[1]+i;
				pos2 = position[0];
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving right
			while(y!=7 && flag==0)
			{
				i++;
				y++;
						
				pos1 = position[1];
				pos2 = position[0]+i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			
			//for moving up
			while(x!=0 && flag==0)
			{
				i++;
				x--;
						
				pos1 = position[1]-i;
				pos2 = position[0];
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving left
			while(y!=0 && flag==0)
			{
				i++;
				y--;
						
				pos1 = position[1];
				pos2 = position[0]-i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			
			//for moving in cross towards bottom right
			while(y!=7 && x!=7 && flag==0)
			{
				i++;
				x++;
				y++;
						
				pos1 = position[1]+i;
				pos2 = position[0]+i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving in cross towards top left
			while(y!=0 && x!=0 && flag==0)
			{
				i++;
				x--;
				y--;
						
				pos1 = position[1]-i;
				pos2 = position[0]-i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving in cross towards top right
			while(y!=7 && x!=0 && flag==0)
			{
				i++;
				x--;
				y++;
						
				pos1 = position[1]-i;
				pos2 = position[0]+i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			i = 0;
			flag = 0;
			//for moving in cross towards bottom left
			while(y!=0 && x!=7 && flag==0)
			{
				i++;
				x++;
				y--;
						
				pos1 = position[1]+i;
				pos2 = position[0]-i;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
					
					flag = 1;
				}
				else
				{
					flag = 1;
				}
			}	
		}
};

class knight:public piece{
	
	public:
		
		void setname()
		{
			name = "knight";
		}
		
		void showmoves()
		{
			size = 0;
			count = 0;
			
			int x,y,z;
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			string pos1,pos2,pos3;
//down-left L-moves			
			x++;
			y = y-2;
			
			if(x<=7 && y>=0)
			{
				pos1 = position[1]+1;
				pos2 = position[0]-2;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x = x+2;
			y--;
			
			if(x<=7 && y>=0)
			{
				pos1 = position[1]+1;
				pos2 = position[0]-2;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
//up-left l-moves			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x = x-2;
			y--;
			
			if(x>=0 && y>=0)
			{
				pos1 = position[1]-2;
				pos2 = position[0]-1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			y = y-2;
			x--;
			
			if(x>=0 && y>=0)
			{
				pos1 = position[1]-1;
				pos2 = position[0]-2;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
//up-right L-moves
			x = int(position[1])-49;
			y = convertposition(position);
			
			y = y+2;
			x--;
			
			if(x>=0 && y<=7)
			{
				pos1 = position[1]-1;
				pos2 = position[0]+2;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x = x-2;
			y++;
			
			if(x>=0 && y<=7)
			{
				pos1 = position[1]-2;
				pos2 = position[0]+1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
//down-right L-moves			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x = x+2;
			y++;
			
			if(x<=7 && y<=7)
			{
				pos1 = position[1]+2;
				pos2 = position[0]+1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			y = y+2;
			x++;
			
			if(x<=7 && y<=7)
			{
				pos1 = position[1]+1;
				pos2 = position[0]+2;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y))
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color))
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
		}
};

class king:public piece{
	
	bool ischeck;
	
	public:
		
		void setname()
		{
			name = "king";
		}
		
		bool getischeck()
		{
			return ischeck;
		}
		
		void showmoves()
		{
		}
		//overloading
		void showmoves(pawn pa[16],knight kn[4],bishop bi[4],rook r[4],queen q[2])
		{
			
			size = 0;
			count = 0;
			
			int x,y,z;
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			string pos1,pos2,pos3;
			
			x++;
			y++;
			
			if(x<=7 && y<=7)
			{
				pos1 = position[1]+1;
				pos2 = position[0]+1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x--;
			y++;
			
			if(x>=0 && y<=7)
			{
				pos1 = position[1]-1;
				pos2 = position[0]+1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x--;
			y--;
			
			if(x>=0 && y>=0)
			{
				pos1 = position[1]-1;
				pos2 = position[0]-1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x++;
			y--;
			
			if(x<=7 && y>=0)
			{
				pos1 = position[1]+1;
				pos2 = position[0]-1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			y++;
			
			if(y<=7)
			{
				pos1 = position[1];
				pos2 = position[0]+1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			y--;
			
			if(y>=0)
			{
				pos1 = position[1];
				pos2 = position[0]-1;
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x++;
			
			if(x<=7)
			{
				pos1 = position[1]+1;
				pos2 = position[0];
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}
			
			x = int(position[1])-49;
			y = convertposition(position);
			
			x--;
			
			if(x>=0)
			{
				pos1 = position[1]-1;
				pos2 = position[0];
				pos3 = pos2+pos1;
				
				if(p->isempty(x,y) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					count++;
							
					if(count==1)
					{
						pp = new string[count];
						pp[count-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[count-1];
						temp = pp;
								
						delete pp;
								
						pp = new string[count];
								
						for(int l=0;l<count-1;l++)
						{
							pp[l] = temp[l];
						}
								
						pp[count-1] = pos3;
								
						delete temp;
					}
				}
				else if(p->isenemy(x,y,color) && afterCheckMoves(pos3,pa,kn,bi,r,q)==false)
				{
					size++;
							
					if(size==1)
					{
					    pe = new string[size];
						pe[size-1] = pos3;
					}
					else
					{
						string *temp;
								
						temp = new string[size-1];
						temp = pe;
								
						delete pe;
								
					    pe = new string[size];
								
						for(int l=0;l<size-1;l++)
						{
						    pe[l] = temp[l];
						}
								
						pe[size-1] = pos3;
								
						delete temp;
					}
				}
			}													
		}
		//checking after enemy's any move that if king becomes checked 
		void ischecked(pawn pa[16],knight kn[4],bishop bi[4],rook r[4],queen q[2])
		{
			for(int i=0;i<16;i++)
			{
				if(pa[i].getcolor()!=color)
				{
					ischeck = checking(pa[i].getpe(),pa[i].getpeSize(),position);
					break;
				}
			}
			
			if(ischeck!=true)
			{
				for(int i=0;i<4;i++)
				{
					if(kn[i].getcolor()!=color)
					{
						ischeck = checking(kn[i].getpe(),kn[i].getpeSize(),position);
						break;
					}
				}
				
				if(ischeck!=true)
				{
					for(int i=0;i<4;i++)
					{
						if(bi[i].getcolor()!=color)
						{
							ischeck = checking(bi[i].getpe(),bi[i].getpeSize(),position);
						    break;
						}
					}
					
					if(ischeck!=true)
					{
						for(int i=0;i<4;i++)
						{
							if(r[i].getcolor()!=color)
							{
								ischeck = checking(r[i].getpe(),r[i].getpeSize(),position);
						        break;
							}
							
							if(ischeck!=true)
							{
								for(int i=0;i<2;i++)
								{
									if(q[i].getcolor()!=color)
									{
										ischeck = checking(r[i].getpe(),r[i].getpeSize(),position);
						                break;
									}
								}
							}
						}
					}
				}
			}
		}
		//checking moves which king can move so that king could not be checked
		bool afterCheckMoves(string pos,pawn pa[16],knight kn[4],bishop bi[4],rook r[4],queen q[2])
		{
			bool flag;
			
		    flag = false;
				
		    for(int i=0;i<16;i++)
			{
				if(pa[i].getcolor()!=color)
				{
					flag = checking(pa[i].getpe(),pa[i].getpeSize(),pos);
				}
			}
			
			if(flag!=true)
			{
				for(int i=0;i<4;i++)
				{
					if(kn[i].getcolor()!=color)
					{
						flag = checking(kn[i].getpe(),kn[i].getpeSize(),pos);
					}
				}
				
				if(flag!=true)
				{
					for(int i=0;i<4;i++)
					{
						if(bi[i].getcolor()!=color)
						{
							flag = checking(bi[i].getpe(),bi[i].getpeSize(),pos);		
						}
					}
					
					if(flag!=true)
					{
						for(int i=0;i<4;i++)
						{
							if(r[i].getcolor()!=color)
							{
								flag = checking(r[i].getpe(),r[i].getpeSize(),pos);
							}
							
							if(flag!=true)
							{
								for(int i=0;i<2;i++)
								{
									if(q[i].getcolor()!=color)
									{
										flag = checking(r[i].getpe(),r[i].getpeSize(),pos);
									}
								}
							}
						}
					}
				}
			}
			
			return flag;
		}
};

class bot{
	
	protected:
		
		
	public:
		
		void movepiece()
		{
			
		}
};

char convert(pawn pa[16],bishop bi[4],rook r[4],knight kn[4],king k[2],queen q[2],string position,board *b)
{
	int x,y,length;
	string pos,color,piece,**grid;
	char c;
	
	x = int(position[1])-49;
	y = convertposition(position);
	
	grid = b->getgrid();
	pos = grid[x][y];
	
	c = pos[0];
	
	if(c=='W')
	{
		color = "white";
	}
	else if(c=='B')
	{
		color = "black";
	}
	
	length = pos.length();
	piece = pos.substr(1,length);
	
	if(piece=="pawn")
	{
		return 'p';
	}
	else if(piece=="knight")
	{
		return 'n';
	}
	else if(piece=="bishop")
	{
		return 'b';
	}
	else if(piece=="rook")
	{
		return 'r';
	}
	else if(piece=="queen")
	{
		return 'q';
	}
	else if(piece=="king")
	{
		return 'k';
	}		
}

int find_array(char piece,pawn pa[16],bishop bi[4],rook r[4],knight kn[4],king k[2],queen q[2],string position)
{
	switch(piece)
	{
		case 'p':
			
			for(int i=0;i<16;i++)
			{
				if(pa[i].getposition()==position)
				{
					return i;
				}
			}
			
			break;
			
		case 'b':
			
			for(int i=0;i<4;i++)
			{
				if(bi[i].getposition()==position)
				{
					return i;
				}
			}
			
			break;
			
		case 'r':
			
			for(int i=0;i<4;i++)
			{
				if(r[i].getposition()==position)
				{
					return i;
				}
			}
			
			break;
			
		case 'n':
			
			for(int i=0;i<4;i++)
			{
				if(kn[i].getposition()==position)
				{
					return i;
				}
			}
			
			break;
		
		case 'k':
			
			for(int i=0;i<2;i++)
			{
				if(k[i].getposition()==position)
				{
					return i;
				}
			}
			
			break;
			
		case 'q':
			
			for(int i=0;i<2;i++)
			{
				if(q[i].getposition()==position)
				{
					return i;
				}
			}
			
			break;
			
		default:
			
			cout<<"No piece available of this type!\n";
	}
}

main()
{
	board *b = new board();
	
	/*pawn p,p1,p2;
	bishop bi;
	rook r;
	knight k;
	queen q;
	king ki;
	
	string cpos,fpos;//cpos: current position ||  fpos:  final position
	
	ki.setdetails("black","e8",50,b);
	ki.setname();
	ki.showmoves();
	
	q.setdetails("white","d1",40,b);
	q.setname();
	q.showmoves();
	
	p1.setdetails("white","d2",10,b);
	p1.setname();
	p1.showmoves();
	
	k.setdetails("black","b8",20,b);
	k.setname();
	k.showmoves();
	
	r.setdetails("black","a8",20,b);
	r.setname();
	r.showmoves();
	
	bi.setdetails("white","c1",20,b);
	bi.setname();
	bi.showmoves();
	
	p.setdetails("white","b2",10,b);
	p.setname();
	p.showmoves();
	
	b->display();
	b->displaymoves(p.getpp(),p.getpe(),p.getppSize(),p.getpeSize());
	b = p.movepiece("b3");
	
	b->display();
	
	p.showmoves();
	
	b->displaymoves(p.getpp(),p.getpe(),p.getppSize(),p.getpeSize());
	b = p.movepiece("b4");
	
	b->display();
	
	p.showmoves();
	b->displaymoves(p.getpp(),p.getpe(),p.getppSize(),p.getpeSize());
	
	bi.setboard(b);
	bi.showmoves();
	b->displaymoves(bi.getpp(),bi.getpe(),bi.getppSize(),bi.getpeSize());
	
	r.setboard(b);
	r.showmoves();
	b->displaymoves(r.getpp(),r.getpe(),r.getppSize(),r.getpeSize());
	
	k.setboard(b);
	k.showmoves();
	b->displaymoves(k.getpp(),k.getpe(),k.getppSize(),k.getpeSize());
	
	p1.showmoves();
	b->displaymoves(p1.getpp(),p1.getpe(),p1.getppSize(),p1.getpeSize());
	p1.movepiece("d4");
	b->display();
	
	q.showmoves();
	b->displaymoves(q.getpp(),q.getpe(),q.getppSize(),q.getpeSize());
	q.movepiece("d3");
	b->display();
	
	q.showmoves();
	b->displaymoves(q.getpp(),q.getpe(),q.getppSize(),q.getpeSize());
	
	p2.setdetails("black","f7",10,b);
	p2.setname();
	p2.showmoves();
	
	b->displaymoves(p2.getpp(),p2.getpe(),p2.getppSize(),p2.getpeSize());
	p2.movepiece("f5");
	
	q.setboard(b);
	q.showmoves();
	b->displaymoves(q.getpp(),q.getpe(),q.getppSize(),q.getpeSize());
	
	cout<<endl;
	cout<<endl;*/

	string cpos,fpos;//cpos: current position ||  fpos:  final position
	pawn p[16];
	knight kn[4];
	rook r[4];
	bishop bi[4];
	king k[2];
	queen q[2];
	
	for(int i=0;i<16;i++)
	{
		p[i].setname();
	}
	
	for(int i=0;i<4;i++)
	{
		kn[i].setname();
		r[i].setname();
		bi[i].setname();
	}
	
	for(int i=0;i<2;i++)
	{
		k[i].setname();
		q[i].setname();
	}
	
	//Setting Details of All 8 White Pawns.
	p[0].setdetails("white","a2",10,b);
	p[1].setdetails("white","b2",10,b);
	p[2].setdetails("white","c2",10,b);
	p[3].setdetails("white","d2",10,b);
	p[4].setdetails("white","e2",10,b);
	p[5].setdetails("white","f2",10,b);
	p[6].setdetails("white","g2",10,b);
	p[7].setdetails("white","h2",10,b);
	
	//Setting Details of All 8 Black Pawns.
	p[8].setdetails("black","a7",10,b);
	p[9].setdetails("black","b7",10,b);
	p[10].setdetails("black","c7",10,b);
	p[11].setdetails("black","d7",10,b);
	p[12].setdetails("black","e7",10,b);
	p[13].setdetails("black","f7",10,b);
	p[14].setdetails("black","g7",10,b);
	p[15].setdetails("black","h7",10,b);
	
	//Setting Details of All 2 White Rooks.
	r[0].setdetails("white","a1",20,b);
	r[1].setdetails("white","h1",20,b);
	
	//Setting Details of All 2 Black Rooks.
	r[2].setdetails("black","a8",20,b);
	r[3].setdetails("black","h8",20,b);
	
	//Setting Details of All 2 White Bishops.
	bi[0].setdetails("white","c1",20,b);
	bi[1].setdetails("white","f1",20,b);
	
	//Setting Details of All 2 Black Bishops.
	bi[2].setdetails("black","c8",20,b);
	bi[3].setdetails("black","f8",20,b);
	
	//Setting Details of All 2 White Knights.
	kn[0].setdetails("white","b1",20,b);
	kn[1].setdetails("white","g1",20,b);
	
	//Setting Details of All 2 Black Knights.
	kn[2].setdetails("black","b8",20,b);
	kn[3].setdetails("black","g8",20,b);
	
	//Setting Details of White Queen.
	q[0].setdetails("white","d1",40,b);
	
	//Setting Details of Black Queen.
	q[1].setdetails("black","d8",40,b);
	
	//Setting Details of White King.
	k[0].setdetails("white","e1",50,b);
	
	//Setting Details of Black King.
	k[1].setdetails("black","e8",50,b);
	
	
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char char1,piece;
	int num=0,even=0;
	
	SetConsoleTextAttribute(hconsole, 14);
	
	cout<<"____________________________________\n";
	cout<<"!!!!START THE GAME BY PRESSING 1!!!!\n";
	cout<<"------------------------------------\n";
	cout<<"\t\t";
	cin>>char1;
	
	if(char1==49)
	{
		b->display();
		
		cout<<endl;
		cout<<endl;
		
		SetConsoleTextAttribute(hconsole, 4);
		
		if(even%2==0)
		{
			cout<<endl<<"White's turn!"<<endl;
		}
		else
		{
			cout<<endl<<"Black's turn!"<<endl;
		}
		
		cout<<"END THE GAME  ANYTIME BY ENTERING FINISH/finish!\nIF NOT\nEnter position for piece to be selected: ";
		cin>>cpos;
		
		while(cpos!="FINISH" && cpos!="finish")
		{
			piece = convert(p,bi,r,kn,k,q,cpos,b);
			
			switch(piece)
			{
				case 'p':
					
					num = find_array(piece,p,bi,r,kn,k,q,cpos);
					p[num].setboard(b);
					p[num].showmoves();
					b->displaymoves(p[num].getpp(),p[num].getpe(),p[num].getppSize(),p[num].getpeSize());
					
					cout<<endl;
					cout<<endl;
					
					cout<<"Enter position for piece to move: ";
					cin>>fpos;
					
					b = p[num].movepiece(fpos);
					p[num].setboard(b);
					b->display();
					
					break;
					
				case 'b':
					
					num = find_array(piece,p,bi,r,kn,k,q,cpos);
					bi[num].setboard(b);
					bi[num].showmoves();
					b->displaymoves(bi[num].getpp(),bi[num].getpe(),bi[num].getppSize(),bi[num].getpeSize());
					
					cout<<endl;
					cout<<endl;
					
					cout<<"Enter position for piece to move: ";
					cin>>fpos;
					
					b = bi[num].movepiece(fpos);
					bi[num].setboard(b);
					b->display();
					
					break;
					
				case 'r':
					
					num = find_array(piece,p,bi,r,kn,k,q,cpos);
					r[num].setboard(b);
					r[num].showmoves();
					b->displaymoves(r[num].getpp(),r[num].getpe(),r[num].getppSize(),r[num].getpeSize());
					
					cout<<endl;
					cout<<endl;
					
					cout<<"Enter position for piece to move: ";
					cin>>fpos;
					
					b = r[num].movepiece(fpos);
					r[num].setboard(b);
					b->display();
					
					break;
					
				case 'n':
					
					num = find_array(piece,p,bi,r,kn,k,q,cpos);
					kn[num].setboard(b);
					kn[num].showmoves();
					b->displaymoves(kn[num].getpp(),kn[num].getpe(),kn[num].getppSize(),kn[num].getpeSize());
					
					cout<<endl;
					cout<<endl;
					
					cout<<"Enter position for piece to move: ";
					cin>>fpos;
					
					b = kn[num].movepiece(fpos);
					kn[num].setboard(b);
					b->display();
					
					break;
					
				case 'k':
					
					num = find_array(piece,p,bi,r,kn,k,q,cpos);
					k[num].setboard(b);
					k[num].showmoves();
					b->displaymoves(k[num].getpp(),k[num].getpe(),k[num].getppSize(),k[num].getpeSize());
					
					cout<<endl;
					cout<<endl;
					
					cout<<"Enter position for piece to move: ";
					cin>>fpos;
					
					b = k[num].movepiece(fpos);
					k[num].setboard(b);
					b->display();
					
					break;
					
				case 'q':
					
					num = find_array(piece,p,bi,r,kn,k,q,cpos);
					q[num].setboard(b);
					q[num].showmoves();
					b->displaymoves(q[num].getpp(),q[num].getpe(),q[num].getppSize(),q[num].getpeSize());
					
					cout<<endl;
					cout<<endl;
					
					cout<<"Enter position for piece to move: ";
					cin>>fpos;
					
					b = q[num].movepiece(fpos);
					q[num].setboard(b);
					b->display();
					
					
					break;
					
				default:
					
					cout<<"No piece available of this type!\n";
			}
			
			cout<<endl;
			cout<<endl;
			
			cout<<"Enter position for piece to be selected: ";
			cin>>cpos;
		}
	}
	
	SetConsoleTextAttribute(hconsole, 15);
}