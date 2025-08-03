/*
	CS F222 Project.
	By:- 2022A7PS0076G (Yash Pratap Singh)
		 2022A7PS1273G (Vansh Agarwal)
		 2022A7PS1237G (Satvik Jain)
*/
#include<bits/stdc++.h>
using namespace std;
int main()
{		
	int x1,x2,x3; // x1 = number of prof in x1 category , x2 = no. of prof in x2 category, x3= no. of prof in x3 category
	ifstream inputFile("input.txt");
	 if (!inputFile.is_open()) {
        cerr << "Error opening input file" << endl;
        return 1;
    }
	ofstream outputFile("output.txt");
	if (!outputFile.is_open()) {
        cerr << "Error opening output file" << endl;
        return 1;
    }

	int numTestCases;
    inputFile >> numTestCases;

    for (int testCase = 1; testCase <= numTestCases; ++testCase)
	{

	
	
	inputFile>>x1>>x2>>x3; // input : taking in number of professors under each category 

	vector<vector<string>> v1,v2,v3; // v1 is a vector of vector of strings : each index in v1/v2/v3 is a vector which stores professors name followed by courses preferred by the prof
		
			vector<pair<string,bool>> p1,p2,p3; //p1 is a vector of professors of x1 category . each index has a pair {Prof name, Boolean value}, boolean value is true is prof has been alloted a course.
			/*

			Output files:
				vector<string> prof_and_courses;

			*/
			vector<pair<string,bool>> half_p3;  // vector of pair to denote whether a prof of X3 category has been allotted a course with 0.5 credit in association with another prof of x1 category, as seen later in the code.

vector<vector<string>> prof_and_courses; // each index in this vector is a vector which stores the name/code of professor followed by courses allotted to that prof
int maxnum=0; // maxnum is the maximum number of courses preferred by any prof
		for(int i=0;i<x1;i++)
		{
			vector<string> tv; // temporary vector to push values in v1 
			
			string p; // name/code of i'th prof
			inputFile>>p;
			tv.push_back(p);
			p1.push_back({p,false});
			
			int nocp; // number of courses preferred by i'th professor 
			inputFile>>nocp;
			if(nocp>maxnum)
			{
				maxnum=nocp;
			}
			for(int j=0;j<nocp;j++)
			{
				
				string a; // taking preference input by i'th prof
				inputFile>>a;
				tv.push_back(a);
			}
		
			v1.push_back(tv); // input for i'th professor completed
		}
		for(int i=0;i<x2;i++)
		{
			vector<string> tv;
			
			string p;
			inputFile>>p;
			tv.push_back(p);
			p2.push_back({p,false});
			
			
			int nocp;
			inputFile>>nocp;
			if(nocp>maxnum)
			{
				maxnum=nocp;
			}
			for(int j=0;j<nocp;j++)
			{
				
				string a;
				inputFile>>a;
				tv.push_back(a);
			}
			v2.push_back(tv);
		}
		for(int i=0;i<x3;i++)
		{
			vector<string> tv;
			
			string p;
			inputFile>>p;
			tv.push_back(p);
			p3.push_back({p,false});
			half_p3.push_back({p,false});
			
			
			int nocp;
			inputFile>>nocp;
			if(nocp>maxnum)
			{
				maxnum=nocp;
			}
			for(int j=0;j<nocp;j++)
			{
				
				string a;
				inputFile>>a;
				tv.push_back(a);
			}
		
			v3.push_back(tv);
		}
      // Now we will equalize the sizes of vectors of all professors by appending "null" course at end of each vector.
	  // This is done to facilitate our allottment procedure, as seen later in the code.
			for(int i=0;i<x1;i++)
			{
				while(v1[i].size()<=maxnum+1)
				{
					// vector<string> tv;
					// tv.push_back("null");
					v1[i].push_back("null");
				}
			}
			for(int i=0;i<x2;i++)
			{
				while(v2[i].size()<=maxnum+1)
				{
					// vector<string> tv;
					// tv.push_back("null");
					v2[i].push_back("null");
				}
			}
			for(int i=0;i<x3;i++)
			{
				while(v3[i].size()<=maxnum+1)
				{
					// vector<string> tv;
					// tv.push_back("null");
					v3[i].push_back("null");
				}
			}
		//cout<<"Enter number of First Degree CDCs available for a professor"<<endl;
				int num_of_fcdc;
				inputFile>>num_of_fcdc; //enter the number of  FD CDCs  to be considered for allottment.
			map<string,bool> mfcdc; // hashmap for allotment of courses, value for the 'key' course will become true if it is given to a professor.
		/* 
			
		*/
			//cout<<"Enter number of First Degree ELEs available for a professor"<<endl;
			int num_of_fdel;
			inputFile>>num_of_fdel;

			map<string,bool> mfdel;
			//cout<<"Enter number of HD CDCs available for a professor"<<endl;
			int num_of_hcdc;
			map<string,bool> mhcdc;
			inputFile>>num_of_hcdc;
			//cout<<"Enter number of HD ELEs available for a professor"<<endl;
			int num_of_hdel;
			map<string,bool> mhdel;
			inputFile>>num_of_hdel;

			
			for(int i=0;i<num_of_fcdc;i++)
			{
				
				string c;
				inputFile>>c; //Taking input for i'th FD CDC
				//mfcdc[c]=false;
				mfcdc.insert({c,false});
			}


			for(int i=0;i<num_of_fdel;i++)
			{
				//cout<<"Enter ELE for First degree"<<endl;
				string c;
				inputFile>>c;
				mfdel[c]=false;
			}

			for(int i=0;i<num_of_hcdc;i++)
			{
				//cout<<"Enter CDC for HD"<<endl;
				string c;
				inputFile>>c;
				mhcdc[c]=false;
			}
			for(int i=0;i<num_of_hdel;i++)
			{
				//cout<<"Enter ELE for HD"<<endl;
				string c;
				inputFile>>c;
				mhdel[c]=false;
			}




			

				/* 


					We will begin course allotment in the following manner:
						first we allot FD CDC , then we allot FD Ele, then HD CDC and finally HD Ele

				*/

			//Allotting FDCDC.
			int column=1; // In every prof's preference list the FD CDC are in COlumn 1, 2 , 3 ,4
						//Column value will store the index value , the course at which will be checked when iterating through different professors.
			for(auto it = mfcdc.begin(); it!=mfcdc.end();++it)
			{
					int flag=0; //normal flag variable
					string course=(*it).first;  //  checking a particular FD CDC denoted by the iterator 'it'.
					column=1;
					while(column<=maxnum) 
					{
					if(mfcdc[course]==false) //this means the course has not been allotted to any one.
					{  


						//we will first check  preferences of x2 catergory
						for(int i=0;i<x2;i++)
						{
							//If for the i'th professor the preference number 'column' is the course which we are trying to allot, and the prof has not been given any course and the course also has not been allotted to any prof completely, then we mark the course as allotted and mark the boolean value for prof as treu.
								if(v2[i][column]==course && p2[i].second==false && mfcdc[course]==false)
								{
									mfcdc[course]=true;
									p2[i].second=true;
									
									flag=1; //flag marked 1 which means that no further iterations will be made to allot the concerned course as it has been now allotted
									vector<string> ttv; // temporary vector to store the prof's name and course allotted to the prof.
									ttv.push_back(v2[i][0]);
									ttv.push_back(course);
									prof_and_courses.push_back(ttv);

									break;
								}
						}
							if(flag==0) // if the course could not be allotted to any prof in category x2 with preference number 'column' we move to x3 category and do the same.
							{
								for(int i=0;i<x3;i++)
								{
								if(v3[i][column]==course && p3[i].second==false && mfcdc[course]==false)
								{
									mfcdc[course]=true;
									p3[i].second=true;
									flag=1;
									vector<string> ttv;
									ttv.push_back(v3[i][0]);
									ttv.push_back(course);
									prof_and_courses.push_back(ttv);
									break;
								}
								}
							}
							if(flag==0) // if x3 prof with preference number 'column' also could not get the course we move to x1 in a special fashion
							{	
								int counter=0; //counts the no. of prof with matching course at preference no. 'column'.
								int fi=0; //stores the index of first professor with a matching course at a matching preference number.
								int fc=0; 
								int found_course_twice=0; // checks if the course is preferred by 2 distinct profs in category x1, with same preference number 'column'
								for(int i=0;i<x1;i++)
								{			
								if(v1[i][column]==course && p1[i].second==false && mfcdc[course]==false)
								{
									if(counter==0) //we found our first prof in category x1 
									{
										counter++;
										fc=column;
										fi=i; // index of first professor 
									}
									else
									{
										if(counter==1)
										{                     //copy to remaining.
											counter++; //we have found second prof,now we will allot 0.5 course to both the professors by  making a temp vector. 
											found_course_twice=1;
											mfcdc[course]=true;
										p1[fi].second=true;
										p1[i].second=true;
										flag=1;
										vector<string> ttv;
										vector<string> t2;
									ttv.push_back(v1[i][0]);
									ttv.push_back(course);
									t2.push_back(v1[fi][0]);
									t2.push_back(course);
									prof_and_courses.push_back(t2);
									prof_and_courses.push_back(ttv);
										break;
										}
									}

								}
							}

								if(found_course_twice==0 && counter==1)
								{ //if we could find only 1 prof, we now check all preferences of all professors of x3 category to allot 0.5 to the first prof in x1 category and 0.5 to a prof in x3 category
										for(int j=1;j<=maxnum;j++)
										{
											for(int i=0;i<x3;i++)
											{
												if(v3[i][j]==course && half_p3[i].second==false)
												{
													mfcdc[course]=true;
													p1[fi].second=true;
													half_p3[i].second=true;
													vector<string> t;
													t.push_back(v3[i][0]);
													t.push_back(course);
													vector<string> t2;
													t2.push_back(v1[fi][0]);
													t2.push_back(course);
													prof_and_courses.push_back(t);
													prof_and_courses.push_back(t2);
													flag=1;
													break;
												}
												if(flag==1)
													break;
											}
											if(flag==1)
												break;
										}
								}
								if(mfcdc[course]==false && counter==1)
								{ //if we could not find a prof in x3 categorry we again turn to x1 category but this time we do not restrict ourselves to same preference 'column' , rather we iterate through all columns of all profesor who were not allotted any course so far
									// while(fc<=maxnum)
									// {

									// 	fc++;
									// }
									int flag2=0;
									for(int i=0;i<x1;i++)
									{
										if(i==fi || p1[i].second==true)
										{
											continue;
										}
										else
										{
											for(int j=1;j<=maxnum;j++)
											{
												if(v1[i][j]==course && p1[i].second==false)
												{
													flag2=1;
													mfcdc[course]=true;
													p1[fi].second=true;
													p1[i].second=true; //if found  , course is allotted
													break;
												}
												if(flag2==1)
												{
													break;
												}
											}
											if(flag2==1)
											{
												break;
											}
										}
										if(flag2==1)
										{
											break;
										}
									}
								}
							}
					}
					column++;
					if(column>maxnum)
					break;
					if(mfcdc[course]==true)
						break;
				}
			}	


			
		

				/*
					
						ALLOTMENT OF FD CDCs Complete as per the considered ALGORITHM.
		
				*/



				// Beginning Allotment of FD ELE

				column=1; // In every prof's preference list the FD Ele are in COlumn 5,6
			for(auto it = mfdel.begin(); it!=mfdel.end();++it)
			{
					int flag=0;
					string course=(*it).first;
					column=1;
					 while(column<=maxnum)
				  {
					if(mfdel[course]==false)
					{  //5<=column<=6


						//we will first check first preferences of x2 catergory
						for(int i=0;i<x2;i++)
						{
								if(v2[i][column]==course && p2[i].second==false && mfdel[course]==false)
								{
									mfdel[course]=true;
									p2[i].second=true;
									flag=1;
									vector<string> ttv;
									ttv.push_back(v2[i][0]);
									ttv.push_back(course);
									prof_and_courses.push_back(ttv);

									break;
								}
						}
							if(flag==0)
							{
								for(int i=0;i<x3;i++)
								{
								if(v3[i][column]==course && p3[i].second==false && mfdel[course]==false)
								{
									mfdel[course]=true;
									p3[i].second=true;
									flag=1;
									vector<string> ttv;
									ttv.push_back(v3[i][0]);
									ttv.push_back(course);
									prof_and_courses.push_back(ttv);
									break;
								}
								}
							}
							if(flag==0)
							{	
								int counter=0;
								int fi=0;
								int found_course_twice=0;
								for(int i=0;i<x1;i++)
								{			
								if(v1[i][column]==course && p1[i].second==false && mfdel[course]==false)
								{
									if(counter==0)
									{
										counter++;
										fi=i;
									}
									else
									{
										if(counter==1)
										{
											mfdel[course]=true;
										p1[fi].second=true;
										p1[i].second=true;
										flag=1;
										vector<string> ttv;
										vector<string> t2;
									ttv.push_back(v1[i][0]);
									ttv.push_back(course);
									t2.push_back(v1[fi][0]);
									t2.push_back(course);
									prof_and_courses.push_back(t2);
									prof_and_courses.push_back(ttv);
										break;
										}
									}
									
								 }
								}
								if(found_course_twice==0 && counter==1)
								{
										for(int j=1;j<=maxnum;j++)
										{
											for(int i=0;i<x3;i++)
											{
												if(v3[i][j]==course && half_p3[i].second==false)
												{
													mfdel[course]=true;
													p1[fi].second=true;
													half_p3[i].second=true;
													vector<string> t;
													t.push_back(v3[i][0]);
													t.push_back(course);
													vector<string> t2;
													t2.push_back(v1[fi][0]);
													t2.push_back(course);
													prof_and_courses.push_back(t);
													prof_and_courses.push_back(t2);
													flag=1;
													break;
												}
												if(flag==1)
													break;
											}
											if(flag==1)
												break;
										}
								}
								if(mfdel[course]==false && counter==1)
								{
									// while(fc<=maxnum)
									// {

									// 	fc++;
									// }
									int flag2=0;
									for(int i=0;i<x1;i++)
									{
										if(i==fi || p1[i].second==true)
										{
											continue;
										}
										else
										{
											for(int j=1;j<=maxnum;j++)
											{
												if(v1[i][j]==course && p1[i].second==false)
												{
													flag2=1;
													mfdel[course]=true;
													p1[fi].second=true;
													p1[i].second=true;
													break;
												}
												if(flag2==1)
												{
													break;
												}
											}
											if(flag2==1)
											{
												break;
											}
										}
										if(flag2==1)
										{
											break;
										}
									}
								}
							}
					}
					column++;
					if(column>maxnum)
						break;
					if(mfdel[course]==true)
						break;
				}
			}	


				

				/* 

					Allotment of FD ELE complete.
	
				*/

 // Beginning Allotment of HD CDC

				column=1; // In every prof's preference list the HD CDC are in COlumn 9,10
			for(auto it = mhcdc.begin(); it!=mhcdc.end();++it)
			{
					int flag=0;
					string course=(*it).first;
					column=1;
					 while(column<=maxnum)
				  {
					if(mhcdc[course]==false)
					{  //9<=column<=10


						//we will first check first preferences of x2 catergory
						for(int i=0;i<x2;i++)
						{
								if(v2[i][column]==course && p2[i].second==false && mhcdc[course]==false)
								{
									mhcdc[course]=true;
									p2[i].second=true;
									flag=1;
									vector<string> ttv;
									ttv.push_back(v2[i][0]);
									ttv.push_back(course);
									prof_and_courses.push_back(ttv);

									break;
								}
						}
							if(flag==0)
							{
								for(int i=0;i<x3;i++)
								{
								if(v3[i][column]==course && p3[i].second==false && mhcdc[course]==false)
								{
									mhcdc[course]=true;
									p3[i].second=true;
									flag=1;
									vector<string> ttv;
									ttv.push_back(v3[i][0]);
									ttv.push_back(course);
									prof_and_courses.push_back(ttv);
									break;
								}
								}
							}
							if(flag==0)
							{	
								int counter=0;
								int found_course_twice=0;
								int fi=0;
								for(int i=0;i<x1;i++)
								{			
								if(v1[i][column]==course && p1[i].second==false && mhcdc[course]==false)
								{
									if(counter==0)
									{
										counter++;
										fi=i;
									}
									else
									{
										if(counter==1)
										{
											found_course_twice=1;
											mhcdc[course]=true;
										p1[fi].second=true;
										p1[i].second=true;
										flag=1;
										vector<string> ttv;
										vector<string> t2;
									ttv.push_back(v1[i][0]);
									ttv.push_back(course);
									t2.push_back(v1[fi][0]);
									t2.push_back(course);
									prof_and_courses.push_back(t2);
									prof_and_courses.push_back(ttv);
										break;
										}
									}
									
								}
								}
								if(found_course_twice==0 && counter==1)
								{
										for(int j=1;j<=maxnum;j++)
										{
											for(int i=0;i<x3;i++)
											{
												if(v3[i][j]==course && half_p3[i].second==false)
												{
													mhcdc[course]=true;
													p1[fi].second=true;
													half_p3[i].second=true;
													vector<string> t;
													t.push_back(v3[i][0]);
													t.push_back(course);
													vector<string> t2;
													t2.push_back(v1[fi][0]);
													t2.push_back(course);
													prof_and_courses.push_back(t);
													prof_and_courses.push_back(t2);
													flag=1;
													break;
												}
												if(flag==1)
													break;
											}
											if(flag==1)
												break;
										}
								}
								if(mhcdc[course]==false && counter==1)
								{
									// while(fc<=maxnum)
									// {

									// 	fc++;
									// }
									int flag2=0;
									for(int i=0;i<x1;i++)
									{
										if(i==fi || p1[i].second==true)
										{
											continue;
										}
										else
										{
											for(int j=1;j<=maxnum;j++)
											{
												if(v1[i][j]==course && p1[i].second==false)
												{
													flag2=1;
													mhcdc[course]=true;
													p1[fi].second=true;
													p1[i].second=true;
													break;
												}
												if(flag2==1)
												{
													break;
												}
											}
											if(flag2==1)
											{
												break;
											}
										}
										if(flag2==1)
										{
											break;
										}
									}
								}
							}
					}
					column++;
					if(column>maxnum)
						break;
					if(mhcdc[course]==true)
						break;
				}
			}	



				/*

					Allotment of HD CDC Complete

				*/


				// Beginning Allotment of HD ELE

				column=1; // In every prof's preference list the HD Ele are in COlumn 11,12
			for(auto it = mhdel.begin(); it!=mhdel.end();++it)
			{
					int flag=0;
					string course=(*it).first;
					column=1;
					 while(column<=maxnum)
				  {
					if(mhdel[course]==false)
					{  //11<=column<=12


						//we will first check first preferences of x2 catergory
						for(int i=0;i<x2;i++)
						{
								if(v2[i][column]==course && p2[i].second==false && mhdel[course]==false)
								{
									mhdel[course]=true;
									p2[i].second=true;
									flag=1;
									vector<string> ttv;
									ttv.push_back(v2[i][0]);
									ttv.push_back(course);
									prof_and_courses.push_back(ttv);

									break;
								}
						}
							if(flag==0)
							{
								for(int i=0;i<x3;i++)
								{
								if(v3[i][column]==course && p3[i].second==false && mhdel[course]==false)
								{
									mhdel[course]=true;
									p3[i].second=true;
									flag=1;
									vector<string> ttv;
									ttv.push_back(v3[i][0]);
									ttv.push_back(course);
									prof_and_courses.push_back(ttv);
									break;
								}
								}
							}
							if(flag==0)
							{	
								int counter=0;
								int fi=0;
								int found_course_twice=0;
								for(int i=0;i<x1;i++)
								{			
								if(v1[i][column]==course && p1[i].second==false && mhdel[course]==false)
								{
									if(counter==0)
									{
										counter++;
										fi=i;
									}
									else
									{
										if(counter==1)
										{
											found_course_twice=1;
												mhdel[course]=true;
										p1[fi].second=true;
										p1[i].second=true;
										flag=1;
										vector<string> ttv;
										vector<string> t2;
									ttv.push_back(v1[i][0]);
									ttv.push_back(course);
									t2.push_back(v1[fi][0]);
									t2.push_back(course);
									prof_and_courses.push_back(t2);
									prof_and_courses.push_back(ttv);
										break;
										}
									}
								
								}
							}
							if(found_course_twice==0 && counter==1)
								{
										for(int j=1;j<=maxnum;j++)
										{
											for(int i=0;i<x3;i++)
											{
												if(v3[i][j]==course && half_p3[i].second==false)
												{
													mhdel[course]=true;
													p1[fi].second=true;
													half_p3[i].second=true;
													vector<string> t;
													t.push_back(v3[i][0]);
													t.push_back(course);
													vector<string> t2;
													t2.push_back(v1[fi][0]);
													t2.push_back(course);
													prof_and_courses.push_back(t);
													prof_and_courses.push_back(t2);
													flag=1;
													break;
												}
												if(flag==1)
													break;
											}
											if(flag==1)
												break;
										}
								}
								if(mhdel[course]==false && counter==1)
								{
									// while(fc<=maxnum)
									// {

									// 	fc++;
									// }
									int flag2=0;
									for(int i=0;i<x1;i++)
									{
										if(i==fi || p1[i].second==true)
										{
											continue;
										}
										else
										{
											for(int j=1;j<=maxnum;j++)
											{
												if(v1[i][j]==course && p1[i].second==false)
												{
													flag2=1;
													mhdel[course]=true;
													p1[fi].second=true;
													p1[i].second=true;
													break;
												}
												if(flag2==1)
												{
													break;
												}
											}
											if(flag2==1)
											{
												break;
											}
										}
										if(flag2==1)
										{
											break;
										}
									}
								}
							}
					}
					column++;
					if(column>maxnum)
						break;
					if(mhdel[course]==true)
						break;
				}
			}	


			




				/* 

					All ALLOTMENTS COMPLETE....
					Initiating Output sequence.
	
				*/
			outputFile<<"testcase number:"<<testCase<<endl;
				
				for(auto it=mfcdc.begin();it!=mfcdc.end();++it)
				{
					if(it==mfcdc.begin())
					{
						outputFile<<"Course code vs Allotment map for FD CDC :"<<endl;
					}
					//outputFile<<mfcdc.size()<<endl;
					outputFile<<(*it).first<<"	"<<(*it).second<<endl;
				}
				
				for(auto it=mfdel.begin();it!=mfdel.end();++it)
				{
					if(it==mfdel.begin())
					{
						outputFile<<"Course code vs Allotment map for FD ELE :"<<endl;
					}
				outputFile<<(*it).first<<"	"<<(*it).second<<endl;
				}
				
				for(auto it=mhcdc.begin();it!=mhcdc.end();++it)
				{
					if(it==mhcdc.begin())
					{
						outputFile<<"Course code vs Allotment map for HD CDC :"<<endl;
					}
					outputFile<<(*it).first<<"	"<<(*it).second<<endl;
				}
				
				for(auto it=mhdel.begin();it!=mhdel.end();++it)
				{
					if(it==mhdel.begin())
					{
						outputFile<<"Course code vs Allotment map for HD ELE :"<<endl;
					}
					outputFile<<(*it).first<<"	"<<(*it).second<<endl;
				}

				
				for(int i=0;i<x1;i++)
				{
					if(i==0)
					{
						outputFile<<"		"<<"Professors of category x1 and Course Allotment"<<endl;
					}
					outputFile<<p1[i].first<<"	"<<p1[i].second<<endl;
				}
				
				for(int i=0;i<x2;i++)
				{
					if(i==0)
					{
						outputFile<<"		"<<"Professors of category x2 and Course Allotment"<<endl;
					}
					outputFile<<p2[i].first<<"	"<<p2[i].second<<endl;
				}
				
				for(int i=0;i<x3;i++)
				{
					if(i==0)
					{
						outputFile<<"		"<<"Professors of category x3 and Course Allotment"<<endl;
					}
					outputFile<<p3[i].first<<"	"<<p3[i].second<<endl;
				}

				outputFile<<"		"<<"Professors AND Courses"<<endl;
				for(int i=0;i<prof_and_courses.size();i++)
				{
					for(int j=0;j<prof_and_courses[i].size();j++)
					{
						outputFile<<prof_and_courses[i][j]<<"	";
					}
					outputFile<<endl;
				}
				mfcdc.clear();
				mhcdc.clear();
				mfdel.clear();
				mhdel.clear();
				}
				

	return 0;
}


