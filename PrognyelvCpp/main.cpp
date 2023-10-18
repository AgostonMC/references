// Az array_util osztály template
// megkönnyíti a hagyományos C-s tömbök kezelését, így a template paraméter,
// hogy milyen típusú elemeket tárol a tömb. Az array_util létrehozáskor
// megkap egy tömböt, az equals metódussal vagy az operator==-vel megvizsgáljuk,
// hogy a két array_util mögötti tömb megegyezik-e, azaz ugyanakkorák és 
// ugyanazokon az indexeken ugyanazok az értékek vannak. A copy-val a tömbbe
// másoljuk a paraméterként kapott array_util mögötti tömbelemeket. A másolás
// a két tömb méretének minimumát érinti, így nem indexelünk ki semelyik tömbből.
// Ugyanezt éri el az értékadás operátor. A permutation azt vizsgálja, hogy két tömbben
// ugyanazok az elemek szerepelnek-e nem feltétlenül ugyanabban a sorrendben.
// A megoldás működjön együtt std::vectorral is.

#include <iostream>
#include "arutil.h"
#include <vector>
#include <string>
#include "arutil.h"
#include <algorithm>

const int max = 1000;

bool check()
{
  int a[] = { 7, 1, 9, 2 };
  int b[] = { 3, 8, 1 };
  int c[] = { 5, 3, 1 };
  int d[] = { 9, 1, 3 };

  array_util<int> au( a, sizeof( a ) / sizeof( a[ 0 ] ) );
  array_util<int> bu( b, sizeof( b ) / sizeof( b[ 0 ] ) );
  const array_util<int> cu( c, sizeof( c ) / sizeof( c[ 0 ] ) );
  array_util<int> du( d, sizeof( d ) / sizeof( d[ 0 ] ) );

  du.copy( au );
  bu.copy( cu );

  std::string e[] = { "Hello", "World" };
  std::string f[] = { "Hello", "World" };
  std::string g[] = { "Goodbye", "Cruel", "World" };
  array_util<std::string> eu( e, sizeof( e ) / sizeof( e[ 0 ] ) );
  array_util<std::string> fu( f, sizeof( f ) / sizeof( f[ 0 ] ) );
  array_util<std::string> gu( g, sizeof( g ) / sizeof( g[ 0 ] ) );

  gu.copy( eu );

  int m[ max ] = {};
  array_util<int> mu( m, sizeof( m ) / sizeof( m[ 0 ] ) );

  if ( !eu.equals( fu ) || "World" != g[ 2 ] ||
       gu.equals( fu ) || "Hello" != g[ 0 ] ||
       !bu.equals( cu ) || 3 != b[ 1 ] || 9 != d[ 2 ] ||
       cu.equals( du ) ||  mu.equals( au ) )
  {
    return false;
  }

  g[ 1 ].clear();
  mu = au;
  gu = eu;
  std::swap( f[ 0 ], f[ 1 ] );
  std::swap( c[ 0 ], c[ 2 ] );

  if ( !fu.permutation( eu ) || fu.equals( eu ) ||
       "World" != g[ 1 ] || !cu.permutation( bu ) ||
       cu.equals( bu ) || mu.equals( au ) ||
       mu.permutation( au ) || bu.permutation( du ) )
  {
    return false;
  }

  std::vector<int> v( m, m + max );
  array_util<int> vu( v );
  std::vector<std::string> s;
  s.push_back( "I" );
  s.push_back( "<3" );
  s.push_back( "C++" );
  const array_util<std::string> su( s );
  gu = su;

  std::vector<int> vm( max );
  array_util<int> vmu( vm );
  vmu = au;

  return ( mu == vu && su == gu && "<3" == g[ 1 ] &&
         !( fu == eu ) && 7 == vm[ 0 ] && 1 == vm[ 1 ] );
}

int main()
{
  std::cout
    << "Your solution is "
    << (check() ? "" : "not ")
    << "ready for submission."
    << std::endl;
}