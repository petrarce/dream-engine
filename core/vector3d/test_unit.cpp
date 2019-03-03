#define BOOST_TEST_MODULE ATOMATON_TEST
#include <cmath>
#include <vector3d_cartesian.hpp>
#include <boost/test/included/unit_test.hpp>

using namespace std;
using namespace dream_vector3d;

BOOST_AUTO_TEST_CASE(vector3d_cartesian_check)
{
	vector3d_cartesian v1(1,1,1);
	const vector3d_cartesian v2(1,1,1);
	const vector3d_cartesian v3(3,3,3);
	const vector3d_cartesian v4(2,2,2);

	BOOST_REQUIRE((v1==v2) == true);

	BOOST_REQUIRE((v1==v3) == false);

	double magn = v1.get_magnitude();
	BOOST_REQUIRE_MESSAGE(fabs(magn - 1.7320) < 0.001, "magn = " + to_string(magn)); //set accuracy not less dthan 0.001

	v1 *= 3;
	BOOST_REQUIRE((v1==v3) == true);

	v1 -= v4;
	BOOST_REQUIRE((v1==v2) == true);

	v1 += v2;
	BOOST_REQUIRE((v1==v4) == true);

	v1 = v2;
	v1 = v1 * 3;
	BOOST_REQUIRE((v1==v3) == true);

	v1 = v2;
	v1 = 3 * v1;
	BOOST_REQUIRE((v1==v3) == true);

	v1 =  v1 - v4;
	BOOST_REQUIRE((v1==v2) == true);

	v1 = v1 + v2;
	BOOST_REQUIRE((v1==v4) == true);

	const vector3d_cartesian i(1,0,0);
	const vector3d_cartesian j(0,1,0);
	const vector3d_cartesian k(0,0,1);
	vector3d_cartesian temp;

	temp = i^j;
	BOOST_REQUIRE((temp==k) == true);

	temp = j^k;
	BOOST_REQUIRE((temp==i) == true);

	temp = k^i;
	BOOST_REQUIRE((temp==j) == true);

	BOOST_REQUIRE(fabs(v3*v3 - pow(v3.get_magnitude(),2)) < 0.0001);

	double aangle_cos = get_angle(i, j);
	BOOST_REQUIRE(fabs(aangle_cos) < 0.0001);

}