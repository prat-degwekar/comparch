#include <iostream>
#include <set>
#include <vector>

using namespace std;

bool Xor( bool a , bool b )
{
    return ( a == b ) ? false : true ;
}

class rule
{

private:

    bool dcs[104];  //dont care state
    bool value[104];
    int part1;          //partition after max approach
    int part2;          //partition after min-max approach

public :

    rule()
    {
        dcs[104] = { false };
        value[104] = { false };
    }

    rule( string str )
    {
        char t;
        for( int i=0 ; i<104 ; i++ )
        {
            t = str[i];

            if( t == '*' )
            {
                 dcs[i] = true;
                 value[i] = false;
            }
            else
            {
                dcs[i] = false;

                if( t == '0' )
                    value[i] = false;
                else
                    value[i] = true;
            }
        }
    }

    bool isx ( int n )
    {
        return dcs[n];
    }

    bool bit( int n )
    {
        return value[n];
    }

    void setx( int n , bool val )
    {
        dcs[n] = val;
    }

    void setval( int n , bool val )
    {
        value[n] = val;
    }

    int getMaxPart()
    {
        return part1;
    }

    int getMinMaxPart()
    {
        return part2;
    }

    void setMaxPart( int p )
    {
        part1 = p;
    }

    void setMinMaxPart( int p )
    {
        part2 = p;
    }

    int distance( rule a )
    {
        int d = 0;

        for( int i=0 ; i<104 ; i++ )
        {
            if( dcs[i] || a.isx( i ) )
                continue;

            d += Xor( value[i] , a.bit(i) );
            /*if( Xor( value[i] , a.bit(i) ) )
                cout<<"d = "<<d<<" value[ "<<i<<" ] : "<<value[i]<<" , bit( "<<i<<" ) = "<<a.bit(i)<<" , dcs[ "<<i<<" ] = "<<dcs[i]<<" , isx( "<<i<<" ) = "<<a.isx(i)<<endl;
            */
        }

        return d;
    }
};

rule convert( string str )
{
    rule c1;

    for( int i = 0 ; i < 104 ; i++ )
    {
        char t = str[i];
        if( t == '*' )
        {
            c1.setx( i , true );
            c1.setval( i , false );
        }
        else
        {
            c1.setx( i , false );
            if( t == '0' )
                c1.setval( i , false );
            else
                c1.setval( i , true );
        }
    }

    return c1;

}

void minm();
void MaxPartition( vector<vector<int>> & );
void MinMaxPartition( vector<vector<int>> );

rule sets[250];

void getRules( int n )
{
    for(int i=0 ; i<n ; i++ )
    {
        string k;
        cout<<"enter rule "<<i<<" : ";
        cin>>k;
        //rule test( k );
        //sets[i] = test;
        sets[i] = convert( k );
    }
}

int main()
{
    cout << "Hello world!" << endl;

    //rule r1( "1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010****" );
    //rule r2( "1010101010101010*****01010101*10101011011010***0101010101010101010***0101010101010101010101010101010****" );
    getRules( 5 );
    cout<<"rule 1 : ";
    for(int i=0 ; i<104 ; i++ )
    {
        if(sets[0].isx(i))
            cout<<'x';
        else
            cout<<sets[0].bit( i );
    }
    cout<<"\nagainst : "<<"1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010****"<<endl;
    int k = sets[0].distance( sets[1] );
    cout<<k<<endl;

    vector < vector <int> > parts;

    //minm();
    MaxPartition(parts);

    cout<<"in main : \n\n";

    for( vector< vector <int> > :: iterator jt = parts.begin() ; jt != parts.end() ; jt++ )   //or auto i : parts
    {
        vector < int > jj = *jt;
        for( int it : *jt )
        {
            cout<<" , "<<it;
        }
        cout<<endl;
    }

    return 0;
}

void minm()
{
    vector < vector <int> > parts;

    set < set < int > > partitions;

    //getRules( 5 );

    //set all rules using other methods

    vector <int> first;
    first.push_back( 0 );

    bool flag = 0;

    parts.push_back( first );
    int ii=0;

    for( int i=1 ; i<5 ; i++ )
    {
        ii = 0;

        //for( vector< vector <int> > :: iterator jt = parts.begin() ; jt != parts.end() ; jt++ , ii++ )   //or auto i : parts
        //for( vector <int> jt : parts )
        for(int j=0 ; j<parts.size() ; j++ )
        {
            //for( vector <int> :: iterator it = jt.begin() ; it != jt.end() ; it++ )       //for( auto it : jt ) // int value
            //vector < int > jj = *jt;
            for( int it : parts[j] )
                cout<<"it = "<<it<<endl;
            for( int it : parts[j] )
            {
                int k = sets[i].distance( sets[ it ] );
                cout<<" while adding, it = "<<it<<" , for rule : "<<i<<" and k = "<<k<<" , while its size = "<<parts[j].size()<<endl;
                if( k == 0)
                {
                    flag = 1;
                    //vector <int> :: iterator jt2 = (*jt).begin();
                    //vector <int> jk = jt;
                    //jk.push_back( i );
                    //cout<<"jk has size : "<<jk.size()<<endl;
                    //jt.push_back( i );
                    //jt.insert( jt.end() , i );
                    //jt.assign( jk.begin() , jk.end());
                    parts[j].push_back( i );
                    sets[i].setMaxPart( j );
                    break;
                }
                /*else
                {
                    int kk;
                    cin>>kk;
                }*/
            }

            if( flag )
            {
                //flag = 0;
                break;
            }
            ii++;
        }
        //add a vector to parts with this

        if( !flag )
        {
            vector <int> another;
            another.push_back( i );
            parts.push_back( another );
            //parts[ii] = another;
            int kk;
            cin>>kk;
        }
        else
            flag = 0;
    }

    int index=0;

    for(int i=0 ; i<parts.size() ; i++)
    {
        if( parts[i].size() == 1 )
        {
            index = i;
            break;
        }
    }

    cout<<"index = "<<index<<endl;

    for(int i=0 ; i<parts.size() ; i++)
    {
        if( parts[i].size() == 1 )
        {
            if( i == index )
                continue;

            parts[index].insert( parts[index].end() , parts[i].begin() , parts[i].end() );
            parts[i].clear();
        }
    }

    for( vector< vector <int> > :: iterator jt = parts.begin() ; jt != parts.end() ; jt++ , ii++ )   //or auto i : parts
    {
        vector < int > jj = *jt;
        for( int it : *jt )
        {
            cout<<" , "<<it;
        }
        cout<<endl;
    }
}

