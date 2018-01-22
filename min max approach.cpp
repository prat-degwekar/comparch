#include <iostream>

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
        if( t == 'x' )
        {
            c1.setx( i , true );
        }
        else
        {
            if( t == '0' )
                c1.setval( i , false );
            else
                c1.setval( i , true );
        }
    }

    return c1;

}

int main()
{
    cout << "Hello world!" << endl;

    rule r1( "1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010****" );
    rule r2( "1010101010101010*****01010101*10101011011010***0101010101010101010***0101010101010101010101010101010****" );
    /*cout<<"rule r1 : ";
    for(int i=0 ; i<104 ; i++ )
    {
        if(r1.isx(i))
            cout<<'x';
        else
            cout<<r1.bit( i );
    }
    cout<<"\nagainst : "<<"1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010****"<<endl;
    int k = r2.distance( r1 );
    cout<<k<<endl;*/
    return 0;
}