void MaxPartition( vector < vector <int> > &parts )
{
    vector <int> first;
    first.push_back( 0 );

    bool flag = 0;

    parts.push_back( first );
    int ii=0;

    for( int i=1 ; i<5 ; i++ )
    {
        ii = 0;

        for(int j=0 ; j<parts.size() ; j++ )
        {
            for( int it : parts[j] )
                cout<<"it = "<<it<<endl;
            for( int it : parts[j] )
            {
                int k = sets[i].distance( sets[ it ] );
                cout<<" while adding, it = "<<it<<" , for rule : "<<i<<" and k = "<<k<<" , while its size = "<<parts[j].size()<<endl;
                if( k == 0)
                {
                    flag = 1;
                    parts[j].push_back( i );
                    sets[i].setMaxPart( j );
                    break;
                }
            }

            if( flag )
            {
                //flag = 0;
                break;
            }
            ii++;
        }
        //add a vector to parts with this

        if( !flag )
        {
            vector <int> another;
            another.push_back( i );
            parts.push_back( another );
        }
        else
            flag = 0;
    }

    int index=0;

    for(int i=0 ; i<parts.size() ; i++)
    {
        if( parts[i].size() == 1 )
        {
            index = i;
            break;
        }
    }

    cout<<"index = "<<index<<endl;

    for(int i=0 ; i<parts.size() ; i++)
    {
        if( parts[i].size() == 1 )
        {
            if( i == index )
                continue;

            parts[index].insert( parts[index].end() , parts[i].begin() , parts[i].end() );
            parts[i].clear();
        }
    }

    for( vector< vector <int> > :: iterator jt = parts.begin() ; jt != parts.end() ; jt++ , ii++ )   //or auto i : parts
    {
        vector < int > jj = *jt;
        for( int it : *jt )
        {
            cout<<" , "<<it;
        }
        cout<<endl;
    }
}

void MinMaxPartition( vector< vector< int > > parts )
{
    for( int i=0 ; i<parts.size() ; i++ )
    {
        int kk=0;
        vector< vector< int > > newvect;

        ///plan -> split every max vector into min vector of vectors, then remove the max vector and add new vector of vectors

        for( int it : parts[i] )
        {
            if(kk == 0)
            {
                vector<int> first;
                first.push_back(it);
                kk++;
                newvect.push_back(first);
                continue;
            }   ///create first vector of vectors

            bool flg = 0;

            for( int j=0 ; j<newvect.size() ; j++ )
            {
                flg = 0;
                for( int ii : newvect[j] )  ///for every min partition
                {
                    int k = sets[it].distance( sets[ii] );
                    ///if distance != 0 continue, else set flag and make new partition
                    if( k == 0 )
                    {
                        flg = 1;
                        break;
                    }
                }
                if(flg == 0)
                {
                    newvect[j].push_back(it);
                    ///set min partition as j for the rule
                    break;
                }
            }

            ///if flg is 1, then create new partition, else it has already been added

            if(flg)
            {
                vector<int> first;
                first.push_back(it);
                newvect.push_back(first);
            }

        }
        ///print the vector of vectors

        cout<<"newvect here is : "<<endl;

        for( vector< vector <int> > :: iterator jt = newvect.begin() ; jt != newvect.end() ; jt++ )   //or auto i : parts
        {
            vector < int > jj = *jt;
            for( int it : *jt )
            {
                cout<<" , "<<it;
            }
            cout<<endl;
        }

        cout<<"newvwct printing ends"<<endl;

        ///remove old vector and insert new vector of vectors

        parts[i].clear();
        parts.insert( parts.end() , newvect.begin() , newvect.end() );

        ///done
    }

    ///print parts vector that now represents full minmax partition

    for( vector< vector <int> > :: iterator jt = parts.begin() ; jt != parts.end() ; jt++ , ii++ )   //or auto i : parts
    {
        vector < int > jj = *jt;
        for( int it : *jt )
        {
            cout<<" , "<<it;
        }
        cout<<endl;
    }

}
